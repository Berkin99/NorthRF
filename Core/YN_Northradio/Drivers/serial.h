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

/*
 * @return HAL_StatusTypeDef
 * @retval 0 -> HAL_OK
 * @retval 1 -> HAL_ERROR
 * @retval 2 -> HAL_BUSY
 * @retval 3 -> HAL_TIMEOUT
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdarg.h>
#include "system.h"

typedef enum {
	BAUD_9600,
	BAUD_19200,
	BAUD_38400,
	BAUD_57600,
	BAUD_115200
} baudRate_e;

static const uint32_t baudRates[] = {
	9600,
	19200,
	38400,
	57600,
	115200
};

void     serialInit(void);
int8_t   serialIndex(UART_HandleTypeDef* huart);
int8_t	 serialSize(void);
void     serialSetBaudRate(UART_HandleTypeDef* huart, baudRate_e index);
uint32_t serialGetBaudRate(UART_HandleTypeDef* huart);
int8_t   serialRead (UART_HandleTypeDef* huart, uint8_t* pRxData, uint16_t len);
int8_t   serialWrite(UART_HandleTypeDef* huart, const uint8_t* pTxData, uint16_t len);

void serialPrint(char* format, ...);

#endif /* SERIAL_H_ */
