/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "display_io.h"
#include "Tft/conio_tft.h"
#include "Basic.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/


/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

/** \brief Demo init API
 *
 * This function is called from main during initialization phase
 */
void display_io_init(void)
{
    /* setup our name string */
    conio_ascii_printfxy (DISPLAY_IO0, 10, 0, (uint8 *)"<<DISPLAY INFO 0>>");

    conio_ascii_printfxy (DISPLAY_IO1, 10, 0, (uint8 *)"<<DISPLAY INFO 1>>");



}


/** \brief Demo run API
 *
 * This function is called from main, background loop
 */
void display_io_run(void)
{
    /* setup our name string */
	conio_ascii_printfxy (DISPLAY_IO1, 0,  4, (uint8 *)" Motor0En : %4d     Motor1En : %4d", IR_getMotor0En(), IR_getMotor1En());
	conio_ascii_printfxy (DISPLAY_IO1, 0,  5, (uint8 *)" Motor0Vol: %4.2f     Motor1En: %4.2f", IR_getMotor0Vol(), IR_getMotor1Vol());
	conio_ascii_printfxy (DISPLAY_IO1, 0,  6, (uint8 *)" SrvAngle : %4.2f", IR_getSrvAngle());

	conio_ascii_printfxy (DISPLAY_IO1, 0,  8, (uint8 *)" EncSpeed : %4.0f     EncPos   : %4d", IR_getEncSpeed(), IR_getEncPosition());

	conio_ascii_printfxy (DISPLAY_IO1, 0,  10, (uint8 *)" AdcChn0 : %4.2f     AdcChn1 : %4.2f", IR_getUsrAdcChn0(), IR_getUsrAdcChn1());
	conio_ascii_printfxy (DISPLAY_IO1, 0,  11, (uint8 *)" AdcChn2 : %4.2f     AdcChn3 : %4.2f", IR_getUsrAdcChn2(), IR_getUsrAdcChn3());

	conio_ascii_printfxy (DISPLAY_IO1, 0,  13, (uint8 *)" PORT00_0 : %4d     PORT00_1 : %4d", IR_getPort00_0(), IR_getPort00_1());

	conio_ascii_printfxy (DISPLAY_IO1, 0,  15, (uint8 *)" BP_Freq  : %4.0f     BP_VOL  : %4.2f", IR_getBeeperFreq(), IR_getBeeperVol());
}
