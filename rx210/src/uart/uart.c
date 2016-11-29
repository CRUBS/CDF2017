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

void uart9_init(void)
{
	SYSTEM.PRCR.WORD=0xA502;	//unlock protection
	SYSTEM.MSTPCRC.BIT.ACSE=0;	//clear ACSE bit (all-module clock stop mode enable
	MSTP(SCI9)=0;			// cancel state of SCI9 peripheral to enable writing
	SYSTEM.PRCR.WORD=0xA500;	// relocking

	SCI9.SCR.BYTE=0x00;		// unable TIE, RXI, TX, RX and set cke to internal
	
	SCI9.SIMR1.BIT.IICM=0;		//clear to use uart
	SCI9.SPMR.BIT.CKPA=0;		// clock polarity not invert
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
		
	

}
