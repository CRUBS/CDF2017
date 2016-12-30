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
	unsigned char out_data[100];
	unsigned char in_data[10];
	unsigned short wait_index;
	unsigned short send_index;
	unsigned short input_index;
	unsigned short read_index;
	unsigned char busy;
	unsigned short load;
};

/*******************************************************************************
Exported global functions (to be accessed by other files)
*******************************************************************************/
void uart9_init(void);			//fonction d'initialisation de l'uart n°9
int uart_put_char(unsigned char message);	//fonction permettant d'envoyer une trame sur l'uart 9
void active_reception(void);
void renvoi_le_recu(void);

#endif
