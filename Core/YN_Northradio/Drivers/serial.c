/**
 *    __  __ ____ _  __ ____ ___ __  __
 *    \ \/ // __// |/ //  _// _ |\ \/ /
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

#include <stdint.h>
#include <stdbool.h>
#include <system.h>
#include <serial.h>
#include <sysconfig.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "semphr.h"

#ifdef HAL_UART_MODULE_ENABLED

#define SERIAL_TIMEOUT pdMS_TO_TICKS(1000)

typedef enum {
	#ifdef USART1
	USART1_INDEX,
	#endif
	#ifdef USART2
	USART2_INDEX,
	#endif
	#ifdef USART3
	USART3_INDEX,
	#endif
	#ifdef USART4
	USART4_INDEX,
	#endif
	#ifdef USART5
	USART5_INDEX,
	#endif
	#ifdef USART6
	USART6_INDEX,
	#endif
	#ifdef USART7
	USART7_INDEX,
	#endif
	#ifdef USART8
	USART8_INDEX,
	#endif
	USART_COUNT
} usartIndex_e;


static SemaphoreHandle_t serialMutex[USART_COUNT];
static SemaphoreHandle_t txComplete[USART_COUNT];
static SemaphoreHandle_t rxComplete[USART_COUNT];
static SemaphoreHandle_t serialPrintMutex;

void serialInit(void){
	for (uint8_t i = 0; i < USART_COUNT; ++i) {
		serialMutex[i]   = xSemaphoreCreateMutex();
		serialPrintMutex = xSemaphoreCreateMutex();
		txComplete[i] = xSemaphoreCreateBinary();
		rxComplete[i] = xSemaphoreCreateBinary();
	}
}

int8_t serialIndex(UART_HandleTypeDef* huart){
	#ifdef	USART1
		if(huart->Instance == USART1) return USART1_INDEX;
	#endif
	#ifdef	USART2
		if(huart->Instance == USART2) return USART2_INDEX;
	#endif
	#ifdef	USART3
		if(huart->Instance == USART3) return USART3_INDEX;
	#endif
	#ifdef	USART4
		if(huart->Instance == USART4) return USART4_INDEX;
	#endif
	#ifdef	USART5
		if(huart->Instance == USART5) return USART5_INDEX;
	#endif
	#ifdef	USART6
		if(huart->Instance == USART6) return USART6_INDEX;
	#endif
	#ifdef	USART7
		if(huart->Instance == USART7) return USART7_INDEX;
	#endif
	#ifdef	USART8
		if(huart->Instance == USART8) return USART8_INDEX;
	#endif
	return -1;
}

int8_t	serialSize(void){
	return USART_COUNT;
}

void serialSetBaudRate(UART_HandleTypeDef* huart, baudRate_e index){
	HAL_UART_Abort(huart);
	HAL_UART_DeInit(huart);
	huart->Init.BaudRate = baudRates[index];
	HAL_UART_Init(huart);
}

uint32_t serialGetBaudRate(UART_HandleTypeDef* huart){
	uint32_t baud = huart->Init.BaudRate;
	return baud;
}

int8_t serialRead  (UART_HandleTypeDef* huart, uint8_t* pRxData, uint16_t len){
	int8_t ix = serialIndex(huart);
	if(ix == -1) return HAL_ERROR;

	if(xSemaphoreTake(serialMutex[ix],SERIAL_TIMEOUT)!=pdTRUE)return HAL_ERROR;
	HAL_UART_Receive_IT(huart, pRxData, len);
	if(xSemaphoreTake(rxComplete[ix],SERIAL_TIMEOUT)!=pdTRUE){
		xSemaphoreGive(serialMutex[ix]);
		return HAL_ERROR;
	}

	xSemaphoreGive(serialMutex[ix]);
	return HAL_OK;
}

int8_t serialWrite (UART_HandleTypeDef* huart, const uint8_t* pTxData, uint16_t len){
	int8_t ix = serialIndex(huart);
	if(ix == -1) return HAL_ERROR;

	if(xSemaphoreTake(serialMutex[ix],SERIAL_TIMEOUT)!=pdTRUE)return HAL_ERROR;
	HAL_UART_Transmit_IT(huart, pTxData, len);
	if(xSemaphoreTake(txComplete[ix],SERIAL_TIMEOUT)!=pdTRUE){
		xSemaphoreGive(serialMutex[ix]);
		return HAL_ERROR;
	}
	xSemaphoreGive(serialMutex[ix]);
	return HAL_OK;
}

#ifdef SYSDEBUG
void serialPrint(char* format, ...){

    va_list args;
    char temp[84] = {0};
    uint8_t length = 0;

    va_start(args, format);
    vsprintf(temp,format,args);
    va_end(args);

    for(uint8_t i = 0; i < 84; i++){
    	if(temp[i] == 0x00){
    		length = i;
    		break;
    	}
    }

    serialWrite(&SYSDEBUG, (uint8_t*)temp, length);
}
#endif

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	int8_t ix = serialIndex(huart);
	if(ix==-1) return;

	xSemaphoreGiveFromISR(rxComplete[ix],&xHigherPriorityTaskWoken);
	if(xHigherPriorityTaskWoken){
		portYIELD();
	}
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	int8_t ix = serialIndex(huart);
	if(ix==-1) return;

	xSemaphoreGiveFromISR(txComplete[ix],&xHigherPriorityTaskWoken);
	if(xHigherPriorityTaskWoken){
		portYIELD();
	}
}

#endif
