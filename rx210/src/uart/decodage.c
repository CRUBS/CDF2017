 /*******************************************************************************
 * Autor                 :Lebansais yo & Leconte Micki
 *
 * File Name             : decodage.c
 * Version               : 1
 * Device                : rx210 
 * H/W Platform  : 
 * Description   : fichier regroupant les fonctions liées à la com par l'uart
 *******************************************************************************/
 /*******************************************************************************
 * History : DD.MM.YYYY     Version     Description
 *           23.11.2016     Ver. 1      first
 *******************************************************************************/
 
 /******************************************************************************
 Includes   <System Includes> , "Project Includes"
 *******************************************************************************/
 #include "uart.h"
 #include "asservissement.h"
 #include "decoder_quadra.h"
 #include "odometrie.h"
 //#include "trajectory.h"
 #include "RPBRX210.h"

 /******************************************************************************
 Macro definitions
 ******************************************************************************/

 /*****************************************************************************
 Private global variables and function
 ****************************************************************************/
void (*hach_sht[NB_ADR])(short *value);
void (*hach_int[NB_ADR])(int *value);
void (*hach_flt[NB_ADR])(float *value);
void (*hach_char[NB_ADR])(char *value);

void init_hach_char()
{
	hach_char[1]=transmission_data;
}
void init_hach_int()
{
//	hach_int[1]=led_com2;
}
void init_hach_flt()
{
	hach_flt[1]=load_pd;
	hach_flt[2]=load_id;
	hach_flt[3]=load_dd;
	hach_flt[4]=send_pd;
	hach_flt[5]=send_id;
	hach_flt[6]=send_dd;
	hach_flt[7]=load_pa;
	hach_flt[8]=load_ia;
	hach_flt[9]=load_da;
	hach_flt[10]=send_pa;
	hach_flt[11]=send_ia;
	hach_flt[12]=send_da;
}
/******************************************************************************
 * Function Name :uart9_init 
 * Description   : initialise la communication de l'uart n°9 a 115200 bauds 
 * Arguments     : none
 * Return value  : none
 *******************************************************************************/
void init_hach_sht()
{
	hach_sht[1]=send_codeur_d;
	hach_sht[2]=send_codeur_g;
	hach_sht[3]=send_pilot_mg;
	hach_sht[4]=send_pilot_md;
//	hach_sht[5];
//	hach_sht[6];
	hach_sht[7]=load_dist_pid;
	hach_sht[8]=load_ang_pid;
}

/******************************************************************************
 * Function Name :uart9_init 
 * Description   : initialise la communication de l'uart n°9 a 115200 bauds 
 * Arguments     : none
 * Return value  : none
 *******************************************************************************/
void adress_chr_table(char *adr,char *value)
{
	hach_char[*adr](value);
}
/******************************************************************************
 * Function Name :uart9_init 
 * Description   : initialise la communication de l'uart n°9 a 115200 bauds 
 * Arguments     : none
 * Return value  : none
 *******************************************************************************/
void adress_sht_table(char *adr,short *value)
{
	hach_sht[*adr](value);
}
/******************************************************************************
 * Function Name :uart9_init 
 * Description   : initialise la communication de l'uart n°9 a 115200 bauds 
 * Arguments     : none
 * Return value  : none
 *******************************************************************************/
void adress_int_table(char *adr,int *value)
{
	hach_int[*adr](value);
}
/******************************************************************************
 * Function Name :uart9_init 
 * Description   : initialise la communication de l'uart n°9 a 115200 bauds 
 * Arguments     : none
 * Return value  : none
 *******************************************************************************/
void adress_flt_table(char *adr,float *value)
{
	hach_flt[*adr](value);
}
/******************************************************************************
 * Function Name :uart9_init 
 * Description   : initialise la communication de l'uart n°9 a 115200 bauds 
 * Arguments     : none
 * Return value  : none
 *******************************************************************************/
void copy_part_tab(char nombre, unsigned char *tab1,unsigned char *index, char size_tab1, char *tab2)
{
	char i = 0;
	for(i = 0; i<nombre; i++)
	{
		*(tab2+ i)=*(tab1+*index);
		if((*index)+1<size_tab1){(*index)++;}
		else{*index=0;}
	}
}

/******************************************************************************
 * Function Name :uart9_init 
 * Description   : initialise la communication de l'uart n°9 a 115200 bauds 
 * Arguments     : none
 * Return value  : none
 *******************************************************************************/
char checksum(char *tab,char size)
{
	char sum=0,i = 0;
	for(i = 0; i<size;i++){sum+=*(tab+i);}
	return sum;
}

/******************************************************************************
 * Function Name :uart9_init 
 * Description   : initialise la communication de l'uart n°9 a 115200 bauds 
 * Arguments     : none
 * Return value  : none
 *******************************************************************************/
void read_int(char *trame,int *value)
{
	char sign=(trame[0] & sign_mask) >>2;			//read the signe of the int
	
	//concatenation of char to have an int
	char i =0;
	for(i = 1;i<int_size;i++)
	{
		*value <<= 8;				//start by offset 1 byte 
		*value += trame[i];			//add value
	}
	if(sign == 1){*value = -1*((*value -1)^(0xFFFFFFFE));}
}
/******************************************************************************
 * Function Name :uart9_init 
 * Description   : initialise la communication de l'uart n°9 a 115200 bauds 
 * Arguments     : none
 * Return value  : none
 *******************************************************************************/
void read_sht(char *trame,short *value)
{
	char sign =(trame[0] & sign_mask)>>2;			//read sign
	char i =0;
	for(i=1;i<sht_size;i++)
	{
		*value <<=8;					//offset
		*value += trame[i];				//conca
	}
}
/******************************************************************************
 * Function Name :uart9_init 
 * Description   : initialise la communication de l'uart n°9 a 115200 bauds 
 * Arguments     : none
 * Return value  : none
 *******************************************************************************/
void read_flt(char *trame,float *value)
{
	char sign =(trame[0] & sign_mask)>>2;			//read sign
	char i =0;
	int int_to_flt=0;

	for(i=1;i<flt_size;i++)
	{
		int_to_flt <<=8;					//offset
		int_to_flt += trame[i];				//conca
	}
	*value = int_to_flt/flt_div;
}


	
/******************************************************************************
* Function Name	: send_int
* Description	: send a var type int in 4 char on uart with the CRUBS_ll protocole
* Arguments	:pointer on adresse and pointer on value
* Return value	: void
*******************************************************************************/

void send_int(char* adresse, int *value)
{
	char byte_one = 0, signe = 0, checksum = 0;
	char byte_to_send[int_size];
	byte_one = *adresse;
	if(*value<0){signe=1;}
	byte_one=byte_one<<1;
	byte_one += signe;
	byte_one = byte_one<<2;
	byte_one += int_mask;
	
	byte_to_send[0] = byte_one;
	//cutting the int value in 4 char
	byte_to_send[1] = *value >>24;
	byte_to_send[2] = *value >>16;
	byte_to_send[3] = *value >> 8;
	byte_to_send[4] = *value;

	//send all this shit
	uart_put_char(start_byte);
	for(int i = 0; i<int_size;i++)
	{
		uart_put_char(byte_to_send[i]);
		checksum+=byte_to_send[i];
	}
	uart_put_char(checksum);
	uart_put_char(stop_byte);
	
}


/******************************************************************************
* Function Name	: send_char()
* Description	: send a char on uart by using the protocole CRUBS_ll
* Arguments	: pointeur on a variable adress and pointer on value to send
* Return value	: void
*******************************************************************************/

void send_char(char *adresse, char *value)
{
	char byte_one = 0, signe = 0,checksum = 0;			//decla de variable
	byte_one = *adresse;				//recopie de variable
	if(*value<0){signe=1;}				//test if char is signed
	byte_one=byte_one<<1;					//decalaga and add signature
	byte_one+=signe;
	byte_one= byte_one<<2;					//decalage and add type
	byte_one+=char_mask;
	checksum = byte_one + *value;			//calcul du checksum

	uart_put_char(start_byte);
	uart_put_char(byte_one);			//send adresse and type
	uart_put_char(*value);				//send the value
	uart_put_char(checksum);			//send a byte of verification
	uart_put_char(stop_byte);
}

/******************************************************************************
* Function Name	: send short with crubs_ll protocole 
* Description	: cut a short to send it byte by byte on uart
* Arguments	:char pointer on adresse, pointer on short  
* Return value	: void
*******************************************************************************/

void send_sht(char* adresse,short *value)		//verif le passage par référence d'un tableau
{
	char byte_one = 0, signe =0,checksum =0;	//declaration of var
	char to_send[sht_size];						//array to store the byte to send

	to_send[0] = *adresse;						//save the adress
	if(*value<0){signe=1;}						//save the sign
	to_send[0] = (to_send[0] <<1)+signe;			//put sign in the first byte
	to_send[0] = (to_send[0] <<2)+sht_mask;			//finish to prepare the first byte
	to_send[1]= *value >> 8;					//cut the short and put it in table
	to_send[2]= *value;							//...

	uart_put_char(start_byte);
	for(int i = 0; i<sht_size;i++)					//send
	{
		uart_put_char(to_send[i]);
		checksum+=to_send[i];
	}
	uart_put_char(checksum);					//send the checksum
	uart_put_char(stop_byte);
	

}


/******************************************************************************
* Function Name	: send float with crubs_ll protocole 
* Description	: cut a float to send it byte by byte on uart
* Arguments	:char pointer on adresse, car  
* Return value	: void
*******************************************************************************/

void send_flt(char* adresse,float *value)		//verif le passage par référence d'un tableau
{
	char signe =0,checksum =0;	//declaration of var
	char to_send[flt_size];						//array to store the byte to send
	int int_flt=0;
	to_send[0] = *adresse;						//save the adress
	if(*value<0){signe=1;}						//save the sign
	to_send[0] = (to_send[0] <<1)+signe;			//put sign in the first byte
	to_send[0] = (to_send[0] <<2)+flt_mask;			//finish to prepare the first byte

	int_flt=(int)((*value)*flt_div);							//mov into a int
	to_send[1] = int_flt >>24;
	to_send[2] = int_flt >>16;
	to_send[3] = int_flt >> 8;
	to_send[4] = int_flt;

	//send all this shit
	uart_put_char(start_byte);
	for(int i = 0; i<flt_size;i++)
	{
		uart_put_char(to_send[i]);
		checksum+=to_send[i];
	}
	uart_put_char(checksum);
	uart_put_char(stop_byte);
}


/******************************************************************************
* Function Name	: send_end_transmi()
* Description	: send the word 'end' on uart to to say at the software now transmit 
	          are over
* Arguments	:none
* Return value	: void
*******************************************************************************/

void send_end_transmi()
{
	uart_put_char('e');
	uart_put_char('n');
	uart_put_char('d');
}

