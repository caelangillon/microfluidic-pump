/*
 * PID_controller_.c
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
#include "PID_controller__private.h"
#include "rtwtypes.h"
#include <string.h>
#include <stddef.h>
#include "rt_nonfinite.h"
#include <math.h>

/* Block signals (default storage) */
B_PID_controller__T PID_controller__B;

/* Block states (default storage) */
DW_PID_controller__T PID_controller__DW;

/* Real-time model */
static RT_MODEL_PID_controller__T PID_controller__M_;
RT_MODEL_PID_controller__T *const PID_controller__M = &PID_controller__M_;
static void rate_scheduler(void);

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (PID_controller__M->Timing.TaskCounters.TID[2])++;
  if ((PID_controller__M->Timing.TaskCounters.TID[2]) > 9) {/* Sample time: [0.01s, 0.0s] */
    PID_controller__M->Timing.TaskCounters.TID[2] = 0;
  }
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

real32_T rt_roundf_snf(real32_T u)
{
  real32_T y;
  if ((real32_T)fabs(u) < 8.388608E+6F) {
    if (u >= 0.5F) {
      y = (real32_T)floor(u + 0.5F);
    } else if (u > -0.5F) {
      y = u * 0.0F;
    } else {
      y = (real32_T)ceil(u - 0.5F);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model step function */
void PID_controller__step(void)
{
  /* local block i/o variables */
  real32_T rtb_NProdOut;
  real32_T rtb_NProdOut_g;
  real32_T rtb_Switch;
  real32_T rtb_Switch_i;
  real_T tmp_0;
  int32_T offset_i;
  real32_T rtb_DeadZone_e;
  real32_T rtb_MATLABSystem_0;
  real32_T scale_i;
  real32_T tmp;
  real32_T tmp_1;
  int8_T tmp_3;
  int8_T tmp_4;
  uint8_T b_status;
  uint8_T tmp_2;
  if (PID_controller__M->Timing.TaskCounters.TID[2] == 0) {
    /* MATLABSystem: '<Root>/Serial Receive' */
    MW_Serial_read(0, 28U, &PID_controller__B.rtb_SerialReceive_o1_m[0],
                   &b_status, NULL, 0.0, NULL, 0.0);

    /* MATLABSystem: '<Root>/Write received variables to memory' incorporates:
     *  DataTypeConversion: '<Root>/Data Type Conversion'
     *  MATLABSystem: '<Root>/Serial Receive'
     * */
    if (b_status != 0) {
      memcpy((void *)&PID_controller__B.dataInput[0], (void *)
             &PID_controller__B.rtb_SerialReceive_o1_m[0], (size_t)28 * sizeof
             (uint8_T));
      MW_EEPROMWrite(1U, &PID_controller__B.dataInput[0], 28.0);
    }

    /* End of MATLABSystem: '<Root>/Write received variables to memory' */

    /* MATLABSystem: '<S1>/Read PID variables from memory' */
    MW_EEPROMRead(5.0, 6.0, 3.0,
                  &PID_controller__B.ReadPIDvariablesfrommemory_f[0]);

    /* MATLABSystem: '<S2>/Read PID variables from memory' */
    MW_EEPROMRead(17.0, 6.0, 3.0, &PID_controller__B.ReadPIDvariablesfrommemory
                  [0]);

    /* MATLABSystem: '<Root>/Read target pressure from memory' */
    MW_EEPROMRead(1.0, 6.0, 1.0, &PID_controller__B.Readtargetpressurefrommemory);
  }

  /* MATLABSystem: '<Root>/MATLAB System' */
  if (PID_controller__DW.obj_a.SCALE != PID_controller__P.MATLABSystem_SCALE) {
    PID_controller__DW.obj_a.SCALE = PID_controller__P.MATLABSystem_SCALE;
  }

  if (PID_controller__DW.obj_a.OFFSET != PID_controller__P.MATLABSystem_OFFSET)
  {
    PID_controller__DW.obj_a.OFFSET = PID_controller__P.MATLABSystem_OFFSET;
  }

  if (PID_controller__DW.obj_a.SampleTime !=
      PID_controller__P.MATLABSystem_SampleTime) {
    PID_controller__DW.obj_a.SampleTime =
      PID_controller__P.MATLABSystem_SampleTime;
  }

  /*         %% Define output properties */
  /*  Simulink side (double) */
  rtb_MATLABSystem_0 = 0.0F;

  /*  --- Convert to hardware types --- */
  scale_i = (real32_T)PID_controller__DW.obj_a.SCALE;
  tmp_0 = rt_roundd_snf(PID_controller__DW.obj_a.OFFSET);
  if (tmp_0 < 2.147483648E+9) {
    if (tmp_0 >= -2.147483648E+9) {
      offset_i = (int32_T)tmp_0;
    } else {
      offset_i = MIN_int32_T;
    }
  } else {
    offset_i = MAX_int32_T;
  }

  stepFunctionPressure_Sensor(&rtb_MATLABSystem_0, &scale_i, &offset_i);

  /* Sum: '<Root>/Sum' incorporates:
   *  MATLABSystem: '<Root>/MATLAB System'
   */
  PID_controller__B.Saturation = PID_controller__B.Readtargetpressurefrommemory
    - rtb_MATLABSystem_0;

  /* Saturate: '<Root>/Saturation1' */
  if (PID_controller__B.Saturation > PID_controller__P.Saturation1_UpperSat) {
    tmp_1 = PID_controller__P.Saturation1_UpperSat;
  } else if (PID_controller__B.Saturation <
             PID_controller__P.Saturation1_LowerSat) {
    tmp_1 = PID_controller__P.Saturation1_LowerSat;
  } else {
    tmp_1 = PID_controller__B.Saturation;
  }

  /* Gain: '<Root>/Gain' incorporates:
   *  Saturate: '<Root>/Saturation1'
   */
  PID_controller__B.Gain = PID_controller__P.Gain_Gain * tmp_1;

  /* Product: '<S98>/NProd Out' incorporates:
   *  Constant: '<S2>/Constant'
   *  DiscreteIntegrator: '<S90>/Filter'
   *  Product: '<S88>/DProd Out'
   *  Sum: '<S90>/SumD'
   */
  rtb_NProdOut = (PID_controller__B.Gain *
                  PID_controller__B.ReadPIDvariablesfrommemory[2] -
                  PID_controller__DW.Filter_DSTATE) *
    PID_controller__P.Constant_Value;

  /* Sum: '<S104>/Sum' incorporates:
   *  DiscreteIntegrator: '<S95>/Integrator'
   *  Product: '<S100>/PProd Out'
   */
  scale_i = (PID_controller__B.Gain *
             PID_controller__B.ReadPIDvariablesfrommemory[0] +
             PID_controller__DW.Integrator_DSTATE) + rtb_NProdOut;

  /* Saturate: '<S102>/Saturation' */
  if (scale_i > PID_controller__P.PIDController_UpperSaturationLi) {
    tmp_1 = PID_controller__P.PIDController_UpperSaturationLi;
  } else if (scale_i < PID_controller__P.PIDController_LowerSaturationLi) {
    tmp_1 = PID_controller__P.PIDController_LowerSaturationLi;
  } else {
    tmp_1 = scale_i;
  }

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Constant'
   *  Gain: '<Root>/Gain2'
   *  Saturate: '<S102>/Saturation'
   */
  PID_controller__B.Sum2 = PID_controller__P.Gain2_Gain * tmp_1 +
    PID_controller__P.Constant_Value_f;

  /* Saturate: '<Root>/Saturation' */
  if (PID_controller__B.Saturation > PID_controller__P.Saturation_UpperSat) {
    /* Sum: '<Root>/Sum' incorporates:
     *  Saturate: '<Root>/Saturation'
     */
    PID_controller__B.Saturation = PID_controller__P.Saturation_UpperSat;
  } else if (PID_controller__B.Saturation <
             PID_controller__P.Saturation_LowerSat) {
    /* Sum: '<Root>/Sum' incorporates:
     *  Saturate: '<Root>/Saturation'
     */
    PID_controller__B.Saturation = PID_controller__P.Saturation_LowerSat;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* Product: '<S43>/NProd Out' incorporates:
   *  Constant: '<S1>/Constant'
   *  DiscreteIntegrator: '<S35>/Filter'
   *  Product: '<S33>/DProd Out'
   *  Sum: '<S35>/SumD'
   */
  rtb_NProdOut_g = (PID_controller__B.Saturation *
                    PID_controller__B.ReadPIDvariablesfrommemory_f[2] -
                    PID_controller__DW.Filter_DSTATE_n) *
    PID_controller__P.Constant_Value_g;

  /* Sum: '<S49>/Sum' incorporates:
   *  DiscreteIntegrator: '<S40>/Integrator'
   *  Product: '<S45>/PProd Out'
   */
  rtb_DeadZone_e = (PID_controller__B.Saturation *
                    PID_controller__B.ReadPIDvariablesfrommemory_f[0] +
                    PID_controller__DW.Integrator_DSTATE_m) + rtb_NProdOut_g;

  /* Saturate: '<S47>/Saturation' */
  if (rtb_DeadZone_e > PID_controller__P.PIDController_UpperSaturation_i) {
    tmp_1 = PID_controller__P.PIDController_UpperSaturation_i;
  } else if (rtb_DeadZone_e < PID_controller__P.PIDController_LowerSaturation_l)
  {
    tmp_1 = PID_controller__P.PIDController_LowerSaturation_l;
  } else {
    tmp_1 = rtb_DeadZone_e;
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Constant'
   *  Gain: '<Root>/Gain1'
   *  Saturate: '<S47>/Saturation'
   */
  PID_controller__B.Sum1 = PID_controller__P.Gain1_Gain * tmp_1 +
    PID_controller__P.Constant_Value_f;

  /* MATLABSystem: '<Root>/MATLAB System1' */
  if (PID_controller__DW.obj_n.SampleTime !=
      PID_controller__P.MATLABSystem1_SampleTime) {
    PID_controller__DW.obj_n.SampleTime =
      PID_controller__P.MATLABSystem1_SampleTime;
  }

  /* Start for MATLABSystem: '<Root>/MATLAB System1' */
  /*         %% Define output properties */
  tmp_1 = rt_roundf_snf(PID_controller__B.Sum1 * 256.0F) - 1.0F;
  tmp = rt_roundf_snf(PID_controller__B.Sum2 * 256.0F) - 1.0F;
  if (tmp_1 < 256.0F) {
    if (tmp_1 >= 0.0F) {
      b_status = (uint8_T)tmp_1;
    } else {
      b_status = 0U;
    }
  } else {
    b_status = MAX_uint8_T;
  }

  if (tmp < 256.0F) {
    if (tmp >= 0.0F) {
      tmp_2 = (uint8_T)tmp;
    } else {
      tmp_2 = 0U;
    }
  } else {
    tmp_2 = MAX_uint8_T;
  }

  /* MATLABSystem: '<Root>/MATLAB System1' */
  stepFunctionPWM_7812HZ(b_status, tmp_2);

  /* SignalConversion generated from: '<Root>/Vector Concatenate' incorporates:
   *  MATLABSystem: '<Root>/Serial Transmit2'
   */
  PID_controller__B.dataIn[2] = PID_controller__B.Sum1;

  /* DeadZone: '<S32>/DeadZone' */
  if (rtb_DeadZone_e > PID_controller__P.PIDController_UpperSaturation_i) {
    rtb_DeadZone_e -= PID_controller__P.PIDController_UpperSaturation_i;
  } else if (rtb_DeadZone_e >= PID_controller__P.PIDController_LowerSaturation_l)
  {
    rtb_DeadZone_e = 0.0F;
  } else {
    rtb_DeadZone_e -= PID_controller__P.PIDController_LowerSaturation_l;
  }

  /* End of DeadZone: '<S32>/DeadZone' */

  /* Product: '<S92>/IProd Out' incorporates:
   *  Product: '<S37>/IProd Out'
   */
  rtb_Switch_i = PID_controller__B.Saturation *
    PID_controller__B.ReadPIDvariablesfrommemory_f[1];

  /* Switch: '<S30>/Switch1' incorporates:
   *  Constant: '<S30>/Clamping_zero'
   *  Constant: '<S30>/Constant'
   *  Constant: '<S30>/Constant2'
   *  RelationalOperator: '<S30>/fix for DT propagation issue'
   */
  if (rtb_DeadZone_e > PID_controller__P.Clamping_zero_Value) {
    tmp_3 = PID_controller__P.Constant_Value_o;
  } else {
    tmp_3 = PID_controller__P.Constant2_Value;
  }

  /* Switch: '<S30>/Switch2' incorporates:
   *  Constant: '<S30>/Clamping_zero'
   *  Constant: '<S30>/Constant3'
   *  Constant: '<S30>/Constant4'
   *  RelationalOperator: '<S30>/fix for DT propagation issue1'
   */
  if (rtb_Switch_i > PID_controller__P.Clamping_zero_Value) {
    tmp_4 = PID_controller__P.Constant3_Value;
  } else {
    tmp_4 = PID_controller__P.Constant4_Value;
  }

  /* Switch: '<S30>/Switch' incorporates:
   *  Constant: '<S30>/Clamping_zero'
   *  Logic: '<S30>/AND3'
   *  RelationalOperator: '<S30>/Equal1'
   *  RelationalOperator: '<S30>/Relational Operator'
   *  Switch: '<S30>/Switch1'
   *  Switch: '<S30>/Switch2'
   */
  if ((PID_controller__P.Clamping_zero_Value != rtb_DeadZone_e) && (tmp_3 ==
       tmp_4)) {
    /* Switch: '<S30>/Switch' incorporates:
     *  Constant: '<S30>/Constant1'
     */
    rtb_Switch = PID_controller__P.Constant1_Value;
  } else {
    /* Switch: '<S30>/Switch' */
    rtb_Switch = rtb_Switch_i;
  }

  /* End of Switch: '<S30>/Switch' */

  /* SignalConversion generated from: '<Root>/Vector Concatenate' incorporates:
   *  MATLABSystem: '<Root>/Serial Transmit2'
   */
  PID_controller__B.dataIn[3] = PID_controller__B.Sum2;

  /* DeadZone: '<S87>/DeadZone' */
  if (scale_i > PID_controller__P.PIDController_UpperSaturationLi) {
    scale_i -= PID_controller__P.PIDController_UpperSaturationLi;
  } else if (scale_i >= PID_controller__P.PIDController_LowerSaturationLi) {
    scale_i = 0.0F;
  } else {
    scale_i -= PID_controller__P.PIDController_LowerSaturationLi;
  }

  /* End of DeadZone: '<S87>/DeadZone' */

  /* Product: '<S92>/IProd Out' */
  rtb_Switch_i = PID_controller__B.Gain *
    PID_controller__B.ReadPIDvariablesfrommemory[1];

  /* Switch: '<S85>/Switch1' incorporates:
   *  Constant: '<S85>/Clamping_zero'
   *  Constant: '<S85>/Constant'
   *  Constant: '<S85>/Constant2'
   *  RelationalOperator: '<S85>/fix for DT propagation issue'
   */
  if (scale_i > PID_controller__P.Clamping_zero_Value_d) {
    tmp_3 = PID_controller__P.Constant_Value_b;
  } else {
    tmp_3 = PID_controller__P.Constant2_Value_e;
  }

  /* Switch: '<S85>/Switch2' incorporates:
   *  Constant: '<S85>/Clamping_zero'
   *  Constant: '<S85>/Constant3'
   *  Constant: '<S85>/Constant4'
   *  RelationalOperator: '<S85>/fix for DT propagation issue1'
   */
  if (rtb_Switch_i > PID_controller__P.Clamping_zero_Value_d) {
    tmp_4 = PID_controller__P.Constant3_Value_b;
  } else {
    tmp_4 = PID_controller__P.Constant4_Value_l;
  }

  /* Switch: '<S85>/Switch' incorporates:
   *  Constant: '<S85>/Clamping_zero'
   *  Logic: '<S85>/AND3'
   *  RelationalOperator: '<S85>/Equal1'
   *  RelationalOperator: '<S85>/Relational Operator'
   *  Switch: '<S85>/Switch1'
   *  Switch: '<S85>/Switch2'
   */
  if ((PID_controller__P.Clamping_zero_Value_d != scale_i) && (tmp_3 == tmp_4))
  {
    /* Product: '<S92>/IProd Out' incorporates:
     *  Constant: '<S85>/Constant1'
     *  Switch: '<S85>/Switch'
     */
    rtb_Switch_i = PID_controller__P.Constant1_Value_b;
  }

  /* End of Switch: '<S85>/Switch' */

  /* SignalConversion generated from: '<Root>/Vector Concatenate' incorporates:
   *  MATLABSystem: '<Root>/MATLAB System'
   *  MATLABSystem: '<Root>/Serial Transmit2'
   */
  PID_controller__B.dataIn[1] = rtb_MATLABSystem_0;

  /* DataTypeConversion: '<Root>/Data Type Conversion2' incorporates:
   *  Clock: '<Root>/Clock'
   *  MATLABSystem: '<Root>/Serial Transmit2'
   */
  PID_controller__B.dataIn[0] = (real32_T)PID_controller__M->Timing.t[0];

  /* MATLABSystem: '<Root>/Serial Transmit2' */
  MW_Serial_write(PID_controller__DW.obj.port, &PID_controller__B.dataIn[0], 4.0,
                  PID_controller__DW.obj.dataSizeInBytes,
                  PID_controller__DW.obj.sendModeEnum,
                  PID_controller__DW.obj.dataType,
                  PID_controller__DW.obj.sendFormatEnum, 2.0, '\x00', NULL, 0.0,
                  NULL, 0.0);

  /* Update for DiscreteIntegrator: '<S95>/Integrator' */
  PID_controller__DW.Integrator_DSTATE += PID_controller__P.Integrator_gainval *
    rtb_Switch_i;

  /* Update for DiscreteIntegrator: '<S90>/Filter' */
  PID_controller__DW.Filter_DSTATE += PID_controller__P.Filter_gainval *
    rtb_NProdOut;

  /* Update for DiscreteIntegrator: '<S40>/Integrator' */
  PID_controller__DW.Integrator_DSTATE_m +=
    PID_controller__P.Integrator_gainval_f * rtb_Switch;

  /* Update for DiscreteIntegrator: '<S35>/Filter' */
  PID_controller__DW.Filter_DSTATE_n += PID_controller__P.Filter_gainval_m *
    rtb_NProdOut_g;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++PID_controller__M->Timing.clockTick0)) {
    ++PID_controller__M->Timing.clockTickH0;
  }

  PID_controller__M->Timing.t[0] = PID_controller__M->Timing.clockTick0 *
    PID_controller__M->Timing.stepSize0 + PID_controller__M->Timing.clockTickH0 *
    PID_controller__M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    PID_controller__M->Timing.clockTick1++;
    if (!PID_controller__M->Timing.clockTick1) {
      PID_controller__M->Timing.clockTickH1++;
    }
  }

  rate_scheduler();
}

/* Model initialize function */
void PID_controller__initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  PID_controller__P.Saturation1_LowerSat = rtMinusInfF;
  PID_controller__P.Saturation_UpperSat = rtInfF;

  /* initialize real-time model */
  (void) memset((void *)PID_controller__M, 0,
                sizeof(RT_MODEL_PID_controller__T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&PID_controller__M->solverInfo,
                          &PID_controller__M->Timing.simTimeStep);
    rtsiSetTPtr(&PID_controller__M->solverInfo, &rtmGetTPtr(PID_controller__M));
    rtsiSetStepSizePtr(&PID_controller__M->solverInfo,
                       &PID_controller__M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&PID_controller__M->solverInfo, (&rtmGetErrorStatus
      (PID_controller__M)));
    rtsiSetRTModelPtr(&PID_controller__M->solverInfo, PID_controller__M);
  }

  rtsiSetSimTimeStep(&PID_controller__M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&PID_controller__M->solverInfo, false);
  rtsiSetIsContModeFrozen(&PID_controller__M->solverInfo, false);
  rtsiSetSolverName(&PID_controller__M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(PID_controller__M, &PID_controller__M->Timing.tArray[0]);
  PID_controller__M->Timing.stepSize0 = 0.001;

  /* block I/O */
  (void) memset(((void *) &PID_controller__B), 0,
                sizeof(B_PID_controller__T));

  /* states (dwork) */
  (void) memset((void *)&PID_controller__DW, 0,
                sizeof(DW_PID_controller__T));

  {
    real_T tmp;
    int32_T offset;
    real32_T scale;

    /* Start for MATLABSystem: '<Root>/Serial Receive' */
    PID_controller__DW.obj_p.matlabCodegenIsDeleted = false;
    PID_controller__DW.objisempty_n = true;
    PID_controller__DW.obj_p.isInitialized = 1L;
    MW_SCI_Open(0);
    PID_controller__DW.obj_p.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Write received variables to memory' */
    PID_controller__DW.obj_aq.matlabCodegenIsDeleted = false;
    PID_controller__DW.objisempty = true;
    PID_controller__DW.obj_aq.isInitialized = 1L;
    PID_controller__DW.obj_aq.isSetupComplete = true;

    /* Start for MATLABSystem: '<S1>/Read PID variables from memory' */
    PID_controller__DW.obj_j.matlabCodegenIsDeleted = false;
    PID_controller__DW.objisempty_jb = true;
    PID_controller__DW.obj_j.isInitialized = 1L;
    PID_controller__DW.obj_j.DataTypeWidth = 4U;
    PID_controller__DW.obj_j.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/Read PID variables from memory' */
    PID_controller__DW.obj_a4.matlabCodegenIsDeleted = false;
    PID_controller__DW.objisempty_k = true;
    PID_controller__DW.obj_a4.isInitialized = 1L;
    PID_controller__DW.obj_a4.DataTypeWidth = 4U;
    PID_controller__DW.obj_a4.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Read target pressure from memory' */
    PID_controller__DW.obj_d.matlabCodegenIsDeleted = false;
    PID_controller__DW.objisempty_j = true;
    PID_controller__DW.obj_d.isInitialized = 1L;
    PID_controller__DW.obj_d.DataTypeWidth = 4U;
    PID_controller__DW.obj_d.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/MATLAB System' */
    /*  Constructor */
    PID_controller__DW.obj_a.matlabCodegenIsDeleted = false;
    PID_controller__DW.objisempty_hb = true;
    PID_controller__DW.obj_a.SCALE = PID_controller__P.MATLABSystem_SCALE;
    PID_controller__DW.obj_a.OFFSET = PID_controller__P.MATLABSystem_OFFSET;
    PID_controller__DW.obj_a.SampleTime =
      PID_controller__P.MATLABSystem_SampleTime;
    PID_controller__DW.obj_a.isInitialized = 1L;

    /*         %% Define output properties */
    /*   Check the input size */
    scale = (real32_T)PID_controller__DW.obj_a.SCALE;
    tmp = rt_roundd_snf(PID_controller__DW.obj_a.OFFSET);
    if (tmp < 2.147483648E+9) {
      if (tmp >= -2.147483648E+9) {
        offset = (int32_T)tmp;
      } else {
        offset = MIN_int32_T;
      }
    } else {
      offset = MAX_int32_T;
    }

    setupFunctionPressure_Sensor(8, 9, &scale, &offset);
    PID_controller__DW.obj_a.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/MATLAB System' */

    /* Start for MATLABSystem: '<Root>/MATLAB System1' */
    /*  Constructor */
    PID_controller__DW.obj_n.matlabCodegenIsDeleted = false;
    PID_controller__DW.objisempty_a = true;
    PID_controller__DW.obj_n.SampleTime =
      PID_controller__P.MATLABSystem1_SampleTime;
    PID_controller__DW.obj_n.isInitialized = 1L;

    /*         %% Define output properties */
    /*   Check the input size */
    setupFunctionPWM_7812HZ();
    PID_controller__DW.obj_n.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Serial Transmit2' */
    PID_controller__DW.obj.matlabCodegenIsDeleted = false;
    PID_controller__DW.objisempty_h = true;
    PID_controller__DW.obj.isInitialized = 1L;
    PID_controller__DW.obj.port = 0.0;
    PID_controller__DW.obj.dataSizeInBytes = 4.0;
    PID_controller__DW.obj.dataType = 6.0;
    PID_controller__DW.obj.sendModeEnum = 0.0;
    PID_controller__DW.obj.sendFormatEnum = 0.0;
    MW_SCI_Open(0);
    PID_controller__DW.obj.isSetupComplete = true;
  }

  /* InitializeConditions for DiscreteIntegrator: '<S95>/Integrator' */
  PID_controller__DW.Integrator_DSTATE =
    PID_controller__P.PIDController_InitialConditio_m;

  /* InitializeConditions for DiscreteIntegrator: '<S90>/Filter' */
  PID_controller__DW.Filter_DSTATE =
    PID_controller__P.PIDController_InitialConditionF;

  /* InitializeConditions for DiscreteIntegrator: '<S40>/Integrator' */
  PID_controller__DW.Integrator_DSTATE_m =
    PID_controller__P.PIDController_InitialConditio_p;

  /* InitializeConditions for DiscreteIntegrator: '<S35>/Filter' */
  PID_controller__DW.Filter_DSTATE_n =
    PID_controller__P.PIDController_InitialConditio_i;
}

/* Model terminate function */
void PID_controller__terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Serial Receive' */
  if (!PID_controller__DW.obj_p.matlabCodegenIsDeleted) {
    PID_controller__DW.obj_p.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Serial Receive' */

  /* Terminate for MATLABSystem: '<Root>/Write received variables to memory' */
  if (!PID_controller__DW.obj_aq.matlabCodegenIsDeleted) {
    PID_controller__DW.obj_aq.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Write received variables to memory' */

  /* Terminate for MATLABSystem: '<S1>/Read PID variables from memory' */
  if (!PID_controller__DW.obj_j.matlabCodegenIsDeleted) {
    PID_controller__DW.obj_j.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S1>/Read PID variables from memory' */

  /* Terminate for MATLABSystem: '<S2>/Read PID variables from memory' */
  if (!PID_controller__DW.obj_a4.matlabCodegenIsDeleted) {
    PID_controller__DW.obj_a4.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S2>/Read PID variables from memory' */

  /* Terminate for MATLABSystem: '<Root>/Read target pressure from memory' */
  if (!PID_controller__DW.obj_d.matlabCodegenIsDeleted) {
    PID_controller__DW.obj_d.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Read target pressure from memory' */

  /* Terminate for MATLABSystem: '<Root>/MATLAB System' */
  if (!PID_controller__DW.obj_a.matlabCodegenIsDeleted) {
    PID_controller__DW.obj_a.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/MATLAB System' */

  /* Terminate for MATLABSystem: '<Root>/MATLAB System1' */
  if (!PID_controller__DW.obj_n.matlabCodegenIsDeleted) {
    PID_controller__DW.obj_n.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/MATLAB System1' */

  /* Terminate for MATLABSystem: '<Root>/Serial Transmit2' */
  if (!PID_controller__DW.obj.matlabCodegenIsDeleted) {
    PID_controller__DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Serial Transmit2' */
}
