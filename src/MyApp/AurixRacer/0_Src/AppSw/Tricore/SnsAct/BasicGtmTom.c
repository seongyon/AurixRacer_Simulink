/**
 * \file GtmAtomPwmHlDemo.c
 * \brief Demo GtmAtomPwmHlDemo
 *
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include <stdio.h>
#include "BasicGtmTom.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/
/** \brief Application information */
typedef struct
{
	float32           gtmFreq;
	float32           gtmGclkFreq;
	float32           gtmCmuClk0Freq; /**< \brief CMU CLK 0 frequency*/
}Basic_Gtm;

typedef struct
{
    Ifx_TimerValue    pwmPeriod;
#if BOARD == APPLICATION_KIT_TC237
    Ifx_TimerValue    tOn[2];  /**< \brief PwmHl onTime value */
#elif BOARD == SHIELD_BUDDY
    Ifx_TimerValue    tOn[3];  /**< \brief PwmHl onTime value */
#endif
    struct
    {
        IfxGtm_Tom_Timer timer;        /**< \brief Timer driver */
        IfxGtm_Tom_PwmHl pwm;
    }drivers;
}Basic_GtmTomPwmHl;

typedef struct
{
	float32 onTime; /* 0.5: -90, 1.5: 0, 2.5: +90 */
	struct
    {
        IfxGtm_Tom_Timer timerSrv;        /**< \brief Timer driver */
    }drivers;
} Basic_GtmTomSrv;

#if BOARD == APPLICATION_KIT_TC237
typedef struct
{
	boolean cmdBeeper;
	float32 cmdFrequency;
	Ifx_TimerValue cmdTriggerPoint;
	struct
    {
        IfxGtm_Tom_Timer timerBeeper;        /**< \brief Timer driver */
    }drivers;
} Basic_GtmTomBeeper;

#elif BOARD == SHIELD_BUDDY

#endif



/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/
Basic_Gtm g_Gtm;
Basic_GtmTomPwmHl g_GtmTomPwmHl; /**< \brief Demo information */
Basic_GtmTomSrv g_GtmTomSrv = {
		.onTime = 1.5
};
#if BOARD == APPLICATION_KIT_TC237
Basic_GtmTomBeeper g_GtmTomBeeper = {
		.cmdBeeper = FALSE,
		.cmdFrequency = 2048,
		.cmdTriggerPoint = 300
};
#elif BOARD == SHIELD_BUDDY
Basic_GtmTomSrv g_GtmTomSrvScan = {
		.onTime = 1.5
};
#endif

#if BOARD == APPLICATION_KIT_TC237
IR_Motor_t IR_Motor = {
		.Motor0Vol = 0.0,
		.Motor1Vol = 0.0
};
#elif BOARD == SHIELD_BUDDY
IR_Motor_t IR_Motor = {
		.Motor0Vol = 0.0,
		.Motor0VolU = 0.0,
		.Motor0VolV = 0.0,
		.Motor0VolW = 0.0
};

#endif

IR_Srv_t IR_Srv = {
		.Angle = 0.0
};

#if BOARD == APPLICATION_KIT_TC237
IR_Beeper_t IR_Beeper ={
		.On = FALSE,
		.Frequency = 2048,
		.Volume = 0.1
};
#elif BOARD == SHIELD_BUDDY
IR_Srv_t IR_SrvScan = {
		.Angle = 0.0
};
#endif

/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/
void GtmTomPwmHl_run(void);

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

void GtmTomPwmHl_initTimer(void)
{
    {   /* GTM TOM configuration */
        IfxGtm_Tom_Timer_Config timerConfig;
        IfxGtm_Tom_PwmHl_Config pwmHlConfig;

        IfxGtm_Tom_Timer_initConfig(&timerConfig, &MODULE_GTM);
        timerConfig.base.frequency                  = 10000; /*10KHz */
        timerConfig.base.minResolution              = (1.0 / timerConfig.base.frequency) / 1000;
        timerConfig.base.trigger.enabled            = FALSE;
//        timerConfig.tom                             = IfxGtm_Tom_0;
//        timerConfig.timerChannel                    = IfxGtm_Tom_Ch_8;
		timerConfig.tom                             = M_TRIGGER.tom;
		timerConfig.timerChannel                    = M_TRIGGER.channel;
        timerConfig.triggerOut						= &M_TRIGGER;
        timerConfig.clock                           = IfxGtm_Tom_Ch_ClkSrc_cmuFxclk0;

//        timerConfig.triggerOut                      = NULL_PTR;
        timerConfig.base.trigger.outputEnabled      = TRUE;
        timerConfig.base.trigger.enabled            = TRUE;
        timerConfig.base.trigger.triggerPoint       = 500;
        timerConfig.base.trigger.risingEdgeAtPeriod = TRUE;

        IfxGtm_Tom_Timer_init(&g_GtmTomPwmHl.drivers.timer, &timerConfig);

        IfxGtm_Tom_PwmHl_initConfig(&pwmHlConfig);

#if BOARD == APPLICATION_KIT_TC237
        IfxGtm_Tom_ToutMapP ccx[2], coutx[2];
        ccx[0]		= &M11_IN;
        coutx[0]	= &M12_IN;
        ccx[1]		= &M21_IN;
        coutx[1]	= &M22_IN;

        pwmHlConfig.timer                 = &g_GtmTomPwmHl.drivers.timer;
        pwmHlConfig.tom                   = timerConfig.tom;
        pwmHlConfig.base.deadtime         = 0.0;
        pwmHlConfig.base.minPulse         = 1e-6;
        pwmHlConfig.base.channelCount     = 2;
        pwmHlConfig.base.emergencyEnabled = FALSE;
        pwmHlConfig.base.outputMode       = IfxPort_OutputMode_pushPull;
        pwmHlConfig.base.outputDriver     = IfxPort_PadDriver_cmosAutomotiveSpeed1;
        pwmHlConfig.base.ccxActiveState   = Ifx_ActiveState_high;
        pwmHlConfig.base.coutxActiveState = Ifx_ActiveState_high;
        pwmHlConfig.ccx                   = ccx;
        pwmHlConfig.coutx                 = coutx;

#elif BOARD == SHIELD_BUDDY
        IfxGtm_Tom_ToutMapP ccx[3], coutx[3];
        ccx[0]		= &M_IN_UT;
        coutx[0]	= &M_IN_UB;
        ccx[1]		= &M_IN_VT;
        coutx[1]	= &M_IN_VB;
        ccx[2]		= &M_IN_WT;
        coutx[2]	= &M_IN_WB;

        pwmHlConfig.timer                 = &g_GtmTomPwmHl.drivers.timer;
        pwmHlConfig.tom                   = timerConfig.tom;
        pwmHlConfig.base.deadtime         = 0.0;
        pwmHlConfig.base.minPulse         = 1e-6;
        pwmHlConfig.base.channelCount     = 3;
        pwmHlConfig.base.emergencyEnabled = FALSE;
        pwmHlConfig.base.outputMode       = IfxPort_OutputMode_pushPull;
        pwmHlConfig.base.outputDriver     = IfxPort_PadDriver_cmosAutomotiveSpeed1;
        pwmHlConfig.base.ccxActiveState   = Ifx_ActiveState_high;
        pwmHlConfig.base.coutxActiveState = Ifx_ActiveState_high;
        pwmHlConfig.ccx                   = ccx;
        pwmHlConfig.coutx                 = coutx;
#endif

        IfxGtm_Tom_PwmHl_init(&g_GtmTomPwmHl.drivers.pwm, &pwmHlConfig);

        IfxGtm_Tom_Timer_run(&g_GtmTomPwmHl.drivers.timer);
    }

}

void GtmTomSrv_initTimer(void)
{
    {   /* GTM TOM configuration */
        IfxGtm_Tom_Timer_Config timerConfig;
        IfxGtm_Tom_Timer_initConfig(&timerConfig, &MODULE_GTM);
        timerConfig.base.frequency       = 100;
//        timerConfig.base.isrPriority     = ISR_PRIORITY(INTERRUPT_TIMER_1MS);
//        timerConfig.base.isrProvider     = ISR_PROVIDER(INTERRUPT_TIMER_1MS);
        timerConfig.base.minResolution   = (1.0 / timerConfig.base.frequency) / 1000;
        timerConfig.base.trigger.enabled = FALSE;
        timerConfig.tom                  = SRV.tom;
        timerConfig.timerChannel         = SRV.channel;
        timerConfig.clock                = IfxGtm_Tom_Ch_ClkSrc_cmuFxclk2;

        timerConfig.triggerOut                      = &SRV;
        timerConfig.base.trigger.outputEnabled      = TRUE;
        timerConfig.base.trigger.enabled            = TRUE;
        timerConfig.base.trigger.triggerPoint       = 150000/16/16; /* 1.5msec source: Fxclk1 100MHz/16 */
        timerConfig.base.trigger.risingEdgeAtPeriod = TRUE; /* Interrupt at rising edge */

        IfxGtm_Tom_Timer_init(&g_GtmTomSrv.drivers.timerSrv, &timerConfig);

        IfxGtm_Tom_Timer_run(&g_GtmTomSrv.drivers.timerSrv);
    }
}

#if BOARD == APPLICATION_KIT_TC237

sint32 GtmTomBeeper_init (void)
{
    /* initialize the beeper (2048Hz) */
	IfxGtm_Tom_Timer_Config timerConfig;

	IfxGtm_Tom_Timer_initConfig(&timerConfig, &MODULE_GTM);
	timerConfig.tom = BEEPER.tom;
	timerConfig.timerChannel = BEEPER.channel;
	timerConfig.triggerOut = &BEEPER;
	timerConfig.base.frequency = 2048;
	timerConfig.base.minResolution = 0;
    timerConfig.clock = IfxGtm_Tom_Ch_ClkSrc_cmuFxclk1;

    timerConfig.base.trigger.enabled = TRUE;
	timerConfig.base.trigger.outputEnabled = TRUE;
	timerConfig.base.trigger.outputMode = IfxPort_OutputMode_pushPull;
	timerConfig.base.trigger.outputDriver = IfxPort_PadDriver_cmosAutomotiveSpeed1;
	timerConfig.base.trigger.triggerPoint =  300;
	timerConfig.base.trigger.risingEdgeAtPeriod = TRUE;
	IfxGtm_Tom_Timer_init (&g_GtmTomBeeper.drivers.timerBeeper, &timerConfig);

	/* switch off the beeper */
	IfxPort_setPinModeInput(BEEPER.pin.port, BEEPER.pin.pinIndex, IfxPort_Mode_inputPullDown);
	/* start the 2048Hz for Beeper */
	IfxGtm_Tom_Timer_run(&g_GtmTomBeeper.drivers.timerBeeper);
	/* we don't save the driverData because no longer used (needed) */

	return (0);
}

#elif BOARD == SHIELD_BUDDY
void GtmTomSrvScan_initTimer(void)
{
    {   /* GTM TOM configuration */
        IfxGtm_Tom_Timer_Config timerConfig;
        IfxGtm_Tom_Timer_initConfig(&timerConfig, &MODULE_GTM);
        timerConfig.base.frequency       = 100;
//        timerConfig.base.isrPriority     = ISR_PRIORITY(INTERRUPT_TIMER_1MS);
//        timerConfig.base.isrProvider     = ISR_PROVIDER(INTERRUPT_TIMER_1MS);
        timerConfig.base.minResolution   = (1.0 / timerConfig.base.frequency) / 1000;
        timerConfig.base.trigger.enabled = FALSE;
        timerConfig.tom                  = SRV_SCAN.tom;
        timerConfig.timerChannel         = SRV_SCAN.channel;
        timerConfig.clock                = IfxGtm_Tom_Ch_ClkSrc_cmuFxclk2;

        timerConfig.triggerOut                      = &SRV_SCAN;
        timerConfig.base.trigger.outputEnabled      = TRUE;
        timerConfig.base.trigger.enabled            = TRUE;
        timerConfig.base.trigger.triggerPoint       = 150000/16/16; /* 1.5msec source: Fxclk1 100MHz/16 */
        timerConfig.base.trigger.risingEdgeAtPeriod = TRUE; /* Interrupt at rising edge */

        IfxGtm_Tom_Timer_init(&g_GtmTomSrvScan.drivers.timerSrv, &timerConfig);

        IfxGtm_Tom_Timer_run(&g_GtmTomSrvScan.drivers.timerSrv);
    }
}


#endif


/** \brief Demo init API
 *
 * This function is called from main during initialization phase
 */

void BasicGtmTom_init(void)
{
    /* disable interrupts */
    boolean  interruptState = IfxCpu_disableInterrupts();
	Ifx_GTM *gtm = &MODULE_GTM;

    /** - Initialise the GTM part */
    {
		/** - GTM clocks */
		g_Gtm.gtmFreq = IfxGtm_Cmu_getModuleFrequency(gtm);
		IfxGtm_enable(gtm);

		/* Set the global clock frequencies */
		IfxGtm_Cmu_setGclkFrequency(gtm, g_Gtm.gtmFreq);
		g_Gtm.gtmGclkFreq = IfxGtm_Cmu_getGclkFrequency(gtm);

		IfxGtm_Cmu_setClkFrequency(gtm, IfxGtm_Cmu_Clk_0, g_Gtm.gtmGclkFreq);
		g_Gtm.gtmCmuClk0Freq = IfxGtm_Cmu_getClkFrequency(gtm, IfxGtm_Cmu_Clk_0, TRUE);
    }

    /** - Initialise the GtmTomPwmHl part */
#if BOARD == APPLICATION_KIT_TC237
    {
    	GtmTomPwmHl_initTimer();
		g_GtmTomPwmHl.pwmPeriod =  IfxGtm_Tom_Timer_getPeriod(&g_GtmTomPwmHl.drivers.timer);
		g_GtmTomPwmHl.tOn[0] = g_GtmTomPwmHl.pwmPeriod /2;
		g_GtmTomPwmHl.tOn[1] = g_GtmTomPwmHl.pwmPeriod /2;
    }
#elif BOARD == SHIELD_BUDDY
    {
    	GtmTomPwmHl_initTimer();
		g_GtmTomPwmHl.pwmPeriod =  IfxGtm_Tom_Timer_getPeriod(&g_GtmTomPwmHl.drivers.timer);
		g_GtmTomPwmHl.tOn[0] = g_GtmTomPwmHl.pwmPeriod /2;
		g_GtmTomPwmHl.tOn[1] = g_GtmTomPwmHl.pwmPeriod /2;
		g_GtmTomPwmHl.tOn[2] = g_GtmTomPwmHl.pwmPeriod /2;
    }
#endif
    /** - Initialise the GTM part */
    {
    	GtmTomSrv_initTimer();
    }

    /** - Initialise Beeper */
    {
#if BOARD == APPLICATION_KIT_TC237
    	GtmTomBeeper_init();
#elif BOARD == SHIELD_BUDDY
    	GtmTomSrvScan_initTimer();
#endif

    }

    /* enable interrupts again */
    IfxCpu_restoreInterrupts(interruptState);

    IfxGtm_Cmu_enableClocks(gtm, IFXGTM_CMU_CLKEN_FXCLK | IFXGTM_CMU_CLKEN_CLK0);

}


/** \brief run API
 *
 * This function is called from main, background loop
 */
void GtmTomPwmHl_run(void){
	/* GtmTomPwmHl for Motor */
	IfxGtm_Tom_PwmHl *pwmHl = &g_GtmTomPwmHl.drivers.pwm;
    IfxGtm_Tom_Timer *timer = &g_GtmTomPwmHl.drivers.timer;
    Ifx_TimerValue halfPeriod = (g_GtmTomPwmHl.pwmPeriod /2);

#if BOARD == APPLICATION_KIT_TC237
    g_GtmTomPwmHl.tOn[0] =  halfPeriod + halfPeriod * IR_Motor.Motor0Vol;
    g_GtmTomPwmHl.tOn[1] =  halfPeriod - halfPeriod * IR_Motor.Motor0Vol;
#elif BOARD == SHIELD_BUDDY
    IR_Motor.Motor0VolU = IR_Motor.Motor0Vol;
    IR_Motor.Motor0VolV = -1.0 * IR_Motor.Motor0Vol;
    //IR_Motor.Motor0VolW = IR_Motor.Motor0Vol;
    g_GtmTomPwmHl.tOn[0] =  halfPeriod + halfPeriod * IR_Motor.Motor0VolU;
    g_GtmTomPwmHl.tOn[1] =  halfPeriod + halfPeriod * IR_Motor.Motor0VolV;
    //g_GtmTomPwmHl.tOn[2] =  halfPeriod + halfPeriod * IR_Motor.Motor0VolW;
#endif

    /* Set PWM duty */
	IfxGtm_Tom_PwmHl_setMode(pwmHl, Ifx_Pwm_Mode_centerAligned);
	IfxGtm_Tom_Timer_disableUpdate(timer);
	IfxGtm_Tom_PwmHl_setOnTime(pwmHl, g_GtmTomPwmHl.tOn);
	IfxGtm_Tom_Timer_applyUpdate(timer);

}

void GtmTomSrv_run(void)
{
	IfxGtm_Tom_Timer *timer = &g_GtmTomSrv.drivers.timerSrv;

	if(IR_Srv.Angle > 1.0){
		IR_Srv.Angle = 1.0;
	} else if(IR_Srv.Angle < -1.0) {
		IR_Srv.Angle = -1.0;
	}
	g_GtmTomSrv.onTime = 0.8 * IR_Srv.Angle + 1.5;
	Ifx_TimerValue triggerPoint= (g_GtmTomSrv.onTime * 100000) /16/16;
	IfxGtm_Tom_Timer_disableUpdate(timer);
	IfxGtm_Tom_Timer_setTrigger(timer, triggerPoint);
	IfxGtm_Tom_Timer_applyUpdate(timer);
}

#if BOARD == APPLICATION_KIT_TC237
void GtmTomBeeper_run(void){
	g_GtmTomBeeper.cmdBeeper = IR_Beeper.On;
	g_GtmTomBeeper.cmdFrequency = IR_Beeper.Frequency;
	g_GtmTomBeeper.cmdTriggerPoint = g_GtmTomBeeper.drivers.timerBeeper.base.period * IR_Beeper.Volume;

	IfxGtm_Tom_Timer *timer = &g_GtmTomBeeper.drivers.timerBeeper;
	if(g_GtmTomBeeper.cmdBeeper == TRUE){
		IfxGtm_Tom_Timer_disableUpdate(timer);
		IfxGtm_Tom_Timer_setFrequency(timer, g_GtmTomBeeper.cmdFrequency);
		IfxGtm_Tom_Timer_setTrigger(timer, g_GtmTomBeeper.cmdTriggerPoint);
		IfxGtm_Tom_Timer_applyUpdate(timer);
		IfxPort_setPinModeOutput(BEEPER.pin.port, BEEPER.pin.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_alt1);
	}
	else
	{
		IfxPort_setPinModeInput(BEEPER.pin.port, BEEPER.pin.pinIndex, IfxPort_Mode_inputPullDown);
	}
}


#elif BOARD == SHIELD_BUDDY
void GtmTomSrvScan_run(void)
{
	IfxGtm_Tom_Timer *timer = &g_GtmTomSrvScan.drivers.timerSrv;

	if(IR_SrvScan.Angle > 1.0){
		IR_SrvScan.Angle = 1.0;
	} else if(IR_SrvScan.Angle < -1.0) {
		IR_SrvScan.Angle = -1.0;
	}
	g_GtmTomSrvScan.onTime = 0.8 * IR_SrvScan.Angle + 1.5;
	Ifx_TimerValue triggerPoint= (g_GtmTomSrvScan.onTime * 100000) /16/16;
	IfxGtm_Tom_Timer_disableUpdate(timer);
	IfxGtm_Tom_Timer_setTrigger(timer, triggerPoint);
	IfxGtm_Tom_Timer_applyUpdate(timer);
}

#endif


void BasicGtmTom_run(void)
{
	GtmTomPwmHl_run();
	GtmTomSrv_run();
#if BOARD == APPLICATION_KIT_TC237
	GtmTomBeeper_run();
#elif BOARD == SHIELD_BUDDY
	GtmTomSrvScan_run();
#endif

}

void IR_setMotor0Vol(float32 vol){
	if(vol > 1.0){
		vol = 1.0;
	}
	else if(vol <-1.0){
		vol = -1.0;
	}
	IR_Motor.Motor0Vol = vol;
}

void IR_setSrvAngle(float32 angle){
	if(angle > 1.0){
		angle = 1.0;
	}
	else if(angle <-1.0){
		angle = -1.0;
	}
	IR_Srv.Angle = angle;
}

#if BOARD == APPLICATION_KIT_TC237
void IR_setMotor1Vol(float32 vol){
	if(vol > 1.0){
		vol = 1.0;
	}
	else if(vol <-1.0){
		vol = -1.0;
	}
	IR_Motor.Motor1Vol = vol;
}

void IR_setBeeperOn(boolean beeper){
	if(beeper != FALSE){
		beeper = TRUE;
	}
	IR_Beeper.On = beeper;
}

void IR_setBeeperFreq(float32 freq){
	if(freq > 10000.0){
		freq = 10000.0;
	}
	else if(freq <100.0){
		freq = 100.0;
	}
	IR_Beeper.Frequency = freq;
}

void IR_setBeeperVol(float32 volume){
	if(volume < 0.0){
		volume = 0.0 ;
	} else if(volume > 0.99){
		volume = 0.99 ;
	}
	IR_Beeper.Volume = volume;
}

#elif BOARD == SHIELD_BUDDY
void IR_setSrvScanAngle(float32 angle){
	if(angle > 1.0){
		angle = 1.0;
	}
	else if(angle <-1.0){
		angle = -1.0;
	}
	IR_SrvScan.Angle = angle;
}


#endif

