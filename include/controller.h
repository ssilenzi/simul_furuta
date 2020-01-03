/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: controller.h
 *
 * Code generated for Simulink model 'slow'.
 *
 * Model version                  : 1.257
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Tue Dec 31 19:40:45 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Debugging
 *    3. Traceability
 * Validation result: All passed
 */

#ifndef RTW_HEADER_controller_h_
#define RTW_HEADER_controller_h_
#include <string.h>
#include <math.h>
#ifndef slow_COMMON_INCLUDES_
# define slow_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#endif                                 /* slow_COMMON_INCLUDES_ */

//#include "types.h"
#include "rt_zcfcn.h"

// 		SCRITTO DA PEPO 	//
#include "condiviso.h"
// 	FINE SCRITTO DA PEPO 	//

/* by pepo
// Block signals and states (default storage) for system '<S5>/ref_gen' 
typedef struct {
  real_T DiscreteTransferFcn_states;   // '<S8>/Discrete Transfer Fcn' 
  uint8_T DiscreteTransferFcn_icLoad; // '<S8>/Discrete Transfer Fcn' 
} DW_ref_gen_slow_T;


// Zero-crossing (trigger) state for system '<S5>/ref_gen'
typedef struct {
  ZCSigState DiscreteTransferFcn_Reset_ZCE;// '<S8>/Discrete Transfer Fcn'
} ZCE_ref_gen_slow_T;
*/

extern void slow_ref_gen_Init(DW_ref_gen_slow_T *localDW);
extern void slow_ref_gen(real_T rtu_alpha_ref, real_T rtu_alpha, real_T
  rtu_reset, real_T *rty_out, DW_ref_gen_slow_T *localDW, ZCE_ref_gen_slow_T
  *localZCE);
extern void controller_Init(void);
extern void controller(real32_T rtu_alpha_ref, uint8_T rtu_swingup, uint16_T
  rtu_CNT_alpha, uint16_T rtu_CNT_theta, uint8_T rtu_delay, real32_T
  *rty_theta_ref, real32_T rty_alpha[2], real32_T *rty_voltage, uint16_T
  *rty_CCR);

#endif                                 /* RTW_HEADER_controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
