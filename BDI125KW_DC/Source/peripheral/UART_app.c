/*
 * UART_app.c
 *
 *  Created on: Mar 19, 2014
 *      Author: angga
 */

#include "peripheral/UART_app.h"

volatile int string_read_xmc_increment = 0;
volatile char string_read_xmc[64];
volatile int flag_update_send_xmc =0;
volatile int flag_update_receive_xmc =0;
volatile int flag_data_receive_xmc;
volatile int data_uart_xmc[16];

volatile int string_read_rabbit_increment =0;
volatile char string_read_rabbit[256];
volatile int flag_update_send_rabbit =0;
volatile int flag_update_receive_rabbit =0;
volatile int data_uart_rabbit[50];
volatile int data_uart_rabbit_update[50];

int state_hmi;
//volatile uint8_t DebugMode;
//volatile char data = 'a';
//volatile char button;

void UART_Init(void)
{

	//Standar receive event RCI mode
	SET_BIT(UART_RS485->RBCTR,USIC_CH_RBCTR_RNM_Pos);
	//RCI control
	WR_REG(UART_RS485->RBCTR,USIC_CH_RBCTR_RCIM_Msk,USIC_CH_RBCTR_RCIM_Pos,2);
	//Enable Interrupt
	SET_BIT(UART_RS485->RBCTR,USIC_CH_RBCTR_SRBIEN_Pos);

	//Set SEL_485 as output
	WR_REG(PORT0->IOCR8,PORT0_IOCR8_PC10_Msk,PORT0_IOCR8_PC10_Pos,0x10);
	//Set SEL_485 as R/T
	CLR_BIT(PORT0->OUT,SEL_485);

	//Enable Frame Finished Interrupt
	//SET_BIT(UART_RS485->PCR_ASCMode,USIC_CH_PCR_ASCMode_FFIEN_Pos);

	//Set Interrupt Priority
	NVIC_SetPriority(USIC1_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),60,0));
	//Enable CCU81_0_IRQHandler (PWM_Inverter) interrupt
	NVIC_EnableIRQ(USIC1_0_IRQn);

	//Standar receive event RCI mode
	SET_BIT(UART_RS232->RBCTR,USIC_CH_RBCTR_RNM_Pos);
	//RCI control
	WR_REG(UART_RS232->RBCTR,USIC_CH_RBCTR_RCIM_Msk,USIC_CH_RBCTR_RCIM_Pos,2);
	//Enable Interrupt
	SET_BIT(UART_RS232->RBCTR,USIC_CH_RBCTR_SRBIEN_Pos);

	//Set Interrupt Priority
	NVIC_SetPriority(USIC0_5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),60,0));
	//Enable CCU81_0_IRQHandler (PWM_Inverter) interrupt
	NVIC_EnableIRQ(USIC0_5_IRQn);

	//Standar receive event RCI mode
	SET_BIT(UART_U1->RBCTR,USIC_CH_RBCTR_RNM_Pos);
	//RCI control
	WR_REG(UART_U1->RBCTR,USIC_CH_RBCTR_RCIM_Msk,USIC_CH_RBCTR_RCIM_Pos,2);
	//Enable Interrupt
	SET_BIT(UART_U1->RBCTR,USIC_CH_RBCTR_SRBIEN_Pos);

	//Set Interrupt Priority
	NVIC_SetPriority(USIC2_2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),60,0));
	//Enable CCU81_0_IRQHandler (PWM_Inverter) interrupt
	NVIC_EnableIRQ(USIC2_2_IRQn);
}


void kirimnullchar(USIC_CH_TypeDef* UartRegs)
{
	  while(USIC_IsTxFIFOfull(UartRegs));
	  UartRegs->IN[0] = NULL;
}


uint32_t UART001_WaitWriteDataMultiple
(
  USIC_CH_TypeDef* UartRegs,
  uint8_t* DataPtr,
  uint32_t Count
)
{
  uint32_t WriteCount = 0x00U;

  /* <<<DD_UART001_API_2>>>*/
  while(Count)
  {
	  while(USIC_IsTxFIFOfull(UartRegs));
	  UartRegs->IN[0] = *DataPtr;
	  Count--;
	  WriteCount++;
	  DataPtr++;
  }

  return WriteCount;
}

uint32_t UART001_WaitReadDataMultiple
(
	USIC_CH_TypeDef* UartRegs,
	uint8_t* DataPtr,
	uint32_t Count
)
{
  uint32_t ReadCount = 0x00U;

  while(Count)
  {
	  //wait data while USART RX FIFO Empty
	  while(USIC_ubIsRxFIFOempty(UartRegs));
	  *DataPtr = (uint16_t)UartRegs->OUTR;
	  Count--;
	  ReadCount++;
	  DataPtr++;
  }

  return ReadCount;
}


void uart_xmc_request(int command){
	char kal[32];
	if (command == 0){ // give update early for initialization
		sprintf(kal,"A");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 1 ){
		sprintf(kal,"B");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 2 ){
		sprintf(kal,"C");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 3 ){
		sprintf(kal,"D");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 4 ){
		sprintf(kal,"E");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 5 ){
		sprintf(kal,"F");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 6 ){
		sprintf(kal,"G");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 7 ){
		sprintf(kal,"H");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 8 ){
		sprintf(kal,"I");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 9 ){
		sprintf(kal,"J");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 10 ){
		sprintf(kal,"K");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 11 ){
		sprintf(kal,"L");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 12 ){
		sprintf(kal,"M");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 13 ){
		sprintf(kal,"N");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 14 ){
		sprintf(kal,"O");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 15 ){
		sprintf(kal,"P");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 16 ){
		sprintf(kal,"Q");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 17 ){
		sprintf(kal,"R");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 18 ){
		sprintf(kal,"S");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 19 ){
		sprintf(kal,"T");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 20 ){
		sprintf(kal,"U");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
	else if ( command == 21 ){
		sprintf(kal,"V");
		UART001_WaitWriteDataMultiple(UART_U1,kal,strlen(kal));
	}
}

void uart_xmc_receive(){
	const char s[2] = ";"; // ini terima aja buat memotong2 data
	char *token; /// ini terima aja buat memotong2 data
	int increment=0; // ini variabel buat increment aja
    token = strtok(string_read_xmc,s);
    while(token){
      data_uart_xmc[increment]=atof(token);
      token = strtok(NULL,s);
      increment++;
      }
}

void uart_xmc_send(){
	char buf_out[128],buf[128];
	strcpy(buf_out,"");
	    sprintf(buf,"%d;",data_uart_xmc[0]);
	    strcpy(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[1]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[2]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[3]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[4]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[5]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[6]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[7]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[8]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[9]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[10]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[11]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[12]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[13]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[14]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[15]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[16]);
	    strcat(buf_out, buf);
/*	    sprintf(buf,"%d;",data_uart_xmc[17]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[18]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[19]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[20]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[21]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[22]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[23]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[24]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[25]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[26]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[27]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[28]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[29]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[30]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[31]);
	    strcat(buf_out, buf);
	    sprintf(buf,"%d;",data_uart_xmc[32]);
	    strcat(buf_out, buf);
*/
	    strcat(buf_out,"T");
    UART001_WaitWriteDataMultiple(UART_U1,buf_out,strlen(buf_out));
}

//UNTUK KOMUNIKASI RABBIT-HMI

volatile int start_scan =1;
volatile char *save_str;
volatile char *token; /// ini terima aja buat memotong2 data

void uart_rabbit_receive(int increment){
	const char s[2] = ","; // ini terima aja buat memotong2 data
    if (start_scan == 1){
    	token = strtok_r(string_read_rabbit,s,&save_str); //sudah termasuk semua informasi 250 char data masuk baris sini
    	start_scan = 0;
    	}
    if (token != NULL){
      data_uart_rabbit_update[increment]=atof(token);
      token = strtok_r(NULL,s,&save_str);
      }
}


void data_rabbit(){

	if (state_fsm == 10){state_hmi = 0xA;}
	else if (state_fsm == 11){state_hmi = 0xB;}
	else {state_hmi = state_fsm;}

	data_uart_rabbit[0] = 0;//
	data_uart_rabbit[1]= 0;//
	data_uart_rabbit[2]= p_set_hmi;//
	data_uart_rabbit[3]= q_set_hmi;//Power//
	data_uart_rabbit[4]= Ptot;//
	data_uart_rabbit[5]= Qtot;//
	data_uart_rabbit[6]= 0;//m1;//
	data_uart_rabbit[7]= 0;//c1;//
	data_uart_rabbit[8]= 0;//m2;//
	data_uart_rabbit[9]= 0;//c2;//
	data_uart_rabbit[10]= 0;//
	data_uart_rabbit[11]= 0;//
	data_uart_rabbit[12]= 0;//
	data_uart_rabbit[13]= 0;//
	data_uart_rabbit[14]= 0;//
	data_uart_rabbit[15]= state_hmi;//
	data_uart_rabbit[16]= 0;//
	data_uart_rabbit[17]= flag_fault;//
	data_uart_rabbit[18]= 0;//
	data_uart_rabbit[19]= 0;//
}

void uart_rabbit_send(int data_part){
	char buf_out[16],buf[16];

	strcpy(buf_out,"");
	if (data_part == 0){

	    sprintf(buf,"H");
		strcat(buf_out,buf);
	}
	else if (data_part == 1){

	    sprintf(buf,"B");
		strcat(buf_out,buf);
	}
	else if (data_part == 2){

	    sprintf(buf,"D");
		strcat(buf_out,buf);
	}
	else if (data_part == 3){

	    sprintf(buf,"I");
		strcat(buf_out,buf);
	}
	else if (data_part == 4){

	    sprintf(buf,"2");
		strcat(buf_out,buf);
	}

	// 5
	else if ( data_part > 4 && data_part <= 16 ){
	    sprintf(buf,"%+06d,",data_uart_rabbit[data_part-5]);
	    strcat(buf_out, buf);
	}

	// 84
	else if ( data_part > 16 && data_part <= 23 ){
		    sprintf(buf,"%X,",data_uart_rabbit[data_part-5]);
		    strcat(buf_out, buf);
		}
	//13
	else if (data_part == 24){
		    sprintf(buf,"%X",data_uart_rabbit[data_part-5]);
		    strcat(buf_out, buf);
		}
	else if (data_part == 25){
	    sprintf(buf,"T");
	    strcat(buf_out, buf);
	}
	else if (data_part == 26){

		kirimnullchar(UART_RS232);
		kirimnullchar(UART_RS485);
	}


	   UART001_WaitWriteDataMultiple(UART_RS485,buf_out,strlen(buf_out));
	   UART001_WaitWriteDataMultiple(UART_RS232,buf_out,strlen(buf_out));

}
