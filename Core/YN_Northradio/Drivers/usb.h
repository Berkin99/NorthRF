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

#ifndef USB_H_
#define USB_H_

#include <stdint.h>
#include <stdarg.h>

#include "system.h"

void     usbInit(void);
int8_t   usbReceive (uint8_t* pRxData, uint16_t len);
int8_t   usbTransmit(uint8_t* pTxData, uint16_t len);
uint16_t usbAvailableData(void);
void     usbWaitDataReady(void);

void 	 usbPrint(char* format, ...);

#endif /* USB_H_ */
