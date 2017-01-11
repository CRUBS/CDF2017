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

#include "iodefine.h"
#include "RPBRX210.h"
#include "interrupt_handlers.h"
#include "typedefine.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/
#define char_mask 0b00
#define int_mask 0b01
#define str_mask 0b10
#define float_mask 0b11

/******************************************************************************
Definition des structures
*******************************************************************************/
typedef struct uart uart;
struct uart
{
	unsigned char out_data[100];
	unsigned char in_data[100];
	unsigned short wait_index;
	unsigned short send_index;
	unsigned short input_index;
	unsigned short read_index;
	unsigned char busy;
	unsigned short load;
	unsigned short in_load;
};

/*******************************************************************************
Exported global functions (to be accessed by other files)
*******************************************************************************/
//hardware function
void uart9_init(void);			//fonction d'initialisation de l'uart n°9
int uart_put_char(unsigned char message);	//fonction permettant d'envoyer une trame sur l'uart 9
void active_reception(void);
void renvoi_le_recu(void);

//software function
//send function
void send_int(char* adresse, int *value);		//allow to sned an int with the protocole describe in the doc
void send_char(char* adresse, char* value); 	//send a char
void send_short(char* adresse, short* value);	//send a short
void send_string(char* adresse,char text[]);	// send a text (string) 

//recieve function
char read_adresse();

#endif
