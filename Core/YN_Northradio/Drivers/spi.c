/**
 * __  __ ____ _  __ ____ ___ __  __
 * \ \/ // __// |/ //  _// _ |\ \/ /
 *  \  // _/ /    /_/ / / __ | \  /
 *  /_//___//_/|_//___//_/ |_| /_/
 *
 * Yeniay Control Computer Firmware
 *
 * Copyright (C) 2022 Yeniay
 *
 * This program is free software: you
 * can redistribute it and/or modify it
 * under the terms of the GNU General
 * Public License as published by the
 * Free Software Foundation, in version 3.
 *
 * You should have received a copy of
 * the GNU General Public License along
 * with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "system.h"

#define SPI_TIMEOUT 1000

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

void spiInit(void){
	return;
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

void spiBeginTransaction(SPI_HandleTypeDef* hspi){return;}
void spiEndTransaction(SPI_HandleTypeDef* hspi){return;}

uint8_t spiReceive(SPI_HandleTypeDef* hspi ,uint8_t* pRxData, uint8_t len){
	return HAL_SPI_Receive(hspi, pRxData, len, SPI_TIMEOUT);
}

uint8_t spiTransmit(SPI_HandleTypeDef* hspi ,uint8_t* pTxData, uint8_t len){
	return HAL_SPI_Transmit(hspi, pTxData, len, SPI_TIMEOUT);
}

uint8_t spiTransmitReceive(SPI_HandleTypeDef* hspi ,uint8_t* pRxData, uint8_t* pTxData, uint8_t len){
	return HAL_SPI_TransmitReceive(hspi, pTxData, pRxData, len, SPI_TIMEOUT);
}
