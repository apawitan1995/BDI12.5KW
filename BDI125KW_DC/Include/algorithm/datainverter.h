/*
 * datainverter.h
 *
 *  Created on: Feb 1, 2017
 *      Author: Mukhlish
 */

#ifndef DATAINVERTER_H_
#define DATAINVERTER_H_

#include <stdio.h>
#include <DAVE3.h>			//Declarations from DAVE3 Code Generation (includes SFR declaration)

#include "common/delay.h"
#include "common/global.h"
#include "common/look_up_table.h"
#include "common/my_multiplexer.h"

#include "peripheral/IO_app.h"
#include "peripheral/UART_app.h"
#include "peripheral/ADC_app.h"
#include "peripheral/PWM_app.h"
#include "peripheral/DMA_app.h"
#include "peripheral/DAC_app.h"
#include "peripheral/ERU_app.h"
#include "peripheral/I2C_SW_app.h"
#include "peripheral/CAN_app.h"
#include "peripheral/ISR_app.h"

#include "external/EEP25LC1024_app.h"
#include "external/display_app.h"
#include "external/AD5328_app.h"
#include "external/MCP79410_app.h"
#include "external/button_app.h"
#include "external/relay_app.h"

#include "algorithm/converter.h"

//Data Analog
extern volatile float ACCTR, ACCTS, ACCTT, GCTR, GCTS, GCTT, DCPT1, GPTR, GPTS, GPTT, TF1, TF2, DCCT1, IVCTR, IVCTS, IVCTT, DCPT2, ACPTR, ACPTS, ACPTT, FREQR, FREQS, FREQT;

//DI
extern volatile uint8_t DI;
extern volatile uint8_t DIS1_Flag, DIS2_Flag, DIS3_Flag, DI_K2F_Flag;
extern volatile uint8_t DI_K2FNO, DI_K2FNC;

//DO
extern volatile uint8_t DO, DOS;
extern volatile uint8_t DO_K1_Flag, DO_K2_Flag, DO_HK1_Flag, DO_HK2_Flag, DOS1_Flag, DOS2_Flag;

extern volatile uint8_t batterylevel, softwareversion;

//Fault Software
extern volatile uint8_t FSW1, FSW2, FSW3, FSW4, FSW5, FSW6, FSW7, FSW8;
extern volatile uint8_t GEN_FB, K3_FB, K2_FB, K1_FB, GCTT_OL, GCTS_OL, GCTR_OL, GPTT_UV;
extern volatile uint8_t GPTS_UV, GPTR_UV, GPTT_OV, GPTS_OV, GPTR_OV, ACCTT_OL, ACCTS_OL, ACCTR_OL;
extern volatile uint8_t ACPTT_UV, ACPTS_UV, ACPTR_UV, ACPTT_OV, ACPTS_OV, ACPTR_OV, DCPT2_UV, DCPT2_OV;
extern volatile uint8_t DCCT1_OC, GEN_SYNC, STF, FSW, FHW, RESET_TYPE;

//Fault Hardware
extern volatile uint8_t ACPT_FHW, GRPT_FHW, DCPT_FHW, CT_FHW, GD_FHW;
extern volatile uint8_t GRPT1_HWP, GRPT2_HWP, GRPT3_HWP;
extern volatile uint8_t ACPT1_HWP, ACPT2_HWP, ACPT3_HWP;
extern volatile uint8_t DCPT1_HWP, DCPT2_HWP;
extern volatile uint8_t CT1_HWP, CT234_HWP, CT56_HWP, CT78_HWP;
extern volatile uint8_t GD1_HWP, GD2_HWP;
extern volatile uint8_t FHW, Fault;
/*
extern volatile uint8_t FHW1, FHW2, FHW3;
extern volatile uint8_t ACPTS_HWP, ACPTR_HWP, DCPT2_HWP, IVCTT_HWP, IVCTS_HWP, IVCTR_HWP, DCCT1_HWP;
extern volatile uint8_t GDsp1F_HWP, GDS1F_HWP, GDR2F_HWP, GDR1F_HWP, GDT2F_HWP, GDT1F_HWP, GDS2F_HWP;
extern volatile uint8_t ACPTT_HWP, GDsp3F_HWP, GDsp2F_HWP, SPVP5_HWP, SPVN15_HWP, SPVP15_HWP, SPVP24_HWP;
*/

//Data Spare
extern volatile uint32_t spare;

void dataanalog(void);
void datadigital(void);
char dectohex(long int decimalNumber);
char signeddata(int data);
int findn(int num);

#endif /* DATAINVERTER_H_ */
