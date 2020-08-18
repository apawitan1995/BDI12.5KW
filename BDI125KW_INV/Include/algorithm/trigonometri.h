/*
 * trigonometri.h
 *
 *  Created on: Mar 30, 2017
 *      Author: Bima Nugraha S
 */

#ifndef TRIGONOMETRI_H_
#define TRIGONOMETRI_H_

#include <DAVE3.h>
#include <arm_math.h>

extern volatile int32_t Theta_fix4, teta_fix2;

//-----------------------------PLL-------------------------------
extern volatile int32_t TetaSine_PLL_fix,TetaCos_PLL_fix;
extern volatile int32_t integSine_PLL_fix,integCos_PLL_fix;
extern volatile int32_t sinTeta_PLL_fix,cosTeta_PLL_fix;
extern volatile int32_t cosinus_pll, sinus_pll, cosmin_pll, cosplus_pll, sinmin_pll, sinplus_pll;

int trigonometri_PLL_Sin (int32_t Teta_PLL);
int trigonometri_PLL_Cos (int32_t Teta_PLL);

//---------------------------Trigonometri----------------------------------
extern int32_t TetaSine_fix,TetaCos_fix;
extern int32_t integSine_fix,integCos_fix;
extern int32_t sinTeta_fix,cosTeta_fix;

int trigonometri_Cos (int32_t Teta);
int trigonometri_Sin (int32_t Teta);

/*
//---------------------------Trigonometri----------------------------------
extern volatile int32_t TetaSine1_fix, TetaSine2_fix, TetaSine3_fix, TetaCos1_fix, TetaCos2_fix, TetaCos3_fix;
extern volatile int32_t integSine1_fix, integSine2_fix, integSine3_fix, integCos1_fix, integCos2_fix, integCos3_fix;
extern volatile int32_t sinTeta1_fix, sinTeta2_fix, sinTeta3_fix, cosTeta1_fix, cosTeta2_fix, cosTeta3_fix;

int trigonometri_Cos1 (int32_t Teta);
int trigonometri_Cos2 (int32_t Teta);
int trigonometri_Cos3 (int32_t Teta);
int trigonometri_Sin1 (int32_t Teta);
int trigonometri_Sin2 (int32_t Teta);
int trigonometri_Sin3 (int32_t Teta);
*/
#endif /* TRIGONOMETRI_H_ */
