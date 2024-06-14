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

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>
#include <system.h>

/*	INFO:
 * 	This HAL driver wrap developed for
 * 	FreeRTOS integrated SPI communication.
 * 	Interrupt driven peripherals.
 * 	> All SPI peripherals should use interrupt.
 * 	> Do not use more than 7 MBits/s SPI speed.
 */

void spiInit(void);
int8_t spiIndex(SPI_HandleTypeDef* hspi);

void spiBeginTransaction(SPI_HandleTypeDef* hspi);
void spiEndTransaction(SPI_HandleTypeDef* hspi);

uint8_t spiReceive(SPI_HandleTypeDef* hspi ,uint8_t* pRxData, uint8_t len);
uint8_t spiTransmit(SPI_HandleTypeDef* hspi ,uint8_t* pTxData, uint8_t len);
uint8_t spiTransmitReceive(SPI_HandleTypeDef* hspi ,uint8_t* pRxData, uint8_t* pTxData, uint8_t len);

#endif /* SPI_H_ */
