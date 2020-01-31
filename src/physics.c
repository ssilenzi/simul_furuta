/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: physics.c
 *
 * Code generated for Simulink model 'fast'.
 *
 * Model version                  : 1.256
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Fri Jan 31 08:54:33 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Debugging
 *    3. Traceability
 * Validation result: All passed
 */

#include "physics.h"

/* System initialize for atomic system: '<Root>/Physics' */
void physics_Init(void)
{
  /* InitializeConditions for Delay: '<S3>/Delay' */
  fast_DW.Delay_DSTATE_j = 3.14159274F;

  /* InitializeConditions for Delay: '<S6>/Delay' */
  fast_DW.Delay_DSTATE[0] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S6>/Discrete-Time Integrator' */
  fast_DW.DiscreteTimeIntegrator_DSTATE[0] = 0.0F;

  /* InitializeConditions for Delay: '<S6>/Delay' */
  fast_DW.Delay_DSTATE[1] = 3.14159274F;

  /* InitializeConditions for DiscreteIntegrator: '<S6>/Discrete-Time Integrator' */
  fast_DW.DiscreteTimeIntegrator_DSTATE[1] = 3.14159274F;

  /* InitializeConditions for Delay: '<S6>/Delay' */
  fast_DW.Delay_DSTATE[2] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S6>/Discrete-Time Integrator' */
  fast_DW.DiscreteTimeIntegrator_DSTATE[2] = 0.0F;

  /* InitializeConditions for Delay: '<S6>/Delay' */
  fast_DW.Delay_DSTATE[3] = 0.0F;

  /* InitializeConditions for DiscreteIntegrator: '<S6>/Discrete-Time Integrator' */
  fast_DW.DiscreteTimeIntegrator_DSTATE[3] = 0.0F;
}

/* Output and update for atomic system: '<Root>/Physics' */
void physics(uint16_T rtu_CCR, real32_T rtu_dist, const real32_T rtu_noise[2],
             uint16_T rtyy_CNT_alphaCNT_theta[2])
{
  boolean_T rEQ0;
  real32_T rtb_current;
  real32_T rtb_Sum1;
  real32_T LR_circuit_tmp;
  real32_T rtb_TmpSignalConversionAtSFun_0;
  real32_T rtb_TmpSignalConversionAtSFun_1;
  real32_T rtb_x_d_idx_2;
  real32_T x_idx_1;
  real32_T x_idx_2;
  real32_T x_idx_3;
  real32_T rtb_x_d_idx_2_tmp;
  real32_T rtb_x_d_idx_2_tmp_0;
  real32_T rtb_x_d_idx_2_tmp_1;

  /* DiscreteTransferFcn: '<S2>/LR_circuit' incorporates:
   *  DataTypeConversion: '<S5>/Cast1'
   *  Delay: '<S2>/Delay'
   *  Fcn: '<S5>/Fcn1'
   *  Gain: '<S2>/Gain2'
   *  Sum: '<S2>/Sum1'
   */
  /* MATLAB Function 'Physics/Disturbance_generator/dist_gen': '<S7>:1' */
  /* '<S7>:1:3' tau_1 = F*Larm; */
  /* '<S7>:1:4' tau_2 = F*cos(theta)*Lp; */
  LR_circuit_tmp = ((2.0F * (real32_T)rtu_CCR / 5250.0F - 1.0F) * 6.0F - 0.5376F
                    * fast_DW.Delay_DSTATE_c) - 0.756756783F *
    fast_DW.LR_circuit_states;

  /* SignalConversion generated from: '<S9>/ SFunction ' incorporates:
   *  Delay: '<S3>/Delay'
   *  DiscreteTransferFcn: '<S2>/LR_circuit'
   *  Gain: '<S2>/Gain3'
   *  MATLAB Function: '<S3>/dist_gen'
   *  MATLAB Function: '<S6>/f_mecc'
   *  Sum: '<S6>/Sum2'
   */
  rtb_TmpSignalConversionAtSFun_0 = (0.337837845F * LR_circuit_tmp +
    0.337837845F * fast_DW.LR_circuit_states) * 0.48384F + rtu_dist * 0.216F;
  rtb_TmpSignalConversionAtSFun_1 = rtu_dist * cosf(fast_DW.Delay_DSTATE_j) *
    0.337F;

  /* MATLAB Function: '<S6>/f_mecc' incorporates:
   *  Delay: '<S6>/Delay'
   */
  /*     This function was generated by the Symbolic Math Toolbox version 8.4. */
  /*     09-Dec-2019 19:45:31 */
  /* MATLAB Function 'Physics/Pendulum/f_mecc': '<S9>:1' */
  /* '<S9>:1:7' al_d = x(3); */
  /* '<S9>:1:8' tau1 = tau(1); */
  /* '<S9>:1:9' tau2 = tau(2); */
  /* '<S9>:1:10' th = x(2); */
  /* '<S9>:1:11' th_d = x(4); */
  /* '<S9>:1:12' x_d = [al_d;th_d;((Jp.*tau1.*-2.0+Jp.*al_d.*bma.*2.0+Jp.^2.*al_d.*th_d.*sin(th.*2.0).*2.0+Larm.*lp.*mp.*tau2.*cos(th).*2.0-Larm.*bp.*lp.*mp.*th_d.*cos(th).*2.0+Larm.*g.*lp.^2.*mp.^2.*cos(th).*sin(th).*2.0-Jp.*Larm.*lp.*mp.*th_d.^2.*sin(th).*2.0+Jp.*Larm.*al_d.^2.*lp.*mp.*sin(th.*2.0).*cos(th)).*(-1.0./2.0))./(Jp.^2.*sin(th).^2+J0.*Jp-Larm.^2.*lp.^2.*mp.^2.*cos(th).^2);(J0.*tau2.*2.0+Jp.*tau2.*sin(th).^2.*2.0-J0.*bp.*th_d.*2.0+Jp.^2.*al_d.^2.*sin(th.*2.0).*sin(th).^2-Jp.*bp.*th_d.*sin(th).^2.*2.0+J0.*Jp.*al_d.^2.*sin(th.*2.0)+Jp.*g.*lp.*mp.*sin(th).^3.*2.0-Larm.*lp.*mp.*tau1.*cos(th).*2.0+J0.*g.*lp.*mp.*sin(th).*2.0+Larm.*al_d.*bma.*lp.*mp.*cos(th).*2.0-Larm.^2.*lp.^2.*mp.^2.*th_d.^2.*cos(th).*sin(th).*2.0+Jp.*Larm.*al_d.*lp.*mp.*th_d.*sin(th.*2.0).*cos(th).*2.0)./(Jp.^2.*sin(th).^2.*2.0+J0.*Jp.*2.0-Larm.^2.*lp.^2.*mp.^2.*cos(th).^2.*2.0)]; */
  rtb_current = sinf(fast_DW.Delay_DSTATE[1]);
  rtb_Sum1 = cosf(fast_DW.Delay_DSTATE[1]);
  x_idx_1 = sinf(fast_DW.Delay_DSTATE[1] * 2.0F);
  x_idx_2 = rtb_current * rtb_current;
  x_idx_3 = fast_DW.Delay_DSTATE[2] * fast_DW.Delay_DSTATE[2];
  rtb_x_d_idx_2_tmp = fast_DW.Delay_DSTATE[3] * fast_DW.Delay_DSTATE[3];
  rtb_x_d_idx_2_tmp_0 = x_idx_2 * 1.84098662E-5F;
  rtb_x_d_idx_2_tmp_1 = rtb_Sum1 * rtb_Sum1 * 1.83131979E-5F;
  rtb_x_d_idx_2 = (((((((0.00429067202F * fast_DW.Delay_DSTATE[2] * 0.0174F *
    2.0F + 0.00429067202F * rtb_TmpSignalConversionAtSFun_0 * -2.0F) +
                        1.84098662E-5F * fast_DW.Delay_DSTATE[2] *
                        fast_DW.Delay_DSTATE[3] * x_idx_1 * 2.0F) +
                       0.00427939277F * rtb_TmpSignalConversionAtSFun_1 *
                       rtb_Sum1 * 2.0F) - 1.02705417E-5F * fast_DW.Delay_DSTATE
                      [3] * rtb_Sum1 * 2.0F) + 0.000831724377F * rtb_Sum1 *
                     rtb_current * 2.0F) - rtb_x_d_idx_2_tmp * 1.83614684E-5F *
                    rtb_current * 2.0F) + x_idx_3 * 0.000926785171F * 0.156F *
                   0.127F * x_idx_1 * rtb_Sum1) * -0.5F / ((rtb_x_d_idx_2_tmp_0
    + 4.49253384E-5F) - rtb_x_d_idx_2_tmp_1);
  rtb_TmpSignalConversionAtSFun_0 = (((((((((((0.00429067202F *
    rtb_TmpSignalConversionAtSFun_1 * x_idx_2 * 2.0F + 0.0104704667F *
    rtb_TmpSignalConversionAtSFun_1 * 2.0F) - 2.51291222E-5F *
    fast_DW.Delay_DSTATE[3] * 2.0F) + x_idx_3 * 1.84098662E-5F * x_idx_1 *
    x_idx_2) - 1.02976137E-5F * fast_DW.Delay_DSTATE[3] * x_idx_2 * 2.0F) +
    x_idx_3 * 4.49253384E-5F * x_idx_1) + 0.000833916711F * powf(rtb_current,
    3.0F) * 2.0F) - 0.00427939277F * rtb_TmpSignalConversionAtSFun_0 * rtb_Sum1 *
    2.0F) + 0.00203499524F * rtb_current * 2.0F) + 0.216F *
    fast_DW.Delay_DSTATE[2] * 0.0174F * 0.156F * 0.127F * rtb_Sum1 * 2.0F) -
    rtb_x_d_idx_2_tmp * 1.83131979E-5F * rtb_Sum1 * rtb_current * 2.0F) +
    0.000926785171F * fast_DW.Delay_DSTATE[2] * 0.156F * 0.127F *
    fast_DW.Delay_DSTATE[3] * x_idx_1 * rtb_Sum1 * 2.0F) / ((rtb_x_d_idx_2_tmp_0
    * 2.0F + 8.98506769E-5F) - rtb_x_d_idx_2_tmp_1 * 2.0F);

  /* DiscreteIntegrator: '<S6>/Discrete-Time Integrator' incorporates:
   *  Delay: '<S6>/Delay'
   *  MATLAB Function: '<S6>/f_mecc'
   */
  rtb_TmpSignalConversionAtSFun_1 = 0.0005F * fast_DW.Delay_DSTATE[2] +
    fast_DW.DiscreteTimeIntegrator_DSTATE[0];
  x_idx_1 = 0.0005F * fast_DW.Delay_DSTATE[3] +
    fast_DW.DiscreteTimeIntegrator_DSTATE[1];
  x_idx_2 = 0.0005F * rtb_x_d_idx_2 + fast_DW.DiscreteTimeIntegrator_DSTATE[2];
  x_idx_3 = 0.0005F * rtb_TmpSignalConversionAtSFun_0 +
    fast_DW.DiscreteTimeIntegrator_DSTATE[3];

  /* Sum: '<S1>/Sum3' */
  /* MATLAB Function 'Physics/Encoder/rad_to_CNT': '<S8>:1' */
  /* '<S8>:1:3' CNT = floor(mod(rad,single(2*pi))/single(2*pi)*encoder_res); */
  rtb_x_d_idx_2_tmp = rtu_noise[0] + rtb_TmpSignalConversionAtSFun_1;

  /* MATLAB Function: '<S4>/rad_to_CNT' */
  if (rtb_x_d_idx_2_tmp == 0.0F) {
    rtb_current = 0.0F;
  } else {
    rtb_current = fmodf(rtb_x_d_idx_2_tmp, 6.28318548F);
    rEQ0 = (rtb_current == 0.0F);
    if (!rEQ0) {
      rtb_Sum1 = fabsf(rtb_x_d_idx_2_tmp / 6.28318548F);
      rEQ0 = (fabsf(rtb_Sum1 - floorf(rtb_Sum1 + 0.5F)) <= 1.1920929E-7F *
              rtb_Sum1);
    }

    if (rEQ0) {
      rtb_current = 0.0F;
    } else {
      if (rtb_x_d_idx_2_tmp < 0.0F) {
        rtb_current += 6.28318548F;
      }
    }
  }

  /* DataTypeConversion: '<S4>/Cast2' incorporates:
   *  MATLAB Function: '<S4>/rad_to_CNT'
   */
  rtyy_CNT_alphaCNT_theta[0] = (uint16_T)floorf(rtb_current / 6.28318548F *
    4096.0F);

  /* Sum: '<S1>/Sum3' */
  rtb_x_d_idx_2_tmp = rtu_noise[1] + x_idx_1;

  /* MATLAB Function: '<S4>/rad_to_CNT' */
  if (rtb_x_d_idx_2_tmp == 0.0F) {
    rtb_current = 0.0F;
  } else {
    rtb_current = fmodf(rtb_x_d_idx_2_tmp, 6.28318548F);
    rEQ0 = (rtb_current == 0.0F);
    if (!rEQ0) {
      rtb_Sum1 = fabsf(rtb_x_d_idx_2_tmp / 6.28318548F);
      rEQ0 = (fabsf(rtb_Sum1 - floorf(rtb_Sum1 + 0.5F)) <= 1.1920929E-7F *
              rtb_Sum1);
    }

    if (rEQ0) {
      rtb_current = 0.0F;
    } else {
      if (rtb_x_d_idx_2_tmp < 0.0F) {
        rtb_current += 6.28318548F;
      }
    }
  }

  /* DataTypeConversion: '<S4>/Cast2' incorporates:
   *  MATLAB Function: '<S4>/rad_to_CNT'
   */
  rtyy_CNT_alphaCNT_theta[1] = (uint16_T)floorf(rtb_current / 6.28318548F *
    4096.0F);

  /* Update for Delay: '<S3>/Delay' */
  fast_DW.Delay_DSTATE_j = x_idx_1;

  /* Update for Delay: '<S2>/Delay' */
  fast_DW.Delay_DSTATE_c = x_idx_2;

  /* Update for DiscreteTransferFcn: '<S2>/LR_circuit' */
  fast_DW.LR_circuit_states = LR_circuit_tmp;

  /* Update for Delay: '<S6>/Delay' */
  fast_DW.Delay_DSTATE[0] = rtb_TmpSignalConversionAtSFun_1;

  /* Update for DiscreteIntegrator: '<S6>/Discrete-Time Integrator' incorporates:
   *  Delay: '<S6>/Delay'
   *  MATLAB Function: '<S6>/f_mecc'
   * */
  fast_DW.DiscreteTimeIntegrator_DSTATE[0] = 0.0005F * fast_DW.Delay_DSTATE[2] +
    rtb_TmpSignalConversionAtSFun_1;

  /* Update for Delay: '<S6>/Delay' */
  fast_DW.Delay_DSTATE[1] = x_idx_1;

  /* Update for DiscreteIntegrator: '<S6>/Discrete-Time Integrator' incorporates:
   *  Delay: '<S6>/Delay'
   *  MATLAB Function: '<S6>/f_mecc'
   * */
  fast_DW.DiscreteTimeIntegrator_DSTATE[1] = 0.0005F * fast_DW.Delay_DSTATE[3] +
    x_idx_1;

  /* Update for Delay: '<S6>/Delay' */
  fast_DW.Delay_DSTATE[2] = x_idx_2;

  /* Update for DiscreteIntegrator: '<S6>/Discrete-Time Integrator' incorporates:
   *  Delay: '<S6>/Delay'
   */
  fast_DW.DiscreteTimeIntegrator_DSTATE[2] = 0.0005F * rtb_x_d_idx_2 + x_idx_2;

  /* Update for Delay: '<S6>/Delay' */
  fast_DW.Delay_DSTATE[3] = x_idx_3;

  /* Update for DiscreteIntegrator: '<S6>/Discrete-Time Integrator' incorporates:
   *  Delay: '<S6>/Delay'
   */
  fast_DW.DiscreteTimeIntegrator_DSTATE[3] = 0.0005F *
    rtb_TmpSignalConversionAtSFun_0 + x_idx_3;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
