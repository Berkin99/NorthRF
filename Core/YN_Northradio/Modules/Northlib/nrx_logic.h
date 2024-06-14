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

#ifndef NRX_LOGIC_H_
#define NRX_LOGIC_H_

#include <stdbool.h>
#include <stdint.h>

#include "nrx.h"
#include "ntrp.h"

#define NRX_VARID_IS_VALID(varId) (varId.id != 0xffffu)

typedef struct nrxVarId_s {
  uint16_t id;
  uint16_t index;
} __attribute__((packed)) nrxVarId_t;

struct nrx_s* nrxGetVar(uint16_t index);
nrxVarId_t nrxGetVarId(const char* group, const char* name);

int nrxGetType(uint16_t index);

uint8_t nrxVarSize(int type);
uint8_t nrxGroupSize(int index);

void nrxLogicInit();

#endif /* nrx_LOGIC_H_ */
