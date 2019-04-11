/*
 * File: IR_Controller.c
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
#include "Basic.h"
#include "InfineonRacer.h"

/* Block states (default storage) */
D_Work_IR_Controller IR_Controller_DWork;

/* Model step function */
void IR_Controller_step(void)
{
    real_T rtb_Lane_Offset;
    real_T rtb_ProportionalGain;
    real_T rtb_TSamp;
    int32_T rtb_PulseGenerator1;

    /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
    rtb_Lane_Offset = ((IR_Controller_DWork.clockTickCounter < 125) &&
                       (IR_Controller_DWork.clockTickCounter >= 0)) ? 100.0 :
        0.0;
    if (IR_Controller_DWork.clockTickCounter >= 249)
    {
        IR_Controller_DWork.clockTickCounter = 0;
    }
    else
    {
        IR_Controller_DWork.clockTickCounter++;
    }

    /* End of DiscretePulseGenerator: '<Root>/Pulse Generator' */

    /* Sum: '<Root>/Add' incorporates:
     *  Inport: '<Root>/EncSpd'
     */
    rtb_Lane_Offset -= IR_getEncSpeed();

    /* Gain: '<S81>/Proportional Gain' */
    rtb_ProportionalGain = IR_Controller_P.LongiPid.P * rtb_Lane_Offset;

    /* DiscreteIntegrator: '<S76>/Integrator' incorporates:
     *  Gain: '<S73>/Integral Gain'
     */
    IR_Controller_DWork.Integrator_DSTATE += (IR_Controller_P.LongiPid.I *
        rtb_Lane_Offset) * 0.02;

    /* Gain: '<S70>/Derivative Gain' */
    rtb_Lane_Offset *= IR_Controller_P.LongiPid.D;

    /* SampleTimeMath: '<S71>/TSamp'
     *
     * About '<S71>/TSamp':
     *  y = u * K where K = 1 / ( w * Ts )
     */
    rtb_TSamp = rtb_Lane_Offset * 50.0;

    /* Sum: '<S85>/Sum' incorporates:
     *  Delay: '<S71>/UD'
     *  Sum: '<S71>/Diff'
     */
    IR_setMotor0Vol((rtb_ProportionalGain +
                     IR_Controller_DWork.Integrator_DSTATE) + (rtb_TSamp -
                     IR_Controller_DWork.UD_DSTATE));

    /* Sum: '<Root>/Add2' incorporates:
     *  Inport: '<Root>/L0Margin'
     *  Inport: '<Root>/L1Margin'
     */
    rtb_Lane_Offset = IR_getLs1Margin() - IR_getLs0Margin();

    /* SampleTimeMath: '<S27>/TSamp' incorporates:
     *  Gain: '<S26>/Derivative Gain'
     *
     * About '<S27>/TSamp':
     *  y = u * K where K = 1 / ( w * Ts )
     */
    rtb_ProportionalGain = (IR_Controller_P.LatPid.D * rtb_Lane_Offset) * 50.0;

    /* Sum: '<S41>/Sum' incorporates:
     *  Delay: '<S27>/UD'
     *  DiscreteIntegrator: '<S32>/Integrator'
     *  Gain: '<S37>/Proportional Gain'
     *  Sum: '<S27>/Diff'
     */
    IR_setSrvAngle(((IR_Controller_P.LatPid.P * rtb_Lane_Offset) +
                    IR_Controller_DWork.Integrator_DSTATE_k) +
                   (rtb_ProportionalGain - IR_Controller_DWork.UD_DSTATE_j));

    /* DiscretePulseGenerator: '<Root>/Pulse Generator1' */
    rtb_PulseGenerator1 = ((IR_Controller_DWork.clockTickCounter_a < 25) &&
                           (IR_Controller_DWork.clockTickCounter_a >= 0));
    if (IR_Controller_DWork.clockTickCounter_a >= 49)
    {
        IR_Controller_DWork.clockTickCounter_a = 0;
    }
    else
    {
        IR_Controller_DWork.clockTickCounter_a++;
    }

    /* End of DiscretePulseGenerator: '<Root>/Pulse Generator1' */

    /* DataTypeConversion: '<Root>/Data Type Conversion' */
    IR_setLed0(rtb_PulseGenerator1 != 0);

    /* Update for Delay: '<S71>/UD' */
    IR_Controller_DWork.UD_DSTATE = rtb_TSamp;

    /* Update for DiscreteIntegrator: '<S32>/Integrator' incorporates:
     *  Gain: '<S29>/Integral Gain'
     */
    IR_Controller_DWork.Integrator_DSTATE_k += (IR_Controller_P.LatPid.I *
        rtb_Lane_Offset) * 0.02;

    /* Update for Delay: '<S27>/UD' */
    IR_Controller_DWork.UD_DSTATE_j = rtb_ProportionalGain;
}

/* Model initialize function */
void IR_Controller_initialize(void)
{
    /* Start for DiscretePulseGenerator: '<Root>/Pulse Generator' */
    IR_Controller_DWork.clockTickCounter = -50;

    /* ConstCode for Constant: '<Root>/Constant' */
    IR_setMotor0En(1.0);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
