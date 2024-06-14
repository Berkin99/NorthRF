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

#ifndef LED_H_
#define LED_H_

#include <stdint.h>
#include <system.h>
#include <sysconfig.h>

#define LED_SIZE  		1
#define LED_MAIN 		0

typedef enum{
	#ifdef LED1_PIN
		LED_1,
	#endif
	#ifdef LED2_PIN
		LED_2,
	#endif
	#ifdef LED3_PIN
		LED_3,
	#endif
	#ifdef LED4_PIN
		LED_4,
	#endif
	LED_COUNT
}led_e;

typedef enum{
	LED_LOW = 0,
	LED_HIGH
}led_value_e;

void ledSet(uint8_t index, led_value_e value);
led_value_e ledGet(uint8_t index);
void ledToggle(uint8_t index);

#endif /* LED_H_ */
