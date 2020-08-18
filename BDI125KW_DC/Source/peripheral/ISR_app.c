/*
 * ISR_app.c
 *
 *  Created on: Sep 26, 2014
 *      Author: angga + bima + iqbal + mukhlis
 */

#include "peripheral/ISR_app.h"

int state_fsm;
int prev_state_fsm;
int next_state_fsm;
volatile unsigned short int state=0; // state for FSM (Finite State Machine) from State Diagram
volatile unsigned short int previous_state=0;
volatile int flag_fault = 0;
volatile int flag_activation = 0;
volatile int flag_deactivation = 0;

volatile int32_t flag_rabbit=0;
volatile bool data_rabbit_enable = FALSE;

void UART_RS485_Handler(void)	//interrupt handler UART485 U1Ch1
{
	char data;
	static char kal[32];

	data=UART_RS485->OUTR;

	string_read_rabbit[string_read_rabbit_increment]= data;

	//if ( data == 'H' && flag_rabbit == 0){
	//	flag_rabbit = 1;
	//}
	//else if ( flag_rabbit == 0){
	//	string_read_rabbit_increment = -1;
	//}
	if( data == 'T'){//&& flag_rabbit == 1){

		if (flag_rabbit == 0){
			flag_rabbit = 1;
			string_read_rabbit_increment = -2;
		}
		else{
			flag_rabbit = 0;
			flag_update_receive_rabbit=1;
			string_read_rabbit_increment = -2;
			NVIC_DisableIRQ(USIC1_0_IRQn);
			//sprintf(kal,"masuk!\r\n");
			//UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

		}

	}

	string_read_rabbit_increment++;

	SET_BIT(UART_RS485->TRBSCR,USIC_CH_TRBSCR_CSRBI_Pos);
}

void UART_RS232_Handler(void)	//interrupt handler UART232 U0Ch1
{
	status_t status;
	//unsigned char NULLCHAR = 'NULL';
	static char ch=0;
	static char kal[32];
	//uint8_t Data1[8] = {0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01};
	//uint8_t Data2[8] = {0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02};
	//char button;
	static float DACout_Volt=0.5;
	uint32_t i;

	static char datakomunikasi[300];

	ch=UART_RS232->OUTR;

	switch(ch)
	{
		case '1'	:

			sprintf(kal,"\r\r\n- ADC INFINEON 1 -\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"DCPT1: %d; %f\r\n", DCPT1_AIN_Result, (float)((int32_t)DCPT1_AIN_Result-DCPT1_OFFSET)/DCPT1_GRAD);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"DCPT2: %d; %f\r\n", DCPT2_AIN_Result, (float)((int32_t)DCPT2_AIN_Result-DCPT2_OFFSET)/DCPT2_GRAD);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"CT1: %d; %f\r\n", CT1_Result, (float)((int32_t)CT1_Result-CT1_OFF)/CT1_GRAD);
			UART001_WaitWriteDataMultiple(UART_RS232,kal, strlen(kal));

			sprintf(kal,"CT3: %d; %f\r\n", CT3_Result, (float)((int32_t)CT3_Result-CT3_OFF)/CT3_GRAD);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"GRPT3: %d; %f\r\n", GRPT3_AIN_Result, (float)((int32_t)GRPT3_AIN_Result-GRPT3_OFFSET)/GRPT3_GRAD);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			//sprintf(kal,"CT4: %d; %f\r\n", CT4_Result, (float)((int32_t)CT4_Result-CT4_OFF)/CT4_GRAD);
			//UART001_WaitWriteDataMultiple(UART_RS232,kal, strlen(kal));

			//sprintf(kal,"CT6: %d; %f\r\n", CT6_Result, (float)((int32_t)CT6_Result-CT6_OFF)/CT6_GRAD);
			//UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"---PWM4-PWM5 (K2)---\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal, strlen(kal));

			sprintf(kal,"CT5: %d; %f\r\n", CT5_Result, (float)((int32_t)CT5_Result-CT5_OFF)/CT5_GRAD);
			UART001_WaitWriteDataMultiple(UART_RS232,kal, strlen(kal));

			sprintf(kal,"CT7: %d; %f\r\n", CT7_Result, (float)((int32_t)CT7_Result-CT7_OFF)/CT7_GRAD);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"ACPT2: %d; %f\r\n", ACPT2_AIN_Result, (float)((int32_t)ACPT2_AIN_Result-ACPT2_OFFSET)/ACPT2_GRAD);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"GRPT2: %d; %f\r\n", GRPT2_AIN_Result, (float)((int32_t)GRPT2_AIN_Result-GRPT2_OFFSET)/GRPT2_GRAD);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"---PWM6-PWM7 (K3)---\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal, strlen(kal));

			sprintf(kal,"CT2: %d; %f\r\n", CT2_Result, (float)((int32_t)CT2_Result-CT2_OFF)/CT2_GRAD);
			UART001_WaitWriteDataMultiple(UART_RS232,kal, strlen(kal));

			sprintf(kal,"CT8: %d; %f\r\n", CT8_Result, (float)((int32_t)CT8_Result-CT8_OFF)/CT8_GRAD);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"ACPT1: %d; %f\r\n", ACPT1_AIN_Result, (float)((int32_t)ACPT1_AIN_Result-ACPT1_OFFSET)/ACPT1_GRAD);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"GRPT1: %d; %f\r\n", GRPT1_AIN_Result, (float)((int32_t)GRPT1_AIN_Result-GRPT1_OFFSET)/GRPT1_GRAD);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

		break;

		case '2'	:
			sprintf(kal,"\r\r\n- DATA DARI XMC 2 -\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"Q_Filt_1: %d\r\n", Q_Filt_1);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"Q_Filt_2: %d\r\n", Q_Filt_2);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

/*
			sprintf(kal,"comparepwm4: %d\r\n", comparepwm4);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"PWM inv open loop: %d\r\n", pwm_peak_feedback);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"Vinv ref closed loop: %d\r\n", Vreff_inv_feedback);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"yf_p: %f\r\n", yf_p);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"Ptot: %f\r\n", Ptot);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"yf_q: %f\r\n", yf_q);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"Qtot: %f\r\n", Qtot);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
*/
			uart_xmc_request(1);
		break;

		case 'Q'	:
			sprintf(kal,"DO_K1 ON (CLOSE/TUTUP)\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			SET_BIT(PORT1->OUT,DO_K1);
			flag_K1 = 1; // close
		break;
		case 'q'	:
			sprintf(kal,"DO_K1 OFF (OPEN/BUKA)\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			CLR_BIT(PORT1->OUT,DO_K1);
			flag_K1 = 0; // open
		break;

		case 'W'	:
			sprintf(kal,"DO_K2 ON (CLOSE/TUTUP)\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			SET_BIT(PORT1->OUT,DO_K2);
			flag_K2 = 1; // close
			flag_invalid_K2 = 0;

			flag_disable_fault = 1;
			// matikan proteksi sementara
			NVIC_DisableIRQ(ERU0_0_IRQn);
			NVIC_DisableIRQ(ERU0_1_IRQn);
			//NVIC_DisableIRQ(ERU0_2_IRQn);
			//NVIC_DisableIRQ(ERU0_3_IRQn);
			NVIC_DisableIRQ(ERU1_1_IRQn);
			NVIC_DisableIRQ(ERU1_2_IRQn);
		break;
		case 'w'	:
			sprintf(kal,"DO_K2 OFF (OPEN/BUKA)\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			CLR_BIT(PORT1->OUT,DO_K2);
			flag_K2 = 0; // open
			flag_invalid_K2 = 1;

			flag_disable_fault = 1;
			// matikan proteksi sementara
			NVIC_DisableIRQ(ERU0_0_IRQn);
			NVIC_DisableIRQ(ERU0_1_IRQn);
			//NVIC_DisableIRQ(ERU0_2_IRQn);
			//NVIC_DisableIRQ(ERU0_3_IRQn);
			NVIC_DisableIRQ(ERU1_1_IRQn);
			NVIC_DisableIRQ(ERU1_2_IRQn);
		break;

		case 'E'	:
			sprintf(kal,"DO_K3 ON (CLOSE/TUTUP)\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			SET_BIT(PORT1->OUT,DO_K3);
			flag_K3 = 1; // close
			flag_invalid_K3 = 0;

			flag_disable_fault = 1;
			// matikan proteksi sementara
			NVIC_DisableIRQ(ERU0_0_IRQn);
			NVIC_DisableIRQ(ERU0_1_IRQn);
			//NVIC_DisableIRQ(ERU0_2_IRQn);
			//NVIC_DisableIRQ(ERU0_3_IRQn);
			NVIC_DisableIRQ(ERU1_1_IRQn);
			NVIC_DisableIRQ(ERU1_2_IRQn);
		break;
		case 'e'	:
			sprintf(kal,"DO_K3 OFF (OPEN/BUKA)\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			CLR_BIT(PORT1->OUT,DO_K3);
			flag_K3 = 0; // open
			flag_invalid_K3 = 1;

			flag_disable_fault = 1;
			// matikan proteksi sementara
			NVIC_DisableIRQ(ERU0_0_IRQn);
			NVIC_DisableIRQ(ERU0_1_IRQn);
			//NVIC_DisableIRQ(ERU0_2_IRQn);
			//NVIC_DisableIRQ(ERU0_3_IRQn);
			NVIC_DisableIRQ(ERU1_1_IRQn);
			NVIC_DisableIRQ(ERU1_2_IRQn);
		break;

		case 'R'	:
			sprintf(kal,"DO_HK2 ON (OPEN/BUKA)\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			SET_BIT(PORT1->OUT,DO_HK2);
			flag_HK2=0; // open
		break;
		case 'r'	:
			sprintf(kal,"DO_HK2 OFF (CLOSE/TUTUP)\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			CLR_BIT(PORT1->OUT,DO_HK2);
			flag_HK2=1; // close
		break;

		case 'T'	:
			sprintf(kal,"DOS1 ON\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			SET_BIT(PORT2->OUT,DOS1);
			DOS1_Flag=1;
		break;
		case 't'	:
			sprintf(kal,"DOS1 OFF\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			CLR_BIT(PORT2->OUT,DOS1);
			DOS1_Flag=0;
		break;

		case 'Y'	:
			sprintf(kal,"DOS2 ON\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			SET_BIT(PORT2->OUT,DOS2);
			DOS2_Flag=1;
		break;
		case 'y'	:
			sprintf(kal,"DOS2 OFF\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			CLR_BIT(PORT2->OUT,DOS2);
			DOS2_Flag=0;
		break;

		case 'G'	:
			GST_HIGH();
			sprintf(kal,"GST High");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
		break;

		case 'g'	:
			CLR_BIT(PORT0->OUT,13); //GST_LOW();
			sprintf(kal,"GST Low");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			CLR_BIT(PORT1->OUT,DO_K1);
			CLR_BIT(PORT1->OUT,DO_K2);
			CLR_BIT(PORT1->OUT,DO_K3);
			CLR_BIT(PORT1->OUT,DO_HK2);
			uart_xmc_request(5); //Inverter off

			sprintf(kal,"\r\r>>> PANIC BUTTON <<< \r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal, strlen(kal));

			sprintf(kal,"DCPT2 @NOW: %d; %f\r\n", DCPT2_AIN_Result, (float)((int32_t)DCPT2_AIN_Result-DCPT2_OFFSET)/DCPT2_GRAD);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"ACPT1 @NOW: %d; %f\r\n", ACPT1_AIN_Result, (float)((int32_t)ACPT1_AIN_Result-ACPT1_OFFSET)/ACPT1_GRAD);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"GRPT1 @NOW: %d; %f\r\r\n", GRPT1_AIN_Result, (float)((int32_t)GRPT1_AIN_Result-GRPT1_OFFSET)/GRPT1_GRAD);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
		break;

		case '7'	:
			sprintf(kal,"mode inverter = open loop \r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			uart_xmc_request(2);
		break;

		case '8'	:
			sprintf(kal,"mode inverter = closed loop \r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			uart_xmc_request(3);
		break;

		case 'I'	:
			sprintf(kal,"PWM Inverter on\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			uart_xmc_request(4);
		break;
		case 'i'	:
			sprintf(kal,"PWM Inverter off\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			Vreff_inv = 10;
			teta_manual_fix = 0;
			p_set = 0;
			q_set = 0;
			uart_xmc_request(5);
		break;

		case 'U'	:
			Vreff_inv= Vreff_inv +10;
			if (Vreff_inv > 340){
				Vreff_inv = 340;
			}
			flag_update_send_xmc = 1;
			sprintf(kal,"Vreff inv : %d \r\n",Vreff_inv);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
		break;
		case 'u'	:
			Vreff_inv= Vreff_inv - 10;
			if (Vreff_inv < 10){
				Vreff_inv = 10;
			}
			flag_update_send_xmc =1;
			sprintf(kal,"Vreff inv: %d \r\n",Vreff_inv);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
		break;

		case '.'	:
			pwm_peak_reff = pwm_peak_reff + 50;
			if (pwm_peak_reff > 3740){
				pwm_peak_reff = 3740;
			}
			flag_update_send_xmc = 1;
			sprintf(kal,"PWM inv open loop reff: %d \r\n",pwm_peak_reff);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
		break;
		case ','	:
			pwm_peak_reff = pwm_peak_reff - 50;
			if (pwm_peak_reff < 0){
				pwm_peak_reff = 0;
			}
			flag_update_send_xmc = 1;
			sprintf(kal,"PWM inv open loop reff: %d \r\n",pwm_peak_reff);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
		break;

		case 'D'	:
			sprintf(kal,"droop P on\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			uart_xmc_request(6);
		break;
		case 'd'	:
			sprintf(kal,"droop P off\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			uart_xmc_request(7);
			p_set = 0;
		break;

		case 'L'	:
			sprintf(kal,"PLL on\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			uart_xmc_request(8);
		break;
		case 'l'	:
			sprintf(kal,"PLL off\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			uart_xmc_request(9);
		break;

		case 'S'	:
			sprintf(kal,"Sinkronisasi 1 on\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			uart_xmc_request(10);
		break;
		case 's'	:
			sprintf(kal,"Sinkronisasi 1 off\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			uart_xmc_request(11);
		break;

		case 'K'	:
			teta_manual_fix++;
			sprintf(kal,"counter teta_manual_fix = %d\r\n", teta_manual_fix);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			uart_xmc_request(12);
		break;
		case 'k'	:
			teta_manual_fix--;
			sprintf(kal,"counter teta_manual_fix = %d\r\n", teta_manual_fix);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			uart_xmc_request(13);
		break;

		case 'F'	:
			sprintf(kal,"droop Q on\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			uart_xmc_request(14);
		break;
		case 'f'	:
			sprintf(kal,"droop Q off\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			uart_xmc_request(15);
			q_set = 0;
		break;

		case 'P'	:
			p_set = p_set + 100;
			if (p_set > 6400){
				p_set = 6400;
			}
			flag_update_send_xmc = 1;
			sprintf(kal,"p_set inv : %d \r\n",p_set);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
		break;
		case 'p'	:
			p_set = p_set - 100;
			if (p_set < -5000){
				p_set = -5000;
			}
			flag_update_send_xmc = 1;
			sprintf(kal,"p_set inv : %d \r\n",p_set);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
		break;

		case 'O'	:
			q_set = q_set + 100;
			if (q_set > 5000){
				q_set = 5000;
			}
			flag_update_send_xmc = 1;
			sprintf(kal,"q_set inv : %d \r\n",q_set);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
		break;
		case 'o'	:
			q_set = q_set - 100;
			if (q_set < -5000){
				q_set = -5000;
			}
			flag_update_send_xmc = 1;
			sprintf(kal,"q_set inv : %d \r\n",q_set);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
		break;

		case '0'	:
			fault_count = 0;
			DCPT2_Fault = 0;
			GD1_Fault = 0;
			sprintf(kal,"Fault Count Reset\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			GST_HIGH();

			NVIC_EnableIRQ(ERU0_0_IRQn);
			NVIC_EnableIRQ(ERU0_1_IRQn);
			//NVIC_EnableIRQ(ERU0_2_IRQn);
			//NVIC_EnableIRQ(ERU0_3_IRQn);
			NVIC_EnableIRQ(ERU1_1_IRQn);
			NVIC_EnableIRQ(ERU1_2_IRQn);
		break;

		case '`'	:
			uart_xmc_request(1);

			sprintf(kal,"p_set_hmi = %d\r\n", p_set_hmi);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			sprintf(kal,"q_set_hmi = %d\r\n", q_set_hmi);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			sprintf(kal,"p_set = %d\r\n", p_set);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			sprintf(kal,"q_set = %d\r\n", q_set);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			sprintf(kal,"p_set_feedback = %d\r\n", p_set_feedback);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			sprintf(kal,"q_set_feedback = %d\r\n", q_set_feedback);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			sprintf(kal,"Ptot = %d\r\n", Ptot);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			sprintf(kal,"Qtot = %d\r\n", Qtot);
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

			sprintf(kal,"\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

		break;

		case 'M'	:
			sprintf(kal,"data rabbit enable\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			data_rabbit_enable = TRUE;
		break;
		case 'm'	:
			sprintf(kal,"data rabbit disable\r\n");
			UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
			data_rabbit_enable = FALSE;
		break;


		default		:
		break;
	}

	//clear ch
	ch=0;

	//Clear UART Receive Interrupt
	SET_BIT(UART_RS232->TRBSCR,USIC_CH_TRBSCR_CSRBI_Pos);
}

void UART_XMC_Handler(void)	//interrupt handler UARTXMC U2Ch0
{
	char data;

	data=UART_U1->OUTR;

	string_read_xmc[string_read_xmc_increment]= data;

	if(data == 'T'){
		flag_update_receive_xmc=1;
		string_read_xmc_increment=-1;
	}
	else if(data == 'X'){
		flag_data_receive_xmc =1;
		string_read_xmc_increment=-1;
	}

	string_read_xmc_increment++;

	SET_BIT(UART_U1->TRBSCR,USIC_CH_TRBSCR_CSRBI_Pos);
}

// Function called at the end of the transfer
void end_transfer_handler(DMA_IRQType IRQType, uint32_t CbArg)
{
	char kal[32];

	g_endTransfer = true;

	// check TRBSR register whether the TEMPTY bit has been cleared
	while(RD_REG(UART_RS485->TRBSR,USIC_CH_TRBSR_TEMPTY_Msk,USIC_CH_TRBSR_TEMPTY_Pos)==0);
	//disable TX driver
	CLR_BIT(PORT1->OUT,SEL_485);
	//SET_BIT(GPDMA0->CLEARTFR,GPDMA0_CLEARTFR_CH5_Pos);
}

void PWM1A1B_IRQ_Handler(void)	//interrupt handler PWM_1A_1B CCU81.SR3
{
	char kal[32];

	while(CheckBit(VADC_G0->RESD[CT1_Result_Register],VADC_G_RESD_VF_Pos)==0);
	CT1_Result = VADC_G0->RES[CT1_Result_Register] & VADC_G_RES_RESULT_Msk;

	while(CheckBit(VADC_G0->RESD[CT2_Result_Register],VADC_G_RESD_VF_Pos)==0);
	CT2_Result = VADC_G0->RES[CT2_Result_Register] & VADC_G_RES_RESULT_Msk;

	while(CheckBit(VADC_G0->RESD[CT3_Result_Register],VADC_G_RESD_VF_Pos)==0);
	CT3_Result = VADC_G0->RES[CT3_Result_Register] & VADC_G_RES_RESULT_Msk;

	while(CheckBit(VADC_G0->RESD[CT4_Result_Register],VADC_G_RESD_VF_Pos)==0);
	CT4_Result = VADC_G0->RES[CT4_Result_Register] & VADC_G_RES_RESULT_Msk;

	while(CheckBit(VADC_G0->RESD[DCPT1_AIN_Result_Register],VADC_G_RESD_VF_Pos)==0);
	DCPT1_AIN_Result = VADC_G0->RES[DCPT1_AIN_Result_Register] & VADC_G_RES_RESULT_Msk;

	while(CheckBit(VADC_G0->RESD[DCPT2_AIN_Result_Register],VADC_G_RESD_VF_Pos)==0);
	DCPT2_AIN_Result = VADC_G0->RES[DCPT2_AIN_Result_Register] & VADC_G_RES_RESULT_Msk;
	DCPT2_fix = ((int32_t)DCPT2_AIN_Result-DCPT2_OFFSET)*DCPT2_GRAD_FIX;

	if ((DCPT2_Fault >2) || (GD1_Fault ==1) || (fault_count>2)) {

		CLR_BIT(PORT0->OUT,13); //GST_LOW();
		CLR_BIT(PORT1->OUT,DO_K1);
		CLR_BIT(PORT1->OUT,DO_K2);
		CLR_BIT(PORT1->OUT,DO_K3);
		CLR_BIT(PORT1->OUT,DO_HK2);

		if (flag_fault = 0){
			Vreff_inv = 10; // referensi inverter dibuat jadi 10 V
			flag_fault = 1;
			uart_xmc_request(5); //Inverter off
			flag_update_send_xmc = 1; // kirim referensi baru ke inverter
		}

		DCPT2_Fault = 0;
		fault_count = 0;
		GD1_Fault = 0;

		state_fsm = 7;

		sprintf(kal,"\r\r>>> STOPPED BY FAULT <<< \r\n");
		UART001_WaitWriteDataMultiple(UART_RS232,kal, strlen(kal));

		sprintf(kal,"DCPT2 @Fault: %d; %f\r\n", DCPT2_AIN_Result, (float)((int32_t)DCPT2_AIN_Result-DCPT2_OFFSET)/DCPT2_GRAD);
		UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

		sprintf(kal,"ACPT1 @Fault: %d; %f\r\n", ACPT1_AIN_Result, (float)((int32_t)ACPT1_AIN_Result-ACPT1_OFFSET)/ACPT1_GRAD);
		UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

		sprintf(kal,"GRPT1 @Fault: %d; %f\r\r\n", GRPT1_AIN_Result, (float)((int32_t)GRPT1_AIN_Result-GRPT1_OFFSET)/GRPT1_GRAD);
		UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
	}

	//Clear Interrupt
	SET_BIT(PWM_1A_1B->SWR,CCU8_CC8_SWR_RCM1D_Pos);
	SET_BIT(PWM_1A_1B->SWR,CCU8_CC8_SWR_RCM2D_Pos);
}

void PWM2A2B_IRQ_Handler(void)	//interrupt handler PWM_2A_2B CCU81.SR1
{
	//Clear Interrupt
	SET_BIT(PWM_2A_2B->SWR,CCU8_CC8_SWR_RCM1D_Pos);
	SET_BIT(PWM_2A_2B->SWR,CCU8_CC8_SWR_RCM2D_Pos);
}

void PWM3A3B_IRQ_Handler(void)	//interrupt handler PWM_3A_3B CCU81.SR2
{
	while(CheckBit(VADC_G2->RESD[CT5_Result_Register],VADC_G_RESD_VF_Pos)==0);
	CT5_Result = VADC_G2->RES[CT5_Result_Register] & VADC_G_RES_RESULT_Msk;

	while(CheckBit(VADC_G2->RESD[CT6_Result_Register],VADC_G_RESD_VF_Pos)==0);
	CT6_Result = VADC_G2->RES[CT6_Result_Register] & VADC_G_RES_RESULT_Msk;

	while(CheckBit(VADC_G1->RESD[CT7_Result_Register],VADC_G_RESD_VF_Pos)==0);
	CT7_Result = VADC_G1->RES[CT7_Result_Register] & VADC_G_RES_RESULT_Msk;

	while(CheckBit(VADC_G1->RESD[CT8_Result_Register],VADC_G_RESD_VF_Pos)==0);
	CT8_Result = VADC_G1->RES[CT8_Result_Register] & VADC_G_RES_RESULT_Msk;

	while(CheckBit(VADC_G2->RESD[ACPT1_AIN_Result_Register],VADC_G_RESD_VF_Pos)==0);
	ACPT1_AIN_Result = VADC_G2->RES[ACPT1_AIN_Result_Register] & VADC_G_RES_RESULT_Msk;

	while(CheckBit(VADC_G2->RESD[ACPT2_AIN_Result_Register],VADC_G_RESD_VF_Pos)==0);
	ACPT2_AIN_Result = VADC_G2->RES[ACPT2_AIN_Result_Register] & VADC_G_RES_RESULT_Msk;

	while(CheckBit(VADC_G2->RESD[ACPT3_AIN_Result_Register],VADC_G_RESD_VF_Pos)==0);
	ACPT3_AIN_Result = VADC_G2->RES[ACPT3_AIN_Result_Register] & VADC_G_RES_RESULT_Msk;

	while(CheckBit(VADC_G2->RESD[GRPT1_AIN_Result_Register],VADC_G_RESD_VF_Pos)==0);
	GRPT1_AIN_Result = VADC_G2->RES[GRPT1_AIN_Result_Register] & VADC_G_RES_RESULT_Msk;

	while(CheckBit(VADC_G2->RESD[GRPT2_AIN_Result_Register],VADC_G_RESD_VF_Pos)==0);
	GRPT2_AIN_Result = VADC_G2->RES[GRPT2_AIN_Result_Register] & VADC_G_RES_RESULT_Msk;

	while(CheckBit(VADC_G2->RESD[GRPT3_AIN_Result_Register],VADC_G_RESD_VF_Pos)==0);
	GRPT3_AIN_Result = VADC_G2->RES[GRPT3_AIN_Result_Register] & VADC_G_RES_RESULT_Msk;

	//Clear Interrupt
	SET_BIT(PWM_3A_3B->SWR,CCU8_CC8_SWR_RCM1D_Pos);
	SET_BIT(PWM_3A_3B->SWR,CCU8_CC8_SWR_RCM2D_Pos);
}
