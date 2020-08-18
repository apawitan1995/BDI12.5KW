/*
 * DMA_app.h
 *
 *  Created on: Jan 22, 2014
 *      Author: Hanif
 */

#ifndef DMA_APP_H_
#define DMA_APP_H_

#include <DAVE3.h>
#include "peripheral/UART_app.h" //debug
#include "peripheral/ADC_app.h" //ADC result handling using DMA
#include <stdbool.h>

#define BUFFER_SIZE 256

extern volatile uint32_t srcBuffer[BUFFER_SIZE];
extern __IO uint32_t *dstBuffer;
extern volatile bool g_endTransfer; // Global to signal end of the DMA tranfer

void DMA_RS485_Init(void);
void DMA_Init_app(void);
void DMA0_CH0_Init(void);
void DMA0_CH1_Init(void);
void DMA0_CH2_Init(void);
void DMA0_CH4_Init(void);
void DMA0_CH5_Init(void);



#endif /* DMA_APP_H_ */
