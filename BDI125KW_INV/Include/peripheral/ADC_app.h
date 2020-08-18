/*
 * ADC_app.h
 *
 *  Created on: Dec 12, 2013
 *      Author: Hanif
 */

#ifndef ADC_APP_H_
#define ADC_APP_H_

#include <DAVE3.h>
#include "common/global.h"

//Definisi macro untuk DAVE ADC API
#define ADC_G0_Scan_API (ADC003_HandleType*)&ADC003_Handle0
#define ADC_G1_Scan_API (ADC003_HandleType*)&ADC003_Handle1
#define ADC_G2_Scan_API (ADC003_HandleType*)&ADC003_Handle2

#define ADC_G0CH1_CT2_Handler ADCCH001_Handle9
#define ADC_G0CH4_CT5_Handler ADCCH001_Handle0
#define ADC_G0CH5_CT6_Handler ADCCH001_Handle1
#define ADC_G0CH7_DCPT2_AINHandler ADCCH001_Handle8
#define ADC_G1CH4_CT7_Handler ADCCH001_Handle2
#define ADC_G1CH5_CT4_Handler ADCCH001_Handle3
#define ADC_G2CH2_ACPT1_AINHandler ADCCH001_Handle4
#define ADC_G2CH3_ACPT2_AINHandler ADCCH001_Handle5
#define ADC_G2CH5_GRPT1_AINHandler ADCCH001_Handle6
#define ADC_G2CH6_GRPT2_AINHandler ADCCH001_Handle7
#define ADC_G2CH7_GRPT3_AINHandler ADCCH001_Handle10

#define CT2_Result_Register 1
#define CT5_Result_Register 4
#define CT6_Result_Register 5
#define DCPT2_AIN_Result_Register 7
#define CT7_Result_Register 4
#define CT8_Result_Register 5
#define ACPT1_AIN_Result_Register 2
#define ACPT2_AIN_Result_Register 3
#define GRPT1_AIN_Result_Register 5
#define GRPT2_AIN_Result_Register 6
#define GRPT3_AIN_Result_Register 7

/*
#define VADC_REF 3.235f
#define ADCtoAnaVolt VADC_REF/4095.0f
#define AnaVolttoADC 4095.0f/VADC_REF

#define ADC_DCPTtoHV(x) (x-523)/5.5f
#define ADC_CTtoHV(x) (x-1724)/13.8f
#define ADC_ACPTtoHV(x) (x-1600)/3.03f
*/

#define	DCPT1_OFFSET 2455
#define	DCPT1_GRAD 2.899
#define	DCPT1_GRAD_FIX 353

#define DCPT2_OFFSET 2458
#define DCPT2_GRAD 2.890
#define	DCPT2_GRAD_FIX 354

#define ACPT1_OFFSET 2112
#define ACPT1_GRAD 3.145
#define ACPT1_GRAD_FIX 326

#define ACPT2_OFFSET 2109
#define ACPT2_GRAD 3.135
#define ACPT2_GRAD_FIX 327

#define ACPT3_OFFSET 2112
#define ACPT3_GRAD 3.145
#define ACPT3_GRAD_FIX 326

#define GRPT1_OFFSET 2112
#define GRPT1_GRAD 3.145
#define GRPT1_GRAD_FIX 326

#define GRPT2_OFFSET 2111
#define GRPT2_GRAD 3.135
#define GRPT2_GRAD_FIX 327

#define GRPT3_OFFSET 2106
#define GRPT3_GRAD 3.125
#define GRPT3_GRAD_FIX 328

//#define CT1_OFF 1810
#define CT1_GRAD -14.286
#define CT1_GRAD_FIX -72

//#define CT2_OFF 1676
#define CT2_GRAD -8.929
#define CT2_GRAD_FIX -115

//#define CT3_OFF 1672
#define CT3_GRAD 27.027
#define CT3_GRAD_FIX 38

//#define CT4_OFF 1673
#define CT4_GRAD 27.027
#define CT4_GRAD_FIX 38

//#define CT5_OFF 1666
#define CT5_GRAD 8.850
#define CT5_GRAD_FIX 116

//#define CT6_OFF 1656
#define CT6_GRAD 13.514
#define CT6_GRAD_FIX 78

//#define CT7_OFF 1797
#define CT7_GRAD 14.286
#define CT7_GRAD_FIX 72

//#define CT8_OFF 1797
#define CT8_GRAD 14.286
#define CT8_GRAD_FIX 72

extern volatile int32_t CT1_OFF;
extern volatile int32_t CT2_OFF;
extern volatile int32_t CT3_OFF;
extern volatile int32_t CT4_OFF;
extern volatile int32_t CT5_OFF;
extern volatile int32_t CT6_OFF;
extern volatile int32_t CT7_OFF;
extern volatile int32_t CT8_OFF;

//baru sampe sini kalibrasinya, tq ais belum
/*
#define TQ1_OFF 1761
#define TQ1_GRAD 14.286
#define TQ1_GRAD_FIX 71

#define TQ2_OFF 1738
#define TQ2_GRAD 14.348
#define TQ2_GRAD_FIX 71

#define AIS1_OFF 1738
#define AIS1_GRAD 14.348
#define AIS1_GRAD_FIX 71

#define AIS2_OFF 1738
#define AIS2_GRAD 14.348
#define AIS2_GRAD_FIX 71
*/
/*
extern volatile uint32_t ACPT1_OFFSET; // 2065
extern volatile uint32_t ACPT2_OFFSET; // 2059
extern volatile uint32_t ACPT3_OFFSET;
extern volatile uint32_t GRPT1_OFFSET;
extern volatile uint32_t GRPT2_OFFSET;
extern volatile uint32_t GRPT3_OFFSET;
*/

//extern volatile uint32_t DCPT1_AIN_Result;
extern volatile uint32_t DCPT2_AIN_Result;
extern volatile uint32_t ACPT1_AIN_Result;
extern volatile uint32_t ACPT2_AIN_Result;
//extern volatile uint32_t ACPT3_AIN_Result;
extern volatile uint32_t GRPT1_AIN_Result;
extern volatile uint32_t GRPT2_AIN_Result;
extern volatile uint32_t GRPT3_AIN_Result;
extern volatile uint32_t CT1_Result;
extern volatile uint32_t CT2_Result;
extern volatile uint32_t CT3_Result;
extern volatile uint32_t CT4_Result;
extern volatile uint32_t CT5_Result;
extern volatile uint32_t CT6_Result;
extern volatile uint32_t CT7_Result;
extern volatile uint32_t CT8_Result;
//extern volatile uint32_t TQ1_AIN_Result;
//extern volatile uint32_t TQ2_AIN_Result;
//extern volatile uint32_t AIS1_AIN_Result;
//extern volatile uint32_t AIS2_AIN_Result;

void ADC_Init(void);
void ADC_G0_Init(void);
void ADC_G1_Init(void);
void ADC_G2_Init(void);

void ADC_G0_Queue_Init(void);
void ADC_G1_Scan_Init(void);
void ADC_G2_Scan_Init(void);
void ADC_Background_Init(void);

void ADC_SWScan_Conv(ADC003_HandleType HandlePtr);
void ADC_SWBackground_Conv(void);

#endif /* ADC_APP_H_ */
