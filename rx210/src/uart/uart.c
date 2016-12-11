/*******************************************************************************
* Autor			:Lebansais yo & Leconte Micki
*
* File Name		: uart.c
* Version 		: 1
* Device 		: rx210 
* H/W Platform	: 
* Description 	: fichier regroupant les fonctions liées à la com par l'uart
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY     Version     Description
*           23.11.2016     Ver. 1      first
*                     
*******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "iodefine.h"
#include "RPBRX210.h"
#include "interrupt_handlers.h"
#include "typedefine.h"
#include "uart.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define baud_rate 115200
#define mtclk	32000000

/*****************************************************************************
Private global variables and function
****************************************************************************/

/******************************************************************************
* Function Name	:uart9_init 
* Description	: initialise la communication de l'uart n°9 a 115200 bauds 
* Arguments     : none
* Return value	: none
*******************************************************************************/

void uart9_init(uart* uart9)
{
	int i;
	SYSTEM.PRCR.WORD=0xA502;	//unlock protection
	SYSTEM.MSTPCRA.BIT.ACSE=0;	//clear ACSE bit (all-module clock stop mode enable
	MSTP(SCI9)=0;			// cancel state of SCI9 peripheral to enable writing
	SYSTEM.PRCR.WORD=0xA500;	// relocking

	SCI9.SCR.BYTE=0x00;		// unable TIE, RXI, TX, RX and set cke to internal
	
	SCI9.SIMR1.BIT.IICM=0;		//clear to use uart
	SCI9.SPMR.BIT.CKPOL=0;		// clock polarity not invert
	SCI9.SPMR.BIT.CKPH=0;		// clock phase not invert

	SCI9.SMR.BYTE=0x00;		//b[0:1] =0b00 -> pclk/1
					//b2 no multiprocess mode
					//b3 1 stop bit
					//b4,b5 no parity
					//b6 8 bits data
					//b7 asynchrone mode
	SCI9.SCMR.BYTE=0xFC;		//b0 serial communication interface mode
					//b1 should be xrite at 1
					//b2 no invert data 
					//b3 MSB send first
					//b[4:6] should be write at 1
					// BCP2 =1 to have clock diviser 32
	SCI9.BRR=0x10;			// bps = 115200
	for(i=0;i<500;i++){}	//attente pour s'assurer de la bonne mise en place des paramètres
	SCI9.SCR.BYTE=0b11000100;		//b0,b1 internal clock select
					//b2 transmit end interrupt enable
					//b3 multipro unable
					//b4 reception enable
					//b5 transmission enable
					//b6 recept interrupt enable
					//b7 transmission interrupt enable
	SCI9.SEMR.BYTE=0x10;			// ABCS = 8 base clock cycles for 1 bit periode


	IR(SCI9,RXI9)=0;		//on efface le flag rxi
	IR(SCI9,TXI9)=0;		//on efface le flag txi
//maintenant on gère les priorités
//	IPR(SCI9,RXI9)=0x1;		// faible priorité
//	IPR(SCI9,RTI9)=0x1;		// faible priorité
// initialiser les différentes variables nécessaires
	uart9->out_data=0;
	uart9->out_index=0;		//on initialise l'index du buffer de sortie à 0
	uart9->in_index=0;		//on init l'index du buffer d'entrée à 0
	uart9->busy=0;			// on place le flag busy à 0
}


/******************************************************************************
* Function Name	: uart_put_char
* Description	: envoi un lot de 8 bit sur l'uart n°9
* Arguments     : char pointeur
* Return value	: un int quand à sa disponibilité
*******************************************************************************/

void uart_put_char(uart* uart9)
{
	//ici un code pour envoyer les donnée sur 8bits
	IEN(SCI9,TXI9)=1;		//activation des interruptions de transmission
	SCI9.SCR.BIT.TE=1;			// on active la transmission
	uart9->busy=1;
	SCI9.TDR=*(uart9->out_data);
	
}


/******************************************************************************
* Function Name	: uart_put_char
* Description	: envoi un lot de 8 bit sur l'uart n°9
* Arguments     : char pointeur
* Return value	: un int quand à sa disponibilité
*******************************************************************************/

// SCI9 ERI9
void Excep_SCI9_ERI9(void) {  }

// SCI9 RXI9
void Excep_SCI9_RXI9(void) 
{ 
	//ici le code du busy	
}


// SCI9 TXI9
void Excep_SCI9_TXI9(void) {  }

// SCI9 TEI9
void Excep_SCI9_TEI9(void) {  }


