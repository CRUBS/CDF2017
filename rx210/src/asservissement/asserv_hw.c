/* description du fichier et des fonction
*  auteur lebansais yoann
*  date: 22/11/2016
*  pour le CRUBS cdf 2017
*/

#include "asservissement.h"

void init_echant(){

	SYSTEM.PRCR.WORD=0xA502;
	SYSTEM.MSTPCRA.BIT.ACSE=0;
	MSTP(MTU)=0;
	MTU4.TCR.BYTE=0x03;			//clock frequencies divise by 64
	MTU4.TMDR.BYTE=0x00;		//timer in normal mode
	reset_timer_te;				//initialize the value of timer
    MTU4.TIER.BYTE=0x10;		// set the interrupt but don't active the counter

    IEN(MTU4,TCIV4)=1;
    IPR(MTU4,TCIV4)=13;

    while(MTU4.TIER.BYTE!=0x10);
    SYSTEM.PRCR.WORD=0xA500;

}

    /*  function to start slave */
void start_asserv()
{
	MTU.TSTR.BIT.CST4=1;	// activation du compteur
}

    /* function to stop slave */
void stop_asserv()
{
    pwm_g = 0;
    pwm_d = 0;
    INA_D = 0;
    INB_D = 0;
    INA_G = 0;
    INB_G = 0;
    /* ajouter allumage d'une LED */
}

extern char transmit_data;


/******************************************************************************
* Function Name	: init_base_temps
* Description	: timer to count at 90 sec
* Arguments     : none
* Return value	: none
*******************************************************************************/

void init_base_temps(void)
{
    match_counter = 0;
}

void start_match(void)
{
    /* active interruption of asservissement and start time counter */
    transmit_data =1 ;
    /* enable timer */
    start_asserv();
}

