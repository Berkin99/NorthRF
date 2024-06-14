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

#define LED_SYS		LED_1
#define LED_ERR		LED_1

void systemLaunch(void){

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



