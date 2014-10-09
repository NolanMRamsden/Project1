/*
 * Interrupt.h
 *
 *  Created on: Sep 25, 2014
 *      Author: Karen
 */


#include "alt_types.h"
#include "sys/alt_alarm.h"
#include "Definitions.h"
#include "Drawing.h"

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "headers.h"

extern alt_u32 interruptFunction(void* context);
extern alt_u32 count(void* context);
extern void initInterrupt();
extern void runCountDown();
extern void stopInterrupt();

#endif /* INTERRUPT_H_ */
