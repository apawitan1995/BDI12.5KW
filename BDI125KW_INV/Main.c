/*
 * Main.c
 *
 *  Created on: Mar 19, 2014
 *      Author: Angga
 */
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
//#include "peripheral/DMA_app.h"
#include "peripheral/DAC_app.h"
#include "peripheral/ERU_app.h"
#include "peripheral/I2C_SW_app.h"
//#include "peripheral/CAN_app.h"
#include "peripheral/ISR_app.h"
#include "peripheral/SPI_app.h"

#include "external/EEP25LC1024_app.h"
#include "external/display_app.h"
#include "external/AD5328_app.h"
#include "external/MCP79410_app.h"
#include "external/button_app.h"
#include "external/relay_app.h"

//#include "algorithm/converter.h"
#include "algorithm/inverter.h"

volatile int timeout_grid_available=0;
volatile int timeout_grid_unavailable=0;

void update_data(void);


int main(void)
{
	char kal[32]; // string for debugging on main

	PWM_Inverter_Disable();

	DAVE_Init();			// Initialization of DAVE Apps
	My_DAVE_MUX_Init();

	DAC_Init();

	UART_Init();

	DO_Profiling_Init();
	IO_Slave_Status_Init();
	IO_COM_Init();

	PWM_Inverter_Init();

	ADC_Init();

	PWM_Inverter_Start();

	PWM_Enable_Interrupt_NVIC();

	sprintf(kal,"cek uart xmc 2");
	UART001_WaitWriteDataMultiple(UART_U2,kal, strlen(kal));

	int j;
	for(j=0;j<30;j++) My_Delay_ms(100);

	int i;
	for(i=0;i<10;i++) {
	My_Delay_ms(100);
	CT1_OFF += CT1_Result;
	CT2_OFF += CT2_Result;
	CT3_OFF += CT3_Result;
	CT4_OFF += CT4_Result;
	CT5_OFF += CT5_Result;
	CT6_OFF += CT6_Result;
	CT7_OFF += CT7_Result;
	CT8_OFF += CT8_Result;
	}

	CT1_OFF = CT1_OFF*0.1;
	CT2_OFF = CT2_OFF*0.1;
	CT3_OFF = CT3_OFF*0.1;
	CT4_OFF = CT4_OFF*0.1;
	CT5_OFF = CT5_OFF*0.1;
	CT6_OFF = CT6_OFF*0.1;
	CT7_OFF = CT7_OFF*0.1;
	CT8_OFF = CT8_OFF*0.1;


	while(1)
	{
/*
		if (flag_grid_available == 1){
			timeout_grid_available++;
			if (timeout_grid_available>=100){
				timeout_grid_available=0;
				flag_grid_available =0;

				flag_alone_tied = 1;
				flag_tied_alone=0;
				flag_update_send_xmc = 1;
			}
		}

		if (flag_grid_unavailable == 1){
			timeout_grid_unavailable++;
			if (timeout_grid_unavailable>=100){
				timeout_grid_unavailable=0;
				flag_grid_unavailable =0;
				flag_alone_tied = 0;
				Sinkronisasi = FALSE;
				PLL_status = FALSE;
				flag_tied_alone=1;
				flag_update_send_xmc = 1;
			}
		}
*/
		update_data();
	}
	return 0;
}

void update_data(void){
	if (flag_update_send_xmc == 1){

		//data_uart_xmc[0]= comparepwm4;
		//data_uart_xmc[1]= pwm_peak; //pwm open loop
		//data_uart_xmc[2]= volt_ref; //Volt ref closed loop
		data_uart_xmc[3]= (Pow_Filt_1 + Pow_Filt_2);
		data_uart_xmc[4]= (Q_Filt_1 + Q_Filt_2);
		//data_uart_xmc[5] = p_set;
		//data_uart_xmc[6] = q_set;

		//data_uart_xmc[13]= flag_tied_alone; //Volt ref closed loop
		//data_uart_xmc[14]= flag_alone_tied;

		uart_xmc_send();
		flag_update_send_xmc=0;
	}
	if(flag_update_receive_xmc == 1){
		uart_xmc_receive();
		string_read_xmc_increment=0;

		pwm_peak = data_uart_xmc[0];
		volt_ref = data_uart_xmc[1];
		p_set = data_uart_xmc[2];
		q_set = data_uart_xmc[3];

		flag_phase = data_uart_xmc[4];

		flag_update_receive_xmc = 0;
	}
}
