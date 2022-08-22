/*
 * system.h
 *
 * Created: 8/15/2022 2:48:56 PM
 *  Author: Muhammad_Ali
 */ 


#ifndef SYSTEM_H_
#define SYSTEM_H_
#include <stdlib.h>
#include "ds18b20.h"
#include "e18_e80nk.h"
#include "esp.h"
#include "fan.h"
#include "gps.h"
#include "gsm.h"
#include "lock.h"

void System_Init(void);
void System_SmartBox();
#endif /* SYSTEM_H_ */