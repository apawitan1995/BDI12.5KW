/*
 * datainverter.c
 *
 *  Created on: Feb 1, 2017
 *      Author: Mukhlish
 */

#include "algorithm/datainverter.h"

//Data Analog
volatile float ACCTR, ACCTS, ACCTT, GCTR, GCTS, GCTT, DCPT1, GPTR, GPTS, GPTT, TF1, TF2, DCCT1, IVCTR, IVCTS, IVCTT, DCPT2, ACPTR, ACPTS, ACPTT, FREQR, FREQS, FREQT = 0;

//DI
volatile uint8_t DI = 0;
volatile uint8_t DIS1_Flag, DIS2_Flag, DIS3_Flag, DI_K2F_Flag = 0;
volatile uint8_t DI_K2FNO, DI_K2FNC= 0;

//DO
volatile uint8_t DO, DOS = 0;
volatile uint8_t DO_K1_Flag, DO_K2_Flag, DO_HK1_Flag, DO_HK2_Flag, DOS1_Flag, DOS2_Flag = 0;

volatile uint8_t batterylevel, softwareversion = 0;

//Fault Software
volatile uint8_t FSW1, FSW2, FSW3, FSW4, FSW5, FSW6, FSW7, FSW8 = 0;
volatile uint8_t GEN_FB, K3_FB, K2_FB, K1_FB, GCTT_OL, GCTS_OL, GCTR_OL, GPTT_UV = 0;
volatile uint8_t GPTS_UV, GPTR_UV, GPTT_OV, GPTS_OV, GPTR_OV, ACCTT_OL, ACCTS_OL, ACCTR_OL = 0;
volatile uint8_t ACPTT_UV, ACPTS_UV, ACPTR_UV, ACPTT_OV, ACPTS_OV, ACPTR_OV, DCPT2_UV, DCPT2_OV = 0;
volatile uint8_t DCCT1_OC, GEN_SYNC, STF, FSW, FHW, RESET_TYPE = 0;

//Fault Hardware
volatile uint8_t ACPT_FHW, GRPT_FHW, DCPT_FHW, CT_FHW, GD_FHW = 0;
volatile uint8_t GRPT1_HWP, GRPT2_HWP, GRPT3_HWP;
volatile uint8_t ACPT1_HWP, ACPT2_HWP, ACPT3_HWP = 0;
volatile uint8_t DCPT1_HWP, DCPT2_HWP = 0;
volatile uint8_t CT1_HWP, CT234_HWP, CT56_HWP, CT78_HWP = 0;
volatile uint8_t GD1_HWP, GD2_HWP = 0;
volatile uint8_t FHW, Fault = 0;
/*
volatile uint8_t FHW1, FHW2, FHW3 = 0;
volatile uint8_t ACPTS_HWP, ACPTR_HWP, DCPT2_HWP, IVCTT_HWP, IVCTS_HWP, IVCTR_HWP, DCCT1_HWP = 0;
volatile uint8_t GDsp1F_HWP, GDS1F_HWP, GDR2F_HWP, GDR1F_HWP, GDT2F_HWP, GDT1F_HWP, GDS2F_HWP = 0;
volatile uint8_t ACPTT_HWP, GDsp3F_HWP, GDsp2F_HWP, SPVP5_HWP, SPVN15_HWP, SPVP15_HWP, SPVP24_HWP = 0;
*/

//Data Spare
volatile uint32_t spare = 0;

void dataanalog(void)
{
	ACCTR = (float)((int32_t)CT5_Result-CT5_OFF)/CT5_GRAD*100;
	if(ACCTR > 99999){ACCTR = 99999;}
	if(ACCTR < -99999){ACCTR = -99999;}

	ACCTS = (float)((int32_t)CT6_Result-CT6_OFF)/CT6_GRAD*100;
	if(ACCTS > 99999){ACCTS = 99999;}
	if(ACCTS < -99999){ACCTS = -99999;}

	ACCTT = (float)-((((int32_t)CT5_Result-CT5_OFF)/CT5_GRAD*100)-(((int32_t)CT6_Result-CT6_OFF)/CT6_GRAD*100));
	if(ACCTT > 99999){ACCTT = 99999;}
	if(ACCTT < -99999){ACCTT = -99999;}

	GCTR = (float)((int32_t)CT7_Result-CT7_OFF)/CT7_GRAD*100;
	if(GCTR > 99999){GCTR = 99999;}
	if(GCTR < -99999){GCTR = -99999;}

	GCTS = (float)((int32_t)CT8_Result-CT8_OFF)/CT8_GRAD*100;
	if(GCTS > 99999){GCTS = 99999;}
	if(GCTS < -99999){GCTS = -99999;}

	GCTT = (float)-((((int32_t)CT7_Result-CT7_OFF)/CT7_GRAD*100)-(((int32_t)CT8_Result-CT8_OFF)/CT8_GRAD*100));
	if(GCTT > 99999){GCTT = 99999;}
	if(GCTT < -99999){GCTT = -99999;}

	DCPT1 = (float)((int32_t)DCPT1_AIN_Result-DCPT1_OFFSET)/DCPT1_GRAD*100;
	if(DCPT1 > 99999){DCPT1 = 99999;}
	if(DCPT1 < -99999){DCPT1 = -99999;}

	GPTR = (float)((int32_t)GRPT1_AIN_Result-GRPT1_OFFSET)/GRPT1_GRAD*100;
	if(GPTR > 99999){GPTR = 99999;}
	if(GPTR < -99999){GPTR = -99999;}

	GPTS = (float)((int32_t)GRPT2_AIN_Result-GRPT2_OFFSET)/GRPT2_GRAD*100;
	if(GPTS > 99999){GPTS = 99999;}
	if(GPTS < -99999){GPTS = -99999;}

	GPTT = (float)((int32_t)GRPT3_AIN_Result-GRPT3_OFFSET)/GRPT3_GRAD*100;
	if(GPTT > 99999){GPTT = 99999;}
	if(GPTT < -99999){GPTT = -99999;}

	TF1 = (float)((int32_t)TQ1_AIN_Result-TQ1_OFF)/TQ1_GRAD*100;
	if(TF1 > 99999){TF1 = 99999;}
	if(TF1 < -99999){TF1 = -99999;}

	TF2 = (float)((int32_t)TQ2_AIN_Result-TQ2_OFF)/TQ2_GRAD*100;
	if(TF2 > 99999){TF2 = 99999;}
	if(TF2 < -99999){TF2 = -99999;}

	DCCT1 = (float)((int32_t)CT1_Result-CT1_OFF)/CT1_GRAD*100;
	if(DCCT1 > 99999){DCCT1 = 99999;}
	if(DCCT1 < -99999){DCCT1 = -99999;}

	IVCTR = (float)((int32_t)CT2_Result-CT2_OFF)/CT2_GRAD*100;
	if(IVCTR > 99999){IVCTR = 99999;}
	if(IVCTR < -99999){IVCTR = -99999;}

	IVCTS = (float)((int32_t)CT3_Result-CT3_OFF)/CT3_GRAD*100;
	if(IVCTS > 99999){IVCTS = 99999;}
	if(IVCTS < -99999){IVCTS = -99999;}

	IVCTT = (float)((int32_t)CT4_Result-CT4_OFF)/CT4_GRAD*100;
	if(IVCTT > 99999){IVCTT = 99999;}
	if(IVCTT < -99999){IVCTT = -99999;}

	DCPT2 = (float)((int32_t)DCPT2_AIN_Result-DCPT2_OFFSET)/DCPT2_GRAD*100;
	if(DCPT2 > 99999){DCPT2 = 99999;}
	if(DCPT2 < -99999){DCPT2 = -99999;}

	ACPTR = (float)((int32_t)ACPT1_AIN_Result-ACPT1_OFFSET)/ACPT1_GRAD*100;
	if(ACPTR > 99999){ACPTR = 99999;}
	if(ACPTR < -99999){ACPTR = -99999;}

	ACPTS = (float)((int32_t)ACPT2_AIN_Result-ACPT2_OFFSET)/ACPT2_GRAD*100;
	if(ACPTS > 99999){ACPTS = 99999;}
	if(ACPTS < -99999){ACPTS = -99999;}

	ACPTT = (float)((int32_t)ACPT3_AIN_Result-ACPT3_OFFSET)/ACPT3_GRAD*100;
	if(ACPTT > 99999){ACPTT = 99999;}
	if(ACPTT < -99999){ACPTT = -99999;}

	FREQR = (float) 99999; //FREQ COUNTER R
	if(FREQR > 99999){FREQR = 99999;}
	if(FREQR < -99999){FREQR = -99999;}

	FREQS = (float) 99999; //FREQ COUNTER S
	if(FREQS > 99999){FREQS = 99999;}
	if(FREQS < -99999){FREQS = -99999;}

	FREQT = (float) 100000; //FREQ COUNTER T
	if(FREQT > 99999){FREQT = 99999;}
	if(FREQT < -99999){FREQT = -99999;}
}

void datadigital(void)
{
	//DI
	//DIS1_Flag = RD_REG(PORT3->IN,PORT3_IN_P4_Msk,PORT3_IN_P4_Pos);
	//DIS2_Flag = RD_REG(PORT3->IN,PORT3_IN_P3_Msk,PORT3_IN_P3_Pos);
	//DIS3_Flag = RD_REG(PORT3->IN,PORT3_IN_P15_Msk,PORT3_IN_P15_Pos);
	DI_K2F_Flag = RD_REG(PORT0->IN,PORT0_IN_P3_Msk,PORT0_IN_P3_Pos);
	if (DI_K2F_Flag == 0) {DI_K2FNO = 1;}
	else if (DI_K2F_Flag == 1) {DI_K2FNC = 1;}

	DI = ((DI_K2FNO<<1) | (DI_K2FNC<<0));

	//DO
	//DO_K1_Flag 	= RD_REG(PORT1->OUT,PORT1_OUT_P10_Msk,PORT1_OUT_P10_Pos);
	DO_K2_Flag 	= RD_REG(PORT1->OUT,PORT1_OUT_P11_Msk,PORT1_OUT_P11_Pos);
	//DO_HK1_Flag = RD_REG(PORT1->OUT,PORT1_OUT_P12_Msk,PORT1_OUT_P12_Pos);
	//DO_HK2_Flag = RD_REG(PORT1->OUT,PORT1_OUT_P13_Msk,PORT1_OUT_P13_Pos);
	//DOS1_Flag 	= RD_REG(PORT2->OUT,PORT2_OUT_P11_Msk,PORT2_OUT_P11_Pos);
	//DOS2_Flag 	= RD_REG(PORT2->OUT,PORT2_OUT_P12_Msk,PORT2_OUT_P12_Pos);

	DO 	= (DO_K2_Flag<<0);

	//DOS = ((DOS2_Flag<<1) | (DOS1_Flag<<0));

	//FSW
	//FSW1 = ((GEN_FB<<3) | (K3_FB<<2) | (K2_FB<<1) | (K1_FB<<0));
	//FSW2 = ((GCTT_OL<<3) | (GCTS_OL<<2) | (GCTR_OL<<1) | (GPTT_UV<<0));
	//FSW3 = ((GPTS_UV<<3) | (GPTR_UV<<2) | (GPTT_OV<<1) | (GPTS_OV<<0));
	//FSW4 = ((GPTR_OV<<3) | (ACCTT_OL<<2) | (ACCTS_OL<<1) | (ACCTR_OL<<0));
	//FSW5 = ((ACPTT_UV<<3) | (ACPTS_UV<<2) | (ACPTR_UV<<1) | (ACPTT_OV<<0));
	//FSW6 = ((ACPTS_OV<<3) | (ACPTR_OV<<2) | (DCPT2_UV<<1) | (DCPT2_OV<<0));
	//FSW7 = ((DCCT1_OC<<3) | (GEN_SYNC<<2) | (STF<<1) | (FSW<<0));
	//FSW8 = ((FHW<<3) | (RESET_TYPE<<2));

	//FHW
	GRPT1_HWP	= RD_REG(PORT1->IN,PORT1_IN_P1_Msk,PORT1_IN_P1_Pos);
	GRPT2_HWP	= RD_REG(PORT1->IN,PORT1_IN_P2_Msk,PORT1_IN_P2_Pos);
	GRPT3_HWP	= RD_REG(PORT1->IN,PORT1_IN_P3_Msk,PORT1_IN_P3_Pos);
	ACPT1_HWP	= RD_REG(PORT2->IN,PORT2_IN_P4_Msk,PORT2_IN_P4_Pos);
	ACPT2_HWP	= RD_REG(PORT2->IN,PORT2_IN_P6_Msk,PORT2_IN_P6_Pos);
	ACPT3_HWP	= RD_REG(PORT2->IN,PORT2_IN_P7_Msk,PORT2_IN_P7_Pos);
	DCPT1_HWP	= RD_REG(PORT2->IN,PORT2_IN_P2_Msk,PORT2_IN_P2_Pos);
	DCPT2_HWP	= RD_REG(PORT2->IN,PORT2_IN_P3_Msk,PORT2_IN_P3_Pos);
	CT1_HWP		= RD_REG(PORT2->IN,PORT2_IN_P0_Msk,PORT2_IN_P0_Pos);
	CT234_HWP	= RD_REG(PORT2->IN,PORT2_IN_P5_Msk,PORT2_IN_P5_Pos);
	CT56_HWP	= RD_REG(PORT0->IN,PORT0_IN_P9_Msk,PORT0_IN_P9_Pos);
	CT78_HWP	= RD_REG(PORT3->IN,PORT3_IN_P2_Msk,PORT3_IN_P2_Pos);
	GD1_HWP		= RD_REG(PORT0->IN,PORT0_IN_P12_Msk,PORT0_IN_P12_Pos);
	GD2_HWP		= RD_REG(PORT0->IN,PORT0_IN_P2_Msk,PORT0_IN_P2_Pos);

	//GRPT_FHW = ((GRPT3_HWP<<2) | (GRPT2_HWP<<1) | (GRPT1_HWP<<0));
	//ACPT_FHW = ((ACPT3_HWP<<2) | (ACPT2_HWP<<1) | (ACPT1_HWP<<0));
	//DCPT_FHW = ((DCPT1_HWP<<1) | (DCPT2_HWP<<0));
	//CT_FHW	 = ((CT78_HWP<<3) | (CT56_HWP<<2) | (CT234_HWP<<1) | (CT1_HWP<<0));
	//GD_FHW	 = ((GD2_HWP<<1) | (GD1_HWP<<0));

	FHW = ((GRPT1_HWP) || (GRPT2_HWP) || (GRPT3_HWP) || (ACPT1_HWP) || (ACPT2_HWP) || (ACPT3_HWP) || (DCPT1_HWP) || (DCPT2_HWP) || (CT1_HWP) || (CT234_HWP) || (CT56_HWP) || (CT78_HWP)); // || (GD1_HWP) || (GD2_HWP));

	if (FHW == 1) {Fault = 0;}
	else if (FHW == 0) {Fault = 1;}

	/*
	FHW1 =	((ACPTS_HWP<<7) | (ACPTR_HWP<<6) | (DCPT2_HWP<<5) | (IVCTT_HWP<<4) | (IVCTS_HWP<<3) | (IVCTR_HWP<<2) | (DCCT1_HWP<<1));
	FHW1 =	((GDsp1F_HWP<<7) | (GDS1F_HWP<<6) | (GDR2F_HWP<<5) | (GDR1F_HWP<<4) | (GDT2F_HWP<<3) | (GDT1F_HWP<<2) | (GDS2F_HWP<<1));
	FHW1 =	((ACPTT_HWP<<7) | (GDsp3F_HWP<<6) | (GDsp2F_HWP<<5) | (SPVP5_HWP<<4) | (SPVN15_HWP<<3) | (SPVP15_HWP<<2) | (SPVP24_HWP<<1));
	 */
}

char signeddata(int data)
{
	char datawithsign[32];

	if (data>0)
	{
		sprintf(datawithsign,"%c%d",'+',data);
	}
	else
	{
		sprintf(datawithsign,"%d",data);
	}

	return datawithsign;
}

char dectohex(long int decimalNumber){
	long int remainder,quotient;
    int i=1,j,temp;
    char hexadecimalNumber[4];

    quotient = decimalNumber;

    while(quotient!=0){
    	temp = quotient % 16;
    	if(temp < 10){temp = temp + 48;}
    	else{temp = temp + 55;}
    	hexadecimalNumber[i++]= temp;
    	quotient = quotient/16;
    }

    for(j=i-1;j>0;j--)
    printf("%c",hexadecimalNumber[j]);

    return hexadecimalNumber;
}

int findn(int num)
{
   if (num < 10)
      return 1;
   if (num < 100)
      return 2;
   if (num < 1000)
      return 3;
   if (num < 10000)
      return 4;
   //continue until max int
}
