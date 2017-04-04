/************************************************************
*Fichier "header" de la gestion du décodage des codeurs en 
* quadratures pour le robot coupe de france du CRUBS
*
************************************************************
*	nom : decoder_quadra
*	auteur : lebansais yoann
*	date de création : 25/10/2016
*	MCU: RX63N carte YRDKRX63N	
*
************************************************************
* DESCRIPTION
* ce fichier permet de déclarer les différentes fonctions
* utiliser par le système de décodage en quadrature.
* 
***********************************************************/


#ifndef DEF_DECODER_QUADRA 		 // Si la constante n'a pas été définie le fichier n'a jamais été inclus
#define DEF_DECODER_QUADRA 		 // On définit la constante pour que la prochaine fois le fichier ne soit plus inclus
/*****************************************
 *  include file here
 ****************************************/
#include "iodefine.h"
#include "RPBRX210.h"
#include "interrupt_handlers.h"
#include "typedefine.h"

/***************************************
 *  definitions
 **************************************/

// les différents flags
#define flag_over_MTU1 IR(MTU1,TCIV1)			//flag over et underflow MTU1
#define flag_under_MTU1 IR(MTU1,TCIU1)
#define flag_over_MTU2 IR(MTU2,TCIV2)			//flag over et underflow MTU2
#define flag_under_MTU2 IR(MTU2,TCIV2)
#define sens_rot_g  MTU1.TSR.BIT.TCFD		// changement de sens de rotation MTU1
#define sens_rot_d  MTU2.TSR.BIT.TCFD		// idem MTU2

// les compteurs maintenant
#define compteur_d MTU1.TCNT		//compteur MTU1
#define compteur_g MTU2.TCNT		//compteur MTU2

void	init_mtclk(void);		// fonction d'initialisation du module de comptage
void	mtclk_start(void);		// démarre le décodage en quadrature
// communication functions access

void send_codeur_g(short* left);
void send_codeur_d(short* right);

#endif
