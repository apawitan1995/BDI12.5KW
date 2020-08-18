/*
 * DMA_app.c
 *
 *  Created on: Jan 22, 2014
 *      Author: Hanif
 */

#include "peripheral/DMA_app.h"

volatile bool g_endTransfer = false;
volatile uint32_t srcBuffer[BUFFER_SIZE];
__IO uint32_t *dstBuffer;

void DMA_RS485_Init(void)
{
	uint32_t i;

	// Set destination to USIC FIFO
	DMA003_Handle0.ChConfig.DstAddress = (uint32_t)UART001_Handle0.UartRegs->IN;

	// Buffer initialization
	for (i = 0; i < BUFFER_SIZE; i++)
	{srcBuffer[i] = i;}
}

void DMA0_CH0_Init(void)
{
	/************************************************************************/
	//Initialization for GPDMA0_CH0 --> VADC_G0_CH6 (DCPT1)
	//Configure DMA channel
	//Write the starting source register for GPDMA0_CH0
	WR_REG(GPDMA0_CH0->SAR,GPDMA0_CH_SAR_SAR_Msk,GPDMA0_CH_SAR_SAR_Pos,(uint32_t)(&(VADC_G0->RES[DCPT1_AIN_Result_Register])));
	//Write the destination register for GPDMA0_CH0
	WR_REG(GPDMA0_CH0->DAR,GPDMA0_CH_DAR_DAR_Msk,GPDMA0_CH_DAR_DAR_Pos,(uint32_t)(&DCPT1_AIN_Result));

	//Configure DMA Control Register
	GPDMA0_CH0->CTLL=(uint32_t)0;
	GPDMA0_CH0->CTLH=(uint32_t)0;
	GPDMA0_CH0->LLP=(uint32_t)0;

	//Disable Interrupt
	//CLR_BIT(GPDMA0_CH0->CTLL,GPDMA0_CH_CTLL_INT_EN_Pos);

	//Write one block size
	WR_REG(GPDMA0_CH0->CTLH,GPDMA0_CH_CTLH_BLOCK_TS_Msk,GPDMA0_CH_CTLH_BLOCK_TS_Pos,0x01);
	//Configure 32 bit width for source and destination register
	WR_REG(GPDMA0_CH0->CTLL,GPDMA0_CH_CTLL_SRC_TR_WIDTH_Msk,GPDMA0_CH_CTLL_SRC_TR_WIDTH_Pos,0x02);
	WR_REG(GPDMA0_CH0->CTLL,GPDMA0_CH_CTLL_DST_TR_WIDTH_Msk,GPDMA0_CH_CTLL_DST_TR_WIDTH_Pos,0x02);
	//No increment or decrement for source and destination register
	WR_REG(GPDMA0_CH0->CTLL,GPDMA0_CH_CTLL_SINC_Msk,GPDMA0_CH_CTLL_SINC_Pos,0x02);
	WR_REG(GPDMA0_CH0->CTLL,GPDMA0_CH_CTLL_DINC_Msk,GPDMA0_CH_CTLL_DINC_Pos,0x02);
	//Disable Scather, Gather, and linked list pointer for both source and destination register
	CLR_BIT(GPDMA0_CH0->CTLL,GPDMA0_CH_CTLL_DST_SCATTER_EN_Pos);
	CLR_BIT(GPDMA0_CH0->CTLL,GPDMA0_CH_CTLL_SRC_GATHER_EN_Pos);
	CLR_BIT(GPDMA0_CH0->CTLL,GPDMA0_CH_CTLL_LLP_DST_EN_Pos);
	CLR_BIT(GPDMA0_CH0->CTLL,GPDMA0_CH_CTLL_LLP_SRC_EN_Pos);
	//1 burst transfer for source and destination register
	WR_REG(GPDMA0_CH0->CTLL,GPDMA0_CH_CTLL_SRC_MSIZE_Msk,GPDMA0_CH_CTLL_SRC_MSIZE_Pos,0x00);
	WR_REG(GPDMA0_CH0->CTLL,GPDMA0_CH_CTLL_DEST_MSIZE_Msk,GPDMA0_CH_CTLL_DEST_MSIZE_Pos,0x00);

	//Set transfer type for peripheral to memory with GPDMA as flow controller
	WR_REG(GPDMA0_CH0->CTLL,GPDMA0_CH_CTLL_TT_FC_Msk,GPDMA0_CH_CTLL_TT_FC_Pos,0x02);

	//Configure channel control register
	//Route DLR line 0 for GPDMA0_CH0
	WR_REG(GPDMA0_CH0->CFGH,GPDMA0_CH_CFGH_SRC_PER_Msk,GPDMA0_CH_CFGH_SRC_PER_Pos,0x00);
	//Enable hardware handshaking for source
	CLR_BIT(GPDMA0_CH0->CFGL,GPDMA0_CH_CFGL_HS_SEL_SRC_Pos);
	//Enable source reload address
	SET_BIT(GPDMA0_CH0->CFGL,GPDMA0_CH_CFGL_RELOAD_SRC_Pos);
	//Enable destination reload address
	SET_BIT(GPDMA0_CH0->CFGL,GPDMA0_CH_CFGL_RELOAD_DST_Pos);

	//Enable GPDMA0_CH0
	//WR_REG(GPDMA0->CHENREG,GPDMA0_CHENREG_CH_Msk,GPDMA0_CHENREG_CH_Pos,0x01);
	GPDMA0->CHENREG |= (((uint32_t) 1 << GPDMA0_CHENREG_CH_Pos) &GPDMA0_CHENREG_CH_Msk)|\
			(((uint32_t)  1<< GPDMA0_CHENREG_WE_CH_Pos) &GPDMA0_CHENREG_WE_CH_Msk);

	//Connect GPDMA0_CH0 DLR0 to VADC_G0.SR3 (DCPT1_AIN)
	WR_REG(DLR->SRSEL0,DLR_SRSEL0_RS0_Msk,DLR_SRSEL0_RS0_Pos,0x02);
	//Enable DLR Line0
	SET_BIT(DLR->LNEN,DLR_LNEN_LN0_Pos);
}

void DMA0_CH1_Init(void)
{
	//Configure GPDMA_CH1 --> VADC_G1_CH3 (ACPT2)
	//Configure DMA channel
	//Write the starting source register for GPDMA0_CH1
	WR_REG(GPDMA0_CH1->SAR,GPDMA0_CH_SAR_SAR_Msk,GPDMA0_CH_SAR_SAR_Pos,(uint32_t)(&(VADC_G1->RES[ACPT2_AIN_Result_Register])));
	//Write the destination register for GPDMA0_CH1
	WR_REG(GPDMA0_CH1->DAR,GPDMA0_CH_DAR_DAR_Msk,GPDMA0_CH_DAR_DAR_Pos,(uint32_t)(&ACPT2_AIN_Result));

	//Configure DMA Control Register
	GPDMA0_CH1->CTLL=(uint32_t)0;
	GPDMA0_CH1->CTLH=(uint32_t)0;
	GPDMA0_CH1->LLP=(uint32_t)0;

	//Write one block size
	WR_REG(GPDMA0_CH1->CTLH,GPDMA0_CH_CTLH_BLOCK_TS_Msk,GPDMA0_CH_CTLH_BLOCK_TS_Pos,0x01);
	//Configure 32 bit width for source and destination register
	WR_REG(GPDMA0_CH1->CTLL,GPDMA0_CH_CTLL_SRC_TR_WIDTH_Msk,GPDMA0_CH_CTLL_SRC_TR_WIDTH_Pos,0x02);
	WR_REG(GPDMA0_CH1->CTLL,GPDMA0_CH_CTLL_DST_TR_WIDTH_Msk,GPDMA0_CH_CTLL_DST_TR_WIDTH_Pos,0x02);
	//No increment or decrement for source and destination register
	WR_REG(GPDMA0_CH1->CTLL,GPDMA0_CH_CTLL_SINC_Msk,GPDMA0_CH_CTLL_SINC_Pos,0x02);
	WR_REG(GPDMA0_CH1->CTLL,GPDMA0_CH_CTLL_DINC_Msk,GPDMA0_CH_CTLL_DINC_Pos,0x02);
	//Disable Scather, Gather, and linked list pointer for both source and destination register
	CLR_BIT(GPDMA0_CH1->CTLL,GPDMA0_CH_CTLL_DST_SCATTER_EN_Pos);
	CLR_BIT(GPDMA0_CH1->CTLL,GPDMA0_CH_CTLL_SRC_GATHER_EN_Pos);
	CLR_BIT(GPDMA0_CH1->CTLL,GPDMA0_CH_CTLL_LLP_DST_EN_Pos);
	CLR_BIT(GPDMA0_CH1->CTLL,GPDMA0_CH_CTLL_LLP_SRC_EN_Pos);
	//1 burst transfer for source and destination register
	WR_REG(GPDMA0_CH1->CTLL,GPDMA0_CH_CTLL_SRC_MSIZE_Msk,GPDMA0_CH_CTLL_SRC_MSIZE_Pos,0x00);
	WR_REG(GPDMA0_CH1->CTLL,GPDMA0_CH_CTLL_DEST_MSIZE_Msk,GPDMA0_CH_CTLL_DEST_MSIZE_Pos,0x00);

	//Set transfer type for peripheral to memory with GPDMA as flow controller
	WR_REG(GPDMA0_CH1->CTLL,GPDMA0_CH_CTLL_TT_FC_Msk,GPDMA0_CH_CTLL_TT_FC_Pos,0x02);

	//Configure channel control register
	//Route DLR line 1 for GPDMA0_CH1
	WR_REG(GPDMA0_CH1->CFGH,GPDMA0_CH_CFGH_SRC_PER_Msk,GPDMA0_CH_CFGH_SRC_PER_Pos,0x01);
	//Enable hardware handshaking for source
	CLR_BIT(GPDMA0_CH1->CFGL,GPDMA0_CH_CFGL_HS_SEL_SRC_Pos);
	//Enable source reload address
	SET_BIT(GPDMA0_CH1->CFGL,GPDMA0_CH_CFGL_RELOAD_SRC_Pos);
	//Enable destination reload address
	SET_BIT(GPDMA0_CH1->CFGL,GPDMA0_CH_CFGL_RELOAD_DST_Pos);

	//Enable GPDMA0_CH1
	GPDMA0->CHENREG |= (((uint32_t) 2 << GPDMA0_CHENREG_CH_Pos) &GPDMA0_CHENREG_CH_Msk)|\
			(((uint32_t) 2 << GPDMA0_CHENREG_WE_CH_Pos) &GPDMA0_CHENREG_WE_CH_Msk);

	//Connect GPDMA0_CH1 DLR1 to VADC_G1.SR0 (ACPT2_AIN)
	WR_REG(DLR->SRSEL0,DLR_SRSEL0_RS1_Msk,DLR_SRSEL0_RS1_Pos,0x03);
	//Enable DLR Line1
	SET_BIT(DLR->LNEN,DLR_LNEN_LN1_Pos);
}

void DMA0_CH2_Init(void)
{
	//Configure GPDMA_CH2 --> VADC_G1_CH2 (DCPT2)
	//Configure DMA channel
	//Write the starting source register for GPDMA0_CH2
	WR_REG(GPDMA0_CH2->SAR,GPDMA0_CH_SAR_SAR_Msk,GPDMA0_CH_SAR_SAR_Pos,(uint32_t)(&(VADC_G1->RES[DCPT2_AIN_Result_Register])));
	//Write the destination register for GPDMA0_CH2
	WR_REG(GPDMA0_CH2->DAR,GPDMA0_CH_DAR_DAR_Msk,GPDMA0_CH_DAR_DAR_Pos,(uint32_t)(&DCPT2_AIN_Result));

	//Configure DMA Control Register
	GPDMA0_CH2->CTLL=(uint32_t)0;
	GPDMA0_CH2->CTLH=(uint32_t)0;
	GPDMA0_CH2->LLP=(uint32_t)0;

	//Write one block size
	WR_REG(GPDMA0_CH2->CTLH,GPDMA0_CH_CTLH_BLOCK_TS_Msk,GPDMA0_CH_CTLH_BLOCK_TS_Pos,0x01);
	//Configure 32 bit width for source and destination register
	WR_REG(GPDMA0_CH2->CTLL,GPDMA0_CH_CTLL_SRC_TR_WIDTH_Msk,GPDMA0_CH_CTLL_SRC_TR_WIDTH_Pos,0x02);
	WR_REG(GPDMA0_CH2->CTLL,GPDMA0_CH_CTLL_DST_TR_WIDTH_Msk,GPDMA0_CH_CTLL_DST_TR_WIDTH_Pos,0x02);
	//No increment or decrement for source and destination register
	WR_REG(GPDMA0_CH2->CTLL,GPDMA0_CH_CTLL_SINC_Msk,GPDMA0_CH_CTLL_SINC_Pos,0x02);
	WR_REG(GPDMA0_CH2->CTLL,GPDMA0_CH_CTLL_DINC_Msk,GPDMA0_CH_CTLL_DINC_Pos,0x02);
	//Disable Scather, Gather, and linked list pointer for both source and destination register
	CLR_BIT(GPDMA0_CH2->CTLL,GPDMA0_CH_CTLL_DST_SCATTER_EN_Pos);
	CLR_BIT(GPDMA0_CH2->CTLL,GPDMA0_CH_CTLL_SRC_GATHER_EN_Pos);
	CLR_BIT(GPDMA0_CH2->CTLL,GPDMA0_CH_CTLL_LLP_DST_EN_Pos);
	CLR_BIT(GPDMA0_CH2->CTLL,GPDMA0_CH_CTLL_LLP_SRC_EN_Pos);
	//1 burst transfer for source and destination register
	WR_REG(GPDMA0_CH2->CTLL,GPDMA0_CH_CTLL_SRC_MSIZE_Msk,GPDMA0_CH_CTLL_SRC_MSIZE_Pos,0x00);
	WR_REG(GPDMA0_CH2->CTLL,GPDMA0_CH_CTLL_DEST_MSIZE_Msk,GPDMA0_CH_CTLL_DEST_MSIZE_Pos,0x00);

	//Set transfer type for peripheral to memory with GPDMA as flow controller
	WR_REG(GPDMA0_CH2->CTLL,GPDMA0_CH_CTLL_TT_FC_Msk,GPDMA0_CH_CTLL_TT_FC_Pos,0x02);

	//Configure channel control register
	//Route DLR line 2 for GPDMA0_CH2
	WR_REG(GPDMA0_CH2->CFGH,GPDMA0_CH_CFGH_SRC_PER_Msk,GPDMA0_CH_CFGH_SRC_PER_Pos,0x02);
	//Enable hardware handshaking for source
	CLR_BIT(GPDMA0_CH2->CFGL,GPDMA0_CH_CFGL_HS_SEL_SRC_Pos);
	//Enable source reload address
	SET_BIT(GPDMA0_CH2->CFGL,GPDMA0_CH_CFGL_RELOAD_SRC_Pos);
	//Enable destination reload address
	SET_BIT(GPDMA0_CH2->CFGL,GPDMA0_CH_CFGL_RELOAD_DST_Pos);

	//Enable GPDMA0_CH2
	GPDMA0->CHENREG |= (uint32_t)
				(((uint32_t) 4 << GPDMA0_CHENREG_CH_Pos) &GPDMA0_CHENREG_CH_Msk)|\
				(((uint32_t) 4 << GPDMA0_CHENREG_WE_CH_Pos) &GPDMA0_CHENREG_WE_CH_Msk);

	//Connect GPDMA0_CH2 DLR2 to VADC_G1.SR3 (DCPT2_AIN)
	WR_REG(DLR->SRSEL0,DLR_SRSEL0_RS2_Msk,DLR_SRSEL0_RS2_Pos,0x03);
	//Enable DLR Line2
	SET_BIT(DLR->LNEN,DLR_LNEN_LN2_Pos);
}

void DMA0_CH4_Init(void)
{
	//Configure GPDMA_CH4 --> VADC_G2_CH1 (CT1)
	//Configure DMA channel
	//Write the starting source register for GPDMA0_CH2
	WR_REG(GPDMA0_CH4->SAR,GPDMA0_CH_SAR_SAR_Msk,GPDMA0_CH_SAR_SAR_Pos,(uint32_t)(&(VADC_G2->RES[CT1_Result_Register])));
	//Write the destination register for GPDMA0_CH1
	WR_REG(GPDMA0_CH4->DAR,GPDMA0_CH_DAR_DAR_Msk,GPDMA0_CH_DAR_DAR_Pos,(uint32_t)(&CT1_Result));

	//Configure DMA Control Register
	GPDMA0_CH4->CTLL=(uint32_t)0;
	GPDMA0_CH4->CTLH=(uint32_t)0;
	GPDMA0_CH4->LLP=(uint32_t)0;

	//Write one block size
	WR_REG(GPDMA0_CH4->CTLH,GPDMA0_CH_CTLH_BLOCK_TS_Msk,GPDMA0_CH_CTLH_BLOCK_TS_Pos,0x01);
	//Configure 32 bit width for source and destination register
	WR_REG(GPDMA0_CH4->CTLL,GPDMA0_CH_CTLL_SRC_TR_WIDTH_Msk,GPDMA0_CH_CTLL_SRC_TR_WIDTH_Pos,0x02);
	WR_REG(GPDMA0_CH4->CTLL,GPDMA0_CH_CTLL_DST_TR_WIDTH_Msk,GPDMA0_CH_CTLL_DST_TR_WIDTH_Pos,0x02);
	//No increment or decrement for source and destination register
	WR_REG(GPDMA0_CH4->CTLL,GPDMA0_CH_CTLL_SINC_Msk,GPDMA0_CH_CTLL_SINC_Pos,0x02);
	WR_REG(GPDMA0_CH4->CTLL,GPDMA0_CH_CTLL_DINC_Msk,GPDMA0_CH_CTLL_DINC_Pos,0x02);
	//Disable Scather, Gather, and linked list pointer for both source and destination register
	CLR_BIT(GPDMA0_CH4->CTLL,GPDMA0_CH_CTLL_DST_SCATTER_EN_Pos);
	CLR_BIT(GPDMA0_CH4->CTLL,GPDMA0_CH_CTLL_SRC_GATHER_EN_Pos);
	CLR_BIT(GPDMA0_CH4->CTLL,GPDMA0_CH_CTLL_LLP_DST_EN_Pos);
	CLR_BIT(GPDMA0_CH4->CTLL,GPDMA0_CH_CTLL_LLP_SRC_EN_Pos);
	//1 burst transfer for source and destination register
	WR_REG(GPDMA0_CH4->CTLL,GPDMA0_CH_CTLL_SRC_MSIZE_Msk,GPDMA0_CH_CTLL_SRC_MSIZE_Pos,0x00);
	WR_REG(GPDMA0_CH4->CTLL,GPDMA0_CH_CTLL_DEST_MSIZE_Msk,GPDMA0_CH_CTLL_DEST_MSIZE_Pos,0x00);

	//Set transfer type for peripheral to memory with GPDMA as flow controller
	WR_REG(GPDMA0_CH4->CTLL,GPDMA0_CH_CTLL_TT_FC_Msk,GPDMA0_CH_CTLL_TT_FC_Pos,0x02);

	//Configure channel control register
	//Route DLR line 4 for GPDMA0_CH4
	WR_REG(GPDMA0_CH4->CFGH,GPDMA0_CH_CFGH_SRC_PER_Msk,GPDMA0_CH_CFGH_SRC_PER_Pos,0x04);
	//Enable hardware handshaking for source
	CLR_BIT(GPDMA0_CH4->CFGL,GPDMA0_CH_CFGL_HS_SEL_SRC_Pos);
	//Enable source reload address
	SET_BIT(GPDMA0_CH4->CFGL,GPDMA0_CH_CFGL_RELOAD_SRC_Pos);
	//Enable destination reload address
	SET_BIT(GPDMA0_CH4->CFGL,GPDMA0_CH_CFGL_RELOAD_DST_Pos);

	//Enable GPDMA0_CH2
	GPDMA0->CHENREG |= (uint32_t)
				(((uint32_t) 4 << GPDMA0_CHENREG_CH_Pos) &GPDMA0_CHENREG_CH_Msk)|\
				(((uint32_t) 4 << GPDMA0_CHENREG_WE_CH_Pos) &GPDMA0_CHENREG_WE_CH_Msk);

	//Connect GPDMA0_CH4 DLR4 to VADC_G2.SR1 (CT1)
	WR_REG(DLR->SRSEL0,DLR_SRSEL0_RS4_Msk,DLR_SRSEL0_RS4_Pos,0x03);
	//Enable DLR Line2
	SET_BIT(DLR->LNEN,DLR_LNEN_LN4_Pos);
}

void DMA0_CH5_Init(void)
{
	//Configure GPDMA_CH5 --> VADC_G2_CH0 (CT6)
	//Configure DMA channel
	//Write the starting source register for GPDMA0_CH2
	WR_REG(GPDMA0_CH5->SAR,GPDMA0_CH_SAR_SAR_Msk,GPDMA0_CH_SAR_SAR_Pos,(uint32_t)(&(VADC_G2->RES[CT6_Result_Register])));
	//Write the destination register for GPDMA0_CH1
	WR_REG(GPDMA0_CH5->DAR,GPDMA0_CH_DAR_DAR_Msk,GPDMA0_CH_DAR_DAR_Pos,(uint32_t)(&CT6_Result));

	//Configure DMA Control Register
	GPDMA0_CH5->CTLL=(uint32_t)0;
	GPDMA0_CH5->CTLH=(uint32_t)0;
	GPDMA0_CH5->LLP=(uint32_t)0;

	//Write one block size
	WR_REG(GPDMA0_CH5->CTLH,GPDMA0_CH_CTLH_BLOCK_TS_Msk,GPDMA0_CH_CTLH_BLOCK_TS_Pos,0x01);
	//Configure 32 bit width for source and destination register
	WR_REG(GPDMA0_CH5->CTLL,GPDMA0_CH_CTLL_SRC_TR_WIDTH_Msk,GPDMA0_CH_CTLL_SRC_TR_WIDTH_Pos,0x02);
	WR_REG(GPDMA0_CH5->CTLL,GPDMA0_CH_CTLL_DST_TR_WIDTH_Msk,GPDMA0_CH_CTLL_DST_TR_WIDTH_Pos,0x02);
	//No increment or decrement for source and destination register
	WR_REG(GPDMA0_CH5->CTLL,GPDMA0_CH_CTLL_SINC_Msk,GPDMA0_CH_CTLL_SINC_Pos,0x02);
	WR_REG(GPDMA0_CH5->CTLL,GPDMA0_CH_CTLL_DINC_Msk,GPDMA0_CH_CTLL_DINC_Pos,0x02);
	//Disable Scather, Gather, and linked list pointer for both source and destination register
	CLR_BIT(GPDMA0_CH5->CTLL,GPDMA0_CH_CTLL_DST_SCATTER_EN_Pos);
	CLR_BIT(GPDMA0_CH5->CTLL,GPDMA0_CH_CTLL_SRC_GATHER_EN_Pos);
	CLR_BIT(GPDMA0_CH5->CTLL,GPDMA0_CH_CTLL_LLP_DST_EN_Pos);
	CLR_BIT(GPDMA0_CH5->CTLL,GPDMA0_CH_CTLL_LLP_SRC_EN_Pos);
	//1 burst transfer for source and destination register
	WR_REG(GPDMA0_CH5->CTLL,GPDMA0_CH_CTLL_SRC_MSIZE_Msk,GPDMA0_CH_CTLL_SRC_MSIZE_Pos,0x00);
	WR_REG(GPDMA0_CH5->CTLL,GPDMA0_CH_CTLL_DEST_MSIZE_Msk,GPDMA0_CH_CTLL_DEST_MSIZE_Pos,0x00);

	//Set transfer type for peripheral to memory with GPDMA as flow controller
	WR_REG(GPDMA0_CH5->CTLL,GPDMA0_CH_CTLL_TT_FC_Msk,GPDMA0_CH_CTLL_TT_FC_Pos,0x02);

	//Configure channel control register
	//Route DLR line 5 for GPDMA0_CH5
	WR_REG(GPDMA0_CH5->CFGH,GPDMA0_CH_CFGH_SRC_PER_Msk,GPDMA0_CH_CFGH_SRC_PER_Pos,0x05);
	//Enable hardware handshaking for source
	CLR_BIT(GPDMA0_CH5->CFGL,GPDMA0_CH_CFGL_HS_SEL_SRC_Pos);
	//Enable source reload address
	SET_BIT(GPDMA0_CH5->CFGL,GPDMA0_CH_CFGL_RELOAD_SRC_Pos);
	//Enable destination reload address
	SET_BIT(GPDMA0_CH5->CFGL,GPDMA0_CH_CFGL_RELOAD_DST_Pos);

	//Enable GPDMA0_CH2
	GPDMA0->CHENREG |= (uint32_t)
				(((uint32_t) 4 << GPDMA0_CHENREG_CH_Pos) &GPDMA0_CHENREG_CH_Msk)|\
				(((uint32_t) 4 << GPDMA0_CHENREG_WE_CH_Pos) &GPDMA0_CHENREG_WE_CH_Msk);

	//Connect GPDMA0_CH5 DLR5 to VADC_G2.SR0 (CT6)
	WR_REG(DLR->SRSEL0,DLR_SRSEL0_RS5_Msk,DLR_SRSEL0_RS5_Pos,0x04);
	//Enable DLR Line2
	SET_BIT(DLR->LNEN,DLR_LNEN_LN5_Pos);
}

void DMA1_CH8_Init(void)
{
	//De-assert reset signal for GPDMA1
		SET_BIT(SCU_RESET->PRCLR2,SCU_RESET_PRCLR2_DMA1RS_Pos);
	//Enable GPDMA0
		SET_BIT(GPDMA1->DMACFGREG,GPDMA1_DMACFGREG_DMA_EN_Pos);
/************************************************************************/
	//Configure GPDMA1_CH0 --> VADC_G2_CH0 (CT6)
	//Configure DMA channel
	//Write the starting source register for GPDMA1_CH0
	WR_REG(GPDMA1_CH0->SAR,GPDMA1_CH_SAR_SAR_Msk,GPDMA1_CH_SAR_SAR_Pos,(uint32_t)(&(VADC_G2->RES[CT6_Result_Register])));
	//Write the destination register for GPDMA0_CH2
	WR_REG(GPDMA1_CH0->DAR,GPDMA1_CH_DAR_DAR_Msk,GPDMA1_CH_DAR_DAR_Pos,(uint32_t)(&CT6_Result));

	//Configure DMA Control Register
	GPDMA1_CH0->CTLL=(uint32_t)0;
	GPDMA1_CH0->CTLH=(uint32_t)0;

	//Write one block size
	WR_REG(GPDMA1_CH0->CTLH,GPDMA1_CH_CTLH_BLOCK_TS_Msk,GPDMA1_CH_CTLH_BLOCK_TS_Pos,0x01);
	//Configure 32 bit width for source and destination register
	WR_REG(GPDMA1_CH0->CTLL,GPDMA1_CH_CTLL_SRC_TR_WIDTH_Msk,GPDMA0_CH_CTLL_SRC_TR_WIDTH_Pos,0x02);
	WR_REG(GPDMA1_CH0->CTLL,GPDMA1_CH_CTLL_DST_TR_WIDTH_Msk,GPDMA0_CH_CTLL_DST_TR_WIDTH_Pos,0x02);
	//No increment or decrement for source and destination register
	WR_REG(GPDMA1_CH0->CTLL,GPDMA1_CH_CTLL_SINC_Msk,GPDMA0_CH_CTLL_SINC_Pos,0x02);
	WR_REG(GPDMA1_CH0->CTLL,GPDMA1_CH_CTLL_DINC_Msk,GPDMA0_CH_CTLL_DINC_Pos,0x02);

	//1 burst transfer for source and destination register
	WR_REG(GPDMA1_CH0->CTLL,GPDMA1_CH_CTLL_SRC_MSIZE_Msk,GPDMA0_CH_CTLL_SRC_MSIZE_Pos,0x00);
	WR_REG(GPDMA1_CH0->CTLL,GPDMA1_CH_CTLL_DEST_MSIZE_Msk,GPDMA0_CH_CTLL_DEST_MSIZE_Pos,0x00);
	//Set transfer type for memory to memory with GPDMA as flow controller
	WR_REG(GPDMA1_CH0->CTLL,GPDMA1_CH_CTLL_TT_FC_Msk,GPDMA0_CH_CTLL_TT_FC_Pos,0x00);

	//Configure channel control register
	//Route DLR line 8 for GPDMA1_CH0
	WR_REG(GPDMA1_CH0->CFGH,GPDMA1_CH_CFGH_SRC_PER_Msk,GPDMA1_CH_CFGH_SRC_PER_Pos,0x00);
//	//Enable hardware handshaking for source
//	SET_BIT(GPDMA0_CH2->CFGL,GPDMA0_CH_CFGL_HS_SEL_SRC_Pos);
	//Enable source reload address
	SET_BIT(GPDMA0_CH2->CFGL,GPDMA0_CH_CFGL_RELOAD_SRC_Pos);
	//Enable destination reload address
	SET_BIT(GPDMA0_CH2->CFGL,GPDMA0_CH_CFGL_RELOAD_DST_Pos);

	//Enable GPDMA0_CH2
	GPDMA0->CHENREG |= (uint32_t)
				(((uint32_t) 4 << GPDMA0_CHENREG_CH_Pos) &GPDMA0_CHENREG_CH_Msk)|\
				(((uint32_t) 4 << GPDMA0_CHENREG_WE_CH_Pos) &GPDMA0_CHENREG_WE_CH_Msk);

	//Connect GPDMA0_CH2 DLR2 to VADC_G1.SR3 (DCPT2_AIN)
	WR_REG(DLR->SRSEL0,DLR_SRSEL0_RS2_Msk,DLR_SRSEL0_RS2_Pos,0x03);
	//Enable DLR Line2
	SET_BIT(DLR->LNEN,DLR_LNEN_LN2_Pos);
}

void DMA_Init_app(void)
{
	//De-assert reset signal for GPDMA0
	SET_BIT(SCU_RESET->PRCLR2,SCU_RESET_PRCLR2_DMA0RS_Pos);
	//Enable GPDMA0
	SET_BIT(GPDMA0->DMACFGREG,GPDMA0_DMACFGREG_DMA_EN_Pos);
/************************************************************************/
	DMA0_CH0_Init();
/************************************************************************/
	DMA0_CH1_Init();
/************************************************************************/
	DMA0_CH2_Init();
/************************************************************************/
	DMA0_CH4_Init();
/************************************************************************/
	DMA0_CH5_Init();
/************************************************************************/
	//Enable GPDMA0 CH0,CH1,CH2,CH4,CH5
	GPDMA0->CHENREG = 0x3737;
//	//Enable GPDMA0 CH0,CH1,CH2,CH4
//	GPDMA0->CHENREG = 0x1717;
//	//Enable GPDMA0 CH2,CH4
//	GPDMA0->CHENREG = 0x1414;
//
//	//Enable GPDMA0 CH0,CH1
//	GPDMA0->CHENREG = 0x0303;
}

