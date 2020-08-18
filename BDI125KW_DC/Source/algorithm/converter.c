
#include "algorithm/converter.h"

volatile int inverter_enable;
volatile int pwm_peak_reff = 800; //0 - 3749 pwm
volatile int pwm_peak_feedback;
volatile int mode_inverter;
volatile int Vreff_inv = 10; //volt
volatile int Vreff_inv_feedback;
volatile int ACPT1_AIN_Result_xmc2;
volatile int ACPT2_AIN_Result_xmc2;
volatile int ACPT3_AIN_Result_xmc2;
volatile int Vd_ref_fix, Vq_ref_fix, delta_vd_fix, delta_vq_fix;
volatile int pembagi = 1;
volatile int pembagi_feedback;
volatile int Vinv_d_fix, Vinv_q_fix, integrator_d_fix, integrator_q_fix, PWM_d_fix, PWM_q_fix, Iinv_d_fix, Iinv_q_fix, Id_fix, Iq_fix;
volatile int Id_ref_fix, Iq_ref_fix;
volatile int Id_fix, Iq_fix, PWM_A_fix, PWM_B_fix, PWM_C_fix;
volatile int KI_V = 8;//136;
volatile int KP_V = 9;//51;
volatile int KI_I = 18;
volatile int KP_I = 11;
//volatile int KP_I = 1;
volatile int KP_V_feedback, KI_V_feedback, KP_I_feedback;
volatile int p_set = 0;
volatile int q_set = 0;
volatile int m1, c1, m2, c2;
volatile int m1_hmi, c1_hmi, m2_hmi, c2_hmi;
volatile int m1_feedback, c1_feedback, m2_feedback, c2_feedback;
volatile int p_set_hmi, q_set_hmi = 0;
volatile int p_set_feedback, q_set_feedback;
volatile float power_calculation;
volatile float yf_p, Ptot, yf_q, Qtot;
volatile int yf_p_fix, Ptot_fix;
volatile int Vgrid_a_fix, Vgrid_b_fix, Vgrid_c_fix, Igrid_a_fix, Igrid_b_fix, Igrid_c_fix;
volatile int Vinv_a_fix, Vinv_b_fix, Vinv_c_fix, Ia_fix, Ib_fix, Ic_fix;
volatile int va_ref_fix, vb_ref_fix, vc_ref_fix;
volatile float Vinv_q, Iinv_q;
volatile int teta_manual_fix = 0;
volatile int VPLL_fix;
volatile int DCPT2_U2_fix;
volatile int32_t xf_PLL[2], yf_PLL[2], xv_PLL[2], yv_PLL[2];
volatile int32_t KP_V_add, KI_V_add, KP_I_add = 0;
volatile int32_t KP_V_add_feedback, KI_V_add_feedback, KP_I_add_feedback;
volatile int32_t wPLL_fix;
volatile int32_t Q_Filt_1, Q_Filt_2;

volatile int32_t mode = 1;
volatile int32_t pwm1_fix, pwm2_fix , pwm3_fix = 2399;
volatile int32_t pwm_set = 0;
volatile int32_t il_reff_fix;
volatile int32_t integ_err_vo_dc_fix;
volatile int32_t integ_err_il1_boost_fix, integ_err_il2_boost_fix, integ_err_il3_boost_fix;
volatile int32_t integ_err_il1_buck_fix, integ_err_il2_buck_fix, integ_err_il3_buck_fix;
volatile int32_t vo_dc_fix;
volatile uint32_t enable_CV=0;
volatile int32_t vodc_reff_boost_fix = 153600 ; // 153600<<10	untuk troubleshoot masih bisa diubah2 di ISR, beda dg VODC_REFF_BOOST_FIX sudah tetap
volatile int32_t boost_active = 1;
volatile int32_t buck_active = 0;
volatile int32_t buck_count = 0;
volatile int32_t err_vo_dc_count, err_vo_dc_max, err_vo_dc_min = 0;
volatile int32_t err_vo_dc_fix;


//buat tes closed loop
volatile int32_t current_reference_test = 0;
volatile int32_t voltage_reference_test = 0;

//======================================Outer Loop Boost Control====================================//

void ClosedLoopVoltageController(void)
{
	//int32_t err_vo_dc_fix;

	//vo_dc_fix = ((int32_t)DCPT2_AIN_Result-DCPT2_OFFSET)*DCPT2_GRAD_FIX;

	//filter
	//xv_PLL[1] = vo_dc_fix>>5;													//5 bit
	//yv_PLL[1] = (xv_PLL[1]*97) + (xv_PLL[0]*97) +((yv_PLL[0]*830));		//20 bit 500 Hz
	//yv_PLL[1] = (xv_PLL[1]*27606) + (xv_PLL[0]*27606) +((yv_PLL[0]*23));			//5+5 bit 50 KHz
	//xv_PLL[0] = xv_PLL[1];
	//yv_PLL[0] = yv_PLL[1]>>5;

	//err_vo_dc_fix = VODC_REFF_FIX - vo_dc_fix; //10
	//err_vo_dc_fix = vodc_reff_boost_fix - vo_dc_fix; //10
	//untuk tes closed loop
	//err_vo_dc_fix = voltage_reference_test - vo_dc_fix; //10
	err_vo_dc_fix = voltage_reference_test - (yv_PLL[1]>>10);

	integ_err_vo_dc_fix = integ_err_vo_dc_fix + ((err_vo_dc_fix*1)>>KI_V);//>>9);//>>6);	// ((errVoDC_fix*40)>>5)
	if(integ_err_vo_dc_fix>INTV_MAX_FIX){integ_err_vo_dc_fix=INTV_MAX_FIX;}
	if(integ_err_vo_dc_fix<INTV_MIN_FIX){integ_err_vo_dc_fix=INTV_MIN_FIX;}

	il_reff_fix = integ_err_vo_dc_fix + (err_vo_dc_fix<<KP_V);//<<8);//<<11); // <<9	- dif_fix; //- (VoDC_fix<<7); //10*kp+10=20; kp=2.5 = 5>>1
	//il_reff_fix = integ_err_vo_dc_fix - (vo_dc_fix<<KP_V);//<<8);//<<11); // <<9	- dif_fix; //- (VoDC_fix<<7); //10*kp+10=20; kp=2.5 = 5>>1
	if(il_reff_fix>IL_MAX_FIX){il_reff_fix=IL_MAX_FIX;}
	if(il_reff_fix<-IL_MAX_FIX){il_reff_fix=-IL_MAX_FIX;}
}

//======================================Inner Loop Buck Control====================================//

void CurrentLoopBuck1Fixed(void)
{
	int32_t err_il1_fix, il1_fix;

	il1_fix = ((int32_t)CT2_Result-CT2_OFF)*CT2_GRAD_FIX; //10

	err_il1_fix = -il_reff_fix + (il1_fix<<10); //20

	integ_err_il1_buck_fix = integ_err_il1_buck_fix + ((err_il1_fix*15)>>18);//>>19); //
	if(integ_err_il1_buck_fix>LIM_PWM_MAX_FIX){integ_err_il1_buck_fix=LIM_PWM_MAX_FIX;}
	if(integ_err_il1_buck_fix<LIM_PWM_MIN_FIX){integ_err_il1_buck_fix=LIM_PWM_MIN_FIX;}

	pwm1_fix = integ_err_il1_buck_fix + (err_il1_fix>>10);//>>11); //KP=<<9 23+9-2=30
	pwm1_fix = ((pwm1_fix <= LIM_PWM_MAX_FIX) ? pwm1_fix : LIM_PWM_MAX_FIX );
	pwm1_fix = ((pwm1_fix > LIM_PWM_MIN_FIX) ? pwm1_fix : LIM_PWM_MIN_FIX );

	//pwm1_fix = 3749-(pwm1_fix>>9)*1.83;
	pwm1_fix = 2399-(pwm1_fix>>9)*1.17;
}

void CurrentLoopBuck2Fixed(void)
{
	int32_t err_il2_fix, il2_fix;

	il2_fix = ((int32_t)CT3_Result-CT3_OFF)*CT3_GRAD_FIX; //10

	err_il2_fix = -il_reff_fix + (il2_fix<<10); //23

	integ_err_il2_buck_fix = integ_err_il2_buck_fix + ((err_il2_fix*15)>>18); //-KAW*(temppwm1-pwm1)); KI=<<13 23+13-6=30
	if(integ_err_il2_buck_fix>LIM_PWM_MAX_FIX){integ_err_il2_buck_fix=LIM_PWM_MAX_FIX;}
	if(integ_err_il2_buck_fix<LIM_PWM_MIN_FIX){integ_err_il2_buck_fix=LIM_PWM_MIN_FIX;}

	pwm2_fix = integ_err_il2_buck_fix + (err_il2_fix>>10); //KP=<<9 23+9-2=30
	pwm2_fix = ( (pwm2_fix <= LIM_PWM_MAX_FIX) ? pwm2_fix : LIM_PWM_MAX_FIX );
	pwm2_fix = ( (pwm2_fix > LIM_PWM_MIN_FIX) ? pwm2_fix : LIM_PWM_MIN_FIX );

	//pwm2_fix = 3749-(pwm2_fix>>9)*1.83;
	pwm2_fix = 2399-(pwm2_fix>>9)*1.17;
}

void CurrentLoopBuck3Fixed(void)
{
	int32_t err_il3_fix, il3_fix;

	il3_fix = ((int32_t)CT4_Result-CT4_OFF)*CT4_GRAD_FIX; //10

	err_il3_fix = -il_reff_fix + (il3_fix<<10); //20

	integ_err_il3_buck_fix = integ_err_il3_buck_fix + ((err_il3_fix*15)>>18); //0
	if(integ_err_il3_buck_fix>LIM_PWM_MAX_FIX){integ_err_il3_buck_fix=LIM_PWM_MAX_FIX;}
	if(integ_err_il3_buck_fix<LIM_PWM_MIN_FIX){integ_err_il3_buck_fix=LIM_PWM_MIN_FIX;}

	pwm3_fix = integ_err_il3_buck_fix + (err_il3_fix>>10); //KP=<<9 20+9-9=20
	pwm3_fix = ( (pwm3_fix <= LIM_PWM_MAX_FIX) ? pwm3_fix : LIM_PWM_MAX_FIX );
	pwm3_fix = ( (pwm3_fix > LIM_PWM_MIN_FIX) ? pwm3_fix : LIM_PWM_MIN_FIX );

	//pwm3_fix = 3749-(pwm3_fix>>9)*1.83;
	pwm3_fix = 2399-(pwm3_fix>>9)*1.17;
}


//======================================Inner Loop Boost Control====================================//

void CurrentLoopBoost1Fixed(void)
{
	int32_t err_il1_fix, il1_fix;

	il1_fix = ((int32_t)CT2_Result-CT2_OFF)*CT2_GRAD_FIX; //10

	err_il1_fix = il_reff_fix - (il1_fix<<10); //20
	//untuk tes closed loop
	//err_il1_fix = current_reference_test - (il1_fix<<10); //20

	integ_err_il1_boost_fix = integ_err_il1_boost_fix + ((err_il1_fix*15)>>KI_I);//18);//>>19);//>>16); //>>17); //15)>>15   // 20-3=17*ki+3=20, ki=15/8/16000
	if(integ_err_il1_boost_fix>LIM_PWM_MAX_FIX){integ_err_il1_boost_fix=LIM_PWM_MAX_FIX;}
	if(integ_err_il1_boost_fix<LIM_PWM_MIN_FIX){integ_err_il1_boost_fix=LIM_PWM_MIN_FIX;}

	pwm1_fix = integ_err_il1_boost_fix + (err_il1_fix>>KP_I);//11);//>>12);//>>9); //>>10 //>>9   //20*kp=20, kp=>>9
	pwm1_fix = ( (pwm1_fix <= LIM_PWM_MAX_FIX) ? pwm1_fix : LIM_PWM_MAX_FIX );
	pwm1_fix = ( (pwm1_fix > LIM_PWM_MIN_FIX) ? pwm1_fix : LIM_PWM_MIN_FIX );

	pwm1_fix = 2399-(pwm1_fix>>9)*1.17;
}

void CurrentLoopBoost2Fixed(void)
{
	int32_t err_il2_fix, il2_fix;

	il2_fix = ((int32_t)CT3_Result-CT3_OFF)*CT3_GRAD_FIX; //10

	err_il2_fix = il_reff_fix - (il2_fix<<10); //20
	//untuk tes closed loop
	//err_il2_fix = current_reference_test - (il2_fix<<10); //20

	integ_err_il2_boost_fix = integ_err_il2_boost_fix + ((err_il2_fix*15)>>KI_I); // (20)*ki=20, ki=15>>12
	if(integ_err_il2_boost_fix>LIM_PWM_MAX_FIX){integ_err_il2_boost_fix=LIM_PWM_MAX_FIX;}
	if(integ_err_il2_boost_fix<LIM_PWM_MIN_FIX){integ_err_il2_boost_fix=LIM_PWM_MIN_FIX;}

	pwm2_fix = integ_err_il2_boost_fix + (err_il2_fix>>KP_I); //KP=<<9 23+9-2=30
	pwm2_fix = ( (pwm2_fix <= LIM_PWM_MAX_FIX) ? pwm2_fix : LIM_PWM_MAX_FIX );
	pwm2_fix = ( (pwm2_fix > LIM_PWM_MIN_FIX) ? pwm2_fix : LIM_PWM_MIN_FIX );

	pwm2_fix = 2399-(pwm2_fix>>9)*1.17;
}

void CurrentLoopBoost3Fixed(void)
{
	int32_t err_il3_fix, il3_fix;

	il3_fix = ((int32_t)CT4_Result-CT4_OFF)*CT4_GRAD_FIX; //10

	err_il3_fix = il_reff_fix - (il3_fix<<10); //20
	//untuk tes closed loop
	//err_il3_fix = current_reference_test - (il3_fix<<10); //20

	integ_err_il3_boost_fix = integ_err_il3_boost_fix + ((err_il3_fix*15)>>KI_I); // (20)*ki=20, ki=15>>12
	if(integ_err_il3_boost_fix>LIM_PWM_MAX_FIX){integ_err_il3_boost_fix=LIM_PWM_MAX_FIX;}
	if(integ_err_il3_boost_fix<LIM_PWM_MIN_FIX){integ_err_il3_boost_fix=LIM_PWM_MIN_FIX;}

	pwm3_fix = integ_err_il3_boost_fix + (err_il3_fix>>KP_I); //KP=<<9 23+9-2=30
	pwm3_fix = ( (pwm3_fix <= LIM_PWM_MAX_FIX) ? pwm3_fix : LIM_PWM_MAX_FIX );
	pwm3_fix = ( (pwm3_fix > LIM_PWM_MIN_FIX) ? pwm3_fix : LIM_PWM_MIN_FIX );

	pwm3_fix = 2399-(pwm3_fix>>9)*1.17;
}



void BoostConstantVoltageControlFixed(void)
{
	int32_t err_vo_dc_fix;

	vo_dc_fix = ((int32_t)DCPT2_AIN_Result-DCPT2_OFFSET)*DCPT2_GRAD_FIX;

	//err_vo_dc_fix = VODC_REFF_BOOST_FIX - vo_dc_fix; //10
	//err_vo_dc_fix = vodc_reff_boost_fix - vo_dc_fix; //10
	//untuk tes closed loop
	err_vo_dc_fix = voltage_reference_test - vo_dc_fix; //10

	integ_err_vo_dc_fix = integ_err_vo_dc_fix + ((err_vo_dc_fix*1)>>KI_V);//>>6);	// ((errVoDC_fix*40)>>5)
	if(integ_err_vo_dc_fix>INTV_MAX_FIX){integ_err_vo_dc_fix=INTV_MAX_FIX;}
	if(integ_err_vo_dc_fix<INTV_MIN_FIX){integ_err_vo_dc_fix=INTV_MIN_FIX;}

	il_reff_fix = integ_err_vo_dc_fix + (err_vo_dc_fix<<KP_V);//<<11); // <<9	- dif_fix; //- (VoDC_fix<<7); //10*kp+10=20; kp=2.5 = 5>>1
	if(il_reff_fix>IL_MAX_FIX){il_reff_fix=IL_MAX_FIX;}
	if(il_reff_fix<-IL_MAX_FIX){il_reff_fix=-IL_MAX_FIX;}
}

//======================================Outer Loop Buck Control====================================//

void BuckConstantVoltageControlFixed(void)
{
	int32_t err_vo_dc_fix;

	vo_dc_fix = ((int32_t)DCPT2_AIN_Result-DCPT2_OFFSET)*DCPT2_GRAD_FIX;

	err_vo_dc_fix = -VODC_REFF_BUCK_FIX + vo_dc_fix; //10

	integ_err_vo_dc_fix = integ_err_vo_dc_fix + ((err_vo_dc_fix*50)>>3);
	if(integ_err_vo_dc_fix>INTV_MAX_FIX){integ_err_vo_dc_fix=INTV_MAX_FIX;}
	if(integ_err_vo_dc_fix<INTV_MIN_FIX){integ_err_vo_dc_fix=INTV_MIN_FIX;}

	il_reff_fix = integ_err_vo_dc_fix + ((err_vo_dc_fix*5)<<8); //- (VoDC_fix<<7); //10*kp+10=20; kp=2.5 = 5>>1
	if(il_reff_fix>IL_MAX_FIX){il_reff_fix=IL_MAX_FIX;}
	if(il_reff_fix<-IL_MAX_FIX){il_reff_fix=-IL_MAX_FIX;}
}

