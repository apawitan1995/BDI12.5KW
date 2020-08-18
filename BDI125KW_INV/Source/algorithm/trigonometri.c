/*
 * trigonometri.c
 *
 *  Created on: Mar 30, 2017
 *      Author: Mukhlish Ghany A
 */

#include "algorithm/trigonometri.h"

//-----------------------------PLL-------------------------------
volatile int32_t TetaSine_PLL_fix,TetaCos_PLL_fix;
volatile int32_t integSine_PLL_fix,integCos_PLL_fix;
volatile int32_t sinTeta_PLL_fix,cosTeta_PLL_fix;
volatile int32_t cosinus_pll, sinus_pll, cosmin_pll, cosplus_pll, sinmin_pll, sinplus_pll;

int trigonometri_PLL_Sin (int32_t Teta_PLL)
	{

	if (Teta_PLL > 3294206 ) {Teta_PLL -= 6588413;} // 20 bit
	else if (Teta_PLL < -3294206) {Teta_PLL += 6588413;} // 20 bit

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

	// Trigonomethric Approximation END Here

	sinTeta_PLL_fix = integSine_PLL_fix>>10; //20-10
	return (sinTeta_PLL_fix);
	}

int trigonometri_PLL_Cos (int32_t Teta_PLL)
	{

	if (Teta_PLL > 3294206 ) {Teta_PLL -= 6588413;} // 20 bit
	else if (Teta_PLL < -3294206) {Teta_PLL += 6588413;} // 20 bit

	//compute cosine
	TetaCos_PLL_fix = Teta_PLL + 1647100;	// 20
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

	cosTeta_PLL_fix = integCos_PLL_fix>>10;

	return (cosTeta_PLL_fix);
	}

//---------------------------Trigonometri----------------------------------

int32_t TetaSine_fix,TetaCos_fix;
int32_t integSine_fix,integCos_fix;
int32_t sinTeta_fix,cosTeta_fix;

int trigonometri_Cos (int32_t Teta)
	{

	if (Teta > 3294206 ) {Teta -= 6588413;} // 20 bit
	else if (Teta < -3294206) {Teta += 6588413;} // 20 bit

	//compute cosine
	TetaCos_fix = Teta + 1647100;	// 20
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
	// Trigonomethric Approximation END Here

	cosTeta_fix = integCos_fix>>10;//20-10

	return (cosTeta_fix);
	}


int trigonometri_Sin (int32_t Teta)
	{

	if (Teta > 3294206 ) {Teta -= 6588413;} // 20 bit
	else if (Teta < -3294206) {Teta += 6588413;} // 20 bit

	TetaSine_fix = Teta;	// 20
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

	sinTeta_fix = integSine_fix>>10; //20-10

	return (sinTeta_fix);
	}

/*
//---------------------------Trigonometri----------------------------------

volatile int32_t TetaSine1_fix, TetaSine2_fix, TetaSine3_fix, TetaCos1_fix, TetaCos2_fix, TetaCos3_fix;
volatile int32_t integSine1_fix, integSine2_fix, integSine3_fix, integCos1_fix, integCos2_fix, integCos3_fix;
volatile int32_t sinTeta1_fix, sinTeta2_fix, sinTeta3_fix, cosTeta1_fix, cosTeta2_fix, cosTeta3_fix;

int trigonometri_Cos1 (int32_t Teta)
{
	if (Teta > 3294206 ) {Teta -= 6588413;} // 20 bit
	else if (Teta < -3294206) {Teta += 6588413;} // 20 bit

	//compute cosine
	TetaCos1_fix = Teta + 1647100;	// 20
	if (TetaCos1_fix > 3294206 ) {TetaCos1_fix -= 6588413;}

	if( TetaCos1_fix < 0)
	{
		integCos1_fix = 1304*(TetaCos1_fix>>10)+(415*(TetaCos1_fix>>10)>>10)*(TetaCos1_fix>>10); // 20 bit
		if (integCos1_fix <0) {integCos1_fix = 261*(((integCos1_fix>>10)*(-integCos1_fix>>10)-integCos1_fix)>>10)+integCos1_fix;}
		else {integCos1_fix = 261*(((integCos1_fix>>10)*(integCos1_fix>>10)-integCos1_fix)>>10)+integCos1_fix;}
	}
	else
	{
		integCos1_fix = 1304*(TetaCos1_fix>>10)-(415*(TetaCos1_fix>>10)>>10)*(TetaCos1_fix>>10); // 20 bit
		if (integCos1_fix <0) {integCos1_fix = 261*(((integCos1_fix>>10)*(-integCos1_fix>>10)-integCos1_fix)>>10)+integCos1_fix;}
		else {integCos1_fix = 261*(((integCos1_fix>>10)*(integCos1_fix>>10)-integCos1_fix)>>10)+integCos1_fix;}
	}
	// Trigonomethric Approximation END Here

	cosTeta1_fix = integCos1_fix>>10;//20-10

	return (cosTeta1_fix); //10
}

int trigonometri_Cos2 (int32_t Teta)
{
	if (Teta > 3294206 ) {Teta -= 6588413;} // 20 bit
	else if (Teta < -3294206) {Teta += 6588413;} // 20 bit

	//compute cosine
	TetaCos2_fix = Teta + 1647100;	// 20
	if (TetaCos2_fix > 3294206 ) {TetaCos2_fix -= 6588413;}

	if( TetaCos2_fix < 0)
	{
		integCos2_fix = 1304*(TetaCos2_fix>>10)+(415*(TetaCos2_fix>>10)>>10)*(TetaCos2_fix>>10); // 20 bit
		if (integCos2_fix <0) {integCos2_fix = 261*(((integCos2_fix>>10)*(-integCos2_fix>>10)-integCos2_fix)>>10)+integCos2_fix;}
		else {integCos2_fix = 261*(((integCos2_fix>>10)*(integCos2_fix>>10)-integCos2_fix)>>10)+integCos2_fix;}
	}
	else
	{
		integCos2_fix = 1304*(TetaCos2_fix>>10)-(415*(TetaCos2_fix>>10)>>10)*(TetaCos2_fix>>10); // 20 bit
		if (integCos2_fix <0) {integCos2_fix = 261*(((integCos2_fix>>10)*(-integCos2_fix>>10)-integCos2_fix)>>10)+integCos2_fix;}
		else {integCos2_fix = 261*(((integCos2_fix>>10)*(integCos2_fix>>10)-integCos2_fix)>>10)+integCos2_fix;}
	}
	// Trigonomethric Approximation END Here

	cosTeta2_fix = integCos1_fix>>10;//20-10

	return (cosTeta2_fix); //10
}

int trigonometri_Cos3 (int32_t Teta)
{
	if (Teta > 3294206 ) {Teta -= 6588413;} // 20 bit
	else if (Teta < -3294206) {Teta += 6588413;} // 20 bit

	//compute cosine
	TetaCos3_fix = Teta + 1647100;	// 20
	if (TetaCos3_fix > 3294206 ) {TetaCos3_fix -= 6588413;}

	if( TetaCos3_fix < 0)
	{
		integCos3_fix = 1304*(TetaCos3_fix>>10)+(415*(TetaCos3_fix>>10)>>10)*(TetaCos3_fix>>10); // 20 bit
		if (integCos3_fix <0) {integCos3_fix = 261*(((integCos3_fix>>10)*(-integCos3_fix>>10)-integCos3_fix)>>10)+integCos3_fix;}
		else {integCos3_fix = 261*(((integCos3_fix>>10)*(integCos3_fix>>10)-integCos3_fix)>>10)+integCos3_fix;}
	}
	else
	{
		integCos3_fix = 1304*(TetaCos3_fix>>10)-(415*(TetaCos3_fix>>10)>>10)*(TetaCos3_fix>>10); // 20 bit
		if (integCos3_fix <0) {integCos3_fix = 261*(((integCos3_fix>>10)*(-integCos3_fix>>10)-integCos3_fix)>>10)+integCos3_fix;}
		else {integCos3_fix = 261*(((integCos3_fix>>10)*(integCos3_fix>>10)-integCos3_fix)>>10)+integCos3_fix;}
	}
	// Trigonomethric Approximation END Here

	cosTeta3_fix = integCos3_fix>>10;//20-10

	return (cosTeta3_fix); //10
}

int trigonometri_Sin1 (int32_t Teta)
{
	if (Teta > 3294206 ) {Teta -= 6588413;} // 20 bit
	else if (Teta < -3294206) {Teta += 6588413;} // 20 bit

	TetaSine1_fix = Teta;	// 20
	//compute sine
	if( TetaSine1_fix < 0)
	{
		integSine1_fix = 1304*(TetaSine1_fix>>10)+(415*(TetaSine1_fix>>10)>>10)*(TetaSine1_fix>>10); // 20 bit
		if (integSine1_fix <0) {integSine1_fix = 261*(((integSine1_fix>>10)*(-integSine1_fix>>10)-integSine1_fix)>>10)+integSine1_fix;}
		else {integSine1_fix = 261*(((integSine1_fix>>10)*(integSine1_fix>>10)-integSine1_fix)>>10)+integSine1_fix;}
	}
	else
	{
		integSine1_fix = 1304*(TetaSine1_fix>>10)-(415*(TetaSine1_fix>>10)>>10)*(TetaSine1_fix>>10); // 20 bit
		if (integSine1_fix <0) {integSine1_fix = 261*(((integSine1_fix>>10)*(-integSine1_fix>>10)-integSine1_fix)>>10)+integSine1_fix;}
		else {integSine1_fix = 261*(((integSine1_fix>>10)*(integSine1_fix>>10)-integSine1_fix)>>10)+integSine1_fix;}
	}

	sinTeta1_fix = integSine1_fix>>10; //20-10

	return (sinTeta1_fix);
}

int trigonometri_Sin2 (int32_t Teta)
{
	if (Teta > 3294206 ) {Teta -= 6588413;} // 20 bit
	else if (Teta < -3294206) {Teta += 6588413;} // 20 bit

	TetaSine2_fix = Teta;	// 20
	//compute sine
	if( TetaSine2_fix < 0)
	{
		integSine2_fix = 1304*(TetaSine2_fix>>10)+(415*(TetaSine2_fix>>10)>>10)*(TetaSine2_fix>>10); // 20 bit
		if (integSine2_fix <0) {integSine2_fix = 261*(((integSine2_fix>>10)*(-integSine2_fix>>10)-integSine2_fix)>>10)+integSine2_fix;}
		else {integSine2_fix = 261*(((integSine2_fix>>10)*(integSine2_fix>>10)-integSine2_fix)>>10)+integSine2_fix;}
	}
	else
	{
		integSine2_fix = 1304*(TetaSine2_fix>>10)-(415*(TetaSine2_fix>>10)>>10)*(TetaSine2_fix>>10); // 20 bit
		if (integSine2_fix <0) {integSine2_fix = 261*(((integSine2_fix>>10)*(-integSine2_fix>>10)-integSine2_fix)>>10)+integSine2_fix;}
		else {integSine2_fix = 261*(((integSine2_fix>>10)*(integSine2_fix>>10)-integSine2_fix)>>10)+integSine2_fix;}
	}

	sinTeta2_fix = integSine2_fix>>10; //20-10

	return (sinTeta2_fix);
}

int trigonometri_Sin3 (int32_t Teta)
{
	if (Teta > 3294206 ) {Teta -= 6588413;} // 20 bit
	else if (Teta < -3294206) {Teta += 6588413;} // 20 bit

	TetaSine3_fix = Teta;	// 20
	//compute sine
	if( TetaSine3_fix < 0)
	{
		integSine3_fix = 1304*(TetaSine3_fix>>10)+(415*(TetaSine3_fix>>10)>>10)*(TetaSine3_fix>>10); // 20 bit
		if (integSine3_fix <0) {integSine3_fix = 261*(((integSine3_fix>>10)*(-integSine3_fix>>10)-integSine3_fix)>>10)+integSine3_fix;}
		else {integSine3_fix = 261*(((integSine3_fix>>10)*(integSine3_fix>>10)-integSine3_fix)>>10)+integSine3_fix;}
	}
	else
	{
		integSine3_fix = 1304*(TetaSine3_fix>>10)-(415*(TetaSine3_fix>>10)>>10)*(TetaSine3_fix>>10); // 20 bit
		if (integSine3_fix <0) {integSine3_fix = 261*(((integSine3_fix>>10)*(-integSine3_fix>>10)-integSine3_fix)>>10)+integSine3_fix;}
		else {integSine3_fix = 261*(((integSine3_fix>>10)*(integSine3_fix>>10)-integSine3_fix)>>10)+integSine3_fix;}
	}

	sinTeta3_fix = integSine3_fix>>10; //20-10

	return (sinTeta3_fix);
}
*/
