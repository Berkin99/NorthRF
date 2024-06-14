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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sysconfig.h>
#include <systime.h>

#include "FreeRTOS.h"
#include "semphr.h"
#include "static_mem.h"

#include "serial.h"
#include "telemetry.h"
#include "northcom.h"
#include "ntrp.h"
#include "nrx_logic.h"
#include "nrx.h"

#ifndef NC_ID
#define NC_ID 		'X'
#endif


static uint8_t txBuffer[NTRP_MAX_MSG_SIZE];
static NTRP_Message_t nc_message;
const static telemetryHandle_t* nc_telemetry;
static uint8_t isInit = 0;
static uint32_t last_data_time = 0;

#define RC_TIMEOUT 500 //ms
static  RC_Handle_t rc_handle;
static  uint32_t rc_last_update_ms;

STATIC_MEM_TASK_ALLOC(nc_task,NC_TASK_STACK,NC_TASK_PRI);

uint8_t ncInit(void){
	if(isInit==1) return NC_INIT;
	nrxLogicInit();

	nc_telemetry = NULL;

#ifdef NC_MODULE
	nc_telemetry = telemetryGetHandle(NC_MODULE);
#endif

	if(nc_telemetry == NULL){
		serialPrint("[-] NorthCom Init ERROR\n");
		return NC_ERROR;
	}

	isInit = 1;
	serialPrint("[+] NorthCom Init OK\n");

	STATIC_MEM_TASK_CREATE(nc_task,ncTask,NULL);
	return NC_OK;
}

void ncTask(void* argv){

	serialPrint("[+] NorthCom Task Init OK\n");

	static uint8_t rxBuffer[NTRP_MAX_MSG_SIZE];
	RC_Init(&rc_handle);

	TickType_t xLastWakeTime = xTaskGetTickCount();
	while(1){
		if(nc_telemetry->receive(rxBuffer)){
			ncDataHandler(rxBuffer);
		}

		if((millis() - rc_last_update_ms)>RC_TIMEOUT) RC_Disarm(&rc_handle);
		vTaskDelayUntil(&xLastWakeTime, (1000/NC_TASK_FREQ));
	}
}

uint32_t ncLastDataTime(void){
	return last_data_time;
}


RC_Handle_t* ncRemoteController(void){
	return &rc_handle;
}

void ncRemoteControllerUpdate(uint8_t* data){
	/* Serial Print For Debugging */
	if(data[0]|data[1]|data[2]|data[3]){
		for (uint8_t i = 0; i < 5; i++) rc_handle.ch[i].value = data[i];
		RC_Update(&rc_handle);
//		serialPrint("%d,%d,%d,%d,%d\n",rc_handle.ch[0].value,rc_handle.ch[1].value,rc_handle.ch[2].value,rc_handle.ch[3].value,rc_handle.ch[4].value);
		rc_last_update_ms = millis();
	}
	else RC_Disarm(&rc_handle); /* Telemetry value error instant disarm */
}

void ncTransmitPacket(NTRP_Packet_t* packet, uint8_t size){
	if(!isInit) return;
	#ifdef NC_NTRPMESSAGE
	if(size > NTRP_MAX_MSG_SIZE) size = NTRP_MAX_MSG_SIZE;
	NTRP_Message_t ntrp_tx;
	ntrp_tx.talkerID = nc_ID;
	ntrp_tx.receiverID = NTRP_MASTER_ID;
	ntrp_tx.packetsize = size;
	ntrp_tx.packet = packet;
	if(NTRP_Unite(txBuffer, &ntrp_tx)) nc_telemetry->transmit(txBuffer, size+5);
	#elif defined(NC_NTRPPACKET)

	if(size > NTRP_MAX_PACKET_SIZE) size = NTRP_MAX_PACKET_SIZE;
	if(NTRP_PackUnite(txBuffer, size, packet)){
		nc_telemetry->transmit(txBuffer, size);}
	#endif
}


void ncDataHandler(const uint8_t* rxBuffer){
	uint8_t status = 0;

	#ifdef NC_NTRPMESSAGE
	status = NTRP_Parse(&nc_message, rxBuffer);
	if(nc_message.receiverID != nc_ID)return;

	#elif defined(NC_NTRPPACKET)
	status = NTRP_PackParse(&nc_message.packet, rxBuffer);
	#endif
	if(status != 1) return;

	last_data_time = millis();
	ncPacketHandler(&nc_message.packet);
}

void ncPacketHandler(NTRP_Packet_t* packet){
switch (packet->header) {
	case NTRP_NAK:ncTransmitPacket(&nc_message.packet,nc_message.packetsize);break;
	case NTRP_ACK:RxACK();break;
	case NTRP_MSG:RxMSG(packet->data.bytes,packet->dataID);break;
	case NTRP_CMD:RxCMD(packet->dataID,packet->data.bytes);break;
	case NTRP_GET:RxGET(packet->dataID);break;
	case NTRP_SET:RxSET(packet->dataID,packet->data.bytes);break;
	default:
	break;
}
}

void RxACK(void){
	/* Rx Ack Event */
	return;
}

void TxACK(void){
	NTRP_Packet_t packet;
	packet.header = NTRP_ACK;
	packet.dataID = 1;
	ncTransmitPacket(&packet, 2);
}

void RxMSG(const uint8_t* msg, uint8_t len){
	static char temp [27];
	uint8_t i;
	for (i = 0; i<len;i++){
		temp[i] = (char)msg[i];
		if(i>=26) break;
	}
	temp[i] = 0x00;
	serialPrint("NCOM Received: %s\n",temp);
	TxACK();
}

void TxMSG(const char* msg){
	NTRP_Packet_t packet;
	packet.header = NTRP_MSG;
	uint8_t i = 0;
	while(i<NTRP_MAX_PACKET_SIZE-2){
		if(msg[i]==0) break;
		packet.data.bytes[i] = msg[i];
		i++;
	}
	packet.dataID = i;
	ncTransmitPacket(&packet,i+2);
}

void RxCMD(uint8_t cmdid, uint8_t* data){

	/* Command Modes */
#define RC_CONTROLLER 		0x00
#define NRX_CONTENT_ID 		0x01
#define FUNC_CONTENT_ID 	0x02

	switch (cmdid){
	case (RC_CONTROLLER):{
		ncRemoteControllerUpdate(data);
	}break;
	case (NRX_CONTENT_ID):{
		uint8_t arr[26] = {0};
		struct nrx_s* val = nrxGetVar(data[0]);
		if(val==NULL){
			TxACK();
			break;
		}
		arr[0] = data[0];
		arr[1] = val->type;
		strcpy((char*)&arr[2],val->name);

		/*WARNING*/
		//serialPrint("NRX:%d:%d:%s\n",arr[0],arr[1],(char*)&arr[2]);
		/*WARNING*/

		TxCMD(NRX_CONTENT_ID, arr);

	}break;
	case (FUNC_CONTENT_ID):{
		break;
	}break;
	default:break;
	}

}

void TxCMD(uint8_t cmdid,const uint8_t* data){
	NTRP_Packet_t packet;
	packet.header = NTRP_CMD;
	packet.dataID = cmdid;

	for(uint8_t i = 0; i<26;i++){
		packet.data.bytes[i] = data[i];
	}
	ncTransmitPacket(&packet,28);
}

void RxGET(uint8_t dataid){
	struct nrx_s* nrxptr = nrxGetVar(dataid);
	if(nrxptr==NULL){ serialPrint("NRX not found: %d\n",dataid);return;}

	NTRP_Packet_t packet;
	packet.header = NTRP_SET;
	packet.dataID = dataid;

	uint8_t byteindex = 0;
	uint8_t isGroup = 0;
	uint8_t datasize;
	uint8_t* ptr;

	if(nrxptr->type & (NRX_GROUP)){
		if(!(nrxptr->type & (NRX_START))) {serialPrint("NRX is not start: %d\n",dataid);return;}
		isGroup = 1;
		nrxptr++;
	}

	do {
		if(nrxptr->type & (NRX_GROUP)) {
			isGroup = 0;
			break;
		}

		datasize = nrxVarSize(nrxptr->type);
		ptr = (uint8_t*)nrxptr->address;
		for(uint8_t j = 0; j<datasize; j++){
			packet.data.bytes[byteindex] = *ptr;
			ptr++;
			byteindex++;
		}
		nrxptr++;
	} while (byteindex<26 && isGroup);

	ncTransmitPacket(&packet, (byteindex+2));
}

void RxSET(uint8_t dataid, uint8_t* data)
{
	struct nrx_s* nrxptr = nrxGetVar(dataid);
	if(nrxptr==NULL) return;

	uint8_t byteindex = 0;
	uint8_t isGroup = 0;
	uint8_t datasize;
	uint8_t* ptr;

	if(nrxptr->type & (NRX_GROUP)){
		if(!(nrxptr->type & (NRX_START))) return;
		isGroup = 1;
		nrxptr++;
	}

	do {
		if(nrxptr->type & (NRX_GROUP)) {isGroup = 0;break;}

		datasize = nrxVarSize(nrxptr->type);
		ptr = (uint8_t*)nrxptr->address;
		for(uint8_t j = 0; j<datasize; j++){
			*ptr = data[byteindex];
			ptr++;
			byteindex++;
		}
		nrxptr++;
	} while (byteindex<26 && isGroup);
}

void TxSET(uint8_t dataid, void* bytes, uint8_t size){
	NTRP_Packet_t packet;
	packet.header = NTRP_SET;
	packet.dataID = dataid;

	for(uint8_t i = 0; i<size; i++){
		packet.data.bytes[i] = ((uint8_t*)bytes)[i];
	}

	ncTransmitPacket(&packet, (size+2));
}
