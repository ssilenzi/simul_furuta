/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: physics.h
 *
 * Code generated for Simulink model 'fast'.
 *
 * Model version                  : 1.243
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Tue Dec 31 19:37:27 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Debugging
 *    3. Traceability
 * Validation result: All passed
 */

#ifndef RTW_HEADER_physics_h_
#define RTW_HEADER_physics_h_
#include <string.h>
#include <math.h>
#ifndef fast_COMMON_INCLUDES_
# define fast_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* fast_COMMON_INCLUDES_ */

// 		SCRITTO DA PEPO 	//
#include "condiviso.h"
// 	FINE SCRITTO DA PEPO 	//


extern void physics_Init(void);
extern void physics(uint16_T rtu_CCR, real32_T rtu_dist, const real32_T
                    rtu_noise[2], uint16_T rtyy_CNT_alphaCNT_theta[2]);

#endif                                 /* RTW_HEADER_physics_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
