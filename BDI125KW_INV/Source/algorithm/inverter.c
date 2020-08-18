/*
 * inverter.c
 *
 *  Created on: Mar 30, 2017
 *      Author: Mukhlish Ghany A
 */

#include "algorithm/inverter.h"

#include <DAVE3.h>
#include <arm_math.h>
#include "common/global.h"
#include "peripheral/ADC_app.h"
#include "peripheral/PWM_app.h"

#include <Stdlib.h>
#include <String.h>
#include <Stdint.h>

int flag_phase=1;

// Cek peripheral
volatile uint8_t mode_inverter = 2;
volatile uint8_t inverter_enable = 0;
volatile int32_t pwm_peak_reff;
volatile int32_t pwm_peak = 800;
volatile int32_t pwm_setA, pwm_setB, pwm_setC  = 3749;

// Buat tes open loop
volatile int32_t w_fix = 0;
//volatile int32_t Tetaref_fix;
volatile int32_t TetaSineA_fix, TetaSineB_fix, TetaSineC_fix;
volatile int32_t integSineA_fix, integSineB_fix, integSineC_fix;
volatile int32_t sinTetaA_fix, sinTetaB_fix, sinTetaC_fix;
volatile int32_t pwm_setA_fix, pwm_setB_fix, pwm_setC_fix  = 0;

// Data acquisition
volatile int32_t DCPT2_fix = 0;
volatile int32_t ACPT1_fix = 0;
volatile int32_t ACPT2_fix = 0;
volatile int32_t ACPT3_fix = 0;
volatile int32_t GRPT1_fix = 0;
volatile int32_t GRPT2_fix = 0;
volatile int32_t GRPT3_fix = 0;
volatile int32_t CT2_fix = 0;
volatile int32_t CT5_fix = 0;
volatile int32_t CT6_fix = 0;
volatile int32_t CT7_fix = 0;
volatile int32_t CT8_fix = 0;

//----DARI ARIF----

volatile float p_set = 0;
volatile float q_set = 0;			//untuk connect grid


// variabel PLL
volatile int32_t VacPLL_fix,Vac_b_fix;
volatile int32_t TetaSine_PLL_fix,TetaCos_PLL_fix;
volatile int32_t Teta_PLL;
volatile int32_t integSine_PLL_fix,integCos_PLL_fix;
volatile int32_t sinTeta_PLL_fix,cosTeta_PLL_fix;
volatile int32_t Vac_d_fix, Vac_q_fix;
volatile int32_t integ_Vac_q_fix;
volatile int32_t Vacw_fix;
volatile int32_t wPLL_fix;
volatile int32_t wref_fix = 329420636;//50 HZ //329420636;
volatile int32_t integ1_fix, integ2_fix;
volatile int32_t delta_w_fix;


// variabel power calculation
volatile int32_t prePow_fix_1;
volatile int32_t Pow_Filt_fix_1;
volatile int32_t Q_Filt_fix_1;
volatile int32_t preQ_fix_1;
volatile float Pow_Filt_1;
volatile float Q_Filt_1;

volatile int32_t prePow_fix_2;
volatile int32_t Pow_Filt_fix_2;
volatile int32_t Q_Filt_fix_2;
volatile int32_t preQ_fix_2;
volatile float Pow_Filt_2;
volatile float Q_Filt_2;

// variabel droop
volatile int32_t deltafrad_fix_1;
volatile float deltaw_1;
volatile int32_t deltaw_fix_1;
volatile float Pref_1;
volatile float Qref_1;

volatile int32_t deltafrad_fix_2;
volatile float deltaw_2;
volatile int32_t deltaw_fix_2;
volatile float Pref_2;
volatile float Qref_2;

//variabel voltage controller
volatile int32_t VoACreff_fix_1;
volatile int32_t VoACreff_fix_2;
#define LIM_INTV_INV_FIX20 2097152000
volatile int32_t errVoAC_fix_1 = 0;
volatile int32_t integ_errVoAC_fix_1 = 0;
volatile int32_t ILreffAC_fix_1 = 0;
volatile int32_t errVoAC_d_fix_1, errVoAC_q_fix_1;
volatile int32_t integ_errVoAC_d_fix_1, integ_errVoAC_q_fix_1;
volatile int32_t ILreffAC_d_fix_1, ILreffAC_q_fix_1;
volatile int32_t VoAC_fix_1;
volatile int32_t errIac_1 = 0;
volatile int32_t integ_errIac_1 = 0;

volatile int32_t errVoAC_fix_2 = 0;
volatile int32_t integ_errVoAC_fix_2 = 0;
volatile int32_t ILreffAC_fix_2 = 0;
volatile int32_t errVoAC_d_fix_2, errVoAC_q_fix_2;
volatile int32_t integ_errVoAC_d_fix_2, integ_errVoAC_q_fix_2;
volatile int32_t ILreffAC_d_fix_2, ILreffAC_q_fix_2;
volatile int32_t VoAC_fix_2;
volatile int32_t errIac_2 = 0;
volatile int32_t integ_errIac_2 = 0;

volatile int32_t ki_il = 0;
volatile int32_t PWMInv_fix_1;
volatile int32_t PWMInv_fix_2;
volatile int32_t volt_ref = 10;

// variabel virtual impedance
volatile long long IacLd_fix_1 = 0;
volatile long long IacLd_y_fix_1 = 0;
volatile long long IacLd_yz_fix_1 = 0;
volatile long long IacLd_yz1_fix_1 = 0;
volatile long long IacLd_z1_fix_1 = 0;
volatile long long IacLdo_fix_1 = 0;
volatile long long IacLdo_z1_fix_1 = 0;

volatile long long IacLd_fix_2 = 0;
volatile long long IacLd_y_fix_2 = 0;
volatile long long IacLd_yz_fix_2 = 0;
volatile long long IacLd_yz1_fix_2 = 0;
volatile long long IacLd_z1_fix_2 = 0;
volatile long long IacLdo_fix_2 = 0;
volatile long long IacLdo_z1_fix_2 = 0;

volatile int32_t b0_Ld_fix = 168;
volatile int32_t a1_Ld_fix = -687;	//Q10
volatile int l_impedance = 5; //10;


// untuk refgen

volatile int32_t TetaSine_fix_1, TetaCos_fix_1, integSine_fix_1, integCos_fix_1;
volatile int32_t sinTeta_fix_1, cosTeta_fix_1;
volatile int32_t Tetaref_fix_1;

volatile int32_t TetaSine_fix, TetaCos_fix, integSine_fix, integCos_fix;
volatile int32_t sinTeta_fix, cosTeta_fix;
volatile int32_t Tetaref_fix;

volatile int32_t TetaSine_fix_2, TetaCos_fix_2, integSine_fix_2, integCos_fix_2;
volatile int32_t sinTeta_fix_2, cosTeta_fix_2;
volatile int32_t Tetaref_fix_2;

//NAMBAH
volatile int32_t teta_manual_fix = 0;
volatile int32_t errdeltaVcor_fix_1, errdeltaVcor_fix_2;
volatile int32_t voac_peak_fix_1, voac_peak_fix_2;


void PLL (void)
{
	//if (flag_phase == 1 || flag_phase == 4){
		VacPLL_fix = GRPT2_fix/320;
	//}
	//else
	if (flag_phase == 2 || flag_phase == 3){
		VacPLL_fix = GRPT3_fix/320;
	}

	TetaSine_PLL_fix = Teta_PLL;	// 20
	//compute sine
	if( TetaSine_PLL_fix < 0)
	{
		integSine_PLL_fix = 1304*(TetaSine_PLL_fix>>10)+(415*(TetaSine_PLL_fix>>10)>>10)*(TetaSine_PLL_fix>>10); // 20 bit
		if (integSine_PLL_fix <0) {integSine_PLL_fix = 261*(((integSine_PLL_fix>>10)*(-integSine_PLL_fix>>10)-integSine_PLL_fix)>>10)+integSine_PLL_fix;}
		else {integSine_PLL_fix = 261*(((integSine_PLL_fix>>10)*(integSine_PLL_fix>>10)-integSine_PLL_fix)>>10)+integSine_PLL_fix;}
	}
	else
	{
		integSine_PLL_fix = 1304*(TetaSine_PLL_fix>>10)-(415*(TetaSine_PLL_fix>>10)>>10)*(TetaSine_PLL_fix>>10); // 20 bit
		if (integSine_PLL_fix <0) {integSine_PLL_fix = 261*(((integSine_PLL_fix>>10)*(-integSine_PLL_fix>>10)-integSine_PLL_fix)>>10)+integSine_PLL_fix;}
		else {integSine_PLL_fix = 261*(((integSine_PLL_fix>>10)*(integSine_PLL_fix>>10)-integSine_PLL_fix)>>10)+integSine_PLL_fix;}
	}

	//compute cosine
	TetaCos_PLL_fix = TetaSine_PLL_fix + 1647100;	// 20
	if (TetaCos_PLL_fix > 3294206 ) {TetaCos_PLL_fix -= 6588413;}

	if( TetaCos_PLL_fix < 0)
	{
		integCos_PLL_fix = 1304*(TetaCos_PLL_fix>>10)+(415*(TetaCos_PLL_fix>>10)>>10)*(TetaCos_PLL_fix>>10); // 20 bit
		if (integCos_PLL_fix <0) {integCos_PLL_fix = 261*(((integCos_PLL_fix>>10)*(-integCos_PLL_fix>>10)-integCos_PLL_fix)>>10)+integCos_PLL_fix;}
		else {integCos_PLL_fix = 261*(((integCos_PLL_fix>>10)*(integCos_PLL_fix>>10)-integCos_PLL_fix)>>10)+integCos_PLL_fix;}
	}
	else
	{
		integCos_PLL_fix = 1304*(TetaCos_PLL_fix>>10)-(415*(TetaCos_PLL_fix>>10)>>10)*(TetaCos_PLL_fix>>10); // 20 bit
		if (integCos_PLL_fix <0) {integCos_PLL_fix = 261*(((integCos_PLL_fix>>10)*(-integCos_PLL_fix>>10)-integCos_PLL_fix)>>10)+integCos_PLL_fix;}
		else {integCos_PLL_fix = 261*(((integCos_PLL_fix>>10)*(integCos_PLL_fix>>10)-integCos_PLL_fix)>>10)+integCos_PLL_fix;}
	}
	// Trigonomethric Approximation END Here

	sinTeta_PLL_fix = integSine_PLL_fix>>10; //20-10
	cosTeta_PLL_fix = integCos_PLL_fix>>10;

	// ab to dq transform
	Vac_d_fix = VacPLL_fix*sinTeta_PLL_fix - (Vac_b_fix>>10)*cosTeta_PLL_fix;  //20 bit err, 1048576
	Vac_q_fix = VacPLL_fix*cosTeta_PLL_fix + (Vac_b_fix>>10)*sinTeta_PLL_fix;

	integ_Vac_q_fix = integ_Vac_q_fix + Ki_pll_fix*(Vac_q_fix>>10);  // 20 bit err, vs Ki_pll_fix*(Vac_q_fix>>10)
	delta_w_fix = integ_Vac_q_fix + Kp_pll_fix*(Vac_q_fix>>10);


	wPLL_fix = wref_fix + delta_w_fix; //20 bit err, max 400M

	// Limit frequency of PLL Upper = 55 Hz Lower 45 Hz
	if(wPLL_fix > 362362700) {wPLL_fix = 362362700;}
	else if (wPLL_fix < 296478572) {wPLL_fix = 296478572;}

	Teta_PLL = Teta_PLL + (wPLL_fix/16000); //20 bit
	if(Teta_PLL > 3294206) {Teta_PLL -= 6588413;}
	else if (Teta_PLL < -3294206) {Teta_PLL+=6588413;}

	//SOGI fixed point
	Vacw_fix = VacPLL_fix*(wPLL_fix>>10); // 10+(20-10) =20
	integ1_fix = integ1_fix + Vacw_fix/16000; // 20 bit err
	Vac_b_fix = integ1_fix - (VacPLL_fix<<10) - integ2_fix;  // 20
	integ2_fix = integ2_fix + (Vac_b_fix>>10)*(wPLL_fix>>10)/16000; //max 2M

}


void power_calculation_1(void)
{
	static int32_t prePow_z1_fix_1;
	static int32_t Pow_Filt_z1_fix_1;
	static int32_t Q_Filt_z1_fix_1;
	static int32_t preQ_z1_fix_1;
/*
prePow_fix_1 = ((ACPT2_fix>>10)*CT7_fix)>>2; //Q8
//prePow_fix_1 = (((ACPT2_fix+ACPT1_fix)>>11)*(CT7_fix + CT8_fix)>>1)>>2; //Q8
Pow_Filt_fix_1 = prePow_fix_1*1.0043 + 1.0043*prePow_z1_fix_1+1021.99*Pow_Filt_z1_fix_1; //Q18, b0 = 0.0015683328, a1 = -0.99686333
Pow_Filt_1 = fixed2float(Pow_Filt_fix_1,18);
prePow_z1_fix_1 = prePow_fix_1; //Q8
Pow_Filt_z1_fix_1 = Pow_Filt_fix_1>>10; //Q8	//after filtering , fc = 5 Hz, p to  8 kilo, fsamp 16kHz

preQ_fix_1 = ((Vac_b_fix>>14)*CT7_fix*5)>>2; //Q8
Q_Filt_fix_1 = preQ_fix_1*1.0043 + 1.0043*preQ_z1_fix_1+1021.99*Q_Filt_z1_fix_1; //Q18, b0 = 0.0015683328, a1 = -0.99686333
Q_Filt_1 = fixed2float(Q_Filt_fix_1,18);
preQ_z1_fix_1 = preQ_fix_1; //Q8
Q_Filt_z1_fix_1 = Q_Filt_fix_1>>10; //Q8	//after filtering , fc = 5 Hz, Q to  8 kilo, fsamp 16kHz
*/

	prePow_fix_1 = ((ACPT2_fix>>10)*CT7_fix)>>2; //Q8
	//prePow_fix_1 = (((ACPT2_fix+ACPT1_fix)>>11)*(CT7_fix + CT8_fix)>>1)>>2; //Q8
	Pow_Filt_fix_1 = prePow_fix_1*1.606 + 1.606*prePow_z1_fix_1+1020.79*Pow_Filt_z1_fix_1; //Q18, b0 = 0.0015683328, a1 = -0.99686333
	Pow_Filt_1 = fixed2float(Pow_Filt_fix_1,18);
	prePow_z1_fix_1 = prePow_fix_1; //Q8
	Pow_Filt_z1_fix_1 = Pow_Filt_fix_1>>10; //Q8	//after filtering , p to  8 kilo, fsamp 4kHz

	preQ_fix_1 = ((Vac_b_fix>>14)*CT7_fix*5)>>2; //Q8
	Q_Filt_fix_1 = preQ_fix_1*1.606 + 1.606*preQ_z1_fix_1+1020.79*Q_Filt_z1_fix_1; //Q18, b0 = 0.0015683328, a1 = -0.99686333
	Q_Filt_1 = fixed2float(Q_Filt_fix_1,18);
	preQ_z1_fix_1 = preQ_fix_1; //Q8
	Q_Filt_z1_fix_1 = Q_Filt_fix_1>>10; //Q8	//after filtering , Q to  8 kilo, fsamp 4kHz

}

void power_calculation_2(void)
{
	static int32_t prePow_z1_fix_2;
	static int32_t Pow_Filt_z1_fix_2;
	static int32_t Q_Filt_z1_fix_2;
	static int32_t preQ_z1_fix_2;
/*
prePow_fix_2 = ((ACPT1_fix>>10)*CT8_fix)>>2; //Q8
Pow_Filt_fix_2 = prePow_fix_2*1.0043 + 1.0043*prePow_z1_fix_2+1021.99*Pow_Filt_z1_fix_2; //Q18, b0 = 0.0015683328, a1 = -0.99686333
Pow_Filt_2 = fixed2float(Pow_Filt_fix_2,18);
prePow_z1_fix_2 = prePow_fix_2; //Q8
Pow_Filt_z1_fix_2 = Pow_Filt_fix_2>>10; //Q8	//after filtering , fc = 5 Hz, p to  8 kilo, fsamp 16kHz

preQ_fix_2 = ((Vac_b_fix>>14)*CT8_fix*5)>>2; //Q8
Q_Filt_fix_2 = preQ_fix_2*1.0043 + 1.0043*preQ_z1_fix_2+1021.99*Q_Filt_z1_fix_2; //Q18, b0 = 0.0015683328, a1 = -0.99686333
Q_Filt_2 = fixed2float(Q_Filt_fix_2,18);
preQ_z1_fix_2 = preQ_fix_2; //Q8
Q_Filt_z1_fix_2 = Q_Filt_fix_2>>10; //Q8	//after filtering , fc = 5 Hz, Q to  8 kilo, fsamp 16kHz
*/
	prePow_fix_2 = ((ACPT1_fix>>10)*CT8_fix)>>2; //Q8
	Pow_Filt_fix_2 = prePow_fix_2*1.606 + 1.606*prePow_z1_fix_2+1020.79*Pow_Filt_z1_fix_2; //Q18, b0 = 0.0015683328, a1 = -0.99686333
	Pow_Filt_2 = fixed2float(Pow_Filt_fix_2,18);
	prePow_z1_fix_2 = prePow_fix_2; //Q8
	Pow_Filt_z1_fix_2 = Pow_Filt_fix_2>>10; //Q8	//after filtering , p to  8 kilo, fsamp 4kHz

	preQ_fix_2 = ((Vac_b_fix>>14)*CT8_fix*5)>>2; //Q8
	Q_Filt_fix_2 = preQ_fix_2*1.606 + 1.606*preQ_z1_fix_2+1020.79*Q_Filt_z1_fix_2; //Q18, b0 = 0.0015683328, a1 = -0.99686333
	Q_Filt_2 = fixed2float(Q_Filt_fix_2,18);
	preQ_z1_fix_2 = preQ_fix_2; //Q8
	Q_Filt_z1_fix_2 = Q_Filt_fix_2>>10; //Q8	//after filtering , Q to  8 kilo, fsamp 4kHz
}



void droop_standalone_1 (void)
{
	Pref_1        = p_set;

	if (Pref_1 > 6400){Pref_1 = 6400;}
	else if (Pref_1 < -5000){Pref_1 = -5000;}

	deltaw_1 = 0.00062832 * (Pref_1-Pow_Filt_1); //0.00062832
	deltafrad_fix_1 = float2fixed(deltaw_1,20);
	deltaw_fix_1 = deltaw_fix_1 + (deltafrad_fix_1/16000); //20 bit, nanti coba di kali 7, sekarang blom
	if(deltaw_fix_1 > 3294206) {deltaw_fix_1 -= 6588413;}
	else if (deltaw_fix_1 < -3294206) {deltaw_fix_1+=6588413;}
}

void droop_standalone_2 (void)
{
	Pref_2        = p_set;

	if (Pref_2 > 6400){Pref_2 = 6400;}
	else if (Pref_2 < -5000){Pref_2 = -5000;}

	deltaw_2 = 0.00062832 * (Pref_2-Pow_Filt_2); //0.00062832
	deltafrad_fix_2 = float2fixed(deltaw_2,20);
	deltaw_fix_2 = deltaw_fix_2 + (deltafrad_fix_2/16000); //20 bit, nanti coba di kali 7, sekarang blom
	if(deltaw_fix_2 > 3294206) {deltaw_fix_2 -= 6588413;}
	else if (deltaw_fix_2 < -3294206) {deltaw_fix_2 +=6588413;}
}




void voltage_controller_1 (void)
{
	VoAC_fix_1 = ACPT2_fix; //10

		/* ---------------- DQ transform -------------*/
		errVoAC_d_fix_1 = ((VoACreff_fix_1>>10) - VoAC_fix_1)*cosTeta_fix_1; //Q20	 = 10+10
		integ_errVoAC_d_fix_1 = integ_errVoAC_d_fix_1 + ((errVoAC_d_fix_1>>10)*32);//96); //1000 Q20
		if(integ_errVoAC_d_fix_1 > LIM_INTV_INV_FIX20){integ_errVoAC_d_fix_1 = LIM_INTV_INV_FIX20;}
		if(integ_errVoAC_d_fix_1 < -LIM_INTV_INV_FIX20){integ_errVoAC_d_fix_1 = -LIM_INTV_INV_FIX20;}
		ILreffAC_d_fix_1 = integ_errVoAC_d_fix_1 + (errVoAC_d_fix_1>>10)*1;

		errVoAC_q_fix_1 = -((VoACreff_fix_1>>10) - VoAC_fix_1)*sinTeta_fix_1;
		integ_errVoAC_q_fix_1 = integ_errVoAC_q_fix_1 + ((errVoAC_q_fix_1>>10)*32);//96); // 1000
		if(integ_errVoAC_q_fix_1 > LIM_INTV_INV_FIX20){integ_errVoAC_q_fix_1 = LIM_INTV_INV_FIX20;}
		if(integ_errVoAC_q_fix_1 < -LIM_INTV_INV_FIX20){integ_errVoAC_q_fix_1 = -LIM_INTV_INV_FIX20;}
		ILreffAC_q_fix_1 = integ_errVoAC_q_fix_1 + (errVoAC_q_fix_1>>10)*1;

		ILreffAC_fix_1 = (ILreffAC_d_fix_1>>10)*cosTeta_fix_1 - (ILreffAC_q_fix_1>>10)*sinTeta_fix_1;

		errIac_1 = ILreffAC_fix_1 - (CT5_fix<<10); //Q20
			integ_errIac_1 += ((errIac_1>>10)*ki_il); //Q20
			if (integ_errIac_1 > 13107200 ){integ_errIac_1 = 13107200;}		// Limit integrator to +- 12.5f
			else if (integ_errIac_1 < -13107200){integ_errIac_1 = -13107200;}

			PWMInv_fix_1 = 0*integ_errIac_1 + ((errIac_1>>10)*3); //Q20


}

void voltage_controller_2 (void)
{
	VoAC_fix_2 = ACPT1_fix; //10

		/* ---------------- DQ transform -------------*/
		errVoAC_d_fix_2 = ((VoACreff_fix_2>>10) - VoAC_fix_2)*cosTeta_fix_2; //Q20	 = 10+10
		integ_errVoAC_d_fix_2 = integ_errVoAC_d_fix_2 + ((errVoAC_d_fix_2>>10)*32);//96); //1000 Q20
		if(integ_errVoAC_d_fix_2 > LIM_INTV_INV_FIX20){integ_errVoAC_d_fix_2 = LIM_INTV_INV_FIX20;}
		if(integ_errVoAC_d_fix_2 < -LIM_INTV_INV_FIX20){integ_errVoAC_d_fix_2 = -LIM_INTV_INV_FIX20;}
		ILreffAC_d_fix_2 = integ_errVoAC_d_fix_2 + (errVoAC_d_fix_2>>10)*1;

		errVoAC_q_fix_2 = -((VoACreff_fix_2>>10) - VoAC_fix_2)*sinTeta_fix_2;
		integ_errVoAC_q_fix_2 = integ_errVoAC_q_fix_2 + ((errVoAC_q_fix_2>>10)*32);//96); // 1000
		if(integ_errVoAC_q_fix_2 > LIM_INTV_INV_FIX20){integ_errVoAC_q_fix_2 = LIM_INTV_INV_FIX20;}
		if(integ_errVoAC_q_fix_2 < -LIM_INTV_INV_FIX20){integ_errVoAC_q_fix_2 = -LIM_INTV_INV_FIX20;}
		ILreffAC_q_fix_2 = integ_errVoAC_q_fix_2 + (errVoAC_q_fix_2>>10)*1;

		ILreffAC_fix_2 = (ILreffAC_d_fix_2>>10)*cosTeta_fix_2 - (ILreffAC_q_fix_2>>10)*sinTeta_fix_2;

		errIac_2 = ILreffAC_fix_2 - (-(CT2_fix<<10)); //Q20
			integ_errIac_2 += ((errIac_2>>10)*ki_il); //Q20
			if (integ_errIac_2 > 13107200 ){integ_errIac_2 = 13107200;}		// Limit integrator to +- 12.5f
			else if (integ_errIac_2 < -13107200){integ_errIac_2 = -13107200;}

			PWMInv_fix_2 = 0*integ_errIac_2 + ((errIac_2>>10)*3); //Q20


}

void virtual_impedance_1 (void)
{
	//----------------------------------Virtual Impedance------------------------------
	IacLd_fix_1 = (CT7_fix)*l_impedance; //Q20 = 10+10 //Lvir = 5mH
	IacLd_y_fix_1 = (((IacLd_fix_1) - (IacLd_z1_fix_1))*16000); //Q20
	IacLdo_fix_1 = b0_Ld_fix*IacLd_y_fix_1 + b0_Ld_fix*IacLd_yz1_fix_1 - a1_Ld_fix*IacLdo_z1_fix_1; //Q30

	IacLd_z1_fix_1 = IacLd_fix_1;
	IacLd_yz1_fix_1 = IacLd_y_fix_1;
	IacLdo_z1_fix_1 = (IacLdo_fix_1>>10);

	VoACreff_fix_1 -= (IacLdo_fix_1>>10);

}

void virtual_impedance_2 (void)
{
	//----------------------------------Virtual Impedance------------------------------
	IacLd_fix_2 = (CT8_fix)*l_impedance; //Q20 = 10+10 //Lvir = 5mH
	IacLd_y_fix_2 = (((IacLd_fix_2) - (IacLd_z1_fix_2))*16000); //Q20
	IacLdo_fix_2 = b0_Ld_fix*IacLd_y_fix_2 + b0_Ld_fix*IacLd_yz1_fix_2 - a1_Ld_fix*IacLdo_z1_fix_2; //Q30

	IacLd_z1_fix_2 = IacLd_fix_2;
	IacLd_yz1_fix_2 = IacLd_y_fix_2;
	IacLdo_z1_fix_2 = (IacLdo_fix_2>>10);

	VoACreff_fix_2 -= (IacLdo_fix_2>>10);

}

void refgen (void)
{
	// ----- Teta Reference Generator ------

	Tetaref_fix = Tetaref_fix + (wref_fix/16000); //20 bit
	if(Tetaref_fix > 3294206) {Tetaref_fix -= 6588413;}
	else if (Tetaref_fix < -3294206) {Tetaref_fix+=6588413;}
/*
	// voltage reference generator
	TetaSine_fix = Tetaref_fix;	// 20 using Tetaref_fix as an input for trigo. func.
	if(TetaSine_fix > 3294206) {TetaSine_fix -= 6588413;}
	else if (TetaSine_fix < -3294206) {TetaSine_fix+=6588413;}

	//compute sine
		if( TetaSine_fix < 0)
		{
			integSine_fix = 1304*(TetaSine_fix>>10)+(415*(TetaSine_fix>>10)>>10)*(TetaSine_fix>>10); // 20 bit
			if (integSine_fix <0) {integSine_fix = 261*(((integSine_fix>>10)*(-integSine_fix>>10)-integSine_fix)>>10)+integSine_fix;}
			else {integSine_fix = 261*(((integSine_fix>>10)*(integSine_fix>>10)-integSine_fix)>>10)+integSine_fix;}
		}
		else
		{
			integSine_fix = 1304*(TetaSine_fix>>10)-(415*(TetaSine_fix>>10)>>10)*(TetaSine_fix>>10); // 20 bit
			if (integSine_fix <0) {integSine_fix = 261*(((integSine_fix>>10)*(-integSine_fix>>10)-integSine_fix)>>10)+integSine_fix;}
			else {integSine_fix = 261*(((integSine_fix>>10)*(integSine_fix>>10)-integSine_fix)>>10)+integSine_fix;}
		}

		//compute cosine
		TetaCos_fix = TetaSine_fix + 1647100;	// 20
		if (TetaCos_fix > 3294206 ) {TetaCos_fix -= 6588413;}

		if( TetaCos_fix < 0)
		{
			integCos_fix = 1304*(TetaCos_fix>>10)+(415*(TetaCos_fix>>10)>>10)*(TetaCos_fix>>10); // 20 bit
			if (integCos_fix <0) {integCos_fix = 261*(((integCos_fix>>10)*(-integCos_fix>>10)-integCos_fix)>>10)+integCos_fix;}
			else {integCos_fix = 261*(((integCos_fix>>10)*(integCos_fix>>10)-integCos_fix)>>10)+integCos_fix;}
		}

		else
		{
			integCos_fix = 1304*(TetaCos_fix>>10)-(415*(TetaCos_fix>>10)>>10)*(TetaCos_fix>>10); // 20 bit
			if (integCos_fix <0) {integCos_fix = 261*(((integCos_fix>>10)*(-integCos_fix>>10)-integCos_fix)>>10)+integCos_fix;}
			else {integCos_fix = 261*(((integCos_fix>>10)*(integCos_fix>>10)-integCos_fix)>>10)+integCos_fix;}
		}

		sinTeta_fix_1 = integSine_fix>>10; //20-10
		cosTeta_fix_1 = integCos_fix>>10;

		sinTeta_fix_2 = integSine_fix>>10; //20-10
		cosTeta_fix_2 = integSine_fix>>10; //20-10

	VoACreff_fix_1 = (volt_ref*1024)*sinTeta_fix_1;
	VoACreff_fix_2 = (volt_ref*1024)*sinTeta_fix_2;
*/
}

void refgen_paralel_1 (void)
{
	//Tetaref_fix_1 = Teta_PLL + deltaw_fix_1 + teta_manual_fix;
	Tetaref_fix_1 = Tetaref_fix + deltaw_fix_1 + teta_manual_fix;

	if (volt_ref > 340){volt_ref = 340;}
	else if (volt_ref < 0){volt_ref = 0;}

	voac_peak_fix_1 = (volt_ref<<10) + errdeltaVcor_fix_1; //Ditambah Droop Q

	// voltage reference generator
	TetaSine_fix_1 = Tetaref_fix_1;	// 20 using Tetaref_fix as an input for trigo. func.
	if(TetaSine_fix_1 > 3294206) {TetaSine_fix_1 -= 6588413;}
	else if (TetaSine_fix_1 < -3294206) {TetaSine_fix_1+=6588413;}

	//compute sine
		if( TetaSine_fix_1 < 0)
		{
			integSine_fix_1 = 1304*(TetaSine_fix_1>>10)+(415*(TetaSine_fix_1>>10)>>10)*(TetaSine_fix_1>>10); // 20 bit
			if (integSine_fix_1 <0) {integSine_fix_1 = 261*(((integSine_fix_1>>10)*(-integSine_fix_1>>10)-integSine_fix_1)>>10)+integSine_fix_1;}
			else {integSine_fix_1 = 261*(((integSine_fix_1>>10)*(integSine_fix_1>>10)-integSine_fix_1)>>10)+integSine_fix_1;}
		}
		else
		{
			integSine_fix_1 = 1304*(TetaSine_fix_1>>10)-(415*(TetaSine_fix_1>>10)>>10)*(TetaSine_fix_1>>10); // 20 bit
			if (integSine_fix_1 <0) {integSine_fix_1 = 261*(((integSine_fix_1>>10)*(-integSine_fix_1>>10)-integSine_fix_1)>>10)+integSine_fix_1;}
			else {integSine_fix_1 = 261*(((integSine_fix_1>>10)*(integSine_fix_1>>10)-integSine_fix_1)>>10)+integSine_fix_1;}
		}

		//compute cosine
		TetaCos_fix_1 = TetaSine_fix_1 + 1647100;	// 20
		if (TetaCos_fix_1 > 3294206 ) {TetaCos_fix_1 -= 6588413;}

		if( TetaCos_fix_1 < 0)
		{
			integCos_fix_1 = 1304*(TetaCos_fix_1>>10)+(415*(TetaCos_fix_1>>10)>>10)*(TetaCos_fix_1>>10); // 20 bit
			if (integCos_fix_1 <0) {integCos_fix_1 = 261*(((integCos_fix_1>>10)*(-integCos_fix_1>>10)-integCos_fix_1)>>10)+integCos_fix_1;}
			else {integCos_fix_1 = 261*(((integCos_fix_1>>10)*(integCos_fix_1>>10)-integCos_fix_1)>>10)+integCos_fix_1;}
		}

		else
		{
			integCos_fix_1 = 1304*(TetaCos_fix_1>>10)-(415*(TetaCos_fix_1>>10)>>10)*(TetaCos_fix_1>>10); // 20 bit
			if (integCos_fix_1 <0) {integCos_fix_1 = 261*(((integCos_fix_1>>10)*(-integCos_fix_1>>10)-integCos_fix_1)>>10)+integCos_fix_1;}
			else {integCos_fix_1 = 261*(((integCos_fix_1>>10)*(integCos_fix_1>>10)-integCos_fix_1)>>10)+integCos_fix_1;}
		}

	//if (flag_phase == 1 || flag_phase == 4){
		sinTeta_fix_1 = integSine_fix_1>>10; //20-10
		cosTeta_fix_1 = integCos_fix_1>>10;
	//}
	//else
	if (flag_phase == 2){
		sinTeta_fix_1	= (((integSine_fix_1>>10)*(-512)) - ((integCos_fix_1>>10)*887))>>10;
		cosTeta_fix_1	= (((integCos_fix_1>>10)*(-512)) + ((integSine_fix_1>>10)*887))>>10;
	}
	else if (flag_phase == 3){
		sinTeta_fix_1	= (((integSine_fix_1>>10)*(-512)) + ((integCos_fix_1>>10)*887))>>10;
		cosTeta_fix_1	= (((integCos_fix_1>>10)*(-512)) - ((integSine_fix_1>>10)*887))>>10;
	}

	VoACreff_fix_1 = voac_peak_fix_1*sinTeta_fix_1;
}

void refgen_paralel_2 (void)
{
	//Tetaref_fix_2 = Teta_PLL + deltaw_fix_2 + teta_manual_fix;
	Tetaref_fix_2 = Tetaref_fix + deltaw_fix_2 + teta_manual_fix;

	if (volt_ref > 340){volt_ref = 340;}
	else if (volt_ref < 0){volt_ref = 0;}

	voac_peak_fix_2 = (volt_ref<<10) + errdeltaVcor_fix_2; //Ditambah Droop Q

	// voltage reference generator
	TetaSine_fix_2 = Tetaref_fix_2;	// 20 using Tetaref_fix as an input for trigo. func.
	if(TetaSine_fix_2 > 3294206) {TetaSine_fix_2 -= 6588413;}
	else if (TetaSine_fix_2 < -3294206) {TetaSine_fix_2+=6588413;}

	//compute sine
		if( TetaSine_fix_2 < 0)
		{
			integSine_fix_2 = 1304*(TetaSine_fix_2>>10)+(415*(TetaSine_fix_2>>10)>>10)*(TetaSine_fix_2>>10); // 20 bit
			if (integSine_fix_2 <0) {integSine_fix_2 = 261*(((integSine_fix_2>>10)*(-integSine_fix_2>>10)-integSine_fix_2)>>10)+integSine_fix_2;}
			else {integSine_fix_2 = 261*(((integSine_fix_2>>10)*(integSine_fix_2>>10)-integSine_fix_2)>>10)+integSine_fix_2;}
		}
		else
		{
			integSine_fix_2 = 1304*(TetaSine_fix_2>>10)-(415*(TetaSine_fix_2>>10)>>10)*(TetaSine_fix_2>>10); // 20 bit
			if (integSine_fix_2 <0) {integSine_fix_2 = 261*(((integSine_fix_2>>10)*(-integSine_fix_2>>10)-integSine_fix_2)>>10)+integSine_fix_2;}
			else {integSine_fix_2 = 261*(((integSine_fix_2>>10)*(integSine_fix_2>>10)-integSine_fix_2)>>10)+integSine_fix_2;}
		}

		//compute cosine
		TetaCos_fix_2 = TetaSine_fix_2 + 1647100;	// 20
		if (TetaCos_fix_2 > 3294206 ) {TetaCos_fix_2 -= 6588413;}

		if( TetaCos_fix_2 < 0)
		{
			integCos_fix_2 = 1304*(TetaCos_fix_2>>10)+(415*(TetaCos_fix_2>>10)>>10)*(TetaCos_fix_2>>10); // 20 bit
			if (integCos_fix_2 <0) {integCos_fix_2 = 261*(((integCos_fix_2>>10)*(-integCos_fix_2>>10)-integCos_fix_2)>>10)+integCos_fix_2;}
			else {integCos_fix_2 = 261*(((integCos_fix_2>>10)*(integCos_fix_2>>10)-integCos_fix_2)>>10)+integCos_fix_2;}
		}

		else
		{
			integCos_fix_2 = 1304*(TetaCos_fix_2>>10)-(415*(TetaCos_fix_2>>10)>>10)*(TetaCos_fix_2>>10); // 20 bit
			if (integCos_fix_2 <0) {integCos_fix_2 = 261*(((integCos_fix_2>>10)*(-integCos_fix_2>>10)-integCos_fix_2)>>10)+integCos_fix_2;}
			else {integCos_fix_2 = 261*(((integCos_fix_2>>10)*(integCos_fix_2>>10)-integCos_fix_2)>>10)+integCos_fix_2;}
		}

	//if (flag_phase == 1 || flag_phase == 4){
		sinTeta_fix_2 = integSine_fix_2>>10; //20-10
		cosTeta_fix_2 = integCos_fix_2>>10;
	//}
	//else
	if (flag_phase == 2){
		sinTeta_fix_2	= (((integSine_fix_2>>10)*(-512)) - ((integCos_fix_2>>10)*887))>>10;
		cosTeta_fix_2	= (((integCos_fix_2>>10)*(-512)) + ((integSine_fix_2>>10)*887))>>10;
	}
	else if (flag_phase == 3){
		sinTeta_fix_2	= (((integSine_fix_2>>10)*(-512)) + ((integCos_fix_2>>10)*887))>>10;
		cosTeta_fix_2	= (((integCos_fix_2>>10)*(-512)) - ((integSine_fix_2>>10)*887))>>10;
	}

	VoACreff_fix_2 = voac_peak_fix_2*sinTeta_fix_2;
}

