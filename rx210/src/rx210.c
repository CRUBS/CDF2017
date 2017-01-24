﻿/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  rx210                                  */
/*      FILE         :  rx210.c                                */
/*      DESCRIPTION  :  Main Program                           */
/*      CPU SERIES   :  RX200                                  */
/*      CPU TYPE     :  RX210                                  */
/*                                                             */
/*      This file is generated by e2 studio.                   */
/*                                                             */
/***************************************************************/                                
                                                                           
                                                                           
/************************************************************************/
/*    File Version: V1.00                                               */
/*    Date Generated: 08/07/2013                                        */
/************************************************************************/

#include "iodefine.h"
#include "RPBRX210.h"
#include "decoder_quadra.h"
#include "pwm_asser_RX210.h"
#include "asservissement.h"
#include "uart.h"

#ifdef CPPAPP
//Initialize global constructors
extern "C" void __main()
{
  static int initialized;
  if (! initialized)
    {
      typedef void (*pfunc) ();
      extern pfunc __ctors[];
      extern pfunc __ctors_end[];
      pfunc *p;

      initialized = 1;
      for (p = __ctors_end; p > __ctors; )
    (*--p) ();

    }
}
#endif 
//init des variables globales
int compteur=0,i = 0;
//fin init variables globales

int main(void)
{
	LED1_OFF;LED0_OFF;LED2_OFF;
	char adresse=0x03;
	int valeur= -8;
	asm volatile("SETPSW I");

	uart9_init();		//init de l'uart
	active_reception();	//active la recepetion
	uart_put_char(0x42);
	while(1)
	{
		if(SW1==0)
		{
			if(read_type()==0x0){send_int(&adresse, &valeur);}

			while(SW1==0){}
			read_type();
			for(i=0; i<100;i++){}
			send_end_transmi();
		}
	}
	return 0;
}
