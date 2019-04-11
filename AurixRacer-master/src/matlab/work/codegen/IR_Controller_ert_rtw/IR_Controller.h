/*
 * File: IR_Controller.h
 *
 * Code generated for Simulink model 'IR_Controller'.
 *
 * Model version                  : 1.145
 * Simulink Coder version         : 9.1 (R2019a) 23-Nov-2018
 * C/C++ source code generated on : Tue Apr  9 13:38:28 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Infineon->TriCore
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_IR_Controller_h_
#define RTW_HEADER_IR_Controller_h_
#ifndef IR_Controller_COMMON_INCLUDES_
# define IR_Controller_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* IR_Controller_COMMON_INCLUDES_ */

#include "IR_Controller_types.h"

/* Macros for accessing real-time model data structure */

/* Block states (default storage) for system '<Root>' */
typedef struct
{
    real_T Integrator_DSTATE;          /* '<S76>/Integrator' */
    real_T UD_DSTATE;                  /* '<S71>/UD' */
    real_T Integrator_DSTATE_k;        /* '<S32>/Integrator' */
    real_T UD_DSTATE_j;                /* '<S27>/UD' */
    int32_T clockTickCounter;          /* '<Root>/Pulse Generator' */
    int32_T clockTickCounter_a;        /* '<Root>/Pulse Generator1' */
}
D_Work_IR_Controller;

/* Parameters (default storage) */
struct Parameters_IR_Controller_
{
    pid_param LatPid;                  /* Variable: LatPid
                                        * Referenced by:
                                        *   '<S26>/Derivative Gain'
                                        *   '<S29>/Integral Gain'
                                        *   '<S37>/Proportional Gain'
                                        */
    pid_param LongiPid;                /* Variable: LongiPid
                                        * Referenced by:
                                        *   '<S70>/Derivative Gain'
                                        *   '<S73>/Integral Gain'
                                        *   '<S81>/Proportional Gain'
                                        */
};

/* Block parameters (default storage) */
extern Parameters_IR_Controller IR_Controller_P;

/* Block states (default storage) */
extern D_Work_IR_Controller IR_Controller_DWork;

/* Model entry point functions */
extern void IR_Controller_initialize(void);
extern void IR_Controller_step(void);

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
 * '<Root>' : 'IR_Controller'
 * '<S1>'   : 'IR_Controller/LatPidCtrl'
 * '<S2>'   : 'IR_Controller/LongiPidCtrl'
 * '<S3>'   : 'IR_Controller/LatPidCtrl/Anti-windup'
 * '<S4>'   : 'IR_Controller/LatPidCtrl/D Gain'
 * '<S5>'   : 'IR_Controller/LatPidCtrl/Filter'
 * '<S6>'   : 'IR_Controller/LatPidCtrl/Filter ICs'
 * '<S7>'   : 'IR_Controller/LatPidCtrl/I Gain'
 * '<S8>'   : 'IR_Controller/LatPidCtrl/Ideal P Gain'
 * '<S9>'   : 'IR_Controller/LatPidCtrl/Ideal P Gain Fdbk'
 * '<S10>'  : 'IR_Controller/LatPidCtrl/Integrator'
 * '<S11>'  : 'IR_Controller/LatPidCtrl/Integrator ICs'
 * '<S12>'  : 'IR_Controller/LatPidCtrl/N Copy'
 * '<S13>'  : 'IR_Controller/LatPidCtrl/N Gain'
 * '<S14>'  : 'IR_Controller/LatPidCtrl/P Copy'
 * '<S15>'  : 'IR_Controller/LatPidCtrl/Parallel P Gain'
 * '<S16>'  : 'IR_Controller/LatPidCtrl/Reset Signal'
 * '<S17>'  : 'IR_Controller/LatPidCtrl/Saturation'
 * '<S18>'  : 'IR_Controller/LatPidCtrl/Saturation Fdbk'
 * '<S19>'  : 'IR_Controller/LatPidCtrl/Sum'
 * '<S20>'  : 'IR_Controller/LatPidCtrl/Sum Fdbk'
 * '<S21>'  : 'IR_Controller/LatPidCtrl/Tracking Mode'
 * '<S22>'  : 'IR_Controller/LatPidCtrl/Tracking Mode Sum'
 * '<S23>'  : 'IR_Controller/LatPidCtrl/postSat Signal'
 * '<S24>'  : 'IR_Controller/LatPidCtrl/preSat Signal'
 * '<S25>'  : 'IR_Controller/LatPidCtrl/Anti-windup/Passthrough'
 * '<S26>'  : 'IR_Controller/LatPidCtrl/D Gain/Internal Parameters'
 * '<S27>'  : 'IR_Controller/LatPidCtrl/Filter/Differentiator'
 * '<S28>'  : 'IR_Controller/LatPidCtrl/Filter ICs/Internal IC - Differentiator'
 * '<S29>'  : 'IR_Controller/LatPidCtrl/I Gain/Internal Parameters'
 * '<S30>'  : 'IR_Controller/LatPidCtrl/Ideal P Gain/Passthrough'
 * '<S31>'  : 'IR_Controller/LatPidCtrl/Ideal P Gain Fdbk/Disabled'
 * '<S32>'  : 'IR_Controller/LatPidCtrl/Integrator/Discrete'
 * '<S33>'  : 'IR_Controller/LatPidCtrl/Integrator ICs/Internal IC'
 * '<S34>'  : 'IR_Controller/LatPidCtrl/N Copy/Disabled wSignal Specification'
 * '<S35>'  : 'IR_Controller/LatPidCtrl/N Gain/Passthrough'
 * '<S36>'  : 'IR_Controller/LatPidCtrl/P Copy/Disabled'
 * '<S37>'  : 'IR_Controller/LatPidCtrl/Parallel P Gain/Internal Parameters'
 * '<S38>'  : 'IR_Controller/LatPidCtrl/Reset Signal/Disabled'
 * '<S39>'  : 'IR_Controller/LatPidCtrl/Saturation/Passthrough'
 * '<S40>'  : 'IR_Controller/LatPidCtrl/Saturation Fdbk/Disabled'
 * '<S41>'  : 'IR_Controller/LatPidCtrl/Sum/Sum_PID'
 * '<S42>'  : 'IR_Controller/LatPidCtrl/Sum Fdbk/Disabled'
 * '<S43>'  : 'IR_Controller/LatPidCtrl/Tracking Mode/Disabled'
 * '<S44>'  : 'IR_Controller/LatPidCtrl/Tracking Mode Sum/Passthrough'
 * '<S45>'  : 'IR_Controller/LatPidCtrl/postSat Signal/Forward_Path'
 * '<S46>'  : 'IR_Controller/LatPidCtrl/preSat Signal/Forward_Path'
 * '<S47>'  : 'IR_Controller/LongiPidCtrl/Anti-windup'
 * '<S48>'  : 'IR_Controller/LongiPidCtrl/D Gain'
 * '<S49>'  : 'IR_Controller/LongiPidCtrl/Filter'
 * '<S50>'  : 'IR_Controller/LongiPidCtrl/Filter ICs'
 * '<S51>'  : 'IR_Controller/LongiPidCtrl/I Gain'
 * '<S52>'  : 'IR_Controller/LongiPidCtrl/Ideal P Gain'
 * '<S53>'  : 'IR_Controller/LongiPidCtrl/Ideal P Gain Fdbk'
 * '<S54>'  : 'IR_Controller/LongiPidCtrl/Integrator'
 * '<S55>'  : 'IR_Controller/LongiPidCtrl/Integrator ICs'
 * '<S56>'  : 'IR_Controller/LongiPidCtrl/N Copy'
 * '<S57>'  : 'IR_Controller/LongiPidCtrl/N Gain'
 * '<S58>'  : 'IR_Controller/LongiPidCtrl/P Copy'
 * '<S59>'  : 'IR_Controller/LongiPidCtrl/Parallel P Gain'
 * '<S60>'  : 'IR_Controller/LongiPidCtrl/Reset Signal'
 * '<S61>'  : 'IR_Controller/LongiPidCtrl/Saturation'
 * '<S62>'  : 'IR_Controller/LongiPidCtrl/Saturation Fdbk'
 * '<S63>'  : 'IR_Controller/LongiPidCtrl/Sum'
 * '<S64>'  : 'IR_Controller/LongiPidCtrl/Sum Fdbk'
 * '<S65>'  : 'IR_Controller/LongiPidCtrl/Tracking Mode'
 * '<S66>'  : 'IR_Controller/LongiPidCtrl/Tracking Mode Sum'
 * '<S67>'  : 'IR_Controller/LongiPidCtrl/postSat Signal'
 * '<S68>'  : 'IR_Controller/LongiPidCtrl/preSat Signal'
 * '<S69>'  : 'IR_Controller/LongiPidCtrl/Anti-windup/Passthrough'
 * '<S70>'  : 'IR_Controller/LongiPidCtrl/D Gain/Internal Parameters'
 * '<S71>'  : 'IR_Controller/LongiPidCtrl/Filter/Differentiator'
 * '<S72>'  : 'IR_Controller/LongiPidCtrl/Filter ICs/Internal IC - Differentiator'
 * '<S73>'  : 'IR_Controller/LongiPidCtrl/I Gain/Internal Parameters'
 * '<S74>'  : 'IR_Controller/LongiPidCtrl/Ideal P Gain/Passthrough'
 * '<S75>'  : 'IR_Controller/LongiPidCtrl/Ideal P Gain Fdbk/Disabled'
 * '<S76>'  : 'IR_Controller/LongiPidCtrl/Integrator/Discrete'
 * '<S77>'  : 'IR_Controller/LongiPidCtrl/Integrator ICs/Internal IC'
 * '<S78>'  : 'IR_Controller/LongiPidCtrl/N Copy/Disabled wSignal Specification'
 * '<S79>'  : 'IR_Controller/LongiPidCtrl/N Gain/Passthrough'
 * '<S80>'  : 'IR_Controller/LongiPidCtrl/P Copy/Disabled'
 * '<S81>'  : 'IR_Controller/LongiPidCtrl/Parallel P Gain/Internal Parameters'
 * '<S82>'  : 'IR_Controller/LongiPidCtrl/Reset Signal/Disabled'
 * '<S83>'  : 'IR_Controller/LongiPidCtrl/Saturation/Passthrough'
 * '<S84>'  : 'IR_Controller/LongiPidCtrl/Saturation Fdbk/Disabled'
 * '<S85>'  : 'IR_Controller/LongiPidCtrl/Sum/Sum_PID'
 * '<S86>'  : 'IR_Controller/LongiPidCtrl/Sum Fdbk/Disabled'
 * '<S87>'  : 'IR_Controller/LongiPidCtrl/Tracking Mode/Disabled'
 * '<S88>'  : 'IR_Controller/LongiPidCtrl/Tracking Mode Sum/Passthrough'
 * '<S89>'  : 'IR_Controller/LongiPidCtrl/postSat Signal/Forward_Path'
 * '<S90>'  : 'IR_Controller/LongiPidCtrl/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_IR_Controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
