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


#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "main.h"
#include "sysdebug.h"

#define SYS_TASK_PRI		(2)
#define SYS_TASK_STACK		(4 * configMINIMAL_STACK_SIZE)

void systemLaunch(void);
void systemWaitReady(void);
void systemErrorCall(void);

#endif /* SYSTEM_H_ */
