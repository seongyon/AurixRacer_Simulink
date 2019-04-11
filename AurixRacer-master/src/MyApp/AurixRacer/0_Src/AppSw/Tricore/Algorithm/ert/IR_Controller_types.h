/*
 * File: IR_Controller_types.h
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

#ifndef RTW_HEADER_IR_Controller_types_h_
#define RTW_HEADER_IR_Controller_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_pid_param_
#define DEFINED_TYPEDEF_FOR_pid_param_

typedef struct
{
    real_T P;
    real_T I;
    real_T D;
    real_T N;
}
pid_param;

#endif

/* Parameters (default storage) */
typedef struct Parameters_IR_Controller_ Parameters_IR_Controller;

#endif                                 /* RTW_HEADER_IR_Controller_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
