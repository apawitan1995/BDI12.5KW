/*
 * ERU_app.h
 *
 *  Created on: Jan 9, 2014
 *      Author: Hanif
 */

#ifndef ERU_APP_H_
#define ERU_APP_H_

#include <DAVE3.h>
//Debug
#include <stdio.h>
#include "peripheral/UART_app.h"

extern volatile uint32_t fault_count;
extern volatile uint32_t DCPT2_Fault;
extern volatile uint32_t GD1_Fault;


void ERU_Init(void);

#endif /* ERU_APP_H_ */
