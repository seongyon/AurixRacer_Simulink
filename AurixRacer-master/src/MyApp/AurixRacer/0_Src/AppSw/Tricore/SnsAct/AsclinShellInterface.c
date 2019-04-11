/**
 * \file AsclinShellInterface.c
 * \brief ASCLIN Shell interface demo
 *
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "AsclinShellInterface.h"
#include "SysSe/Time/Ifx_DateTime.h"
#include "IfxLldVersion.h"
#include "_Impl/IfxGlobal_cfg.h"
#include "Cpu0_Main.h"

#include "AppTaskFu.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

#undef SHELL_HELP_DESCRIPTION_TEXT
#define SHELL_HELP_DESCRIPTION_TEXT                                 \
    "     : Display command list."ENDL                              \
    "           A command followed by a question mark '?' will"ENDL \
    "           show the command syntax"

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/
typedef struct{
	boolean enable;
	sint32	period_ms;
} linescan_t;
/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

App_AsclinShellInterface g_AsclinShellInterface; /**< \brief Demo information */
linescan_t	g_LineScan = {FALSE, 1000};
/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/

boolean AppShell_status(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_motor0vol(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_motor1vol(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_motor0en(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_srv(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_led0(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_led1(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_led2(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_linescan0(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_linescan1(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_monlinescan(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_vadcbg1(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_enc(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_port00_0(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_port00_1(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_info(pchar args, void *data, IfxStdIf_DPipe *io);

#if BOARD == APPLICATION_KIT_TC237
boolean AppShell_motor1en(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_beeperon(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_beeperfreq(pchar args, void *data, IfxStdIf_DPipe *io);
boolean AppShell_beepervol(pchar args, void *data, IfxStdIf_DPipe *io);
#elif BOARD == SHIELD_BUDDY
boolean AppShell_srvscan(pchar args, void *data, IfxStdIf_DPipe *io);
#endif



/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

#if BOARD == APPLICATION_KIT_TC237
/** \brief Application shell command list */
const Ifx_Shell_Command AppShell_commands[] = {
    {"status", "   : Show the application status", &g_AsclinShellInterface,       &AppShell_status,    },
    {"m0v", "      : Motor0Vol", &g_AsclinShellInterface,       &AppShell_motor0vol,    },
    {"m1v", "      : Motor1Vol", &g_AsclinShellInterface,       &AppShell_motor1vol,    },
    {"m0e", "      : Motor0Enable", &g_AsclinShellInterface,       &AppShell_motor0en,    },
    {"m1e", "      : Motor1Enable", &g_AsclinShellInterface,       &AppShell_motor1en,    },
    {"srv", "      : Servo Angle", &g_AsclinShellInterface,       &AppShell_srv,    },
    {"bpon", "     : Beeper On", &g_AsclinShellInterface,       &AppShell_beeperon,    },
    {"bpf", "      : Beeper Freq", &g_AsclinShellInterface,       &AppShell_beeperfreq,    },
    {"bpv", "      : Beeper Vol", &g_AsclinShellInterface,       &AppShell_beepervol,    },
    {"l108", "     : LED108", &g_AsclinShellInterface,       &AppShell_led0,    },
    {"l109", "     : LED109", &g_AsclinShellInterface,       &AppShell_led1,    },
    {"l110", "     : LED110", &g_AsclinShellInterface,       &AppShell_led2,    },
    {"ls0", "      : LineScan0", &g_AsclinShellInterface,       &AppShell_linescan0,    },
    {"ls1", "      : LineScan1", &g_AsclinShellInterface,       &AppShell_linescan1,    },
    {"mls", "      : Monitoring LineScan", &g_AsclinShellInterface,       &AppShell_monlinescan,    },
    {"vadc", "     : Vadc Backgound 1", &g_AsclinShellInterface,       &AppShell_vadcbg1,    },
    {"enc", "      : Encoder", &g_AsclinShellInterface,       &AppShell_enc,    },
    {"p00_0", "    : Port00_0", &g_AsclinShellInterface,       &AppShell_port00_0,    },
    {"p00_1", "    : Port00_1", &g_AsclinShellInterface,       &AppShell_port00_1,    },
    {"info",   "     : Show the welcome screen",   &g_AsclinShellInterface,       &AppShell_info,      },
    {"help",   SHELL_HELP_DESCRIPTION_TEXT,        &g_AsclinShellInterface.shell, &Ifx_Shell_showHelp, },
    IFX_SHELL_COMMAND_LIST_END
};
#elif BOARD == SHIELD_BUDDY
/** \brief Application shell command list */
const Ifx_Shell_Command AppShell_commands[] = {
    {"status", "   : Show the application status", &g_AsclinShellInterface,       &AppShell_status,    },
    {"m0v", "      : Motor0Vol", &g_AsclinShellInterface,       &AppShell_motor0vol,    },
    {"m0e", "      : Motor0Enable", &g_AsclinShellInterface,       &AppShell_motor0en,    },
    {"srv", "      : Servo Angle", &g_AsclinShellInterface,       &AppShell_srv,    },
    {"srvscan", "  : ServoScan Angle", &g_AsclinShellInterface,       &AppShell_srvscan,    },
    {"l0", "       : LED0", &g_AsclinShellInterface,       &AppShell_led0,    },
    {"l1", "       : LED1", &g_AsclinShellInterface,       &AppShell_led1,    },
    {"l2", "       : LED2", &g_AsclinShellInterface,       &AppShell_led2,    },
    {"ls0", "      : LineScan0", &g_AsclinShellInterface,       &AppShell_linescan0,    },
    {"ls1", "      : LineScan1", &g_AsclinShellInterface,       &AppShell_linescan1,    },
    {"mls", "      : Monitoring LineScan", &g_AsclinShellInterface,       &AppShell_monlinescan,    },
    {"vadc", "     : Vadc Backgound 1", &g_AsclinShellInterface,       &AppShell_vadcbg1,    },
    {"enc", "      : Encoder", &g_AsclinShellInterface,       &AppShell_enc,    },
    {"p00_0", "    : Port00_0", &g_AsclinShellInterface,       &AppShell_port00_0,    },
    {"p00_1", "    : Port00_1", &g_AsclinShellInterface,       &AppShell_port00_1,    },
    {"info",   "     : Show the welcome screen",   &g_AsclinShellInterface,       &AppShell_info,      },
    {"help",   SHELL_HELP_DESCRIPTION_TEXT,        &g_AsclinShellInterface.shell, &Ifx_Shell_showHelp, },
    IFX_SHELL_COMMAND_LIST_END
};

#endif



/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/
/** \addtogroup IfxLld_Demo_AsclinShellInterface_SrcDoc_Main_Interrupt
 * \{ */

/** \name Interrupts for Serial interface
 * \{ */

IFX_INTERRUPT(ISR_Asc_0_rx, 0, ISR_PRIORITY_ASC_0_RX);
IFX_INTERRUPT(ISR_Asc_0_tx, 0, ISR_PRIORITY_ASC_0_TX);
IFX_INTERRUPT(ISR_Asc_0_ex, 0, ISR_PRIORITY_ASC_0_EX);

/** \} */

/** \} */

/** \brief Handle Asc0 Rx interrupt
 *
 * \isrProvider \ref ISR_PROVIDER_ASC_0
 * \isrPriority \ref ISR_PRIORITY_ASC_0_RX
 *
 * - Configuration of this interrupt is done by Asc_If_init()
 * - This interrupt is raised each time a data have been received on the serial interface.
 *   and Asc_If_receiveIrq() will be called
 */
void ISR_Asc_0_rx(void)
{
    IfxCpu_enableInterrupts();
    IfxStdIf_DPipe_onReceive(&g_AsclinShellInterface.stdIf.asc);
}


/** \brief Handle Asc0 Tx interrupt
 *
 * \isrProvider \ref ISR_PROVIDER_ASC_0
 * \isrPriority \ref ISR_PRIORITY_ASC_0_TX
 *
 * - Configuration of this interrupt is done by Asc_If_init()
 * - This interrupt is raised each time the serial interface transmit buffer get empty
 *   and Asc_If_transmitIrq() will be called
 */
void ISR_Asc_0_tx(void)
{
    IfxCpu_enableInterrupts();
    IfxStdIf_DPipe_onTransmit(&g_AsclinShellInterface.stdIf.asc);
}


/** \brief Handle Asc0 Ex interrupt.
 *
 * \isrProvider \ref ISR_PROVIDER_ASC_0
 * \isrPriority \ref ISR_PRIORITY_ASC_0_EX
 *
 * - Configuration of this interrupt is done by Asc_If_init()
 * - This interrupt is raised each time an error occurs on the serial interface and
 *   Asc_If_errorIrq() will be called.
 */
void ISR_Asc_0_ex(void)
{
    IfxCpu_enableInterrupts();
    IfxStdIf_DPipe_onError(&g_AsclinShellInterface.stdIf.asc);
}


/** \addtogroup IfxLld_Demo_AsclinShellInterface_SrcDoc_Main_Interrupt
 * \{ */

/** Send the welcome screen to the Terminal
 *
 */
void welcomeScreen(App_AsclinShellInterface *app, IfxStdIf_DPipe *io)
{
    IfxStdIf_DPipe_print(io, ENDL ""ENDL);
    IfxStdIf_DPipe_print(io, "******************************************************************************"ENDL);
    IfxStdIf_DPipe_print(io, "*******  Welcome to Aurix Racer Shell                               *******"ENDL);
    IfxStdIf_DPipe_print(io, "******************************************************************************"ENDL);
    IfxStdIf_DPipe_print(io, "*******  Software Version Date : %4X/%2X/%2X                            *******"ENDL, app->info.srcRevDate >> 16, (app->info.srcRevDate >> 8) & 0xFF, (app->info.srcRevDate & 0xFF));
    IfxStdIf_DPipe_print(io, "*******  Software Version      : %2d.%02d                                 *******"ENDL, (app->info.srcRev >> 8) & 0xFF, (app->info.srcRev >> 0) & 0xFF);
    IfxStdIf_DPipe_print(io, "*******  iLLD version          : %d.%d.%d.%d.%d                            *******"ENDL, IFX_LLD_VERSION_GENERATION, IFX_LLD_VERSION_MAJOR, IFX_LLD_VERSION_MAJOR_UPDATE, IFX_LLD_VERSION_MINOR, IFX_LLD_VERSION_REVISION);
    IfxStdIf_DPipe_print(io, "*******  "COMPILER_NAME " Compiler         : %ld.%1dr%1d                                 *******"ENDL, (app->info.compilerVer >> 16) & 0xFF, (app->info.compilerVer >> 8) & 0xFF, (app->info.compilerVer >> 0) & 0xFF);
    IfxStdIf_DPipe_print(io, "*******  Author                : Wootaik Lee (CI-ARCLab)               *******"ENDL);
    IfxStdIf_DPipe_print(io, "******************************************************************************"ENDL);

    Ifx_DateTime rt;
    DateTime_get(&rt);
    IfxStdIf_DPipe_print(io, "Real-time: %02d:%02d:%02d"ENDL, rt.hours, rt.minutes, rt.seconds);
    IfxStdIf_DPipe_print(io, "CPU Frequency: %ld Hz"ENDL, (sint32)g_AppCpu0.info.cpuFreq);
    IfxStdIf_DPipe_print(io, "SYS Frequency: %ld Hz"ENDL, (sint32)g_AppCpu0.info.sysFreq);
    IfxStdIf_DPipe_print(io, "STM Frequency: %ld Hz"ENDL, (sint32)g_AppCpu0.info.stmFreq);
}


/** \brief Handle the 'info' command.
 *
 * \par Syntax
 * - info : Show application information */
boolean AppShell_info(pchar args, void *data, IfxStdIf_DPipe *io)
{
    App_AsclinShellInterface *app = (App_AsclinShellInterface *)data;

    welcomeScreen(app, io);
    return TRUE;
}


/** \brief Handle the 'status' command
 *
 * \par Syntax
 *  - status : Show the application internal state
 */
boolean AppShell_status(pchar args, void *data, IfxStdIf_DPipe *io)
{
#if BOARD == APPLICATION_KIT_TC237
	AppShell_motor0vol(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_motor1vol(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_motor0en(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_motor1en(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_srv(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_beeperon(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_beeperfreq(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_beepervol(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_led0(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_led1(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_led2(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_vadcbg1(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_enc(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_port00_0(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_port00_1(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
#elif BOARD == SHIELD_BUDDY
	AppShell_motor0vol(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_motor0en(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_srv(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_srvscan(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_led0(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_led1(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_led2(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_vadcbg1(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_enc(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_port00_0(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
	AppShell_port00_1(0, NULL_PTR, &g_AsclinShellInterface.stdIf.asc );
#endif

    return TRUE;
}

boolean AppShell_motor0vol(pchar args, void *data, IfxStdIf_DPipe *io)
{
	float32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : m0v frac-value"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseFloat32(&args, &vol) == TRUE){
    		IR_setMotor0Vol(vol);
    	}
    	IfxStdIf_DPipe_print(io, "  Motor0Vol: %4.2f fraction"ENDL, IR_getMotor0Vol());
    }

    return TRUE;
}

#if BOARD == APPLICATION_KIT_TC237

boolean AppShell_motor1vol(pchar args, void *data, IfxStdIf_DPipe *io)
{
	float32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : m1v frac-value"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseFloat32(&args, &vol) == TRUE){
    		IR_setMotor1Vol(vol);
    	}
    	IfxStdIf_DPipe_print(io, "  Motor1Vol: %4.2f fraction"ENDL, IR_getMotor1Vol());
    }

    return TRUE;
}
#endif

boolean AppShell_motor0en(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : m0e 0/1"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &vol) == TRUE){
    		IR_setMotor0En(vol);
    	}
    	IfxStdIf_DPipe_print(io, "  Motor0En: %4d "ENDL, IR_getMotor0En());
    }

    return TRUE;
}


boolean AppShell_srv(pchar args, void *data, IfxStdIf_DPipe *io)
{
	float32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : srv frac-value"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseFloat32(&args, &vol) == TRUE){
    		IR_setSrvAngle(vol);
    	}
    	IfxStdIf_DPipe_print(io, "  SrvAngle: %4.2f fraction"ENDL, IR_getSrvAngle());
    }

    return TRUE;
}


boolean AppShell_led0(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 led;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : l0 0/1"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &led) != FALSE){
    		IR_setLed0((boolean)led);
    	}
    	IfxStdIf_DPipe_print(io, "  Led0: %4d "ENDL, IR_getLed0());
    }

    return TRUE;
}

boolean AppShell_led1(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 led;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : l1 0/1"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &led) != FALSE){
    		IR_setLed1((boolean)led);
    	}
    	IfxStdIf_DPipe_print(io, "  Led1: %4d "ENDL, IR_getLed1());
    }

    return TRUE;
}

boolean AppShell_led2(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 led;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : l2 0/1"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &led) != FALSE){
    		IR_setLed2((boolean)led);
    	}
    	IfxStdIf_DPipe_print(io, "  Led2: %4d "ENDL, IR_getLed2());
    }

    return TRUE;
}

boolean AppShell_monlinescan(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 period_ms;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : mls period_ms"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &period_ms) != FALSE){
    		g_LineScan.period_ms = period_ms;
    		g_LineScan.enable = TRUE;
    	}else
    	{
    		g_LineScan.enable = FALSE;
    	}
    	IfxStdIf_DPipe_print(io, "  mls: %4d "ENDL, g_LineScan.period_ms);
    }

    return TRUE;
}

boolean AppShell_linescan0(pchar args, void *data, IfxStdIf_DPipe *io){
	sint32 i;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : ls0 "ENDL);
    }
    else
    {
    	IfxStdIf_DPipe_print(io, "  LineScan0 results "ENDL);
    	for(i = 0; i<127; i++){
    		IfxStdIf_DPipe_print(io, "%5d,",IR_LineScan.adcResult[0][i]);
    	}
		IfxStdIf_DPipe_print(io, "%5d"ENDL,IR_LineScan.adcResult[0][i]);
    }
    return TRUE;
}

boolean AppShell_linescan1(pchar args, void *data, IfxStdIf_DPipe *io){
	sint32 i;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : ls1 "ENDL);
    }
    else
    {
    	IfxStdIf_DPipe_print(io, "  LineScan1 results "ENDL);
    	for(i = 0; i<127; i++){
    		IfxStdIf_DPipe_print(io, "%5d,",IR_LineScan.adcResult[1][i]);
    	}
		IfxStdIf_DPipe_print(io, "%5d"ENDL,IR_LineScan.adcResult[1][i]);
    }
    return TRUE;
}

boolean AppShell_vadcbg1(pchar args, void *data, IfxStdIf_DPipe *io){
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : vadc "ENDL);
    }
    else
    {
    	IfxStdIf_DPipe_print(io, "  Vadc ");
    	IfxStdIf_DPipe_print(io, "  Ch0: %4.2f,",IR_getUsrAdcChn0());
    	IfxStdIf_DPipe_print(io, "  Ch1: %4.2f,",IR_getUsrAdcChn1());
    	IfxStdIf_DPipe_print(io, "  Ch2: %4.2f,",IR_getUsrAdcChn2());
    	IfxStdIf_DPipe_print(io, "  Ch3: %4.2f,"ENDL,IR_getUsrAdcChn3());
    }
    return TRUE;
}


boolean AppShell_enc(pchar args, void *data, IfxStdIf_DPipe *io)
{
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : enc "ENDL);
    }
    else
    {
    	IfxStdIf_DPipe_print(io, "  Encoder speed: %5d, position: %4d, direction: %1d "ENDL,
    			IR_getEncSpeed(), IR_getEncPosition(), IR_getEncDirection());
    }

    return TRUE;
}

boolean AppShell_port00_0(pchar args, void *data, IfxStdIf_DPipe *io)
{
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : p00_0 "ENDL);
    }
    else
    {
    	IfxStdIf_DPipe_print(io, "  Port00_0: %4d "ENDL, IR_getPort00_0());
    }

    return TRUE;
}

boolean AppShell_port00_1(pchar args, void *data, IfxStdIf_DPipe *io)
{
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : p00_0 "ENDL);
    }
    else
    {
    	IfxStdIf_DPipe_print(io, "  Port00_0: %4d "ENDL, IR_getPort00_1());
    }

    return TRUE;
}

#if BOARD == APPLICATION_KIT_TC237
boolean AppShell_motor1en(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : m1e 0/1"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &vol) == TRUE){
    		IR_setMotor1En(vol);
    	}
    	IfxStdIf_DPipe_print(io, "  Motor1En: %4d "ENDL, IR_getMotor1En());
    }

    return TRUE;
}

boolean AppShell_beeperon(pchar args, void *data, IfxStdIf_DPipe *io)
{
	sint32 beeper;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : bpon 0/1"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseSInt32(&args, &beeper) != FALSE){
    		IR_setBeeperOn((boolean)beeper);
    	}
    	IfxStdIf_DPipe_print(io, "  Beeper On: %4d "ENDL, IR_getBeeperOn());
    }

    return TRUE;
}

boolean AppShell_beeperfreq(pchar args, void *data, IfxStdIf_DPipe *io)
{
	float32 freq;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : bpf float-value"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseFloat32(&args, &freq) == TRUE){
    		IR_setBeeperFreq(freq);
    	}
    	IfxStdIf_DPipe_print(io, "  Beeper Freq: %7.1f "ENDL, IR_getBeeperFreq());
    }

    return TRUE;
}

boolean AppShell_beepervol(pchar args, void *data, IfxStdIf_DPipe *io)
{
	float32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : bpv frac-value"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseFloat32(&args, &vol) == TRUE){
    		IR_setBeeperVol(vol);
    	}
    	IfxStdIf_DPipe_print(io, "  Beeper Volume: %4.2f "ENDL, IR_getBeeperVol());
    }

    return TRUE;
}

#elif BOARD == SHIELD_BUDDY
boolean AppShell_srvscan(pchar args, void *data, IfxStdIf_DPipe *io)
{
	float32 vol;
	if (Ifx_Shell_matchToken(&args, "?") != FALSE)
    {
        IfxStdIf_DPipe_print(io, "  Syntax     : srvscan frac-value"ENDL);
    }
    else
    {
    	if(Ifx_Shell_parseFloat32(&args, &vol) == TRUE){
    		IR_setSrvScanAngle(vol);
    	}
    	IfxStdIf_DPipe_print(io, "  SrvScanAngle: %4.2f fraction"ENDL, IR_getSrvScanAngle());
    }

    return TRUE;
}


#endif


/** Initialise the serial interafce
 *
 */
void initSerialInterface(void)
{
    {   /** - Serial interface */
        IfxAsclin_Asc_Config config;

#if SHELL_ASCLIN == ASCLIN0
        IfxAsclin_Asc_initModuleConfig(&config, &MODULE_ASCLIN0);
#elif SHELL_ASCLIN == ASCLIN3
        IfxAsclin_Asc_initModuleConfig(&config, &MODULE_ASCLIN3);
#endif
        config.baudrate.baudrate             = CFG_ASC0_BAUDRATE;
        config.baudrate.oversampling         = IfxAsclin_OversamplingFactor_16;
        config.bitTiming.medianFilter        = IfxAsclin_SamplesPerBit_three;
        config.bitTiming.samplePointPosition = IfxAsclin_SamplePointPosition_8;
        config.interrupt.rxPriority          = ISR_PRIORITY(INTERRUPT_ASC_0_RX);
        config.interrupt.txPriority          = ISR_PRIORITY(INTERRUPT_ASC_0_TX);
        config.interrupt.erPriority          = ISR_PRIORITY(INTERRUPT_ASC_0_EX);
        config.interrupt.typeOfService       = ISR_PROVIDER_ASC_0;
        IfxAsclin_Asc_Pins ascPins = {
            .cts       = NULL_PTR,
            .ctsMode   = IfxPort_InputMode_noPullDevice,
            .rx        = &SHELL_RX,
            .rxMode    = IfxPort_InputMode_noPullDevice,
            .rts       = NULL_PTR,
            .rtsMode   = IfxPort_OutputMode_pushPull,
            .tx        = &SHELL_TX,
            .txMode    = IfxPort_OutputMode_pushPull,
            .pinDriver = IfxPort_PadDriver_cmosAutomotiveSpeed1
        };
        config.pins         = &ascPins;
        config.rxBuffer     = g_AsclinShellInterface.ascBuffer.rx;
        config.txBuffer     = g_AsclinShellInterface.ascBuffer.tx;
        config.txBufferSize = CFG_ASC0_TX_BUFFER_SIZE;
        config.rxBufferSize = CFG_ASC0_RX_BUFFER_SIZE;
        IfxAsclin_Asc_initModule(&g_AsclinShellInterface.drivers.asc, &config);

        /* Connect the standard asc interface to the device driver*/
        IfxAsclin_Asc_stdIfDPipeInit(&g_AsclinShellInterface.stdIf.asc, &g_AsclinShellInterface.drivers.asc);
    }

    /* Ifx_Console initialisation */
    Ifx_Console_init(&g_AsclinShellInterface.stdIf.asc);

    /* Assert initialisation */
    Ifx_Assert_setStandardIo(&g_AsclinShellInterface.stdIf.asc);
}


void AsclinShellInterface_init(void)
{
    /** - Initialise the time constants */
    initTime();

    /** - Initialise the serial interface and the console */
    initSerialInterface();

    g_AsclinShellInterface.info.srcRev      = SW_REVISION;
    g_AsclinShellInterface.info.srcRevDate  = SW_REVISION_DATE;
    g_AsclinShellInterface.info.compilerVer = SW_COMPILER_VERSION;

    /** - Enable the global interrupts of this CPU */
    restoreInterrupts(TRUE);

    Ifx_Console_print(ENDL);

    /** - Show the welcome screen using the standard DPipe interface */
    welcomeScreen(&g_AsclinShellInterface, &g_AsclinShellInterface.stdIf.asc);

    /** - Initialise the shell interface  */
    {
        Ifx_Shell_Config config;
        Ifx_Shell_initConfig(&config);
        config.standardIo     = &g_AsclinShellInterface.stdIf.asc;
        config.commandList[0] = &AppShell_commands[0];

        Ifx_Shell_init(&g_AsclinShellInterface.shell, &config);
    }

//    Ifx_Console_print(ENDL "Enter 'help' to see the available commands"ENDL);
}


void AsclinShellInterface_run(void)
{
    /** Handle the shell interface */
    Ifx_Shell_process(&g_AsclinShellInterface.shell);
}

void AsclinShellInterface_runLineScan(void)
{
	sint32 i;
	static sint32 cnt;

	if(g_LineScan.enable == TRUE)
	{
		cnt--;
		if(cnt < 0){
			cnt = (sint32) g_LineScan.period_ms/10;

			for(i = 0; i<128; i++){
			IfxStdIf_DPipe_print(&g_AsclinShellInterface.stdIf.asc, "%5d,%5d"ENDL,IR_LineScan.adcResult[0][i], IR_LineScan.adcResult[1][i]);
			}
		}
	}
}
