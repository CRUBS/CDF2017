/*******************************************************************************		
				DESCRIPTION 

*******************************************************************************/
/*******************************************************************************
* Autor			: leconte mickael & lebansais yoann	
*
* File Name		: odometrie.h
* Version 		: 1 
* Device 		:rx210
* Description 		: file of functions to manage odometrie
*******************************************************************************/
/*******************************************************************************
* History       : DD.MM.YYYY     Version     Description
*                 17.01.2017     Ver. 1 
*******************************************************************************/
#ifndef DEF_ODOMETRIE// multiple inclusion guard
#define DEF_ODOMETRIE

/******************************************************************************
INCLUDE
*******************************************************************************/
#include <math.h>
#include <stdlib.h>
#include "iodefine.h"
#include "RPBRX210.h"
#include "typedefine.h"
#include "interrupt_handlers.h"
#include "uart.h"
/*******************************************************************************
Macro definitions
*******************************************************************************/
#define flag_over_MTU1 IR(MTU1,TCIV1)			//flag over et underflow MTU1
#define flag_under_MTU1 IR(MTU1,TCIU1)
#define flag_over_MTU2 IR(MTU2,TCIV2)			//flag over et underflow MTU2
#define flag_under_MTU2 IR(MTU2,TCIV2)
#define sens_rot_g  MTU1.TSR.BIT.TCFD		// changement de sens de rotation MTU1
#define sens_rot_d  MTU2.TSR.BIT.TCFD		// idem MTU2

// les compteurs maintenant
#define compteur_d MTU1.TCNT		//compteur MTU1
#define compteur_g MTU2.TCNT		//compteur MTU2
#define INIT_COD	0x8000			//reset value of codeur register

/*******************************************************************************
Exported global functions (to be accessed by other files)
*******************************************************************************/

// struct to define parametre en odometrie
//extern typedef struct odometrie odometrie;
struct odometrie{
// calcul in mm of the absolute position
	short x;
	short y;
// calcul in polaire mode
	int delta;	//distance
	double theta;	//angle
/* calcul with tck  */
    int dist_tck;
    int angl_tck;
};

/*******************************************************************************
*
* Function
*
*******************************************************************************/
//*********************************************************
//		ODOMETRIE
//*********************************************************
void overflow_mtu1(int *comp_d);		//function to manage the over&underflow of mtu1
void overflow_mtu2(int *comp_g);		//function to manage the over&underflow of mtu2
void transfer_position_pol(int *dist, int *angl);	//transfert the position tck
/* reset of odometrie use with switch */
void rmz_odo(void);

/**********************************************************
* 		DECODER
**********************************************************/

void	init_mtclk(void);		// fonction d'initialisation du module de comptage
void	mtclk_start(void);		// démarre le décodage en quadrature
// communication functions access
void send_codeur_g( short* left);
void send_codeur_d( short* right);
void reset_cod(void);

/**********************************************************
* 		COMMUNICATION
**********************************************************/

void send_x_pos(void);
void send_y_pos(void);
void send_delta(int *dist);

#endif
