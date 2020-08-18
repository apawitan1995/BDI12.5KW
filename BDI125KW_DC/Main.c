/*
 * Main.c
 *
 *  Created on: Mar 19, 2014 - 2016
 *      Author: Angga, Bima, Iqbal, Mukhlis, Arif

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
#include "algorithm/datainverter.h"
#include "algorithm/fixed_operation.h"

// ini untuk FSM
int flag_prep;
int finish_prep;
int flag_precharging;
int finish_precharging;
int flag_timer;
int flag_timer_nobuzz;
int flag_menu;
int flag_button;
int timeout;
uint8_t minute_start;
uint8_t second_start;
int flag_relaystandby;
int counter_feedback;
int counter_dummy;

uint8_t minute_start_state;
uint8_t second_start_state;
uint8_t minute;
uint8_t second;
uint8_t hour;
char kal1[15];
char kal2[15];
char kal1_old[15];
char kal2_old[15];
//int state_fsm; //pindah ke ISR
//int prev_state_fsm; //pindah ke ISR
//int next_state_fsm; //pindah ke ISR
char buf[15];

// Ini untuk Menu
int flag_change = 0;
int max_PWM = 3745; // ini minimum
int min_PWM = 745; // ini maximum
int max_Index_Modulasi = 3375; // ini minimum
int min_Index_Modulasi = 0; // ini maximum
int max_QREF = 5000; // ini minimum
int min_QREF = 0; // ini maximum
int max_ADC = 1900;
int min_ADC = 0;
int max_menu_standby = 1;
int min_menu_standby = 0;
int max_menu_operation = 9;
int min_menu_operation = 0;
volatile int temp;
int change = 0;
//int state;
//int previous_state;
volatile int state_menu;

// untuk tombol
char button[4];
char flag_push[4];

// untuk membuat referensi voltage controller ( debug only )
uint8_t minute_start_reff;
uint8_t second_start_reff;
uint8_t minute_reff;
uint8_t second_reff;
int flag_reff=0;
int timeout_reff=0;
int state_reff=0;

// untuk cek adc
int state_adc;

// untuk otomasi
volatile int time_activate_deactivate = -1;
volatile int time_finish_voltage_ac=0;
volatile int voltage_reference =0;
volatile int flag_increase_voltage_ac=0;
volatile int time_finish_power=0;
volatile int power_reference =0;
volatile int flag_increase_power=0;
volatile int flag_close_rabbit =0;
volatile int count_check = 0;
volatile int check_ac_voltage = 0;

volatile int flag_tied_alone = 0;
volatile int flag_alone_tied = 0;

// untuk fault
volatile int32_t timeout_disable_fault=0;
volatile int flag_disable_fault;

// untuk otomasi
volatile int32_t timeout_state=1;
volatile int flag_phase;

// untuk droop
volatile int32_t timeout_droop=0;
volatile int flag_drop;

void FSM (void);
void initialization (void);
void preparation (void);
void precharging (void);
void read_button (void);
void start_boost_operation (void);
void add_boost_output_voltage(void);
void print_lcd (void);
void update_data(void);

// Deklarasi fungsi
void menu_standby(void);
void timer_state_nobuzz(int count_num);

int main(void)
{
	initialization();

	while(1)
	{
		sprintf(kal1,"<%d> | DC = %3.0fV", state_fsm, fixed2float(DCPT2_fix,10));

		FSM();
		print_lcd();
		update_data();

		if (flag_disable_fault == 1){
			timeout_disable_fault++;
			if (timeout_disable_fault>=15){
				timeout_disable_fault=0;
				flag_disable_fault =0;

				NVIC_EnableIRQ(ERU0_0_IRQn);
				NVIC_EnableIRQ(ERU0_1_IRQn);
				//NVIC_EnableIRQ(ERU0_2_IRQn);
				//NVIC_EnableIRQ(ERU0_3_IRQn);
				NVIC_EnableIRQ(ERU1_1_IRQn);
				NVIC_EnableIRQ(ERU1_2_IRQn);
			}
		}
/*
		if ( flag_tied_alone == 1 || flag_alone_tied == 1){
			state_fsm = 6;
			if ( flag_tied_alone == 1){
				next_state_fsm = 5;
			}
			else if (flag_alone_tied== 1){
				next_state_fsm = 4;
			}
		}
*/
		if ( fault_count > 2 && (state_fsm != 7 && state_fsm != 8) ){
			state_fsm = 7;
		}

	}
	return 0;
}


void FSM (void){
	char time[15];
			Button_Read(button,flag_push);
			// check state machine whenever posible moderate priority

				if(state_fsm == 0){
					sprintf(kal2,"Preparation");
					//lcd_puts(kal2);
					if(flag_prep == 0 && finish_prep == 0){
					preparation();
					flag_prep = 1;
					}
					if (finish_prep == 1){
					flag_prep = 0;
					state_fsm = 1;
					}
				}
				else if ( state_fsm == 1){

					if (flag_relaystandby == 0){
						CLR_BIT(PORT0->OUT,13); //GST_LOW();
						CLR_BIT(PORT1->OUT,DO_K1);
						CLR_BIT(PORT1->OUT,DO_K2);
						CLR_BIT(PORT1->OUT,DO_K3);
						CLR_BIT(PORT1->OUT,DO_HK2);

						flag_relaystandby = 1;
					}

					sprintf(kal2,"Stdby");

					if (next_state_fsm == 4){
						strcat(kal2,", GridTied");
					}
					else if (next_state_fsm == 5){
						if (flag_phase == 1){
							strcat(kal2,", SA-Mstr R");
						}
						else if (flag_phase == 2){
							strcat(kal2,", SA-Mstr S");
						}
						else if (flag_phase == 3){
							strcat(kal2,", SA-Mstr T");
						}
						else if (flag_phase == 4){
							strcat(kal2,", SA-Slave");
						}
						else {
							strcat(kal2,", SA-Phase?");
						}
					}
					else{
						strcat(kal2,", Mode ?");
					}

					// kendali oleh tombol
					if ( button[0] == '0' && button[1] == '0'){
						flag_button=0;
					}
					if ( button[2] == '1'){
						state_fsm = 10; // state menu ( menu hanya ada pada saat standby )
						flag_push[2]='1';
						flag_relaystandby = 0;
					}
					if ( button[0] == '1' && button[1] == '1' && flag_button == 0){
						prev_state_fsm = 1;
						state_fsm = 9; // state check tombol
						flag_relaystandby = 0;
					}
				}

				else if ( state_fsm == 11){
					timer_state_nobuzz(240);

					sprintf(kal2,"Precharging %3.0f%c",fixed2float(DCPT2_fix,10)/360*100,'%');

					if ( button[2] == '1' && button[3] == '1'){
						fault_count=6;
						state_fsm = 7;
						timeout_state=0;
						flag_timer_nobuzz=0;
					}

					if (timeout_state == 1){
						state_fsm = 1;
						//next_state_fsm = 1;
						Close_HK2();

						timeout_state=0;
						flag_timer_nobuzz = 0;
					}

					if(finish_precharging == 0){
						precharging();
					}
					else if (finish_precharging == 1){
						finish_precharging = 0;

						timeout_state=0;
						flag_timer_nobuzz = 0;

						Close_K1();

						if (next_state_fsm == 4){
							state_fsm = 2;
							next_state_fsm = 1;
							flag_activation = 1;
						}
						else if (next_state_fsm == 5){
							state_fsm = 3;
							next_state_fsm = 1;
							flag_activation = 1;
							}
					}
				}

				else if ( state_fsm == 2){ // state untuk proses aktivasi atau deaktivasi Standby-GridTied

					if (flag_activation==1 && flag_deactivation == 0 ){
						timer_state_nobuzz(1);
						if ( button[2] == '1' && button[3] == '1'){
							fault_count=6;
							state_fsm = 7;
							timeout_state=0;
							flag_timer_nobuzz=0;
							time_activate_deactivate = -1;
							time_finish_voltage_ac=0;
							flag_increase_voltage_ac =0;
						}
						if (time_activate_deactivate == -1){
							time_activate_deactivate = 120;
							time_finish_voltage_ac=0;
						}
						else if(time_activate_deactivate >= 116 && timeout_state ==1){
							sprintf(kal2,"Activate in %dS",(time_activate_deactivate-115));
						}
						else if (time_activate_deactivate == 115 && timeout_state ==1){
							sprintf(kal2,"HK2 open");
							Open_HK2();
							flag_HK2 = 1;
						}
						else if (time_activate_deactivate == 110 && timeout_state ==1){
							sprintf(kal2,"Start PWM");
							GST_HIGH();
							uart_xmc_request(4); // nyalakan PWM Inverter
							Vreff_inv = 10; // ref V peak inverter dimulai dari 10 V
							voltage_reference = 310; // V peak yang dituju
						}
						else if (time_activate_deactivate == 108 && timeout_state ==1){
							sprintf(kal2,"PLL on");
							uart_xmc_request(8); // nyalakan PLL inverter
						}
						else if (time_activate_deactivate == 105 && timeout_state ==1){
							sprintf(kal2,"Synch on");
							uart_xmc_request(10); // nyalakan sinkronisasi
							flag_increase_voltage_ac =1;
						}
						else if(flag_increase_voltage_ac == 1 && timeout_state == 1){
							Vreff_inv = Vreff_inv + 10;
							if (Vreff_inv > voltage_reference){
								Vreff_inv = voltage_reference;
								flag_increase_voltage_ac=0;
								time_finish_voltage_ac = time_activate_deactivate;
								voltage_reference = 0; // reset voltage reference
							}
							sprintf(kal2,"Vp = %dV",Vreff_inv);
							flag_update_send_xmc = 1;

						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-3) && timeout_state ==1){
							sprintf(kal2,"Finished!");
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-5) && timeout_state ==1){
							sprintf(kal2,"K2 close");
							Close_K2();
							flag_K2 = 1; // close
							flag_disable_fault =1;

							// matikan proteksi sementara untuk DCPT2 dan DCPT1
							NVIC_DisableIRQ(ERU0_0_IRQn);
							NVIC_DisableIRQ(ERU0_1_IRQn);
							NVIC_DisableIRQ(ERU1_1_IRQn);
							NVIC_DisableIRQ(ERU1_2_IRQn);
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-8) && timeout_state ==1){
							sprintf(kal2,"K3 close");
							Close_K3();
							flag_K3 = 1; // close
							flag_disable_fault =1;

							// matikan proteksi sementara untuk DCPT2 dan DCPT1
							NVIC_DisableIRQ(ERU0_0_IRQn);
							NVIC_DisableIRQ(ERU0_1_IRQn);
							NVIC_DisableIRQ(ERU1_1_IRQn);
							NVIC_DisableIRQ(ERU1_2_IRQn);
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-9) && timeout_state ==1){
							sprintf(kal2,"Droop P on");
							uart_xmc_request(6); //Droop P Activated
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-10) && timeout_state ==1){
							sprintf(kal2,"Droop Q on");
							uart_xmc_request(14); //Droop Q Activated
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-12) && timeout_state ==1){
							sprintf(kal2,"");
							flag_activation=0;
							time_activate_deactivate = 0;
							state_fsm = 4;

						}

						if (timeout_state==1){
							if (fault_count <= 2){
								fault_count = 0; // bila fault count kurang dari 2 ketika dilakukan 1 perintah operasi, berarti sebenernya gak ada fault
							}
							// reset timer untuk menghitung detik pakai RTC
							timeout_state=0;
							time_activate_deactivate -= 1;
							flag_timer_nobuzz=0;
						}

					}
					else if (flag_deactivation==1 && flag_activation == 0){
						timer_state_nobuzz(1);
						if ( button[2] == '1' && button[3] == '1'){
							fault_count=6;
							state_fsm = 7;
							timeout_state=0;
							flag_timer_nobuzz=0;
							time_activate_deactivate = -1;
							time_finish_voltage_ac=0;
							flag_increase_voltage_ac =0;
						}
						if (time_activate_deactivate == -1){
							time_activate_deactivate = 120;
							time_finish_voltage_ac=0;
							//timeout_state =1;
						}
						else if(time_activate_deactivate >= 116 && timeout_state ==1){
							sprintf(kal2,"Deactivate in %dS",(time_activate_deactivate-115));
						}
						else if(time_activate_deactivate == 115 && timeout_state ==1){
							sprintf(kal2,"K3 open");
							Open_K3();
							flag_K3=0; // open
							flag_disable_fault = 1;

							// matikan proteksi sementara
							NVIC_DisableIRQ(ERU0_0_IRQn);
							NVIC_DisableIRQ(ERU0_1_IRQn);
							NVIC_DisableIRQ(ERU1_1_IRQn);
							NVIC_DisableIRQ(ERU1_2_IRQn);
						}
						else if(time_activate_deactivate == 112 && timeout_state ==1){
							sprintf(kal2,"K2 open");
							Open_K2();
							flag_K2=0; // open
							flag_disable_fault = 1;

							// matikan proteksi sementara
							NVIC_DisableIRQ(ERU0_0_IRQn);
							NVIC_DisableIRQ(ERU0_1_IRQn);
							NVIC_DisableIRQ(ERU1_1_IRQn);
							NVIC_DisableIRQ(ERU1_2_IRQn);
						}
						else if(time_activate_deactivate == 110 && timeout_state ==1){
							sprintf(kal2,"Droop Q Off");
							uart_xmc_request(15); // matikan droop Q

							//untuk tanpa Droop P off, synch off, PLL off dulu
							voltage_reference = 10; // kembalikan ref tegangan ke 10v dimatikan
							flag_increase_voltage_ac=1;
						}
						/*
						else if(time_activate_deactivate >= 112 && timeout_state ==1){
							sprintf(kal2,"Droop Off");
							uart_xmc_request(7); // matikan droop P
						}
						else if (time_activate_deactivate == 110 && timeout_state ==1){
							sprintf(kal2,"synchron off");
							uart_xmc_request(11); // matikan Sinkronisasi
						}
						else if (time_activate_deactivate == 105 && timeout_state ==1){
							sprintf(kal2,"PLL Off");
							uart_xmc_request(9); // matikan PLL
							voltage_reference = 10; // kembalikan ref tegangan ke 10v dimatikan
							flag_increase_voltage_ac=1;
						}
						*/
						else if(flag_increase_voltage_ac == 1 && timeout_state == 1){
							Vreff_inv = Vreff_inv - 10;
							if (Vreff_inv <= voltage_reference){
								Vreff_inv = voltage_reference;
								flag_increase_voltage_ac=0;
								time_finish_voltage_ac = time_activate_deactivate;
								voltage_reference = 0;
								}
							sprintf(kal2,"Vp = %dV",Vreff_inv);
							flag_update_send_xmc = 1;
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-5) && timeout_state ==1){
							sprintf(kal2,"Stop PWM");
							uart_xmc_request(5); // matikan PWM Inverter
							//off droop p, sinkron, pll diakhirkan
							uart_xmc_request(7); // matikan droop P
							uart_xmc_request(11); // matikan Sinkronisasi
							uart_xmc_request(9); // matikan PLL
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-7) && timeout_state ==1){
							GST_LOW();
							// lakukan reset semua kontrol di sini kalau ada
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-9) && timeout_state ==1){
							sprintf(kal2,"K1-HK2 Off");
							//sprintf(kal2,"");
							Close_HK2();
							flag_HK2 = 0;
							Open_K1();
							flag_K1 = 0;
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-15) && timeout_state ==1){
							sprintf(kal2,"");
							flag_deactivation=0;
							time_activate_deactivate =0;
							state_fsm = 1;
							flag_relaystandby = 0;
						}
						if (timeout_state==1){
							if (fault_count <= 2){
								fault_count = 0;
							}
							timeout_state=0;
							time_activate_deactivate -= 1;
							flag_timer_nobuzz=0;
						}
					}
					else {
						timeout_state=0;
						time_activate_deactivate = -1;
						time_finish_voltage_ac=0;
						flag_increase_voltage_ac =0;
					}
				}

				else if ( state_fsm == 3){ // state untuk proses aktivasi atau deaktivasi Standby-StandAlone

					if (flag_activation==1 && flag_deactivation == 0 ){
						timer_state_nobuzz(1);
						if ( button[2] == '1' && button[3] == '1'){
							fault_count=6;
							state_fsm = 7;
							timeout_state=0;
							flag_timer_nobuzz=0;
							time_activate_deactivate = -1;
							time_finish_voltage_ac=0;
							flag_increase_voltage_ac =0;
						}
						if (time_activate_deactivate == -1){
							time_activate_deactivate = 120;
							time_finish_voltage_ac=0;
						}
						else if(time_activate_deactivate >= 116 && timeout_state ==1){
							sprintf(kal2,"Activate in %dS",(time_activate_deactivate-115));
						}
						else if (time_activate_deactivate == 115 && timeout_state ==1){
							sprintf(kal2,"HK2 open");
							Open_HK2();
							flag_HK2 = 1;
						}
						else if (time_activate_deactivate == 110 && timeout_state ==1){
							sprintf(kal2,"Start PWM");
							GST_HIGH();
							uart_xmc_request(4); // nyalakan PWM Inverter
							Vreff_inv = 10; // ref V peak inverter dimulai dari 10 V
							voltage_reference = 310; // V peak yang dituju
						}
						else if (time_activate_deactivate == 108 && timeout_state == 1 && flag_phase == 1){ // Fasa R Master
							sprintf(kal2,"Master-R");
							//gak pake PLL
						}
						else if (time_activate_deactivate == 108 && timeout_state == 1 && flag_phase == 2){ // Fasa S Master
							sprintf(kal2,"Master-S");
							uart_xmc_request(8); // nyalakan PLL inverter tergeser -120 derajat
							//PLL GRPT3 -120 derajat
							}
						else if (time_activate_deactivate == 108 && timeout_state == 1 && flag_phase == 3){ // Fasa T Master
							sprintf(kal2,"Master-T");
							uart_xmc_request(8); // nyalakan PLL inverter tergeser +120 derajat
							//PLL GRPT3 +120 derajat
							}
						else if (time_activate_deactivate == 108 && timeout_state == 1 && flag_phase == 4){ // Slave
							sprintf(kal2,"Slave");
							uart_xmc_request(8); // nyalakan PLL inverter
							}
						else if (time_activate_deactivate == 105 && timeout_state == 1 && flag_phase == 1 ){ // Fasa R Master
							sprintf(kal2,"Master-R");
							// Tidak ada sinkronisasi
							flag_increase_voltage_ac =1;
						}
						else if (time_activate_deactivate == 105 && timeout_state == 1 && (flag_phase == 2 || flag_phase == 3 || flag_phase == 4) ){ // Fasa sisanya
							sprintf(kal2,"Synch on");
							uart_xmc_request(10); // nyalakan sinkronisasi
							flag_increase_voltage_ac =1;
							}
						else if(flag_increase_voltage_ac == 1 && timeout_state == 1){
							Vreff_inv = Vreff_inv + 10;
							if (Vreff_inv > voltage_reference){
								Vreff_inv = voltage_reference;
								flag_increase_voltage_ac = 0;
								time_finish_voltage_ac = time_activate_deactivate;
								voltage_reference = 0; // reset voltage reference
							}
							sprintf(kal2,"Vp = %dV",Vreff_inv);
							flag_update_send_xmc = 1;

						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-3) && timeout_state ==1){
							sprintf(kal2,"Finished!");
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-5) && timeout_state ==1){
							sprintf(kal2,"K2 close");
							Close_K2();
							flag_K2 = 1; // close
							flag_disable_fault = 1;

							// matikan proteksi sementara untuk DCPT2 dan DCPT1
							NVIC_DisableIRQ(ERU0_0_IRQn);
							NVIC_DisableIRQ(ERU0_1_IRQn);
							NVIC_DisableIRQ(ERU1_1_IRQn);
							NVIC_DisableIRQ(ERU1_2_IRQn);
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-8) && timeout_state ==1){
							sprintf(kal2,"K3 close");
							Close_K3();
							flag_K3 = 1; // close
							flag_disable_fault =1;

							// matikan proteksi sementara untuk DCPT2 dan DCPT1
							NVIC_DisableIRQ(ERU0_0_IRQn);
							NVIC_DisableIRQ(ERU0_1_IRQn);
							NVIC_DisableIRQ(ERU1_1_IRQn);
							NVIC_DisableIRQ(ERU1_2_IRQn);
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-9) && timeout_state ==1){
							sprintf(kal2,"Droop P on");
							uart_xmc_request(6); //Droop P Activated
							//flag_droop = 1;
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-10) && timeout_state ==1){
							sprintf(kal2,"Synch off");
							uart_xmc_request(11); //Synch off
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-12) && timeout_state ==1){
							sprintf(kal2,"");
							flag_activation=0;
							time_activate_deactivate = 0;
							state_fsm = 5;
						}

						if (timeout_state==1){
							if (fault_count <= 2){
								fault_count = 0; // bila fault count kurang dari 2 ketika dilakukan 1 perintah operasi, berarti sebenernya gak ada fault
							}
							// reset timer untuk menghitung detik pakai RTC
							timeout_state=0;
							time_activate_deactivate -= 1;
							flag_timer_nobuzz=0;
						}

					}
					else if (flag_deactivation==1 && flag_activation == 0){
						timer_state_nobuzz(1);
						if ( button[2] == '1' && button[3] == '1'){
							fault_count=6;
							state_fsm = 7;
							timeout_state=0;
							flag_timer_nobuzz=0;
							time_activate_deactivate = -1;
							time_finish_voltage_ac=0;
							flag_increase_voltage_ac =0;
						}
						if (time_activate_deactivate == -1){
							time_activate_deactivate = 120;
							time_finish_voltage_ac=0;
							//timeout_state =1;
						}
						else if(time_activate_deactivate >= 116 && timeout_state ==1){
							sprintf(kal2,"Deactivate in %dS",(time_activate_deactivate-115));
						}
						else if(time_activate_deactivate == 115 && timeout_state ==1){
							sprintf(kal2,"K3 open");
							Open_K3();
							flag_K3=0; // open
							flag_disable_fault = 1;

							// matikan proteksi sementara
							NVIC_DisableIRQ(ERU0_0_IRQn);
							NVIC_DisableIRQ(ERU0_1_IRQn);
							NVIC_DisableIRQ(ERU1_1_IRQn);
							NVIC_DisableIRQ(ERU1_2_IRQn);
						}
						else if(time_activate_deactivate == 112 && timeout_state ==1){
							sprintf(kal2,"K2 open");
							Open_K2();
							flag_K2=0; // open
							flag_disable_fault = 1;

							// matikan proteksi sementara
							NVIC_DisableIRQ(ERU0_0_IRQn);
							NVIC_DisableIRQ(ERU0_1_IRQn);
							NVIC_DisableIRQ(ERU1_1_IRQn);
							NVIC_DisableIRQ(ERU1_2_IRQn);
						}
						else if(time_activate_deactivate == 110 && timeout_state ==1){
							sprintf(kal2,"");

							//untuk tanpa Droop P off, synch off, PLL off dulu
							voltage_reference = 10; // kembalikan ref tegangan ke 10v dimatikan
							flag_increase_voltage_ac=1;
						}
						/*
						else if(time_activate_deactivate >= 112 && timeout_state ==1){
							sprintf(kal2,"Droop Off");
							uart_xmc_request(7); // matikan droop P
						}
						else if (time_activate_deactivate == 108 && timeout_state == 1 && flag_phase == 1){ // Fasa R Master
							sprintf(kal2,"");
						}
						else if (time_activate_deactivate == 108 && timeout_state == 1 && (flag_phase == 2 || flag_phase == 3 || flag_phase == 4)){ // Fasa R Sisanya
							sprintf(kal2,"synchron off");
							uart_xmc_request(10); // matikan Sinkronisasi
						}
						else if (time_activate_deactivate == 105 && timeout_state ==1 && flag_phase == 1 ){ // Fasa R Master
							sprintf(kal2,"");
							voltage_reference = 10; // kembalikan ref tegangan ke 10v dimatikan
							flag_increase_voltage_ac=1;
						}
						else if (time_activate_deactivate == 105 && timeout_state ==1 && (flag_phase == 2 || flag_phase == 3 || flag_phase == 4) ){ // Fasa sisanya
							sprintf(kal2,"PLL Off");
							uart_xmc_request(6); // matikan PLL
							voltage_reference = 10; // kembalikan ref tegangan ke 10v dimatikan
							flag_increase_voltage_ac=1;
							}
						*/
						else if(flag_increase_voltage_ac == 1 && timeout_state == 1){
							Vreff_inv = Vreff_inv - 10;
							if (Vreff_inv <= voltage_reference){
								Vreff_inv = voltage_reference;
								flag_increase_voltage_ac=0;
								time_finish_voltage_ac = time_activate_deactivate;
								voltage_reference = 0;
								}
							sprintf(kal2,"Vp = %dV",Vreff_inv);
							flag_update_send_xmc = 1;
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-5) && timeout_state ==1){
							sprintf(kal2,"Stop PWM");
							uart_xmc_request(5); // matikan PWM Inverter
							//off droop p, sinkron, pll diakhirkan
							uart_xmc_request(7); // matikan droop P
							//uart_xmc_request(11); // udah matikan Sinkronisasi
							uart_xmc_request(9); // matikan PLL
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-7) && timeout_state ==1){
							GST_LOW();
							// lakukan reset semua kontrol di sini kalau ada
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-9) && timeout_state ==1){
							sprintf(kal2,"K1-HK off");
							//sprintf(kal2,"");
							Close_HK2();
							flag_HK2 = 0;
							Open_K1();
							flag_K1 = 0;
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-15) && timeout_state ==1){
							sprintf(kal2,"");
							flag_deactivation=0;
							time_activate_deactivate =0;
							state_fsm = 1;
							flag_relaystandby = 0;
						}
						if (timeout_state==1){
							if (fault_count <= 2){
								fault_count = 0;
							}
							timeout_state=0;
							time_activate_deactivate -= 1;
							flag_timer_nobuzz=0;
						}
					}
					else {
						timeout_state=0;
						time_activate_deactivate = -1;
						time_finish_voltage_ac=0;
						flag_increase_voltage_ac =0;
					}
				}

				else if ( state_fsm == 4){ //

					sprintf(kal2,"%+dP %+dQ", p_set*2, q_set*2);
					//sprintf(kal2,"%d %d",counter_feedback, counter_dummy);

					counter_feedback++;
					if(counter_feedback == 150){
						counter_feedback = 0;
						counter_dummy++;
						uart_xmc_request(1);
					}

					if ( button[0] == '0' && button[1] == '0'){
						flag_button=0;
					}
					if ( button[0] == '1' && button[1] == '1' && flag_button == 0){
						prev_state_fsm=4;
						state_fsm = 9;
					}

					if ( button[2] == '1' && button[3] == '1'){
						fault_count=6;
						state_fsm = 7;
					}

				}

				else if ( state_fsm == 5){

					counter_feedback++;
					if(counter_feedback == 150){
						counter_feedback = 0;
						counter_dummy++;
						uart_xmc_request(1);
					}

					if ( flag_phase == 1){ // Master Phase R
						sprintf(kal2,"Master-R %+dP",p_set*2);
					}
					else if ( flag_phase == 2){ // Master Phase S
						sprintf(kal2,"Master-S %+dP",p_set*2);
					}
					else if ( flag_phase == 3){ // Master Phase T
						sprintf(kal2,"Master-T %+dP",p_set*2);
					}
					else if ( flag_phase == 4){ // Slave Phase
						sprintf(kal2,"Slave %+dP",p_set*2);
					}

					if ( button[0] == '0' && button[1] == '0'){
						flag_button=0;
					}
					if ( button[0] == '1' && button[1] == '1' && flag_button == 0){
						prev_state_fsm=5;
						state_fsm = 9;
					}

					if ( button[2] == '1' && button[3] == '1'){
						fault_count=6;
						state_fsm = 7;
					}

				}
/*
				else if ( state_fsm == 6){
					if (flag_tied_alone==1 && flag_alone_tied == 0 ){
						timer_state_nobuzz(1);
						if (time_activate_deactivate == -1){
							time_activate_deactivate = 120;
							time_finish_voltage_ac=0;
						}
						else if(time_activate_deactivate >= 118 && timeout_state ==1){
							sprintf(kal1,"Grid Unavailable");
						}
						else if(time_activate_deactivate >= 117 && timeout_state ==1){
							sprintf(kal1,"Stand Alone Mode");
							uart_xmc_request(10); // matikan Sinkronisasi
						}
						else if (time_activate_deactivate == 117 && timeout_state == 1 && flag_phase == 1){ // Fasa R Master
							sprintf(kal2,"Master Phase R");
							//ganti PLL ke refgen 50Hz sebagai acuan, bikin perintahnya
						}
						else if (time_activate_deactivate == 116 && timeout_state == 1 && flag_phase == 2){ // Fasa R Master
							sprintf(kal2,"Master Phase S");
							//Ganti PLL inverter ke PLL Phase R lalu geser -120 derajat
							}
						else if (time_activate_deactivate == 116 && timeout_state == 1 && flag_phase == 3){ // Fasa R Master
							sprintf(kal2,"Master Phase T");
							//Ganti PLL inverter ke PLL Phase R lalu geser +120 derajat
							}
						else if (time_activate_deactivate == 114 && timeout_state ==1 && flag_phase == 1 ){ // Fasa R Master
							sprintf(kal2,"Master Phase R");
							// Tidak ada sinkronisasi
							flag_increase_voltage_ac =1;
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-8) && timeout_state ==1){
							flag_activation=0;
							time_activate_deactivate = 0;
							state_fsm = 5;
						}

						if (timeout_state==1){
							if (fault_count <= 2){
								fault_count = 0; // bila fault count kurang dari 2 ketika dilakukan 1 perintah operasi, berarti sebenernya gak ada fault
							}
							// reset timer untuk menghitung detik pakai RTC
							timeout_state=0;
							time_activate_deactivate -= 1;
							flag_timer_nobuzz=0;
						}

					}
					else if (flag_alone_tied==1 && flag_tied_alone == 0){
						timer_state_nobuzz(1);

						if (time_activate_deactivate == -1){
							time_activate_deactivate = 120;
							time_finish_voltage_ac=0;
							timeout_state ==1;
						}
						else if(time_activate_deactivate >= 116 && timeout_state ==1){
							sprintf(kal1,"Grid Available");
							sprintf(kal2,"Activate in %d S",(time_activate_deactivate-115));
							}
						else if(time_activate_deactivate == 115 && timeout_state ==1){
							sprintf(kal1,"Grid Available");
							sprintf(kal2,"Disconnect Load");

							Open_K2();
							//Open_K3(); blum ada

							// flag switch
							flag_K2=0; // open
							flag_K3=0; // open

							flag_disable_fault = 1;

							// matikan proteksi sementara
							NVIC_DisableIRQ(ERU0_0_IRQn);
							NVIC_DisableIRQ(ERU0_1_IRQn);

							uart_xmc_request(4); // matikan droop

						}
						else if (time_activate_deactivate == 108 && timeout_state == 1 ){ // Semua Fasa
							sprintf(kal2,"Start PLL Grid");
							uart_xmc_request(7); // Nyalakan PLL pada grid
						}

						else if (time_activate_deactivate == 108 && timeout_state == 1 && (flag_phase == 2 || flag_phase == 3 || flag_phase == 4)){ // Fasa R Sisanya
							sprintf(kal2,"Synchron Grid");
							uart_xmc_request(11); // Nyalakan Sinkronisasi
						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-5) && timeout_state ==1){
							sprintf(kal2,"Droop Activated!");
							Close_K2();
							//Close_K3(); blom ada fungsinya
							flag_droop = 1;
							flag_disable_fault =1;

							// matikan proteksi sementara untuk DCPT2 dan DCPT1
							NVIC_DisableIRQ(ERU0_0_IRQn);
							NVIC_DisableIRQ(ERU0_1_IRQn);

							// flag switch
							flag_K2 = 1; // close
							//flag_K3 = 1; // close, blom ada

						}
						else if (time_activate_deactivate == (time_finish_voltage_ac-8) && timeout_state ==1){
							flag_activation=0;
							time_activate_deactivate = 0;
							state_fsm = 4;
						}
						if (timeout_state==1){
							if (fault_count <= 2){
								fault_count = 0;
							}
							timeout_state=0;
							time_activate_deactivate -= 1;
							flag_timer_nobuzz=0;
						}
					}
				}
*/
				else if ( state_fsm == 7){ // state fault, untuk memberitahu user dan reset beberapa operasi yang belum di reset pada fault handling di interupt

					sprintf(kal2,"FAULT HARDWARE");
					//sprintf(kal2,"PRESS TO RESTART");

					SET_BIT(PORT2->OUT,LED1_BUZZ); // nyalakan buzzer
					CLR_BIT(PORT2->OUT,LED2); // matikan LED Hijau
					SET_BIT(PORT1->OUT,RESET_LCD); // Nyalakan LED Merah

					CLR_BIT(PORT0->OUT,13); //GST_LOW();
					CLR_BIT(PORT1->OUT,DO_K1);
					CLR_BIT(PORT1->OUT,DO_K2);
					CLR_BIT(PORT1->OUT,DO_K3);
					CLR_BIT(PORT1->OUT,DO_HK2);

					if (flag_fault == 0){
						Vreff_inv = 10; // referensi inverter dibuat jadi 10 V
						flag_fault = 1;
						uart_xmc_request(5); // Disable Inverter
						flag_update_send_xmc = 1; // kirim referensi baru ke inverter
						}

					// buat kendali K2 dan K3 terdisable dari HMI
					flag_invalid_K2=2;
					//flag_invalid_K3=2; blom ada

					flag_deactivation = 0;
					flag_activation = 0;

					if ( button[0] == '0' && button[1] == '0'){
						flag_button=0;
					}
					if ( button[0] == '1' && button[1] == '1' && flag_button == 0){
						prev_state_fsm = 7;
						state_fsm = 8;
					}
				}

				else if ( state_fsm == 8){ // state check fault

					sprintf(kal2,"Hold 3 Sec");
					timer_state_nobuzz(3);

					if ( button[0] == '0' || button[1] == '0'){
						state_fsm = 7; // state fault
						flag_timer_nobuzz = 0;
						sprintf(kal2,"");
					}
					if (timeout_state == 1){
						CLR_BIT(PORT2->OUT,LED1_BUZZ); // matiin Buzzer
						SET_BIT(PORT2->OUT,LED2); // nyalain LED warna Hijau
						CLR_BIT(PORT1->OUT,RESET_LCD); // Matiin LED Merah

						// reset deteksi fault
						fault_count = 0;
						flag_fault=0;
						DCPT2_Fault = 0;
						GD1_Fault = 0;

						// nyalakan kembali fault detection
						NVIC_EnableIRQ(ERU0_0_IRQn);
						NVIC_EnableIRQ(ERU0_1_IRQn);
						//NVIC_EnableIRQ(ERU0_2_IRQn);
						//NVIC_EnableIRQ(ERU0_3_IRQn);
						NVIC_EnableIRQ(ERU1_1_IRQn);
						NVIC_EnableIRQ(ERU1_2_IRQn);

						// kembali ke state standby
						state_fsm=1;
						next_state_fsm=1;
						flag_relaystandby = 0;

						flag_timer_nobuzz = 0;
						timeout_state=0;
						flag_button=1;
						sprintf(kal2,"");
					}
				}
				else if ( state_fsm == 9){ // state check button

					sprintf(kal2,"Hold 2 Sec");
					//sprintf(kal2,"");
					timer_state_nobuzz(2);

					if ((prev_state_fsm == 1 && next_state_fsm != 4 && next_state_fsm != 5) || (prev_state_fsm == 1 && next_state_fsm == 5 && flag_phase != 1 && flag_phase != 2 && flag_phase != 3 && flag_phase != 4)){
						state_fsm = 1;
						flag_relaystandby = 0;
						flag_timer_nobuzz = 0;
						//sprintf(kal2,"insert mode!");
					}

					if ( button[0] == '0' || button[1] == '0'){
						state_fsm = prev_state_fsm; //prev_state_fsm = 1 or 4 or 5
						flag_relaystandby = 0;
						flag_timer_nobuzz = 0;
						sprintf(kal2,"");
						}

					if (timeout_state == 1){
						if ( (prev_state_fsm == 1) && (next_state_fsm == 4 || next_state_fsm == 5) ){
							state_fsm = 11;
							Open_HK2();
							}
						else if (prev_state_fsm == 4){
							state_fsm = 2;
							flag_deactivation = 1;
							Ptot=0;
							Qtot=0;
						}
						else if (prev_state_fsm == 5){
							state_fsm = 3;
							flag_deactivation = 1;
						}

						flag_timer_nobuzz = 0;
						timeout_state=0;
						flag_button=1;
						sprintf(kal2,"");
					}
				}

				else if ( state_fsm == 10){
					menu_standby();
					timer_state_nobuzz(999);
					if ( button[0] == '1' || button[1] == '1' || button[2] == '1'){
						flag_timer_nobuzz = 0;
					}
					if ( button[3] == '1' || timeout_state == 1){
						state_fsm = 1;
						flag_relaystandby = 0;

						flag_timer_nobuzz =0;
						flag_menu = 0;
						timeout_state =0;
						sprintf(kal2,"");
					}
				}
}

void buzzer_50ms(void){
	SET_BIT(PORT1->OUT,RESET_LCD);
	My_Delay_ms(50);
	CLR_BIT(PORT1->OUT,RESET_LCD); //BUZZER P1.14
}

void timer_state_nobuzz(int count_num){
	int count;
	if (flag_timer_nobuzz==0){
		RTC_get_time(&hour,&minute_start_state,&second_start_state);
		flag_timer_nobuzz=1;
	}
		RTC_get_time(&hour,&minute,&second);
		count = (minute*60+second) - (minute_start_state*60+second_start_state);
		if (count >= count_num ){
			timeout_state=1;
		}
	}

void initialization (void){
	//initialization();
	int i;
	char kal[32];

	DAVE_Init();			// Initialization of DAVE Apps

	IO_Init();
	//GST_HIGH();	 //utk manual tanpa K1 otomatis
	EN_CV=0;

	UART_Init();
	ADC_Init();
	ERU_Init();
	Display_Init();
	DAC_Init();
	AD5328_Init();

	//tegangan proteksi naik karena pengubahan offset sensor
	AD5328_Set_Value_Volt(ACPT_REF,3.200); // V AC before contactor, 400 V
	AD5328_Set_Value_Volt(GRPT_REF,3.200); // V AC after contactor, 400 V

	//AD5328_Set_Value_Volt(DCPT1REF,1.748); // V battery, DCcap 1.085->150, 1.7489->300 V
	//tegangan proteksi turun karena pengubahan offset sensor
	AD5328_Set_Value_Volt(DCPT1_REF,3.100);//1.577);

	//AD5328_Set_Value_Volt(DCPT2REF,2.412); // DC link 2.46=460V, 0.73=75V, 2.28=420, 2.41=450
	//tegangan proteksi turun karena pengubahan offset sensor
	AD5328_Set_Value_Volt(DCPT2_REF,3.150); //

	AD5328_Set_Value_Volt(CT1_REF,2.100); // MAX(CT1) 25A (assumption) arah charge 5kW bisa sampai ~60A
	AD5328_Set_Value_Volt(CT234_REF,1.900);//1.617); // Max(CT234) 1.722->30A, 2->55A, target 2x 1.944 50A, 5kW ~30A
	AD5328_Set_Value_Volt(CT56_REF,1.900); // Max(CT56) 1.722->30A, 2.222->75A, CT5 arah invert, CT6 arah rectifier,5kW ~40, -60
	AD5328_Set_Value_Volt(CT78_REF,2.200);

	PWM_Buck_Init();
	PWM_Boost_Init();
	PWM_Boost_Disable();
	PWM_Buck_Disable();
	PWM_Boost_Start();
	PWM_Enable_Interrupt_NVIC();

	lcd_gotoxy(0,0);
	lcd_puts("                 ");
	lcd_gotoxy(0,0);
	sprintf(kal,"Initialization");
	lcd_puts(kal);

	comparepwm4= 0;
	comparepwm5= 50;
	comparepwm6= 100;
	state_fsm = 0;

	//PREPARATION

	//Relay Initialization
	Open_K1();
	Open_K2();
	Open_K3();
	Close_HK2();

	flag_K1=0;
	flag_K2=0;
	flag_HK1=0;
	flag_HK2=0;

	//for(i=0;i<10;i++) My_Delay_ms(100);

	//Send RTC data to PC
	//sprintf(kal,"Cek RTC\r\n");
	//UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
	//RTC_get_time_date_str(kal);
	//UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));
	RTC_Init(3,11,2,17,1,40,0);

	for(i=0;i<30;i++) My_Delay_ms(100);

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

	lcd_gotoxy(0,0);
	lcd_puts("                 ");
	lcd_gotoxy(0,0);
	sprintf(kal,"Update nol ADC");
	lcd_puts(kal);

	sprintf(kal,"Update nol ADC\r\n");
	UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

	for(i=0;i<10;i++) My_Delay_ms(100);
/*
	//CHECK COMMUNICATION XMC1-XMC2

	flag_data_receive_xmc =0;

	lcd_gotoxy(0,0);
	lcd_puts("                 ");
	lcd_gotoxy(0,0);
	sprintf(kal,"Check Com XMC");
	lcd_puts(kal);

	while (flag_data_receive_xmc == 0){
		uart_xmc_request(0); // request update for initialization and adc offset renewal
		for(int i=0;i<10;i++) My_Delay_ms(100);
		string_read_xmc_increment=0;
	}

	lcd_gotoxy(0,0);
	lcd_puts("                 ");
	lcd_gotoxy(0,0);
	sprintf(kal,"Update Data");
	lcd_puts(kal);

	while (comparepwm4==0){ // || comparepwm5==50 || comparepwm6==100 ){
		uart_xmc_request(1); // request update for initialization
		for(int i=0;i<10;i++) My_Delay_ms(100);
		uart_xmc_receive();
		string_read_xmc_increment=0;

		comparepwm4 = data_uart_xmc[0];
		pwm_peak_feedback = data_uart_xmc[1]; //pwm open loop
		Vreff_inv_feedback = data_uart_xmc[2]; //Volt ref closed loop

		flag_update_receive_xmc = 0;
	}
*/

	lcd_gotoxy(0,0);
	lcd_puts("                 ");
	lcd_gotoxy(0,0);
	sprintf(kal,"Ready");
	lcd_puts(kal);

	sprintf(kal,"Ready\n");
	UART001_WaitWriteDataMultiple(UART_RS232,kal,strlen(kal));

	for(i=0;i<10;i++) My_Delay_ms(100);

	flag_prep = 0;
	finish_prep = 0;

	lcd_clear();
	GST_LOW();
}

void preparation (void){

	flag_timer_nobuzz = 0;
	timeout_state = 0;
	flag_menu = 0;

	flag_relaystandby = 0;

	finish_prep = 1;
}

void precharging (void){

	if ( DCPT2_AIN_Result < (300*DCPT2_GRAD)+DCPT2_OFFSET ) //precharging sampai 300V
	{
		finish_precharging = 0;
	}
	else
	{
		finish_precharging = 1;
	}
}

void print_lcd(void){

	int flag_refresh_1=0;
	int flag_refresh_2=0;
	int i;
	for(i=0;i<16;i++){
		if (kal1_old[i] != kal1[i]){
			flag_refresh_1 =1;
		}
		if (kal2_old[i] != kal2[i]){
			flag_refresh_2 =1;
		}
		if (flag_refresh_1 == 1 || flag_refresh_2 == 1){
			i=16;
		}
	}
	if ( flag_refresh_1 == 1){
	lcd_gotoxy(0,0);
	lcd_puts("                ");
	lcd_gotoxy(0,0);
	lcd_puts(kal1);
	for(i=0;i<16;i++){
		kal1_old[i] = kal1[i];
		}
	}
	if ( flag_refresh_2 == 1){
	lcd_gotoxy(0,1);
	lcd_puts("                ");
	lcd_gotoxy(0,1);
	lcd_puts(kal2);
	for(i=0;i<16;i++){
		kal2_old[i] = kal2[i];
		}
	}
}

volatile int data_send_count = 0;
volatile int count = 0;
volatile int increment = 0;
volatile int update_data_rabbit = 1;
volatile int data_rabbit_ready = 0;

void update_data(void){
	char buf[16],buf_out[16];
	int i;

	if (flag_update_send_xmc == 1){

		data_uart_xmc[0] = pwm_peak_reff; //openloopinvpwm
		data_uart_xmc[1] = Vreff_inv; //closedloopinvvolt
		data_uart_xmc[2] = p_set;	//P
		data_uart_xmc[3] = q_set;	//Q

		if ( state_fsm == 4 || state_fsm == 2 || next_state_fsm == 4){
			data_uart_xmc[4]= 1;
		}
		else {
			data_uart_xmc[4] = flag_phase;
		}

		uart_xmc_send();
		flag_update_send_xmc=0;
	}
	if(flag_update_receive_xmc == 1){
		uart_xmc_receive();
		string_read_xmc_increment=0;

		//comparepwm4 = data_uart_xmc[0];
		//pwm_peak_feedback = data_uart_xmc[1]; //pwm open loop
		//Vreff_inv_feedback = data_uart_xmc[2]; //Volt ref closed loop
		Ptot = data_uart_xmc[3];
		Qtot = data_uart_xmc[4];
		//p_set_feedback = data_uart_xmc[5];
		//q_set_feedback = data_uart_xmc[6];

		//flag_tied_alone = data_uart_xmc[13];
		//flag_alone_tied = data_uart_xmc[14];

		flag_update_receive_xmc = 0;
	}

	if (flag_update_send_rabbit == 1){
		if (data_send_count == 0 && count == 1){
			data_rabbit();
		}
		if ( count == 2){
			uart_rabbit_send(data_send_count);
			data_send_count ++;
			count = 0;
		}
		if (data_send_count == 26){

			NVIC_EnableIRQ(USIC1_0_IRQn);
			start_scan =1;

			flag_update_send_rabbit=0;
			data_send_count = 0;
			for ( i = 0; i< 31; i++ ){
				data_uart_rabbit_update[i]=0;
			}
		}
		count ++;
	}
	if(flag_update_receive_rabbit == 1){
		int i;
		char buf[30];
		uart_rabbit_receive(increment);
		sprintf(buf,"%d. %d\r\n",increment,data_uart_rabbit_update[increment]);
		UART001_WaitWriteDataMultiple(UART_RS232,buf,strlen(buf));

		if ( increment >= 11){
			increment = -1;
			flag_update_send_rabbit=1;
			flag_update_receive_rabbit = 0;
/*
			if (data_uart_rabbit_update[8] == 1){
				flag_activation = 0;
				flag_deactivation = 1;

				}
			else if (data_uart_rabbit_update[8] == 2){
				flag_activation = 1;
				flag_deactivation = 0;

			}
*/
			if (data_uart_rabbit_update[1] != p_set_hmi){
				p_set = data_uart_rabbit_update[1]/2;
				if (p_set < -5000){p_set = -5000;}
				else if (p_set > 6400){p_set = 6400;}
				flag_update_send_xmc = 1;
			}
			p_set_hmi = data_uart_rabbit_update[1];

			if (data_uart_rabbit_update[2] != q_set_hmi){
				q_set = data_uart_rabbit_update[2]/2;
				if (q_set > 5000){q_set = 5000;}
				else if (q_set < -5000){q_set = -5000;}
				flag_update_send_xmc = 1;
			}
			q_set_hmi = data_uart_rabbit_update[2];

			//uart_xmc_request(1);

		}
		increment++;
	}
}


void menu_standby(){
	volatile char temp_stat[16];

	if (state_menu == 0){
		temp = (next_state_fsm-3)*100;
		}
	else if (state_menu == 1) {
		temp = flag_phase*100;
		}

	if (button[2] == '1' && flag_push[2]=='0'){
		//kal1[0]= 0b00000111;
		if ((button[0] == '1' )&&(flag_push[0] == '0')){
			temp=temp-100;
			flag_push[0]='1';
		}
		if (( button[1] == '1')&&(flag_push[1] == '0')){
			temp=temp+100;
			flag_push[1]='1';
		}

		if (state_menu == 0) {
			if (temp <= 100){
				temp = 100;
				}
			else if (temp > 200){
				temp = 200;
				}
			next_state_fsm = (temp*0.01)+3;
			if (temp == 100){
				sprintf(temp_stat,"Mode = Grid-Tied");
			}
			else if (temp == 200) {
				sprintf(temp_stat,"Mode = Std-Alone");
			}
			sprintf(kal2,"%s",temp_stat);
		}

		else if (state_menu == 1){
			if (temp <= 100){
				temp = 100;
				}
			else if (temp > 400){
				temp = 400;
				}
			flag_phase = temp*0.01;
			flag_update_send_xmc=1;
			if (flag_phase == 1){
				sprintf(temp_stat,"Phase = Master-R");
			}
			else if (flag_phase == 2) {
				sprintf(temp_stat,"Phase = Master-S");
			}
			else if (flag_phase == 3) {
				sprintf(temp_stat,"Phase = Master-T");
			}
			else if (flag_phase == 4) {
				sprintf(temp_stat,"Phase = Slave");
			}
			sprintf(kal2,"%s",temp_stat);
		}
	}

	else if (button[2] == '0'){

		if ((button[0] == '1' )&&(flag_push[0] == '0')){
			state_menu=state_menu-1;
			flag_push[0]='1';
			if (state_menu <= min_menu_standby){
				state_menu = min_menu_standby;
				}
		}
		if (( button[1] == '1')&&(flag_push[1] == '0')){
			state_menu=state_menu+1;
			flag_push[1]='1';
			if (state_menu > max_menu_standby){
				state_menu = max_menu_standby;
				}
		}

		if (state_menu == 0) {
			temp = (next_state_fsm-3)*100;
			if (temp == 100){
				sprintf(kal2,"Mode = Grid-Tied");
			}
			else if (temp == 200) {
				sprintf(kal2,"Mode = Std-Alone");
			}
			else {
				sprintf(kal2,"Mode = ?");
			}
			//sprintf(kal1,"    Oper. Mode");
			//sprintf(kal2,"Mode = %s",temp_stat);
		}

		else if (state_menu == 1){
			temp = flag_phase*100;
			if (temp == 100){
				sprintf(kal2,"Phase = Master-R");
			}
			else if (temp == 200) {
				sprintf(kal2,"Phase = Master-S");
			}
			else if (temp == 300) {
				sprintf(kal2,"Phase = Master-T");
			}
			else if (temp == 400) {
				sprintf(kal2,"Phase = Slave");
			}
			else {
				sprintf(kal2,"Phase = ?");
			}
			//sprintf(kal1," Phase Selection");
			//sprintf(kal2,"Phase = %s",temp_stat);
		}
	}
}
