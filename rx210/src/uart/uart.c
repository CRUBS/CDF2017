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
volatile uart uart9 ={0,0,0,0,0,0,0};
/******************************************************************************
* Function Name	:uart9_init 
* Description	: initialise la communication de l'uart n°9 a 115200 bauds 
* Arguments     : none
* Return value	: none
*******************************************************************************/
void uart9_init()
{
	int i=0;
	SYSTEM.PRCR.WORD=0xA502;	//unlock protection
	SYSTEM.MSTPCRA.BIT.ACSE=0;	//clear ACSE bit (all-module clock stop mode enable
	MSTP(SCI9)=0;			// cancel state of SCI5 peripheral to enable writing
	SYSTEM.PRCR.WORD=0xA500;	// relocking

//mise à 0 du registre de gestion de l'uart
	SCI9.SCR.BYTE=0x00;		// unable TIE, RXI, TX, RX and set cke to internal

//decla des ports	
	MPC.PB7PFS.BYTE=0x0A;		// port7 en uart TX
	PORTB.PMR.BIT.B7=1;
	PORTB.PDR.BIT.B7=1;
	
	SCI9.SIMR1.BIT.IICM=0;		//clear to use uart
	SCI9.SPMR.BYTE=0xC0;		// clock polarity not invert

	SCI9.SMR.BYTE=0x00;		//b[0:1] =0b00 . pclk/1
					//b2 no multiprocess mode
					//b3 1 stop bit
					//b4,b5 no parity
					//b6 8 bits data
					//b7 asynchrone mode
	SCI9.SCMR.BYTE=0;		//b0 serial communication interface mode

					//b1 should be xrite at 1
					//b2 no invert data 
					//b3 MSB send first
					//b[4:6] should be write at 1
					// BCP2 =1 to have clock diviser 32
	SCI9.SEMR.BIT.ABCS=1;		// pour division par 32 de BRR
	SCI9.BRR=207;			// 9600 pour le moment 
					// set a transmission at 80kBds
	for(i=0;i<200;i++){}	//attente pour s'assurer de la bonne mise en place des paramètres
	SCI9.SCR.BYTE=0b11000000;		//b0,b1 internal clock select
					//b2 transmit end interrupt enable
					//b3 multipro unable
					//b4 reception enable
					//b5 transmission enable
					//b6 recept interrupt enable
					//b7 transmission interrupt enable


	IR(SCI9,RXI9)=0;		//on efface le flag rxi
	IR(SCI9,TXI9)=0;		//on efface le flag txi
//maintenant on gère les priorités
	IPR(SCI9,RXI9)=0x1;		// faible priorité
	IPR(SCI9,TXI9)=0x1;		// faible priorité
}


/******************************************************************************
* Description	: fonction qui gère l'envoi de charactère sur l'uart
		  elle utilise une liste tampon pour envoyer des chaine
* Arguments     : char pointeur et tableau de char à envoyer
* Return value	: rien
*******************************************************************************/

int uart_put_char(char message)
{
	LED0=~LED0;
	if(uart9.wait_index>=sizeof(uart9.out_data) && uart9.send_index==0) {return 1;}	// on tcheque l'overflow et gestion circulaire des data

	if(uart9.busy==1)					//si uart occupé on pousse la file d'attente FIFO
	{
		if(uart9.wait_index>=100)//sizeof(uart9.out_data))
		 {
			uart9.wait_index=0;					// on tcheque l'overflow et gestion circulaire des data
		}
		uart9.out_data[uart9.wait_index]=message;			// transfert
		uart9.wait_index++;
		uart9.load++;							//incrémente la file d'attente
	}
	else						//si jamais l'uart est libre on envoie
	{
		uart9.busy=1;					//c'est occupé (WC joke)	
		SCI9.SCR.BIT.TE=1;			// on active la transmission
		SCI9.TDR=message;			//on envoi les datas
		SCI9.SCR.BIT.TIE=1;
		IEN(SCI9,TXI9)=1;			//activation des interruptions de transmission
		LED0_ON;
	}
	SCI9.SCR.BIT.TE=1;				// on active la transmission
	IEN(SCI9,TXI9)=1;	 			//activation des interruptions de transmission
	return 0;
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
void Excep_SCI9_TXI9(void) 
{

	if(!uart9.load)
	{
		IEN(SCI9,TXI9)=0;						//interruption transmission off
		SCI9.SCR.BIT.TIE=0;						//interruption transmission off
		uart9.busy=0;
		LED1_OFF;
		LED2_OFF;
	}
	else
	{
		if(uart9.send_index>=100)//sizeof(uart9.out_data))
		{
			uart9.send_index=0;
		}	//gestion circulaire de la liste d'envoi
		SCI9.TDR=uart9.send_index+48;//out_data[uart9.send_index];			//on envoie
		uart9.send_index++;						//on incrémente 
		uart9.load--;								//on décharge
		uart9.busy=1;
		LED1_ON;
	}
	IR(SCI9,TXI9)=0;						//on efface le flag

}

// SCI9 TEI9
void Excep_SCI9_TEI9(void) 
{
}
