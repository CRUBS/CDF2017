/* description du fichier et des fonction
*  auteur lebansais yoann
*  date: 22/11/2016
*  pour le CRUBS cdf 2017
*/

#include "asservissement.h"
#include "iodefine.h"
#include "RPBRX210.h"
#include "interrupt_handlers.h"
#include "typedefine.h"



void init_echant(double t_echant){
	double post_diviseur_flot= post_diviseur *1.;	//post_diviseur passer en flottant pour le calcul
	int valeur_compteur=(int)(65535-(t_echant*clock/(pre_diviseur*post_diviseur_flot))); // calcul of the initial value of timer to have an t_echant corresponding between clock

	SYSTEM.PRCR.WORD=0xA502;
	SYSTEM.MSTPCRA.BIT.ACSE=0;
	MSTP(MTU);
	MTU0.TCR.BYTE=0x03;			//clock frequencies divise by 64
	MTU0.TMDR.BYTE=0x00;		//timer in normal mode
	MTU0.TCNT=valeur_compteur;	//initialize the value of timer
	MTU0.TIER.BYTE=0x10;		// set the interrupt but don't active the counter
	IEN(MTU0,TCIV0)=1;
	IPR(MTU0,TCIV0)=0x2;
	
	while(MTU0.TIER.BYTE!=0x10);
	SYSTEM.PRCR.WORD=0xA500;

}

void start_echant()
{
	MTU.TSTR.BIT.CST0=1;	// activation du compteur
}
