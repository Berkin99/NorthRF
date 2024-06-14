/**
 *    __  __ ____ _  __ ____ ___ __  __
 * 	  \ \/ // __// |/ //  _// _ |\ \/ /
 *     \  // _/ /    /_/ / / __ | \  /
 *     /_//___//_/|_//___//_/ |_| /_/
 *
 *    Yeniay Control Computer Firmware
 *
 *       Copyright (C) 2022 Yeniay
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
#include <systime.h>
#include <sysconfig.h>
#include "RF24.h"


static int anan = 0;

void systemLaunch(void){

	RF24_Init(&RF24_SPI, RF24_CE_GPIO, RF24_CE, RF24_CS_GPIO, RF24_CS);
	anan = RF24_begin();

	while(1){
		HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin);
		delay(1000);
	}

//  /* FreeRTOS Confiured Hardware Abstraction
//   * Layer Initialize.
//   * */
//  serialInit();
//  i2cInit();
//  spiInit();
//  pwmInit();
//  //adcInit();		/* Not Implemented */
//
//  /* System Task */
//  STATIC_MEM_TASK_CREATE(SYSTEM_TASK,systemTask,NULL);
//  vTaskStartScheduler();
//
//  /*Should not reach here*/
//  systemErrorCall();
//  while(1);
}

void systemTask(void){


}



