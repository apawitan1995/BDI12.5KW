
#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <DAVE3.h>
#include "common/global.h"
//#include "algorithm/droop.h"
#include "peripheral/ADC_app.h"
#include "peripheral/PWM_app.h"

#include "peripheral/ISR_app.h"

#define VODC_REFF_BOOST 	700		// above inverter_active_voltage, inv_act > AC_peak
#define VODC_REFF_BUCK 		760 	// VODC_REFF_BOOST+60
#define VODC_REFF_BOOST_FIX 716800	// 700<<10
#define VODC_REFF_BUCK_FIX 	450560 //778240	// 760<<10

#define VODC_REFF 			690 	// VODC_REFF CONSTANT VOLTAGE
#define VODC_REFF_FIX 		706560	// 690<<10

#define CLOSED_LOOP_ACTIVE_VOLTAGE 	360 // this value has to lower than inverter_active_voltage
#define BUCK_ACTIVE_VOLTAGE 		430 //740 // VODC_REFF_BOOST+40
#define BOOST_ACTIVE_VOLTAGE 		410 //720	// VODC_REFF_BOOST+20
#define OPEN_LOOP_ACTIVE_VOLTAGE 	360 // it could be nominal power supply value
#define	PRECHARGING_VOLTAGE_LIMIT 	330

#define CLOSED_LOOP_ACTIVE_ADC	(uint32_t)((float)CLOSED_LOOP_ACTIVE_VOLTAGE*DCPT2_GRAD+DCPT2_OFFSET)	//678
#define BUCK_ACTIVE_ADC			(uint32_t)((float)BUCK_ACTIVE_VOLTAGE*DCPT2_GRAD+DCPT2_OFFSET)			//901
#define BOOST_ACTIVE_ADC 		(uint32_t)((float)BOOST_ACTIVE_VOLTAGE*DCPT2_GRAD+DCPT2_OFFSET)			//790
#define OPEN_LOOP_ACTIVE_ADC	(uint32_t)((float)OPEN_LOOP_ACTIVE_VOLTAGE*DCPT2_GRAD+DCPT2_OFFSET)		//566
#define	PRECHARGING_ADC_LIMIT 	(uint32_t)((float)PRECHARGING_VOLTAGE_LIMIT*DCPT1_GRAD+DCPT1_OFFSET)	//

#define INTV_MAX_FIX 524288000		// 500<<20
#define INTV_MIN_FIX -524288000				// 0<<20

#define IL_MAX_FIX 104857600			// 100<<20
#define IL_MIN_FIX -104857600		// -50<<20

#define LIM_PWM_MAX_FIX 943718		// 0,9<<20
#define LIM_PWM_MIN_FIX 0			// 0<<20

extern volatile int inverter_enable;
extern volatile int pwm_peak_reff;
extern volatile int pwm_peak_feedback;
extern volatile int mode_inverter;
extern volatile int Vreff_inv;
extern volatile int Vreff_inv_feedback;
extern volatile int ACPT1_AIN_Result_xmc2;
extern volatile int ACPT2_AIN_Result_xmc2;
extern volatile int ACPT3_AIN_Result_xmc2;
extern volatile int Vd_ref_fix, Vq_ref_fix, delta_vd_fix, delta_vq_fix;
extern volatile int pembagi;
extern volatile int pembagi_feedback;
extern volatile int Vinv_d_fix, Vinv_q_fix, integrator_d_fix, integrator_q_fix, PWM_d_fix, PWM_q_fix, Iinv_d_fix, Iinv_q_fix, Id_fix, Iq_fix;;
extern volatile int Id_ref_fix, Iq_ref_fix;
extern volatile int Id_fix, Iq_fix, PWM_A_fix, PWM_B_fix, PWM_C_fix;
extern volatile int KI_V;
extern volatile int KP_V;
extern volatile int KI_I;
extern volatile int KP_I;
//xtern volatile int KP_I;
extern volatile int KP_V_feedback, KI_V_feedback, KP_I_feedback;
extern volatile int p_set;
extern volatile int q_set;
extern volatile int m1, c1, m2, c2;
extern volatile int m1_hmi, c1_hmi, m2_hmi, c2_hmi;
extern volatile int m1_feedback, c1_feedback, m2_feedback, c2_feedback;
extern volatile int p_set_hmi, q_set_hmi;
extern volatile int p_set_feedback, q_set_feedback;
extern volatile float power_calculation;
extern volatile float yf_p, Ptot, yf_q, Qtot;
extern volatile int yf_p_fix, Ptot_fix;
extern volatile int Vgrid_a_fix, Vgrid_b_fix, Vgrid_c_fix, Igrid_a_fix, Igrid_b_fix, Igrid_c_fix;
extern volatile int Vinv_a_fix, Vinv_b_fix, Vinv_c_fix, Ia_fix, Ib_fix, Ic_fix;
extern volatile int va_ref_fix, vb_ref_fix, vc_ref_fix;
extern volatile float Vinv_q, Iinv_q;
extern volatile int teta_manual_fix;
extern volatile int VPLL_fix;
extern volatile int DCPT2_U2_fix;
extern volatile int32_t xf_PLL[2], yf_PLL[2], xv_PLL[2], yv_PLL[2];
extern volatile int32_t KP_V_add, KI_V_add, KP_I_add;
extern volatile int32_t KP_V_add_feedback, KI_V_add_feedback, KP_I_add_feedback;
extern volatile int32_t wPLL_fix;
extern volatile int32_t Q_Filt_1, Q_Filt_2;


//extern variable
extern volatile uint32_t KI;
extern volatile uint32_t KP;
extern volatile uint32_t KIIL;
extern volatile uint32_t KPIL;

extern volatile int32_t mode;
extern volatile int32_t il_reff_fix;
extern volatile int32_t pwm1_fix,pwm2_fix,pwm3_fix;
extern volatile int32_t pwm_set;
extern volatile int32_t integ_err_vo_dc_fix;
extern volatile int32_t integ_err_il1_boost_fix, integ_err_il2_boost_fix, integ_err_il3_boost_fix;
extern volatile int32_t integ_err_il1_buck_fix, integ_err_il2_buck_fix, integ_err_il3_buck_fix;
extern volatile int32_t vo_dc_fix, i_batt_fix;
extern volatile uint32_t enable_CV;
extern volatile uint32_t enable_voltage_update;
extern volatile int32_t vodc_reff_boost_fix;
extern volatile int32_t boost_active;
extern volatile int32_t buck_active;
extern volatile int32_t buck_count;
extern volatile int32_t err_vo_dc_count, err_vo_dc_max, err_vo_dc_min;
extern volatile int32_t err_vo_dc_fix;

//buat tes closed loop
extern volatile int32_t current_reference_test;
extern volatile int32_t voltage_reference_test;

void ClosedLoopVoltageController(void);
void CurrentLoopBoost1Fixed(void);
void CurrentLoopBoost2Fixed(void);
void CurrentLoopBoost3Fixed(void);
void CurrentLoopBuck1Fixed(void);
void CurrentLoopBuck2Fixed(void);
void CurrentLoopBuck3Fixed(void);
void BoostConstantVoltageControlFixed(void);
void BuckConstantVoltageControlFixed(void);

#endif /* CONVERTER_H_ */
