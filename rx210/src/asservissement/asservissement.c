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



void init_echant(short double t_echant)
{
	short double post_diviseur_flot= post_diviseur *1.;	//post_diviseur passer en flottant pour le calcul
	int valeur_compteur=(int)(65535-(t_echant*clock/(pre_divisieur*post_diviseur_flot)); // calcul of the initial value of timer to have an t_echant corresponding between clock
	SYSTEM.PRCR.WORD=0xA502;	//unlock
	SYSTEM.MSTPCRA.BIT.MSTPA13=0;	//the module stop state in canceled	
	TPU0.TCR.BYTE=0x03;	//clock frequencie divise by 64
	TPU0.TMDR.BYTE=0x00;	//timer in normal mode
	TPU0.TCNT=valeur_compteur;	//initialize the value of timer
	TPU0.TIER.BYTE=0x10;		// set the interrupteur but not active the counter
	
	while(TPU0.TIER.BYTE!=0x10);
	SYSTEM.PRCR.WORD=0xA500;	//relock at 00
}

void start_echantillonnage()
{
	TPU0.TSTR.BIT.CST0=1;	// activation du compteur
}
