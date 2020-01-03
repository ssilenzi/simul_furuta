/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: disturbance_and_noise.c
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

#include "disturbance_and_noise.h"

/* Include model header file for global data */
//#include "matlab.h"
#include "rt_urand_Upu32_Yd_f_pw.h"

/* Named constants for Chart: '<S10>/Disturbance_generator' */
#define slow_IN_Off                    ((uint8_T)1U)
#define slow_IN_On                     ((uint8_T)2U)
#define slow_IN_Reset                  ((uint8_T)3U)


// 		SCRITTO DA PEPO 	//
extern DW_slow_T slow_DW;
extern par_dn_t par_dn;
// 	FINE SCRITTO DA PEPO 	//


/* System initialize for atomic system: '<Root>/Disturbance_and_noise' */
void disturbance_and_noise_Init(real32_T *rty_dist)
{
  /* InitializeConditions for UniformRandomNumber: '<S12>/Noise_generator' */
  slow_DW.RandSeed = 153485312U;
  slow_DW.Noise_generator_NextOutput = rt_urand_Upu32_Yd_f_pw(&slow_DW.RandSeed)
    * 2.0 + -1.0;

  /* InitializeConditions for UniformRandomNumber: '<S12>/Noise_generator1' */
  slow_DW.RandSeed_n = 102105088U;
  slow_DW.Noise_generator1_NextOutput = rt_urand_Upu32_Yd_f_pw
    (&slow_DW.RandSeed_n) * 2.0 + -1.0;

  /* SystemInitialize for Chart: '<S10>/Disturbance_generator' */
  *rty_dist = 0.0F;
}

/* Output and update for atomic system: '<Root>/Disturbance_and_noise' */
void disturbance_and_noise(uint8_T rtu_kick, real32_T *rty_dist, real32_T
  rty_noise[2])
{
  /* DataTypeConversion: '<S12>/Cast' incorporates:
   *  Gain: '<S12>/Gain'
   *  Gain: '<S12>/Gain1'
   *  UniformRandomNumber: '<S12>/Noise_generator'
   *  UniformRandomNumber: '<S12>/Noise_generator1'
   */
  rty_noise[0] = (real32_T)(0.0015339808305725455 *
    slow_DW.Noise_generator_NextOutput * par_dn.noise_amp);
  rty_noise[1] = (real32_T)(0.0015339808305725455 *
    slow_DW.Noise_generator1_NextOutput * par_dn.noise_amp);

  /* Chart: '<S10>/Disturbance_generator' */
  /* Gateway: Disturbance_and_noise/Disturbance_and_noise/Disturbance_generator */
  if (slow_DW.temporalCounter_i1 < 15U) {
    slow_DW.temporalCounter_i1++;
  }

  /* During: Disturbance_and_noise/Disturbance_and_noise/Disturbance_generator */
  if (slow_DW.is_active_c8_slow == 0U) {
    /* Entry: Disturbance_and_noise/Disturbance_and_noise/Disturbance_generator */
    slow_DW.is_active_c8_slow = 1U;

    /* Entry Internal: Disturbance_and_noise/Disturbance_and_noise/Disturbance_generator */
    /* Transition: '<S11>:5' */
    slow_DW.is_c8_slow = slow_IN_Reset;

    /* Entry 'Reset': '<S11>:4' */
    /* '<S11>:4:3' dist = 0; */
    *rty_dist = 0.0F;
  } else {
    switch (slow_DW.is_c8_slow) {
     case slow_IN_Off:
      /* During 'Off': '<S11>:25' */
      /* '<S11>:7:1' sf_internal_predicateOutput = kick == 1; */
      if (rtu_kick == 1) {
        /* Transition: '<S11>:7' */
        slow_DW.is_c8_slow = slow_IN_On;
        slow_DW.temporalCounter_i1 = 0U;

        /* Entry 'On': '<S11>:6' */
        /* '<S11>:6:3' dist = par_dn.dist_amp; */
        *rty_dist = par_dn.dist_amp;
      }
      break;

     case slow_IN_On:
      /* During 'On': '<S11>:6' */
      /* '<S11>:8:1' sf_internal_predicateOutput = after(10,tick); */
      if (slow_DW.temporalCounter_i1 >= 10) {
        /* Transition: '<S11>:8' */
        slow_DW.is_c8_slow = slow_IN_Reset;

        /* Entry 'Reset': '<S11>:4' */
        /* '<S11>:4:3' dist = 0; */
        *rty_dist = 0.0F;
      }
      break;

     default:
      /* During 'Reset': '<S11>:4' */
      /* '<S11>:26:1' sf_internal_predicateOutput = kick == 0; */
      if (rtu_kick == 0) {
        /* Transition: '<S11>:26' */
        slow_DW.is_c8_slow = slow_IN_Off;
      }
      break;
    }
  }

  /* End of Chart: '<S10>/Disturbance_generator' */

  /* Update for UniformRandomNumber: '<S12>/Noise_generator' */
  slow_DW.Noise_generator_NextOutput = rt_urand_Upu32_Yd_f_pw(&slow_DW.RandSeed)
    * 2.0 + -1.0;

  /* Update for UniformRandomNumber: '<S12>/Noise_generator1' */
  slow_DW.Noise_generator1_NextOutput = rt_urand_Upu32_Yd_f_pw
    (&slow_DW.RandSeed_n) * 2.0 + -1.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
