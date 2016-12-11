/*******************************************************************************		
				DESCRIPTION 

*******************************************************************************/
/*******************************************************************************
* Autor			:Lebansais yo & Leconte Micki
*
* File Name		: uart.h
* Version 		:1
* Device 		:rx210
* Description 		: fichier d'en tete 
*******************************************************************************/
/*******************************************************************************
* History       : DD.MM.YYYY     Version     Description
*                 23.11.2016     Ver. 1 
*******************************************************************************/
#ifndef UART_H // multiple inclusion guard
#define UART_H

/*******************************************************************************
Macro definitions
*******************************************************************************/
/******************************************************************************
Definition des structures
*******************************************************************************/
typedef struct uart uart;
struct uart
{
	char *out_data;
	char in_data[100];
	unsigned short out_index;
	unsigned short in_index;
	unsigned short busy;
};

/*******************************************************************************
Exported global functions (to be accessed by other files)
*******************************************************************************/
void uart9_init(uart* uart9);			//fonction d'initialisation de l'uart n°9
void uart_put_char(void);//uart* uart9a);		//fonction permettant d'envoyer une trame sur l'uart 9
/*// SCI9 ERI9
void Excep_SCI9_ERI9(void) {  }

// SCI9 RXI9
void Excep_SCI9_RXI9(void) {  }

// SCI9 TXI9
void Excep_SCI9_TXI9(void) {  }

// SCI9 TEI9
void Excep_SCI9_TEI9(void) {  }


*/
#endif
