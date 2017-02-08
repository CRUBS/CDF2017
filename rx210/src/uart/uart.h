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

#include <stdlib.h>
#include "iodefine.h"
#include "RPBRX210.h"
#include "interrupt_handlers.h"
#include "typedefine.h"

//ajout de tout les fichier ou il y a de la com

/*******************************************************************************
Macro definitions
*******************************************************************************/
#define char_mask 0b00
#define int_mask 0b10
#define short_mask 0b01
#define float_mask 0b11
#define sign_mask 0b100


#define int_size 5
#define short_size 3
#define char_size 2
#define float_size 5


#define out_data_size 100
#define in_data_size 100

#define NB_ADR 32
/******************************************************************************
Definition des structures
*******************************************************************************/
typedef struct uart uart;
struct uart
{
	unsigned char out_data[out_data_size];
	unsigned char in_data[in_data_size];
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
void send_float(char* adresse,float* value);	// send a float 
void send_end_transmi();

//recieve function
void adress_table(char *adr,void *value);
void init_hachage();
void copy_part_tab(char nombre,char *tab1,char *index, char size_tab1, char *tab2);
char checksum(char *tab,char size);

int read_uart();
void read_int(char *trame, int *value);
void read_sht(char *trame,short *value);
void read_flt(char *trame,float *value);

#endif
