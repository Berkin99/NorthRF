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


#ifndef NTRPROUTER_H_
#define NTRPROUTER_H_

#include "system.h"

#define NRF_MAX_PIPE_SIZE   6

typedef enum{
  R_OPENPIPE    = 21,
  R_CLOSEPIPE   = 22,
  R_TRX         = 23,
  R_FULLRX      = 24,
  R_FULLTX      = 25,
  R_EXIT        = 26,
}NTRPR_Header_e;

typedef enum{
  R_MODE_TRX      = 0,
  R_MODE_FULLRX   = 1,
  R_MODE_FULLTX   = 2,
}NTRPR_Mode_e;

typedef struct{
  uint8_t id;          	 	/*Pipe ID (Unique) : Represents the 5 byte address*/
  uint8_t channel;      	/*Channel (Not Implemented)*/
  uint8_t bandwidth;    	/*Bandwidth (Not Implemented)*/
  uint8_t txaddress[5];   	/*5 byte address (Unique)*/
  uint8_t rxaddress[5];
}NTRPR_Pipe_t;



void NTRPR_Init(void);

uint8_t NTRPR_sync(uint32_t timeout);
void 	NTRPR_task(void);
void 	NTRPR_debug(const char* msg);

uint8_t NTRPR_receiveMaster(NTRP_Message_t* msg);
void 	NTRPR_transmitMaster(const NTRP_Message_t* msg);

uint8_t NTRPR_receivePipe(NTRP_Message_t* msg);
uint8_t NTRPR_Router_transmitPipe( uint8_t pipeid, const NTRP_Packet_t* packet, uint8_t size);
void 	NTRPR_transmitPipeFast( uint8_t pipeid,const uint8_t* raw_sentence, uint8_t size);

void 	NTRPR_route(NTRP_Message_t* msg);

void    NTRPR_routerCOM(NTRP_Packet_t* packet, uint8_t size);
uint8_t NTRPR_openPipe(NTRPR_Pipe_t cmd);
void    NTRPR_closePipe(char id);


#endif /* NTRPROUTER_H_ */
