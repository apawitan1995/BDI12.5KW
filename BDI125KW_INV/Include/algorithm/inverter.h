/*
 * inverter.h
 *
 *  Created on: Mar 30, 2017
 *      Author: Mukhlish Ghany A
 */

#ifndef INVERTER_H_
#define INVERTER_H_

#include <DAVE3.h>
#include <arm_math.h>
#include "algorithm/fixed_operation.h"

extern int flag_phase;

//cek peripheral
//extern volatile int32_t pwm_set;
extern volatile uint8_t mode_inverter;
extern volatile uint8_t inverter_enable;
extern volatile int32_t pwm_peak_reff;
extern volatile int32_t pwm_peak;
extern volatile int32_t pwm_setA, pwm_setB, pwm_setC;

// Buat tes open loop
extern volatile int32_t w_fix;
//extern volatile int32_t Tetaref_fix;
extern volatile int32_t TetaSineA_fix, TetaSineB_fix, TetaSineC_fix;
extern volatile int32_t integSineA_fix, integSineB_fix, integSineC_fix;
extern volatile int32_t sinTetaA_fix, sinTetaB_fix, sinTetaC_fix;
extern volatile int32_t pwm_setA_fix, pwm_setB_fix, pwm_setC_fix;

//Data Acquistion
extern volatile int32_t DCPT2_fix;
extern volatile int32_t ACPT1_fix;
extern volatile int32_t ACPT2_fix;
extern volatile int32_t ACPT3_fix;
extern volatile int32_t GRPT1_fix;
extern volatile int32_t GRPT2_fix;
extern volatile int32_t GRPT3_fix;
extern volatile int32_t CT5_fix;
extern volatile int32_t CT2_fix;
extern volatile int32_t CT6_fix;
extern volatile int32_t CT7_fix;
extern volatile int32_t CT8_fix;

//----DARI ARIF----

// Buat PLL
#define Ki_pll_fix 343
#define Kp_pll_fix 40960

extern volatile int32_t PWMInv_fix_1;
extern volatile int32_t PWMInv_fix_2;
extern volatile int32_t volt_ref;

extern volatile float p_set ;
extern volatile float q_set ;			//untuk connect grid

extern volatile float Pow_Filt_1;
extern volatile float Q_Filt_1;
extern volatile float Pow_Filt_2;
extern volatile float Q_Filt_2;


// variabel droop
extern volatile int32_t deltafrad_fix_1;
extern volatile float deltaw_1;
extern volatile int32_t deltaw_fix_1;

extern volatile int32_t deltafrad_fix_2;
extern volatile float deltaw_2;
extern volatile int32_t deltaw_fix_2;

// variabel virtual impedance
extern volatile int l_impedance;

extern volatile int32_t Tetaref_fix;

extern volatile int32_t Tetaref_fix_1;

extern volatile int32_t volt_ref_1;
extern volatile float Pow_Filt_1;
extern volatile float Q_Filt_1;

extern volatile int32_t Tetaref_fix_2;

extern volatile int32_t volt_ref_2;
extern volatile float Pow_Filt_2;
extern volatile float Q_Filt_2;

//NAMBAH
extern volatile int32_t teta_manual_fix;
volatile int32_t errdeltaVcor_fix_1, errdeltaVcor_fix_2;
volatile int32_t voac_peak_fix_1, voac_peak_fix_2;

// variabel PLL
extern volatile int32_t Teta_PLL;
extern volatile int32_t integ_Vac_q_fix;
extern volatile int32_t integ1_fix, integ2_fix;
extern volatile int32_t wPLL_fix;
extern volatile int32_t delta_w_fix;

void PLL (void);
void power_calculation_1(void);
void droop_standalone_1 (void);
void virtual_impedance_1 (void);
void refgen (void);
void refgen_paralel_1 (void);
void voltage_controller_1 (void);
void power_calculation_2(void);
void droop_standalone_2 (void);
void virtual_impedance_2 (void);
void refgen_paralel_2 (void);
void voltage_controller_2 (void);

#endif /* INVERTER_H_ */
