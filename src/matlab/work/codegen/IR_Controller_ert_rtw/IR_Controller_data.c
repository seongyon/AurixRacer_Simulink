/*
 * File: IR_Controller_data.c
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

#include "IR_Controller.h"
#include "IR_Controller_private.h"

/* Block parameters (default storage) */
Parameters_IR_Controller IR_Controller_P =
{
    /* Variable: LatPid
     * Referenced by:
     *   '<S26>/Derivative Gain'
     *   '<S29>/Integral Gain'
     *   '<S37>/Proportional Gain'
     */
    {
        0.5,
        5.0,
        0.02,
        0.0
    },

    /* Variable: LongiPid
     * Referenced by:
     *   '<S70>/Derivative Gain'
     *   '<S73>/Integral Gain'
     *   '<S81>/Proportional Gain'
     */
    {
        0.1,
        1.0,
        0.004,
        0.0
    }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
