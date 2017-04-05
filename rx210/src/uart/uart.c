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
*           17.12.2016	   Ver. 1.1    reception & send ok          
*******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "uart.h"
/******************************************************************************
Macro definitions
******************************************************************************/


/*****************************************************************************
Private global variables and function
****************************************************************************/
uart uart9 ={0,0,0,0,0,0,0,0,0};
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
	MPC.PB6PFS.BYTE=0x0A;		// port6 en uart RX
	PORTB.PMR.BIT.B6 = 1;
	PORTB.PDR.BIT.B6 = 0;
	
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
	for(i=0;i<100;i++){}	//attente pour s'assurer de la bonne mise en place des paramètres
	SCI9.SCR.BYTE=0b11110000;		//b0,b1 internal clock select
					//b2 transmit end interrupt enable
					//b3 multipro unable
					//b4 reception enable
					//b5 transmission enable
					//b6 recept interrupt enable
					//b7 transmission interrupt enable


	IR(SCI9,RXI9)=0;		//on efface le flag rxi
	IR(SCI9,TXI9)=0;		//on efface le flag txi
//maintenant on gère les priorités
	IPR(SCI9,RXI9)=0x5;		// faible priorité
	IPR(SCI9,TXI9)=0x5;		// faible priorité
}


/******************************************************************************
* Description	: fonction qui gère l'envoi de charactère sur l'uart
		  elle utilise une liste tampon pour envoyer des chaine
* Arguments     : char à envoyer
* Return value	: rien
*******************************************************************************/

int uart_put_char(unsigned char message)
{
	if(uart9.wait_index>=out_data_size && uart9.send_index==0) {return 1;}	// on tcheque l'overflow et gestion circulaire des data

	if(uart9.busy==1)					//si uart occupé on pousse la file d'attente FIFO
	{
		if(uart9.wait_index>= out_data_size)
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
		SCI9.TDR=message;			//on envoi les datas
		SCI9.SCR.BIT.TIE=1;
		IEN(SCI9,TXI9)=1;			//activation des interruptions de transmission
	}
	IEN(SCI9,TXI9)=1;	 			//activation des interruptions de transmission
	return 0;
}


/******************************************************************************
* Function Name	: active reception
* Description	: place les interruption à 1 afin d'activer le reception de 
		  de données via l'uart.
* Arguments	:none
* Return value	: void
*******************************************************************************/

void active_reception(void)
{
	IR(SCI9,RXI9)=0;			//clear the flag
	IEN(SCI9,RXI9)=1;			//enable interrupt from controller
	SCI9.SCR.BIT.RIE=1;			//enable interrupt from register
}

/******************************************************************************
* Function Name	: desactive reception sur uart
* Description	: place les interruption à 0 afin de desactiver reception de 
		  de données via l'uart.
* Arguments	:none
* Return value	: void
*******************************************************************************/


void stop_reception(void)
{
	IEN(SCI9, RXI9)=0;			//unable interrupt of reception from controller
	SCI9.SCR.BIT.RIE=0;			//unable interrupt of reception from uart register
}

/******************************************************************************
* debug function
* resend what it recieve on uart
********************************************************************************/

void renvoi_le_recu(void)
{
	if(uart9.read_index>=100){uart9.read_index=0;}
	uart_put_char(uart9.in_data[uart9.read_index]);
	uart9.read_index++;
}
/******************************************************************************
* Function Name	: EXECP_SCI9_ERI9
* Description	: uart interruption to tell us reception is end
* Arguments     : 
* Return value	: 
*******************************************************************************/

// SCI9 ERI9
void Excep_SCI9_ERI9(void) {  }


/******************************************************************************
* Function Name	: interruption de reception uart9
* Description	: all in title
* Arguments	:none
* Return value	: void
*******************************************************************************/

void Excep_SCI9_RXI9(void) 
{ 
	//ici le code du busy	
	uart9.in_data[uart9.input_index]=SCI9.RDR;				//on place les données recu dans le tableau
	uart9.input_index++;							//increase the pointer
	if(uart9.input_index>= in_data_size){uart9.input_index=0;}	//gestion du recouvrement de la queu
}


/******************************************************************************
* Function Name	: interruption d'envoi via uart9
* Description	: all in title
* Arguments	:none
* Return value	: void
*******************************************************************************/

void Excep_SCI9_TXI9(void) 
{
	if(!uart9.load)
	{
		IEN(SCI9,TXI9)=0;						//interruption transmission off
		SCI9.SCR.BIT.TIE=0;						//interruption transmission off
		uart9.busy=0;
	}
	else
	{
		if(uart9.send_index>= in_data_size)
		{
			uart9.send_index=0;
		}	//gestion circulaire de la liste d'envoi
		SCI9.TDR=uart9.out_data[uart9.send_index];			//on envoie
		uart9.send_index++;						//on incrémente 
		uart9.load--;								//on décharge
		uart9.busy=1;
	}
	IR(SCI9,TXI9)=0;						//on efface le flag

}


/******************************************************************************
* Function Name	: Excep_SCI9_TEI9
* Description	: interruption end of emission
* Arguments	:none
* Return value	: void
*******************************************************************************/

void Excep_SCI9_TEI9(void) 
{
}

/******************************************************************************
* Function Name	: Excep_SCI9_TEI9
* Description	: interruption end of emission
* Arguments	:none
* Return value	: void
*******************************************************************************/
char read_step()
{
	if(uart9.in_load!=uart9.input_index)
	{
		if(uart9.in_data[uart9.in_load]==stop_byte)
		{
			if(uart9.in_load>=(in_data_size-1)){uart9.in_load=0;}
			else{uart9.in_load++;}
			return 1;
		}
		else
		{
			if(uart9.in_load>=(in_data_size-1)){uart9.in_load=0;}
			else{uart9.in_load++;}
		}
	}
	
	return 0;
}

/******************************************************************************
* Function Name	: read_type
* Description	: read the entry from uart_array and find the type to recover
			the data. after it send the value at haching table
			to call the good function
* Arguments	:none
* Return value	: int to manage error but we will see that after
*******************************************************************************/

int read_uart()
{
//	char i=0;
	char adr=0;
	char trame[int_size];

//dynamic allocation for recovery value
	int *int_recov=NULL,*temp_int=NULL;
	short *sht_recov=NULL;
	float *flt_recov=NULL;
	unsigned char *chr_recov=NULL;

//start reading here
	if(uart9.in_load)									//check if there are something in uart tab
	{
		if(uart9.in_data[uart9.read_index]==start_byte)
		{
			uart9.read_index++;							// we jump the start_byte :)
			trame[0] = uart9.in_data[uart9.read_index];
			switch(trame[0] & 0x03)
			{
				case 0:					// type char
				
					if((uart9.read_index > uart9.input_index) || (uart9.input_index-uart9.read_index >= char_size))
					{
						copy_part_tab(char_size, &uart9.in_data[0],&uart9.read_index,in_data_size, trame);
						if(checksum(trame,char_size)!= uart9.in_data[uart9.read_index]){return 1;}
						else
						{
							adr =trame[0]>>3;						//recover recipient adr
							chr_recov = malloc(sizeof(char));		//alloc
							*chr_recov = trame[1];					//take value
						}
						uart9.read_index+=2;
					}
					else {}
					break;
			
				case 1:					// type short

					if((uart9.read_index > uart9.input_index) || (uart9.input_index-uart9.read_index >=sht_size))
					{
						copy_part_tab(sht_size, &uart9.in_data[0],&uart9.read_index,in_data_size, trame);
						if(checksum(trame,sht_size)!= uart9.in_data[uart9.read_index]){
						return 1;}
						else
						{
							adr = trame[0] >>3;
							sht_recov = malloc(sizeof(short));
							read_sht(trame, sht_recov);
						}
						uart9.read_index+=2;
					}
					else {}
					break;

				case 2:					// type int
					if((uart9.read_index > uart9.input_index) || (uart9.input_index-uart9.read_index >= int_size))
					{
						copy_part_tab(int_size, &uart9.in_data[0],&uart9.read_index,in_data_size, trame);
						if(checksum(trame,int_size)!= uart9.in_data[uart9.read_index]){return 1;}
						else
						{
							adr = trame[0] >>3;		//recover recipient adresse
							int_recov = malloc(sizeof(int));	//alloc
							read_int(trame, int_recov);		//recovery
						}
						uart9.read_index+=2;
					}
					else {}
					break;

				case 3:					// type float
					if((uart9.read_index > uart9.input_index) || (uart9.input_index-uart9.read_index >=flt_size))			
					{
						copy_part_tab(flt_size,&uart9.in_data[0],&uart9.read_index,in_data_size, trame);
						if(checksum(trame,flt_size)!= uart9.in_data[uart9.read_index]){return 1;}
						else
						{
							adr = trame[0]>>3;
							flt_recov = malloc(sizeof(float));
							temp_int = malloc(sizeof(int));				//cheaper way to do this shit cause of lybrary float
							read_int(trame,temp_int);
							*flt_recov = (*temp_int)/flt_div;
						}
						uart9.read_index+=2;
					}
					else{}
					break;
			}
		
			if(int_recov!=NULL)
			{
				adress_int_table(&adr, int_recov); //call the function to this adress
				free(int_recov);			//free the memory
			}
			else if(chr_recov!=NULL)
			{
				if(*chr_recov>1){LED1=0;}//debug
				else{LED1=1;}
				if(adr==1){LED0=~LED0;}
				adress_chr_table(&adr, chr_recov);
				free(chr_recov);			//free
			}
			else if(sht_recov!=NULL)
			{
				adress_sht_table(&adr,sht_recov);
				free(sht_recov);			//free
			}
			else if(flt_recov!=NULL)
			{
				adress_flt_table(&adr, flt_recov);
				free(flt_recov);			//free
			}
		}
		else
		{
			while(uart9.read_index!=uart9.input_index && uart9.in_data[uart9.read_index]!=start_byte)
			{
				if(uart9.read_index>=(in_data_size -1)){uart9.read_index = 0;}
				else{uart9.read_index++;}

			}
		}
	}
	return 0;
}
