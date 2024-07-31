/**
 *    __  __ ____ _  __ ____ ___ __  __
 * 	  \ \/ // __// |/ //  _// _ |\ \/ /
 *     \  // _/ /    /_/ / / __ | \  /
 *     /_//___//_/|_//___//_/ |_| /_/
 *
 *         Yeniay System Firmware
 *
 *       Copyright (C) 2024 Yeniay
 *
 * This  program  is  free software:   you
 * can  redistribute it  and/or  modify it
 * under  the  terms of  the  GNU  General
 * Public  License as  published  by   the
 * Free Software Foundation, in version 3.
 *
 * You  should  have  received  a  copy of
 * the  GNU  General  Public License along
 * with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "FreeRTOS.h"
#include "semphr.h"
#include "usbd_cdc_if.h"
#include "usb.h"

#define USB_TIMEOUT pdMS_TO_TICKS(1000)

static SemaphoreHandle_t usbMutex;
static SemaphoreHandle_t txComplete;
static SemaphoreHandle_t rxComplete;

static uint8_t* pBuffer;
static uint16_t length;

void usbInit(void){
	usbMutex = xSemaphoreCreateMutex();
	txComplete = xSemaphoreCreateBinary();
	rxComplete = xSemaphoreCreateBinary();
}

int8_t usbReceive(uint8_t* pRxData, uint16_t len){
	xSemaphoreTake(rxComplete, portMAX_DELAY);
	if(len > length) len = length;
	memcpy(pRxData, pBuffer, len);
	pBuffer += len;
	length  -= len;
	return HAL_OK;
}

int8_t usbTransmit(uint8_t* pTxData, uint16_t len){
	if (xSemaphoreTake(usbMutex, USB_TIMEOUT) != pdTRUE) return HAL_ERROR;
	CDC_Transmit_FS(pTxData, len);
	xSemaphoreTake(txComplete, USB_TIMEOUT);
	xSemaphoreGive(usbMutex);
	return 	HAL_OK;
}

uint16_t usbAvailableData(void){
	return length;
}

void usbPrint(char* format, ...){

    va_list args;
    char temp[128] = {0};
    uint8_t length = 0;

    va_start(args, format);
    vsprintf(temp,format,args);
    va_end(args);

    for(uint8_t i = 0; i < 128; i++){
    	if(temp[i] == 0x00){
    		length = i;
    		break;
    	}
    }

    usbTransmit((uint8_t*)temp, length);
}

void usbWaitDataReady(void){
	xSemaphoreTake(rxComplete, portMAX_DELAY);
	xSemaphoreGive(rxComplete);
}

void CDC_TransmitCpltCallback(void){
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	xSemaphoreGiveFromISR(txComplete, &xHigherPriorityTaskWoken);
	if(xHigherPriorityTaskWoken){
		portYIELD();
	}
}

void CDC_ReceiveCpltCallback(uint8_t* Buf, uint32_t* Len){
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	pBuffer = Buf;
	length  = (uint16_t)(*Len);
	xSemaphoreGiveFromISR(rxComplete, &xHigherPriorityTaskWoken);
	if(xHigherPriorityTaskWoken){
		portYIELD();
	}
}
