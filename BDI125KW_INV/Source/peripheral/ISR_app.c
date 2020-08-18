/*
 * ISR_app.c
 *
 *  Created on: Sep 26, 2014
 *      Author: angga
 */

#include "peripheral/ISR_app.h"

int8_t counter4=0;

volatile bool PLL_status = FALSE;
volatile bool Sinkronisasi = FALSE;
volatile bool Droop_status = FALSE;
volatile bool Droop_Q_status = FALSE;

volatile bool Sinkronisasi_1 = FALSE;
volatile bool Droop_status_1 = FALSE;

volatile bool Sinkronisasi_2 = FALSE;
volatile bool Droop_status_2 = FALSE;

void UART_XMC_Handler(void)
{
	char data;

	data=UART_U2->OUTR;

	string_read_xmc[string_read_xmc_increment]= data;

	if(data == 'T'){
		flag_update_receive_xmc=1;
		string_read_xmc_increment=-1;
	}
	else if(data == 'A'){
		uart_xmc_request(1);

		string_read_xmc_increment=-1;
	}
	else if(data == 'B'){
		flag_update_send_xmc=1;
		string_read_xmc_increment=-1;
	}

	else if(data == 'C'){
		mode_inverter = 1;
		flag_update_send_xmc=1;
		string_read_xmc_increment=-1;
	}
	else if(data == 'D'){
		mode_inverter = 2;
		flag_update_send_xmc=1;
		string_read_xmc_increment=-1;
	}

	else if(data == 'E'){ // matikan inverter
		inverter_enable=1;
		string_read_xmc_increment=-1;
	}
	else if(data == 'F'){ // nyalakan inverter
		inverter_enable=0;

		Droop_status_1 = FALSE;
		PLL_status = FALSE;
		Sinkronisasi = FALSE;
		Droop_Q_status = FALSE;

		deltaw_1= 0;
		deltaw_fix_1 = 0;
		deltafrad_fix_1 = 0;
		integ_Vac_q_fix = 0;
		integ1_fix = 0;
		integ2_fix = 0;
		Teta_PLL = 0;
		teta_manual_fix = 0;
		p_set = 0;
		q_set = 0;
		errdeltaVcor_fix_1=0;

		deltaw_2= 0;
		deltaw_fix_2 = 0;
		deltafrad_fix_2 = 0;
		errdeltaVcor_fix_2=0;

		string_read_xmc_increment=-1;
	}

	else if(data == 'G'){
		Droop_status_1 = TRUE;
		string_read_xmc_increment=-1;
	}

	else if(data == 'H'){
		Droop_status_1 = FALSE;
		p_set = 0;

		deltaw_1= 0;
		deltaw_fix_1 = 0;
		deltafrad_fix_1 = 0;

		deltaw_2= 0;
		deltaw_fix_2 = 0;
		deltafrad_fix_2 = 0;

		string_read_xmc_increment=-1;
	}

	else if(data == 'I'){
		PLL_status = TRUE;
		string_read_xmc_increment=-1;
	}
	else if(data == 'J'){
		PLL_status = FALSE;
		teta_manual_fix = 0;
		string_read_xmc_increment=-1;
	}

	else if(data == 'K'){
		Sinkronisasi = TRUE;
		string_read_xmc_increment=-1;
	}
	else if(data == 'L'){
		Sinkronisasi = FALSE;
		teta_manual_fix = 0;
		string_read_xmc_increment=-1;
	}

	else if(data == 'M'){
		teta_manual_fix = teta_manual_fix + 10240;	//Q20
		string_read_xmc_increment=-1;
	}
	else if(data == 'N'){
		teta_manual_fix = teta_manual_fix - 10240;	//Q20
		string_read_xmc_increment=-1;
	}

	else if(data == 'O'){
		Droop_Q_status = TRUE;
		string_read_xmc_increment=-1;
	}
	else if(data == 'P'){
		Droop_Q_status = FALSE;
		q_set = 0;
		string_read_xmc_increment=-1;
	}

	else if(data == 'Q'){
		string_read_xmc_increment=-1;
	}
	else if(data == 'R'){
		string_read_xmc_increment=-1;
	}

	else if(data == 'S'){
		string_read_xmc_increment=-1;
	}
	else if(data == 'T'){
		string_read_xmc_increment=-1;
	}

	else if(data == 'U'){
		string_read_xmc_increment=-1;
	}
	else if(data == 'V'){
		string_read_xmc_increment=-1;
	}

	string_read_xmc_increment++;

	SET_BIT(UART_U2->TRBSCR,USIC_CH_TRBSCR_CSRBI_Pos);
}

void PWM4A4B_IRQ_Handler(void)	//interrupt handler PWM_1A_1B CCU81.SR3
{
	// Set Flag for Time Slot Checking
	SET_BIT(PORT0->OUT,0);

	char kal[32];

	static int8_t counter4=0;

	while(CheckBit(VADC_G2->RESD[ACPT1_AIN_Result_Register],VADC_G_RESD_VF_Pos)==0);
	ACPT1_AIN_Result = VADC_G2->RES[ACPT1_AIN_Result_Register] & VADC_G_RES_RESULT_Msk;
	ACPT1_fix = ((int32_t)ACPT1_AIN_Result-ACPT1_OFFSET)*ACPT1_GRAD_FIX; //Q10

	while(CheckBit(VADC_G2->RESD[ACPT2_AIN_Result_Register],VADC_G_RESD_VF_Pos)==0);
	ACPT2_AIN_Result = VADC_G2->RES[ACPT2_AIN_Result_Register] & VADC_G_RES_RESULT_Msk;
	ACPT2_fix = ((int32_t)ACPT2_AIN_Result-ACPT2_OFFSET)*ACPT2_GRAD_FIX; //Q10

	while(CheckBit(VADC_G2->RESD[GRPT1_AIN_Result_Register],VADC_G_RESD_VF_Pos)==0);
	GRPT1_AIN_Result = VADC_G2->RES[GRPT1_AIN_Result_Register] & VADC_G_RES_RESULT_Msk;
	GRPT1_fix = ((int32_t)GRPT1_AIN_Result-GRPT1_OFFSET)*GRPT1_GRAD_FIX; //Q10

	while(CheckBit(VADC_G2->RESD[GRPT2_AIN_Result_Register],VADC_G_RESD_VF_Pos)==0);
	GRPT2_AIN_Result = VADC_G2->RES[GRPT2_AIN_Result_Register] & VADC_G_RES_RESULT_Msk;
	GRPT2_fix = ((int32_t)GRPT2_AIN_Result-GRPT2_OFFSET)*GRPT2_GRAD_FIX; //Q10

	while(CheckBit(VADC_G2->RESD[GRPT3_AIN_Result_Register],VADC_G_RESD_VF_Pos)==0);
	GRPT3_AIN_Result = VADC_G2->RES[GRPT3_AIN_Result_Register] & VADC_G_RES_RESULT_Msk;
	GRPT3_fix = ((int32_t)GRPT3_AIN_Result-GRPT3_OFFSET)*GRPT3_GRAD_FIX; //Q10

	//while(CheckBit(VADC_G0->RESD[DCPT2_AIN_Result_Register],VADC_G_RESD_VF_Pos)==0);
	//DCPT2_AIN_Result = VADC_G0->RES[DCPT2_AIN_Result_Register] & VADC_G_RES_RESULT_Msk;
	//DCPT2_fix = ((int32_t)DCPT2_AIN_Result-DCPT2_OFFSET)*DCPT2_GRAD_FIX; // Q10

	while(CheckBit(VADC_G0->RESD[CT2_Result_Register],VADC_G_RESD_VF_Pos)==0);
	CT2_Result = VADC_G0->RES[CT2_Result_Register] & VADC_G_RES_RESULT_Msk;
	CT2_fix = ((int32_t)CT2_Result-CT2_OFF)*CT2_GRAD_FIX; // Q10

	while(CheckBit(VADC_G0->RESD[CT5_Result_Register],VADC_G_RESD_VF_Pos)==0);
	CT5_Result = VADC_G0->RES[CT5_Result_Register] & VADC_G_RES_RESULT_Msk;
	CT5_fix = ((int32_t)CT5_Result-CT5_OFF)*CT5_GRAD_FIX; // Q10

//	while(CheckBit(VADC_G0->RESD[CT6_Result_Register],VADC_G_RESD_VF_Pos)==0);
//	CT6_Result = VADC_G0->RES[CT6_Result_Register] & VADC_G_RES_RESULT_Msk;
//	CT6_fix = ((int32_t)CT6_Result-CT6_OFF)*CT6_GRAD_FIX; // Q10

	while(CheckBit(VADC_G1->RESD[CT7_Result_Register],VADC_G_RESD_VF_Pos)==0);
	CT7_Result = VADC_G1->RES[CT7_Result_Register] & VADC_G_RES_RESULT_Msk;
	CT7_fix = ((int32_t)CT7_Result-CT7_OFF)*CT7_GRAD_FIX; // Q10

	while(CheckBit(VADC_G1->RESD[CT8_Result_Register],VADC_G_RESD_VF_Pos)==0);
	CT8_Result = VADC_G1->RES[CT8_Result_Register] & VADC_G_RES_RESULT_Msk;
	CT8_fix = ((int32_t)CT8_Result-CT8_OFF)*CT8_GRAD_FIX; // Q10

	if(inverter_enable)
	{

		if (mode_inverter==1){ //open loop

			w_fix = 329420636; //Q20

			Tetaref_fix = Tetaref_fix + (w_fix/16000); //20 bit
			if(Tetaref_fix > 3294206) {Tetaref_fix -= 6588413;}
			else if (Tetaref_fix < -3294206) {Tetaref_fix+=6588413;}

			TetaSineA_fix = Tetaref_fix;
			if(TetaSineA_fix > 3294206) {TetaSineA_fix -= 6588413;}
			else if (TetaSineA_fix < -3294206) {TetaSineA_fix+=6588413;}

			if(TetaSineA_fix < 0)
			{
				integSineA_fix = 1304*(TetaSineA_fix>>10)+(415*(TetaSineA_fix>>10)>>10)*(TetaSineA_fix>>10); // 20 bit
				if (integSineA_fix <0) {integSineA_fix = 261*(((integSineA_fix>>10)*(-integSineA_fix>>10)-integSineA_fix)>>10)+integSineA_fix;}
				else {integSineA_fix = 261*(((integSineA_fix>>10)*(integSineA_fix>>10)-integSineA_fix)>>10)+integSineA_fix;}
			}
			else
			{
				integSineA_fix = 1304*(TetaSineA_fix>>10)-(415*(TetaSineA_fix>>10)>>10)*(TetaSineA_fix>>10); // 20 bit
				if (integSineA_fix <0) {integSineA_fix = 261*(((integSineA_fix>>10)*(-integSineA_fix>>10)-integSineA_fix)>>10)+integSineA_fix;}
				else {integSineA_fix = 261*(((integSineA_fix>>10)*(integSineA_fix>>10)-integSineA_fix)>>10)+integSineA_fix;}
			}

			sinTetaA_fix = integSineA_fix>>10; //20-10

			if (pwm_peak > 3740){pwm_peak = 3740;}
			else if (pwm_peak < 0){pwm_peak = 0;}

			pwm_setA_fix = pwm_peak*0.273*sinTetaA_fix; //20

			if(pwm_setA_fix > 1048576){pwm_setA_fix = 1048576;}
			if(pwm_setA_fix < -1048576){pwm_setA_fix = -1048576;}

			comparepwm4 =  (((int32_t)((-pwm_setA_fix>>9)*1.83))+3749)>>1; //20-9=11
			comparepwm5 =  (((int32_t)((pwm_setA_fix>>9)*1.83))+3749)>>1; //20-9=11
		}

		else if (mode_inverter==2){ //closed loop

			//Algoritma closed loop

			if (Droop_status_1 == TRUE)
			{
				droop_standalone_1();
			}
			else
			{
				if (deltaw_fix_1 > 0){
					deltaw_fix_1 -= 1;
					if (deltaw_fix_1 < 0){deltaw_fix_1 = 0;}
				}
				else if (deltaw_fix_1 < 0){
					deltaw_fix_1 += 1;
					if (deltaw_fix_1 > 0){deltaw_fix_1 = 0;}
				}

				p_set = 0;
				deltaw_1= 0;
				//deltaw_fix_1 = 0;
				deltafrad_fix_1 = 0;
			}

			if(Droop_Q_status == TRUE)
			{
				if (q_set > 5000){q_set = 5000;}
				else if (q_set < -5000){q_set = -5000;}

				if (Q_Filt_1<q_set){errdeltaVcor_fix_1 += 1;}
				else if (Q_Filt_1>q_set){errdeltaVcor_fix_1 -= 1;}

				if(errdeltaVcor_fix_1 > 61440) {errdeltaVcor_fix_1 = 61440;} //limit +60V
				else if (errdeltaVcor_fix_1 < -61440) {errdeltaVcor_fix_1 = -61440;} //limit -60V
			}
			else
			{
				if (errdeltaVcor_fix_1 > 0){
					errdeltaVcor_fix_1 -= 1;
					if (errdeltaVcor_fix_1 < 0){errdeltaVcor_fix_1 = 0;}
				}
				else if (errdeltaVcor_fix_1 < 0){
					errdeltaVcor_fix_1 += 1;
					if (errdeltaVcor_fix_1 > 0){errdeltaVcor_fix_1 = 0;}
				}

				q_set = 0;
				//errdeltaVcor_fix_1=0;
			}

			if (PLL_status == TRUE)
			{
				PLL();
			}
			else
			{
				integ_Vac_q_fix = 0;
				integ1_fix = 0;
				integ2_fix = 0;
				Teta_PLL = 0;
			}

			refgen();

			if (Sinkronisasi == TRUE)
			{
				if (PLL_status == TRUE)
				{
					Tetaref_fix = Teta_PLL;
				}
			}

			refgen_paralel_1();

			//if(counter4 == 3)
			//{
			//	//counter4=4;
			//	power_calculation_2();
			//}

			//power_calculation_1();

			virtual_impedance_1();
			voltage_controller_1();

			if(PWMInv_fix_1 > 1048576){PWMInv_fix_1 = 1048576;}
			if(PWMInv_fix_1 < -1048576){PWMInv_fix_1 = -1048576;}

			comparepwm4 =  (((int32_t)((-PWMInv_fix_1>>9)*1.83))+3749)>>1; //20-9=11
			comparepwm5 =  (((int32_t)((PWMInv_fix_1>>9)*1.83))+3749)>>1; //20-9=11

		}

		PWM4A4B_Set_Compare((uint32_t)comparepwm4,(uint32_t)comparepwm4);
		PWM5A5B_Set_Compare((uint32_t)comparepwm5,(uint32_t)comparepwm5);
		PWM_Inverter_Enable();
	}

	else
	{
		PWM_Inverter_Disable();
		deltaw_1= 0;
		deltaw_fix_1 = 0;
		deltafrad_fix_1 = 0;
		integ_Vac_q_fix = 0;
		integ1_fix = 0;
		integ2_fix = 0;
		Teta_PLL = 0;
		teta_manual_fix = 0;
		p_set = 0;
		q_set = 0;
		errdeltaVcor_fix_1=0;
	}

	CLR_BIT(PORT0->OUT,0);

	//Clear Interrupt
	SET_BIT(PWM_4A_4B->SWR,CCU8_CC8_SWR_RCM1D_Pos);
	SET_BIT(PWM_4A_4B->SWR,CCU8_CC8_SWR_RCM2D_Pos);
}

void PWM5A5B_IRQ_Handler(void)	//interrupt handler PWM_2A_2B CCU81.SR1
{
	//Clear Interrupt
	SET_BIT(PWM_5A_5B->SWR,CCU8_CC8_SWR_RCM1D_Pos);
	SET_BIT(PWM_5A_5B->SWR,CCU8_CC8_SWR_RCM2D_Pos);
}

void PWM6A6B_IRQ_Handler(void)	//interrupt handler PWM_3A_3B CCU81.SR2
{

	// Set Flag for Time Slot Checking
	SET_BIT(PORT0->OUT,9);

	char kal[32];

	if(inverter_enable)
	{

		if (mode_inverter==1){ //open loop

			TetaSineC_fix = TetaSineA_fix; // + 2196138; // 20
			if(TetaSineC_fix > 3294206) {TetaSineC_fix -= 6588413;}
			else if (TetaSineC_fix < -3294206) {TetaSineC_fix += 6588413;}

			if(TetaSineC_fix < 0)
			{
				integSineC_fix = 1304*(TetaSineC_fix>>10)+(415*(TetaSineC_fix>>10)>>10)*(TetaSineC_fix>>10); // 20 bit
				if (integSineC_fix <0) {integSineC_fix = 261*(((integSineC_fix>>10)*(-integSineC_fix>>10)-integSineC_fix)>>10)+integSineC_fix;}
			else {integSineC_fix = 261*(((integSineC_fix>>10)*(integSineC_fix>>10)-integSineC_fix)>>10)+integSineC_fix;}
			}
			else
			{
				integSineC_fix = 1304*(TetaSineC_fix>>10)-(415*(TetaSineC_fix>>10)>>10)*(TetaSineC_fix>>10); // 20 bit
				if (integSineC_fix <0) {integSineC_fix = 261*(((integSineC_fix>>10)*(-integSineC_fix>>10)-integSineC_fix)>>10)+integSineC_fix;}
				else {integSineC_fix = 261*(((integSineC_fix>>10)*(integSineC_fix>>10)-integSineC_fix)>>10)+integSineC_fix;}
			}

			sinTetaC_fix = integSineC_fix>>10; //20-10

			if (pwm_peak > 3740){pwm_peak = 3740;}
			else if (pwm_peak < 0){pwm_peak = 0;}

			pwm_setC_fix = pwm_peak*0.273*sinTetaC_fix; //20

			if(pwm_setC_fix > 1048576){pwm_setC_fix = 1048576;}
			if(pwm_setC_fix < -1048576){pwm_setC_fix = -1048576;}

			comparepwm6 =  (((int32_t)((-pwm_setC_fix>>9)*1.83))+3749)>>1; //20-9=11
			comparepwm7 =  (((int32_t)((pwm_setC_fix>>9)*1.83))+3749)>>1; //20-9=11

		}

		else if (mode_inverter==2){ //closed loop

			//Algoritma closed loop

			if (Droop_status_1 == TRUE)
			{
				droop_standalone_2();
			}
			else
			{
				if (deltaw_fix_2 > 0){
					deltaw_fix_2 -= 1;
					if (deltaw_fix_2 < 0){deltaw_fix_2 = 0;}
				}
				else if (deltaw_fix_2 < 0){
					deltaw_fix_2 += 1;
					if (deltaw_fix_2 > 0){deltaw_fix_2 = 0;}
				}

				p_set = 0;
				deltaw_2= 0;
				//deltaw_fix_2 = 0;
				deltafrad_fix_2 = 0;
			}


			if(Droop_Q_status == TRUE)
			{
				if (q_set > 5000){q_set = 5000;}
				else if (q_set < -5000){q_set = -5000;}

				if (Q_Filt_2<q_set){errdeltaVcor_fix_2 += 1;}
				else if (Q_Filt_2>q_set){errdeltaVcor_fix_2 -= 1;}

				if(errdeltaVcor_fix_2 > 61440) {errdeltaVcor_fix_2 = 61440;} //limit +60V
				else if (errdeltaVcor_fix_2 < -61440) {errdeltaVcor_fix_2 = -61440;} //limit -60V
			}
			else
			{
				if (errdeltaVcor_fix_2 > 0){
					errdeltaVcor_fix_2 -= 1;
					if (errdeltaVcor_fix_2 < 0){errdeltaVcor_fix_2 = 0;}
				}
				else if (errdeltaVcor_fix_2 < 0){
					errdeltaVcor_fix_2 += 1;
					if (errdeltaVcor_fix_2 > 0){errdeltaVcor_fix_2 = 0;}
				}

				q_set = 0;
				//errdeltaVcor_fix_2=0;
			}

			refgen_paralel_2();

			if(counter4 == 3)
			{
				//counter4=4;
				power_calculation_2();
			}

			if(counter4 == 0)
			{
				counter4=4;
				power_calculation_1();
			}
			counter4--;

			//power_calculation_2();
			virtual_impedance_2();
			voltage_controller_2();

			if(PWMInv_fix_2 > 1048576){PWMInv_fix_2 = 1048576;}
			if(PWMInv_fix_2 < -1048576){PWMInv_fix_2 = -1048576;}

			comparepwm6 =  (((int32_t)((-PWMInv_fix_2>>9)*1.83))+3749)>>1; //20-9=11
			comparepwm7 =  (((int32_t)((PWMInv_fix_2>>9)*1.83))+3749)>>1; //20-9=11
		}

		PWM6A6B_Set_Compare((uint32_t)comparepwm6,(uint32_t)comparepwm7);
		PWM_Inverter_Enable();
	}

	else
	{
		PWM_Inverter_Disable();
		deltaw_2= 0;
		deltaw_fix_2 = 0;
		deltafrad_fix_2 = 0;
		teta_manual_fix = 0;
		p_set = 0;
		q_set = 0;
		errdeltaVcor_fix_2=0;
	}

	CLR_BIT(PORT0->OUT,9);

	//Clear Interrupt
	SET_BIT(PWM_6A_6B->SWR,CCU8_CC8_SWR_RCM1D_Pos);
	SET_BIT(PWM_6A_6B->SWR,CCU8_CC8_SWR_RCM2D_Pos);
}
