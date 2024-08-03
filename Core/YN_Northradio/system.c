/**
 *    __  __ ____ _  __ ____ ___ __  __
 * 	  \ \/ // __// |/ //  _// _ |\ \/ /
 *     \  // _/ /    /_/ / / __ | \  /
 *     /_//___//_/|_//___//_/ |_| /_/
 *
 *      Yeniay Northstar RF Firmware
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

#include "FreeRTOS.h"
#include "semphr.h"
#include "cmsis_os.h"

#include "system.h"
#include "systime.h"
#include "sysconfig.h"
#include "static_mem.h"

#include "spi.h"
#include "serial.h"
#include "usb.h"
#include "led.h"
#include "ntrprouter.h"

static uint8_t sysInit;

STATIC_MEM_TASK_ALLOC(SYS_TASK, SYS_TASK_STACK, SYS_TASK_PRI);
void systemTask(void* argv);

void systemLaunch(void){
	if(sysInit) return;

	spiInit();
	serialInit();
	usbInit();

	STATIC_MEM_TASK_CREATE(SYS_TASK, systemTask, NULL);
	sysInit = 1;
}

void systemTask(void* argv){
	ledSet(LED1, 1);
	serialPrint("[>] System start\n");

	NTRPR_Init();

	serialPrint("[>] System Ready\n \n");

	while(1){
		delay(1000);
	}
}

void systemErrorCall(void){

	while(1){
		delay(1000);
	}
}


