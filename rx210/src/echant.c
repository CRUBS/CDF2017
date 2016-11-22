/* description du fichier et des fonction
*  auteur lebansais yoann
*  date: 22/11/2016
*  pour le CRUBS cdf 2017
*/

#include "echant.h"



void init_echant(int t_echant)
{
	int clock=32000000;	// clock 32 MHz of TPU
	short int pre_diviseur=8;// prediviseur of the tpu clock
	short double post_diviseur=64;	//post_diviseur of tpu clock
	int valeur_compteur=(int)(65535-(t_echant*clock/(pre_divisieur*post_diviseur)); // calcul of the initial value of timer to have an t_echant corresponding between clock
	
	TPU0.TCR.BYTE=0x03;	//clock frequencie divise by 64
	TPU0.TMDR.BYTE=0x00;	//timer in normal mode
	TPU0.TCNT=valeur_compteur;	//initialize the value of timer
	TPU0.TIER.BYTE=0x10;		// set the interrupteur but not active the counter
	//reste a faire le .h et les defines de flags et d'activation extinction d'interruption
	// plus une fonction start
	
}
