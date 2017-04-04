/*******************************************************************************
* Autor			: leconte mickael & lebansais yoann
*
* File Name		: odometrie.h
* Version 		:1
* Device 		:rx210
* H/W Platform	: 
* Description 	: file of function to manage odometrie on a robot 
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY     Version     Description
*           17.01.2017     Ver. 1      first 
*                     
*******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "odometrie.h"
#include "decoder_quadra.h"
#include "iodefine.h"
#include "RPBRX210.h"
#include "typedefine.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define p_roue 355			//perimetre de la roue 
#define max_x 3000			//longueur de la table
#define max_y 2000			//largeur de la table

/******************************************************************************
Private global variables and functions
******************************************************************************/

volatile odometrie odo = {0,0,0,0,0,0};

/******************************************************************************
* Function Name	: overflow_mtu1
* Description	: treat the over under flow of mtu1
* Arguments     : none
* Return value	: none
*******************************************************************************/

void overflow_mtu1()
{
	odo.cmp_d =odo.cmp_d & compteur_d;			//update of variable

	if(flag_over_MTU1 && flag_under_MTU1)				// care about over and under  (oscill near to 0 and 0xffff)
	{
		
		if(compteur_d < 0x8000){odo.cmp_d += 0x10000;}	
		else {odo.cmp_d -= (0xffff - compteur_d);}
	}
	else if(flag_over_MTU1){odo.cmp_d += 0x10000;}		//overflow
	else if(flag_under_MTU1){odo.cmp_d -= 0x10000;}		//underflow
}


/******************************************************************************
* Function Name	: overflow_mtu2
* Description	: treat the over under flow of mtu1
* Arguments     : none
* Return value	: none
*******************************************************************************/

void overflow_mtu2()
{
	odo.cmp_g =odo.cmp_g & compteur_g;			//update of variable

	if(flag_over_MTU2 && flag_under_MTU2)				// care about over and under  (oscill near to 0 and 0xffff)
	{
		
		if(compteur_g < 0x8000){odo.cmp_g += 0x10000;}	
		else {odo.cmp_g -= (0xffff - compteur_g);}
	}
	else if(flag_over_MTU2){odo.cmp_d += 0x10000;}		//overflow
	else if(flag_under_MTU2){odo.cmp_g -= 0x10000;}		//underflow
}
