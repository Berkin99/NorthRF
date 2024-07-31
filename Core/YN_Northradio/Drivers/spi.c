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

#include <system.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "spi.h"

#ifdef HAL_SPI_MODULE_ENABLED

#define SPI_TIMEOUT pdMS_TO_TICKS(1000)

typedef enum {
	#ifdef SPI1
	SPI1_INDEX,
	#endif
	#ifdef SPI2
	SPI2_INDEX,
	#endif
	#ifdef SPI3
	SPI3_INDEX,
	#endif
	SPI_COUNT
} spi_e;

static SemaphoreHandle_t spiMutex   [SPI_COUNT];
static SemaphoreHandle_t txComplete [SPI_COUNT];
static SemaphoreHandle_t rxComplete [SPI_COUNT];

void spiInit(void){
	for (uint8_t i = 0; i < SPI_COUNT; i++) {
		spiMutex[i]   = xSemaphoreCreateMutex();
		txComplete[i] = xSemaphoreCreateBinary();
		rxComplete[i] = xSemaphoreCreateBinary();
	}
}

int8_t spiIndex(SPI_HandleTypeDef* hspi){
	#ifdef SPI1
	if(hspi->Instance == SPI1) return SPI1_INDEX;
	#endif
	#ifdef SPI2
	if(hspi->Instance == SPI2) return SPI2_INDEX;
	#endif
	#ifdef SPI3
	if(hspi->Instance == SPI3) return SPI3_INDEX;
	#endif
	return -1;
}

void spiBeginTransaction(SPI_HandleTypeDef* hspi){
	int8_t ix = spiIndex(hspi);
	if(ix==-1) return;
	xSemaphoreTake(spiMutex[ix], SPI_TIMEOUT);
}

void spiEndTransaction(SPI_HandleTypeDef* hspi){
	int8_t ix = spiIndex(hspi);
	if(ix==-1) return;
	xSemaphoreGive(spiMutex[ix]);
}

int8_t spiReceive(SPI_HandleTypeDef* hspi ,uint8_t* pRxData, uint8_t len){
	int8_t ix = spiIndex(hspi);
	if(ix==-1) return HAL_ERROR;

	HAL_SPI_Receive_IT(hspi, pRxData, len);
	xSemaphoreTake(rxComplete[ix],SPI_TIMEOUT);
	return HAL_OK;
}

int8_t spiTransmit(SPI_HandleTypeDef* hspi ,uint8_t* pTxData, uint8_t len){
	int8_t ix = spiIndex(hspi);
	if(ix==-1) return HAL_ERROR;

	HAL_SPI_Transmit_IT(hspi, pTxData, len);
	xSemaphoreTake(txComplete[ix], SPI_TIMEOUT);
	return 	HAL_OK;
}

int8_t spiTransmitReceive(SPI_HandleTypeDef* hspi ,uint8_t* pRxData, uint8_t* pTxData, uint8_t len){
	int8_t ix = spiIndex(hspi);
	if(ix==-1) return HAL_ERROR;

	HAL_SPI_TransmitReceive_IT(hspi, pTxData, pRxData, len);
	if((xSemaphoreTake(txComplete[ix],SPI_TIMEOUT) == pdTRUE)
	&& (xSemaphoreTake(rxComplete[ix],SPI_TIMEOUT) == pdTRUE)) return HAL_OK;

	return HAL_ERROR;
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef* hspi){

	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	int8_t ix = spiIndex(hspi);
	if(ix==-1)	{return;}


	xSemaphoreGiveFromISR(rxComplete[ix],&xHigherPriorityTaskWoken);
	if(xHigherPriorityTaskWoken){
		portYIELD();
	}
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* hspi){
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	int8_t ix = spiIndex(hspi);
	if(ix==-1){return;}

	xSemaphoreGiveFromISR(txComplete[ix],&xHigherPriorityTaskWoken);
	if(xHigherPriorityTaskWoken){
		portYIELD();
	}
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef* hspi){
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	int8_t ix = spiIndex(hspi);
	if(ix==-1){return;}

	xSemaphoreGiveFromISR(txComplete[ix], &xHigherPriorityTaskWoken);
	xSemaphoreGiveFromISR(rxComplete[ix], &xHigherPriorityTaskWoken);

	if(xHigherPriorityTaskWoken){
		portYIELD();
	}
}

#endif
