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

#ifndef SYSCONFIG_H_
#define SYSCONFIG_H_

#include <system.h>

/// SYSTIME /////////////////////////////////////////////////
#define SYSTIME				htim2
/////////////////////////////////////////////////////////////

/// SYSDEBUG ////////////////////////////////////////////////
#define SYSDEBUG			huart2
/////////////////////////////////////////////////////////////

/// LED /////////////////////////////////////////////////////
#define LED1_GPIO			LED_1_GPIO_Port
#define LED1_PIN			LED_1_Pin
#define LED2_GPIO			LED_2_GPIO_Port
#define LED2_PIN			LED_2_Pin
/////////////////////////////////////////////////////////////

/// SPI /////////////////////////////////////////////////////
#define RF24_SPI			hspi1
#define RF24_CE_GPIO		NRF_CE_GPIO_Port
#define RF24_CS_GPIO		NRF_CS_GPIO_Port
#define RF24_CE				NRF_CE_Pin
#define RF24_CS				NRF_CS_Pin
#define RF24_RX_ADDRESS		{0xE7,0xE7,0xE7,0xE3,0x00}
#define RF24_TX_ADDRESS		{0xE7,0xE7,0xE7,0xE3,0x01}
/////////////////////////////////////////////////////////////

#endif /* SYSCONFIG_H_ */
