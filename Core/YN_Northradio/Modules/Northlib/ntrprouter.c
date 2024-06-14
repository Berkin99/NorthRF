///**
// * __  __ ____ _  __ ____ ___ __  __
// * \ \/ // __// |/ //  _// _ |\ \/ /
// *  \  // _/ /    /_/ / / __ | \  /
// *  /_//___//_/|_//___//_/ |_| /_/
// *
// * Yeniay Control Computer Firmware
// *
// * Copyright (C) 2022 Yeniay
// *
// * This program is free software: you
// * can redistribute it and/or modify it
// * under the terms of the GNU General
// * Public License as published by the
// * Free Software Foundation, in version 3.
// *
// * You should have received a copy of
// * the GNU General Public License along
// * with this program. If not, see
// * <http://www.gnu.org/licenses/>.
// */
//
//#include <stdint.h>
//#include <stdbool.h>
//
//#include "systime.h"
//#include "ntrprouter.h"
//#include "ntrp.h"
//
//#include "RF24.h"
//#include "usb.h"
//
//bool _ready; /* Syncronisation ? OK : ERROR */
//
//NTRPR_Pipe_t nrf_pipe[NRF_MAX_PIPE_SIZE];  /* 5 PIPE. Do not use pipe 0 for multiceiver applications */
//uint8_t nrf_pipe_index;
//int8_t  nrf_last_transmit_index;           /* Last Transmit Pipe Index */
//
//uint8_t _rxBuffer[NTRP_MAX_MSG_SIZE];   /* Master RX buffer */
//uint8_t _txBuffer[NTRP_MAX_MSG_SIZE];   /* Slave Transmit buffer */
//
//NTRPR_Mode_e mode; /* RxTx , Rx, Tx modes. Default : RxTx */
//
//uint32_t _timer_us;
//void _timeout_tick(uint32_t tick_us = 1);
//
//
//void NTRPR_Init(void){
//	/* Set the usb */
//}
//
//uint8_t NTRPR_sync(uint32_t timeout){
//
//    char syncdata[] = "---";
//    _timer_us = 0;
//    uint32_t _timeout_us = timeout * 1000000;
//
//    while (serial_port->available()<3){
//        serial_port->print(NTRP_SYNC_DATA);
//        _timeout_tick(100);
//        if(_timer_us>_timeout_us)return 0;
//    }
//
//    syncdata[0] = serial_port->read();
//    syncdata[1] = serial_port->read();
//    syncdata[2] = serial_port->read();
//    if(strcmp(syncdata,NTRP_PAIR_DATA)!=0)return 0;
//
//    _ready = true;
//    return 1;
//}
//
//void NTRPR_task(void){
//    static NTRP_Message_t msgbuffer; /* Static -> do not need to allocate memmory repeatedly */
//    msgbuffer = NTRP_NewMessage();
//
//    /* Continously checks serial port for catch a success ntrp_message */
//    if(NTRPR_receiveMaster(&msgbuffer)){
//    	NTRPR_route(&msgbuffer);
//    }
//
//    /* Continously checks nrf buffer for catch a success ntrp_message */
//    if(NTRPR_receivePipe(&msgbuffer)){
//    	NTRPR_route(&msgbuffer);
//    }
//}
//
//void NTRPR_debug(const char* msg){
//    NTRP_Message_t temp = NTRP_NewMessage();
//
//    temp.talkerID = NTRP_ROUTER_ID;
//    temp.receiverID = NTRP_MASTER_ID;
//
//    uint8_t i = 0;
//    temp.packet.header = NTRP_MSG;
//
//    while(i<=(NTRP_MAX_PACKET_SIZE-2) && msg[i]!=0x00){
//        temp.packet.data.bytes[i] = msg[i];
//        i++;
//    }
//
//    temp.packet.dataID = i;
//    temp.packetsize = i+2;
//    NTRPR_transmitMaster(&temp);
//}
//
//uint8_t NTRPR_receiveMaster(NTRP_Message_t* msg);
//void 	NTRPR_transmitMaster(const NTRP_Message_t* msg);
//
//uint8_t NTRPR_receivePipe(NTRP_Message_t* msg);
//uint8_t NTRPR_Router_transmitPipe( uint8_t pipeid, const NTRP_Packet_t* packet, uint8_t size);
//void 	NTRPR_transmitPipeFast( uint8_t pipeid,const uint8_t* raw_sentence, uint8_t size);
//
//void 	NTRPR_route(NTRP_Message_t* msg);
//
//void    NTRPR_routerCOM(NTRP_Packet_t* packet, uint8_t size);
//uint8_t NTRPR_openPipe(NTRPR_Pipe_t cmd);
//void    NTRPR_closePipe(char id);
