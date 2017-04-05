/*******************************************************************************
* Autor			:Lebansais yo & Leconte Micki
*
* File Name		: decoder_com.c
* Version 		: 1
* Device 		: rx210 
* H/W Platform	: 
* Description 	: file of communication function, allow acces at data of decoder
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY     Version     Description
*           23.11.2016     Ver. 1      first
*           17.12.2016	   Ver. 1.1    reception & send ok          
*******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "decoder_quadra.h"

/******************************************************************************
Macro definitions
******************************************************************************/


/*****************************************************************************
Private global variables and function
****************************************************************************/
/***************************************************************************
* function name: send_codeur_x
* description: send the value of counter
* arguments : pointer on value where you have to put the value
*  return : none
**************************************************************************/
void send_codeur_g(unsigned short* left) {*left = compteur_g;}

void send_codeur_d(unsigned short* right) {*right = compteur_d;}
