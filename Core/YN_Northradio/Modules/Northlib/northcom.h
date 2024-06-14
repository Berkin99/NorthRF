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

#ifndef NORTHCOM_H_
#define NORTHCOM_H_

#include <stdlib.h>
#include <stdint.h>
#include "ntrp.h"
#include "rc_interface.h"

#define NC_TASK_STACK	configMINIMAL_STACK_SIZE*4
#define NC_TASK_PRI		(3)
#define NC_TASK_FREQ	250 //Hz

#define ncDebug(fmt , ...) do{\
	char temp[26] = {0};\
	sprintf(temp,(fmt), ##__VA_ARGS__);\
	TxMSG(temp); break;\
}while (0)\

typedef enum{
	NC_ERROR = 0,
	NC_OK = 1,
	NC_INIT = 2
}nc_Status_e;

uint8_t ncInit(void);
void ncTask(void* argv);

void ncDataHandler(const uint8_t* buffer);
void ncPacketHandler(NTRP_Packet_t* packet);

/* Last Connection Time in milliseconds */
uint32_t ncLastDataTime(void);

void ncTransmitPacket(NTRP_Packet_t* packet, uint8_t size);
RC_Handle_t* ncRemoteController(void);
void ncRemoteControllerUpdate(uint8_t* data);

//void RxNAK(void);
//void TxNAK(void);

void RxACK(void);
void TxACK(void);

void RxMSG(const uint8_t* msg, uint8_t len);
void TxMSG(const char* msg);

void RxCMD(uint8_t cmdid,uint8_t* data);
void TxCMD(uint8_t cmdid,const uint8_t* data);

void RxGET(uint8_t dataid);
//void TxGET(void);	/*Agent Can't control Master Computer but want data from other agents (TOC need to be same)*/

void RxSET(uint8_t dataid, uint8_t* data);
void TxSET(uint8_t dataid, void* bytes, uint8_t size);

#endif /* NORTHCOM_H_ */
