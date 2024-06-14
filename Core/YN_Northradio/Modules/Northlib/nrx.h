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


#ifndef NRX_H_
#define NRX_H_

#include <stdint.h>
#include "nrx_logic.h"

struct nrx_s{
	uint8_t type;
	char * name;
	void * address;
};

#define NRX_BYTES_MASK 0x03
#define NRX_1BYTE  0x00
#define NRX_2BYTES 0x01
#define NRX_4BYTES 0x02
#define NRX_8BYTES 0x03

#define NRX_TYPE_MASK   0x0F
#define NRX_TYPE_INT   (0x00<<2)
#define NRX_TYPE_FLOAT (0x01<<2)

#define NRX_SIGNED 	(0x00<<3)
#define NRX_UNSIGNED 	(0x01<<3)

#define NRX_UINT8  (NRX_1BYTE  | NRX_TYPE_INT | NRX_UNSIGNED)
#define NRX_INT8   (NRX_1BYTE  | NRX_TYPE_INT | NRX_SIGNED)
#define NRX_UINT16 (NRX_2BYTES | NRX_TYPE_INT | NRX_UNSIGNED)
#define NRX_INT16  (NRX_2BYTES | NRX_TYPE_INT | NRX_SIGNED)
#define NRX_UINT32 (NRX_4BYTES | NRX_TYPE_INT | NRX_UNSIGNED)
#define NRX_INT32  (NRX_4BYTES | NRX_TYPE_INT | NRX_SIGNED)

#define NRX_FLOAT  (NRX_4BYTES | NRX_TYPE_FLOAT | NRX_SIGNED)

#define NRX_CORE	(1<<5)
#define NRX_RONLY	(1<<6)

#define NRX_START 1
#define NRX_STOP  0

#define NRX_VARIABLE (0x00<<7)
#define NRX_GROUP    (0x01<<7)

#define NRX_PERSISTENT (1<<8)

#define NRX_ADD(TYPE, NAME, ADDRESS) \
    { .type = (TYPE),\
      .name = #NAME, \
      .address = (void*)(ADDRESS) },

#define NRX_GROUP_START(NAME)  \
  static struct nrx_s __nrxs_##NAME[] __attribute__((section(".nrx."#NAME), used)) = { \
  NRX_ADD(NRX_GROUP | NRX_START, NAME, 0x0) \

#define NRX_GROUP_STOP(NAME) \
  NRX_ADD(NRX_GROUP | NRX_STOP, stop_##NAME, 0x0) \
};

#endif /* NRX_H_ */
