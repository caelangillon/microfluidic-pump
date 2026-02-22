/*
 * PID_controller__data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PID_controller_".
 *
 * Model version              : 1.5
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C source code generated on : Sat Feb 21 18:29:12 2026
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "PID_controller_.h"

/* Block parameters (default storage) */
P_PID_controller__T PID_controller__P = {
  /* Mask Parameter: PIDController_InitialConditionF
   * Referenced by: '<S90>/Filter'
   */
  0.0F,

  /* Mask Parameter: PIDController_InitialConditio_i
   * Referenced by: '<S35>/Filter'
   */
  0.0F,

  /* Mask Parameter: PIDController_InitialConditio_m
   * Referenced by: '<S95>/Integrator'
   */
  0.0F,

  /* Mask Parameter: PIDController_InitialConditio_p
   * Referenced by: '<S40>/Integrator'
   */
  0.0F,

  /* Mask Parameter: PIDController_LowerSaturationLi
   * Referenced by:
   *   '<S102>/Saturation'
   *   '<S87>/DeadZone'
   */
  0.0F,

  /* Mask Parameter: PIDController_LowerSaturation_l
   * Referenced by:
   *   '<S47>/Saturation'
   *   '<S32>/DeadZone'
   */
  0.0F,

  /* Mask Parameter: PIDController_UpperSaturationLi
   * Referenced by:
   *   '<S102>/Saturation'
   *   '<S87>/DeadZone'
   */
  1.0F,

  /* Mask Parameter: PIDController_UpperSaturation_i
   * Referenced by:
   *   '<S47>/Saturation'
   *   '<S32>/DeadZone'
   */
  1.0F,

  /* Expression: 42.255
   * Referenced by: '<Root>/MATLAB System'
   */
  42.255,

  /* Expression: 41500
   * Referenced by: '<Root>/MATLAB System'
   */
  41500.0,

  /* Expression: -1
   * Referenced by: '<Root>/MATLAB System'
   */
  -1.0,

  /* Expression: -1
   * Referenced by: '<Root>/MATLAB System1'
   */
  -1.0,

  /* Computed Parameter: Constant1_Value
   * Referenced by: '<S30>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Constant1_Value_b
   * Referenced by: '<S85>/Constant1'
   */
  0.0F,

  /* Computed Parameter: Saturation1_UpperSat
   * Referenced by: '<Root>/Saturation1'
   */
  0.0F,

  /* Computed Parameter: Saturation1_LowerSat
   * Referenced by: '<Root>/Saturation1'
   */
  0.0F,

  /* Computed Parameter: Gain_Gain
   * Referenced by: '<Root>/Gain'
   */
  -1.0F,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S95>/Integrator'
   */
  0.001F,

  /* Computed Parameter: Filter_gainval
   * Referenced by: '<S90>/Filter'
   */
  0.001F,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S2>/Constant'
   */
  100.0F,

  /* Computed Parameter: Gain2_Gain
   * Referenced by: '<Root>/Gain2'
   */
  0.6F,

  /* Computed Parameter: Constant_Value_f
   * Referenced by: '<Root>/Constant'
   */
  0.4F,

  /* Computed Parameter: Saturation_UpperSat
   * Referenced by: '<Root>/Saturation'
   */
  0.0F,

  /* Computed Parameter: Saturation_LowerSat
   * Referenced by: '<Root>/Saturation'
   */
  0.0F,

  /* Computed Parameter: Integrator_gainval_f
   * Referenced by: '<S40>/Integrator'
   */
  0.001F,

  /* Computed Parameter: Filter_gainval_m
   * Referenced by: '<S35>/Filter'
   */
  0.001F,

  /* Computed Parameter: Constant_Value_g
   * Referenced by: '<S1>/Constant'
   */
  100.0F,

  /* Computed Parameter: Gain1_Gain
   * Referenced by: '<Root>/Gain1'
   */
  0.6F,

  /* Computed Parameter: Clamping_zero_Value
   * Referenced by: '<S30>/Clamping_zero'
   */
  0.0F,

  /* Computed Parameter: Clamping_zero_Value_d
   * Referenced by: '<S85>/Clamping_zero'
   */
  0.0F,

  /* Computed Parameter: Constant_Value_o
   * Referenced by: '<S30>/Constant'
   */
  1,

  /* Computed Parameter: Constant2_Value
   * Referenced by: '<S30>/Constant2'
   */
  -1,

  /* Computed Parameter: Constant3_Value
   * Referenced by: '<S30>/Constant3'
   */
  1,

  /* Computed Parameter: Constant4_Value
   * Referenced by: '<S30>/Constant4'
   */
  -1,

  /* Computed Parameter: Constant_Value_b
   * Referenced by: '<S85>/Constant'
   */
  1,

  /* Computed Parameter: Constant2_Value_e
   * Referenced by: '<S85>/Constant2'
   */
  -1,

  /* Computed Parameter: Constant3_Value_b
   * Referenced by: '<S85>/Constant3'
   */
  1,

  /* Computed Parameter: Constant4_Value_l
   * Referenced by: '<S85>/Constant4'
   */
  -1
};
