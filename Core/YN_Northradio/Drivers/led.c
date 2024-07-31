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

#include <systime.h>
#include "led.h"

typedef struct {
	led_value_e value;
	GPIO_TypeDef* gpio_x;
	uint16_t pin;
}led_t;

static led_t led[LED_COUNT] = {
#ifdef LED1_PIN
		{.value = 0,.gpio_x = (LED1_GPIO),.pin = (LED1_PIN)},
#endif
#ifdef LED2_PIN
		{.value = 0,.gpio_x = (LED2_GPIO),.pin = (LED2_PIN)},
#endif
#ifdef LED3_PIN
		{.value = 0,.gpio_x = (LED3_GPIO),.pin = (LED3_PIN)},
#endif
#ifdef LED4_PIN
		{.value = 0,.gpio_x = (LED4_GPIO),.pin = (LED4_PIN)},
#endif
};


void ledSet(uint8_t index, led_value_e value){
	if(index>=LED_COUNT) return;
	led[index].value = value;
	HAL_GPIO_WritePin(led[index].gpio_x, led[index].pin, value);
}

led_value_e ledGet(uint8_t index){
	if(index>=LED_COUNT) return 0;
	return led[index].value;
}

void ledToggle(uint8_t index){
	ledSet(index, !(ledGet(index)));
}
