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
#include <stdlib.h>
#include <ctype.h>
//ajout de tout les fichier ou il y a de la com

/*******************************************************************************
Macro definitions
*******************************************************************************/
#define char_mask 0b00
#define int_mask 0b10
#define sht_mask 0b01
#define flt_mask 0b11
#define sign_mask 0b100

#define start_bit 0b10100111

#define int_size 5
#define sht_size 3
#define char_size 2
#define flt_size 5


#define out_data_size 100
#define in_data_size 100

#define NB_ADR 32
#define flt_div 1000.

void led_com(short* etat);
/******************************************************************************
Definition des structures
*******************************************************************************/
typedef struct uart uart;
struct uart
{
	unsigned char out_data[out_data_size];
	unsigned char in_data[in_data_size];
	unsigned char wait_index;
	unsigned char send_index;
	unsigned char input_index;
	unsigned char read_index;
	unsigned char busy;
	unsigned char load;
	unsigned char in_load;
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
void send_flt(char* adresse,float* value);	// send a float 
void send_end_transmi();

//recieve function
void adress_chr_table(char *adr,char *value);
void adress_sht_table(char *adr,short *value);
void adress_int_table(char *adr,int *value);
void adress_flt_table(char *adr,float *value);

void init_hach_flt();
void init_hach_char();
void init_hach_int();
void init_hach_sht();

void copy_part_tab(char nombre, unsigned char *tab1,unsigned char *index, char size_tab1, char *tab2);
char checksum(char *tab,char size);

int read_uart();
char read_step();

void read_int(char *trame, int *value);
void read_sht(char *trame,short *value);
void read_flt(char *trame,float *value);

#endif
