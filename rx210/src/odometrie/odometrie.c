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

/******************************************************************************
Macro definitions
******************************************************************************/
#define PERIMETRE_W 355			//perimetre de la roue 
#define TCK_TR 4096			//nb of tck by tr (codeur)
#define MAX_X 3000			//longueur de la table
#define MAX_Y 2000			//largeur de la table
#define TCK_TO_MM(tck)	tck*PERIMETRE_W/TCK_TR	//convert tck to mm

#define F_ROBOT_L 1000	//dist between the wheel of codeur
/******************************************************************************
Private global variables and functions
******************************************************************************/

volatile struct odometrie odo = {0,0,0,0};

/******************************************************************************
* Function Name	: overflow_mtu1
* Description	: treat the over under flow of mtu1
* Arguments     : none
* Return value	: none
*******************************************************************************/

void overflow_mtu1(int *compt_d)
{
	*compt_d = compteur_d - INIT_COD;			//update of variable

	if(flag_over_MTU1 && flag_under_MTU1)				// care about over and under  (oscill near to 0 and 0xffff)
	{
		if(compteur_d < 0x8000){*compt_d += 0xFFFF;}	
		else {*compt_d -= 0xFFFF;}
	}
	else if(flag_over_MTU1){*compt_d += 0xFFFF;}		//overflow
	else if(flag_under_MTU1){*compt_d -= 0xFFFF;}		//underflow
}


/******************************************************************************
* Function Name	: overflow_mtu2
* Description	: treat the over under flow of mtu1
* Arguments     : none
* Return value	: none
*******************************************************************************/

void overflow_mtu2(int *compt_g)
{
	*compt_g = compteur_g - INIT_COD;			//update of variable

	if(flag_over_MTU2 && flag_under_MTU2)				// care about over and under  (oscill near to 0 and 0xffff)
	{
		if(compteur_g < 0x8000){*compt_g += 0xFFFF;}	
		else {*compt_g -= 0xFFFF;}
	}
	else if(flag_over_MTU2){*compt_g += 0xFFFF;}		//overflow
	else if(flag_under_MTU2){*compt_g -= 0xFFFF;}		//underflow
}
/******************************************************************************
* Function Name	: send the position in tck of left/right wheel
* Description	: transfert the value of codeur_g and codeur_d 
* Arguments     : 2 int pointer
* Return value	: none
*******************************************************************************/
void transfer_position_pol(int *dist,int *angl)
{
	int recup_d,recup_g;
	overflow_mtu1(&recup_d);
	overflow_mtu2(&recup_g);
	/* ajouter el reset des decoder pck tu l'a oublié gros con*/
	/* test if we try to turn or to moving forward*/
	if(abs(recup_d-recup_g)>30)
	{
		odo.theta+=(int) asin((recup_d-recup_g)/F_ROBOT_L);
	}
	else
	{
		odo.delta+= (int) (recup_d+recup_g)/2;
	}
//	odo.x += (int)TCK_TO_MM(odo.delta*cos(odo.theta));
//	odo.y += (int)TCK_TO_MM(odo.delta*sin(odo.theta));

	*dist = odo.delta;
	*angl = odo.theta;
}
