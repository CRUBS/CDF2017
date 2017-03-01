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
	MTU0.TCR.BYTE=0x03;			//clock frequencies divise by 64
	MTU0.TMDR.BYTE=0x00;		//timer in normal mode
	reset_timer_te;				//initialize the value of timer
	MTU0.TIER.BYTE=0x10;		// set the interrupt but don't active the counter
	IEN(MTU0,TCIV0)=1;
	IPR(MTU0,TCIV0)=15;

	while(MTU0.TIER.BYTE!=0x10);
	SYSTEM.PRCR.WORD=0xA500;

}

void start_echant()
{
	MTU.TSTR.BIT.CST0=1;	// activation du compteur
}

