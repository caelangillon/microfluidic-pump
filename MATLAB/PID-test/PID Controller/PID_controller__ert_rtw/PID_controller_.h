/*
 * PID_controller_.h
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

#ifndef PID_controller__h_
#define PID_controller__h_
#ifndef PID_controller__COMMON_INCLUDES_
#define PID_controller__COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "Pressure_Sensor.h"
#include "PWM_7812HZ.h"
#include "MW_ArduinoOnBoardEEPROM.h"
#include "MW_SerialRead.h"
#include "MW_SerialWrite.h"
#endif                                 /* PID_controller__COMMON_INCLUDES_ */

#include "PID_controller__types.h"
#include <string.h>
#include "rt_nonfinite.h"
#include <stddef.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  uint8_T dataInput[28];
  real32_T rtb_SerialReceive_o1_m[7];
  real32_T dataIn[4];
  real32_T Gain;                       /* '<Root>/Gain' */
  real32_T Sum2;                       /* '<Root>/Sum2' */
  real32_T Saturation;                 /* '<Root>/Saturation' */
  real32_T Sum1;                       /* '<Root>/Sum1' */
  real32_T Readtargetpressurefrommemory;
                                 /* '<Root>/Read target pressure from memory' */
  real32_T ReadPIDvariablesfrommemory[3];
                                     /* '<S2>/Read PID variables from memory' */
  real32_T ReadPIDvariablesfrommemory_f[3];
                                     /* '<S1>/Read PID variables from memory' */
} B_PID_controller__T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_in_nw_T obj; /* '<Root>/Serial Transmit2' */
  Pressure_Sensor_PID_controlle_T obj_a;/* '<Root>/MATLAB System' */
  PWM_7812HZ_PID_controller__T obj_n;  /* '<Root>/MATLAB System1' */
  codertarget_arduinobase_inter_T obj_d;
                                 /* '<Root>/Read target pressure from memory' */
  codertarget_arduinobase_inter_T obj_a4;
                                     /* '<S2>/Read PID variables from memory' */
  codertarget_arduinobase_inter_T obj_j;
                                     /* '<S1>/Read PID variables from memory' */
  codertarget_arduinobase_int_n_T obj_p;/* '<Root>/Serial Receive' */
  codertarget_arduinobase_i_nwr_T obj_aq;
                               /* '<Root>/Write received variables to memory' */
  real32_T Integrator_DSTATE;          /* '<S95>/Integrator' */
  real32_T Filter_DSTATE;              /* '<S90>/Filter' */
  real32_T Integrator_DSTATE_m;        /* '<S40>/Integrator' */
  real32_T Filter_DSTATE_n;            /* '<S35>/Filter' */
  boolean_T objisempty;        /* '<Root>/Write received variables to memory' */
  boolean_T objisempty_h;              /* '<Root>/Serial Transmit2' */
  boolean_T objisempty_n;              /* '<Root>/Serial Receive' */
  boolean_T objisempty_j;        /* '<Root>/Read target pressure from memory' */
  boolean_T objisempty_k;            /* '<S2>/Read PID variables from memory' */
  boolean_T objisempty_jb;           /* '<S1>/Read PID variables from memory' */
  boolean_T objisempty_a;              /* '<Root>/MATLAB System1' */
  boolean_T objisempty_hb;             /* '<Root>/MATLAB System' */
} DW_PID_controller__T;

/* Parameters (default storage) */
struct P_PID_controller__T_ {
  real32_T PIDController_InitialConditionF;
                              /* Mask Parameter: PIDController_InitialConditionF
                               * Referenced by: '<S90>/Filter'
                               */
  real32_T PIDController_InitialConditio_i;
                              /* Mask Parameter: PIDController_InitialConditio_i
                               * Referenced by: '<S35>/Filter'
                               */
  real32_T PIDController_InitialConditio_m;
                              /* Mask Parameter: PIDController_InitialConditio_m
                               * Referenced by: '<S95>/Integrator'
                               */
  real32_T PIDController_InitialConditio_p;
                              /* Mask Parameter: PIDController_InitialConditio_p
                               * Referenced by: '<S40>/Integrator'
                               */
  real32_T PIDController_LowerSaturationLi;
                              /* Mask Parameter: PIDController_LowerSaturationLi
                               * Referenced by:
                               *   '<S102>/Saturation'
                               *   '<S87>/DeadZone'
                               */
  real32_T PIDController_LowerSaturation_l;
                              /* Mask Parameter: PIDController_LowerSaturation_l
                               * Referenced by:
                               *   '<S47>/Saturation'
                               *   '<S32>/DeadZone'
                               */
  real32_T PIDController_UpperSaturationLi;
                              /* Mask Parameter: PIDController_UpperSaturationLi
                               * Referenced by:
                               *   '<S102>/Saturation'
                               *   '<S87>/DeadZone'
                               */
  real32_T PIDController_UpperSaturation_i;
                              /* Mask Parameter: PIDController_UpperSaturation_i
                               * Referenced by:
                               *   '<S47>/Saturation'
                               *   '<S32>/DeadZone'
                               */
  real_T MATLABSystem_SCALE;           /* Expression: 42.255
                                        * Referenced by: '<Root>/MATLAB System'
                                        */
  real_T MATLABSystem_OFFSET;          /* Expression: 41500
                                        * Referenced by: '<Root>/MATLAB System'
                                        */
  real_T MATLABSystem_SampleTime;      /* Expression: -1
                                        * Referenced by: '<Root>/MATLAB System'
                                        */
  real_T MATLABSystem1_SampleTime;     /* Expression: -1
                                        * Referenced by: '<Root>/MATLAB System1'
                                        */
  real32_T Constant1_Value;            /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S30>/Constant1'
                                        */
  real32_T Constant1_Value_b;          /* Computed Parameter: Constant1_Value_b
                                        * Referenced by: '<S85>/Constant1'
                                        */
  real32_T Saturation1_UpperSat;     /* Computed Parameter: Saturation1_UpperSat
                                      * Referenced by: '<Root>/Saturation1'
                                      */
  real32_T Saturation1_LowerSat;     /* Computed Parameter: Saturation1_LowerSat
                                      * Referenced by: '<Root>/Saturation1'
                                      */
  real32_T Gain_Gain;                  /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<Root>/Gain'
                                        */
  real32_T Integrator_gainval;         /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S95>/Integrator'
                                        */
  real32_T Filter_gainval;             /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S90>/Filter'
                                        */
  real32_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S2>/Constant'
                                        */
  real32_T Gain2_Gain;                 /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<Root>/Gain2'
                                        */
  real32_T Constant_Value_f;           /* Computed Parameter: Constant_Value_f
                                        * Referenced by: '<Root>/Constant'
                                        */
  real32_T Saturation_UpperSat;       /* Computed Parameter: Saturation_UpperSat
                                       * Referenced by: '<Root>/Saturation'
                                       */
  real32_T Saturation_LowerSat;       /* Computed Parameter: Saturation_LowerSat
                                       * Referenced by: '<Root>/Saturation'
                                       */
  real32_T Integrator_gainval_f;     /* Computed Parameter: Integrator_gainval_f
                                      * Referenced by: '<S40>/Integrator'
                                      */
  real32_T Filter_gainval_m;           /* Computed Parameter: Filter_gainval_m
                                        * Referenced by: '<S35>/Filter'
                                        */
  real32_T Constant_Value_g;           /* Computed Parameter: Constant_Value_g
                                        * Referenced by: '<S1>/Constant'
                                        */
  real32_T Gain1_Gain;                 /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real32_T Clamping_zero_Value;       /* Computed Parameter: Clamping_zero_Value
                                       * Referenced by: '<S30>/Clamping_zero'
                                       */
  real32_T Clamping_zero_Value_d;   /* Computed Parameter: Clamping_zero_Value_d
                                     * Referenced by: '<S85>/Clamping_zero'
                                     */
  int8_T Constant_Value_o;             /* Computed Parameter: Constant_Value_o
                                        * Referenced by: '<S30>/Constant'
                                        */
  int8_T Constant2_Value;              /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<S30>/Constant2'
                                        */
  int8_T Constant3_Value;              /* Computed Parameter: Constant3_Value
                                        * Referenced by: '<S30>/Constant3'
                                        */
  int8_T Constant4_Value;              /* Computed Parameter: Constant4_Value
                                        * Referenced by: '<S30>/Constant4'
                                        */
  int8_T Constant_Value_b;             /* Computed Parameter: Constant_Value_b
                                        * Referenced by: '<S85>/Constant'
                                        */
  int8_T Constant2_Value_e;            /* Computed Parameter: Constant2_Value_e
                                        * Referenced by: '<S85>/Constant2'
                                        */
  int8_T Constant3_Value_b;            /* Computed Parameter: Constant3_Value_b
                                        * Referenced by: '<S85>/Constant3'
                                        */
  int8_T Constant4_Value_l;            /* Computed Parameter: Constant4_Value_l
                                        * Referenced by: '<S85>/Constant4'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_PID_controller__T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    struct {
      uint8_T TID[3];
    } TaskCounters;

    SimTimeStep simTimeStep;
    time_T *t;
    time_T tArray[3];
  } Timing;
};

/* Block parameters (default storage) */
extern P_PID_controller__T PID_controller__P;

/* Block signals (default storage) */
extern B_PID_controller__T PID_controller__B;

/* Block states (default storage) */
extern DW_PID_controller__T PID_controller__DW;

/* Model entry point functions */
extern void PID_controller__initialize(void);
extern void PID_controller__step(void);
extern void PID_controller__terminate(void);

/* Real-time Model object */
extern RT_MODEL_PID_controller__T *const PID_controller__M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'PID_controller_'
 * '<S1>'   : 'PID_controller_/PID Controller 1'
 * '<S2>'   : 'PID_controller_/PID Controller 2'
 * '<S3>'   : 'PID_controller_/PID Controller 1/PID Controller'
 * '<S4>'   : 'PID_controller_/PID Controller 1/PID Controller/Anti-windup'
 * '<S5>'   : 'PID_controller_/PID Controller 1/PID Controller/D Gain'
 * '<S6>'   : 'PID_controller_/PID Controller 1/PID Controller/External Derivative'
 * '<S7>'   : 'PID_controller_/PID Controller 1/PID Controller/Filter'
 * '<S8>'   : 'PID_controller_/PID Controller 1/PID Controller/Filter ICs'
 * '<S9>'   : 'PID_controller_/PID Controller 1/PID Controller/I Gain'
 * '<S10>'  : 'PID_controller_/PID Controller 1/PID Controller/Ideal P Gain'
 * '<S11>'  : 'PID_controller_/PID Controller 1/PID Controller/Ideal P Gain Fdbk'
 * '<S12>'  : 'PID_controller_/PID Controller 1/PID Controller/Integrator'
 * '<S13>'  : 'PID_controller_/PID Controller 1/PID Controller/Integrator ICs'
 * '<S14>'  : 'PID_controller_/PID Controller 1/PID Controller/N Copy'
 * '<S15>'  : 'PID_controller_/PID Controller 1/PID Controller/N Gain'
 * '<S16>'  : 'PID_controller_/PID Controller 1/PID Controller/P Copy'
 * '<S17>'  : 'PID_controller_/PID Controller 1/PID Controller/Parallel P Gain'
 * '<S18>'  : 'PID_controller_/PID Controller 1/PID Controller/Reset Signal'
 * '<S19>'  : 'PID_controller_/PID Controller 1/PID Controller/Saturation'
 * '<S20>'  : 'PID_controller_/PID Controller 1/PID Controller/Saturation Fdbk'
 * '<S21>'  : 'PID_controller_/PID Controller 1/PID Controller/Sum'
 * '<S22>'  : 'PID_controller_/PID Controller 1/PID Controller/Sum Fdbk'
 * '<S23>'  : 'PID_controller_/PID Controller 1/PID Controller/Tracking Mode'
 * '<S24>'  : 'PID_controller_/PID Controller 1/PID Controller/Tracking Mode Sum'
 * '<S25>'  : 'PID_controller_/PID Controller 1/PID Controller/Tsamp - Integral'
 * '<S26>'  : 'PID_controller_/PID Controller 1/PID Controller/Tsamp - Ngain'
 * '<S27>'  : 'PID_controller_/PID Controller 1/PID Controller/postSat Signal'
 * '<S28>'  : 'PID_controller_/PID Controller 1/PID Controller/preInt Signal'
 * '<S29>'  : 'PID_controller_/PID Controller 1/PID Controller/preSat Signal'
 * '<S30>'  : 'PID_controller_/PID Controller 1/PID Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S31>'  : 'PID_controller_/PID Controller 1/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S32>'  : 'PID_controller_/PID Controller 1/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S33>'  : 'PID_controller_/PID Controller 1/PID Controller/D Gain/External Parameters'
 * '<S34>'  : 'PID_controller_/PID Controller 1/PID Controller/External Derivative/Error'
 * '<S35>'  : 'PID_controller_/PID Controller 1/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S36>'  : 'PID_controller_/PID Controller 1/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S37>'  : 'PID_controller_/PID Controller 1/PID Controller/I Gain/External Parameters'
 * '<S38>'  : 'PID_controller_/PID Controller 1/PID Controller/Ideal P Gain/Passthrough'
 * '<S39>'  : 'PID_controller_/PID Controller 1/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S40>'  : 'PID_controller_/PID Controller 1/PID Controller/Integrator/Discrete'
 * '<S41>'  : 'PID_controller_/PID Controller 1/PID Controller/Integrator ICs/Internal IC'
 * '<S42>'  : 'PID_controller_/PID Controller 1/PID Controller/N Copy/Disabled'
 * '<S43>'  : 'PID_controller_/PID Controller 1/PID Controller/N Gain/External Parameters'
 * '<S44>'  : 'PID_controller_/PID Controller 1/PID Controller/P Copy/Disabled'
 * '<S45>'  : 'PID_controller_/PID Controller 1/PID Controller/Parallel P Gain/External Parameters'
 * '<S46>'  : 'PID_controller_/PID Controller 1/PID Controller/Reset Signal/Disabled'
 * '<S47>'  : 'PID_controller_/PID Controller 1/PID Controller/Saturation/Enabled'
 * '<S48>'  : 'PID_controller_/PID Controller 1/PID Controller/Saturation Fdbk/Disabled'
 * '<S49>'  : 'PID_controller_/PID Controller 1/PID Controller/Sum/Sum_PID'
 * '<S50>'  : 'PID_controller_/PID Controller 1/PID Controller/Sum Fdbk/Disabled'
 * '<S51>'  : 'PID_controller_/PID Controller 1/PID Controller/Tracking Mode/Disabled'
 * '<S52>'  : 'PID_controller_/PID Controller 1/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S53>'  : 'PID_controller_/PID Controller 1/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S54>'  : 'PID_controller_/PID Controller 1/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S55>'  : 'PID_controller_/PID Controller 1/PID Controller/postSat Signal/Forward_Path'
 * '<S56>'  : 'PID_controller_/PID Controller 1/PID Controller/preInt Signal/Internal PreInt'
 * '<S57>'  : 'PID_controller_/PID Controller 1/PID Controller/preSat Signal/Forward_Path'
 * '<S58>'  : 'PID_controller_/PID Controller 2/PID Controller'
 * '<S59>'  : 'PID_controller_/PID Controller 2/PID Controller/Anti-windup'
 * '<S60>'  : 'PID_controller_/PID Controller 2/PID Controller/D Gain'
 * '<S61>'  : 'PID_controller_/PID Controller 2/PID Controller/External Derivative'
 * '<S62>'  : 'PID_controller_/PID Controller 2/PID Controller/Filter'
 * '<S63>'  : 'PID_controller_/PID Controller 2/PID Controller/Filter ICs'
 * '<S64>'  : 'PID_controller_/PID Controller 2/PID Controller/I Gain'
 * '<S65>'  : 'PID_controller_/PID Controller 2/PID Controller/Ideal P Gain'
 * '<S66>'  : 'PID_controller_/PID Controller 2/PID Controller/Ideal P Gain Fdbk'
 * '<S67>'  : 'PID_controller_/PID Controller 2/PID Controller/Integrator'
 * '<S68>'  : 'PID_controller_/PID Controller 2/PID Controller/Integrator ICs'
 * '<S69>'  : 'PID_controller_/PID Controller 2/PID Controller/N Copy'
 * '<S70>'  : 'PID_controller_/PID Controller 2/PID Controller/N Gain'
 * '<S71>'  : 'PID_controller_/PID Controller 2/PID Controller/P Copy'
 * '<S72>'  : 'PID_controller_/PID Controller 2/PID Controller/Parallel P Gain'
 * '<S73>'  : 'PID_controller_/PID Controller 2/PID Controller/Reset Signal'
 * '<S74>'  : 'PID_controller_/PID Controller 2/PID Controller/Saturation'
 * '<S75>'  : 'PID_controller_/PID Controller 2/PID Controller/Saturation Fdbk'
 * '<S76>'  : 'PID_controller_/PID Controller 2/PID Controller/Sum'
 * '<S77>'  : 'PID_controller_/PID Controller 2/PID Controller/Sum Fdbk'
 * '<S78>'  : 'PID_controller_/PID Controller 2/PID Controller/Tracking Mode'
 * '<S79>'  : 'PID_controller_/PID Controller 2/PID Controller/Tracking Mode Sum'
 * '<S80>'  : 'PID_controller_/PID Controller 2/PID Controller/Tsamp - Integral'
 * '<S81>'  : 'PID_controller_/PID Controller 2/PID Controller/Tsamp - Ngain'
 * '<S82>'  : 'PID_controller_/PID Controller 2/PID Controller/postSat Signal'
 * '<S83>'  : 'PID_controller_/PID Controller 2/PID Controller/preInt Signal'
 * '<S84>'  : 'PID_controller_/PID Controller 2/PID Controller/preSat Signal'
 * '<S85>'  : 'PID_controller_/PID Controller 2/PID Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S86>'  : 'PID_controller_/PID Controller 2/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S87>'  : 'PID_controller_/PID Controller 2/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S88>'  : 'PID_controller_/PID Controller 2/PID Controller/D Gain/External Parameters'
 * '<S89>'  : 'PID_controller_/PID Controller 2/PID Controller/External Derivative/Error'
 * '<S90>'  : 'PID_controller_/PID Controller 2/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S91>'  : 'PID_controller_/PID Controller 2/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S92>'  : 'PID_controller_/PID Controller 2/PID Controller/I Gain/External Parameters'
 * '<S93>'  : 'PID_controller_/PID Controller 2/PID Controller/Ideal P Gain/Passthrough'
 * '<S94>'  : 'PID_controller_/PID Controller 2/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S95>'  : 'PID_controller_/PID Controller 2/PID Controller/Integrator/Discrete'
 * '<S96>'  : 'PID_controller_/PID Controller 2/PID Controller/Integrator ICs/Internal IC'
 * '<S97>'  : 'PID_controller_/PID Controller 2/PID Controller/N Copy/Disabled'
 * '<S98>'  : 'PID_controller_/PID Controller 2/PID Controller/N Gain/External Parameters'
 * '<S99>'  : 'PID_controller_/PID Controller 2/PID Controller/P Copy/Disabled'
 * '<S100>' : 'PID_controller_/PID Controller 2/PID Controller/Parallel P Gain/External Parameters'
 * '<S101>' : 'PID_controller_/PID Controller 2/PID Controller/Reset Signal/Disabled'
 * '<S102>' : 'PID_controller_/PID Controller 2/PID Controller/Saturation/Enabled'
 * '<S103>' : 'PID_controller_/PID Controller 2/PID Controller/Saturation Fdbk/Disabled'
 * '<S104>' : 'PID_controller_/PID Controller 2/PID Controller/Sum/Sum_PID'
 * '<S105>' : 'PID_controller_/PID Controller 2/PID Controller/Sum Fdbk/Disabled'
 * '<S106>' : 'PID_controller_/PID Controller 2/PID Controller/Tracking Mode/Disabled'
 * '<S107>' : 'PID_controller_/PID Controller 2/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S108>' : 'PID_controller_/PID Controller 2/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S109>' : 'PID_controller_/PID Controller 2/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S110>' : 'PID_controller_/PID Controller 2/PID Controller/postSat Signal/Forward_Path'
 * '<S111>' : 'PID_controller_/PID Controller 2/PID Controller/preInt Signal/Internal PreInt'
 * '<S112>' : 'PID_controller_/PID Controller 2/PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* PID_controller__h_ */
