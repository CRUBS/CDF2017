/***************************************************************/
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
<<<<<<< HEAD
=======

>>>>>>> cf78325593dc2ab124315dc74382270ad54f4720

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
int compteur=0;

int main(void)
{
	LED1_ON;LED0_OFF;LED2_OFF;
/*	mtclk_init();		// fonction d'initialisation du module de comptage
	mtclk_start();		// démarre le décodage en quadrature
	PWM_asser_init(0x03E8);
	INA_D=1;INB_D=~INA_D;
	INA_G=1;INB_G=~INA_G;
	init_echant();
<<<<<<< HEAD
	start_echant();*/
=======
	start_echant();
	uart uart9 = {0,0,0,0,0};		//crea et init var type uart
	uart9_init(&uart9);		//init de l'uart
	*(uart9.out_data)=0x35;
	uart_put_char(&uart9);
>>>>>>> cf78325593dc2ab124315dc74382270ad54f4720
	while(1){
/*
		if(compteur_g>compteur+4096||compteur_g<compteur-4096)
		{
			LED1=~LED1;
			compteur = compteur_g;
			if(sens_rot_g==1){LED0_ON;}
			else if (sens_rot_g==0){LED0_OFF;}
			}
		pwm_g=0x01F4;
		pwm_d=0x01F4;

		if (flag_over_MTU2==1){
			flag_over_MTU2=0;
			INA_D=~INA_D;
			INB_D=~INB_D;
		}
		if (flag_under_MTU2==1){
			flag_under_MTU2=0;
			INA_D=~INA_D;
			INB_D=~INB_D;
		}
		if (flag_over_MTU1==1){
			flag_over_MTU1=0;
			INA_G=~INA_G;
			INB_G=~INB_G;
		}
		if (flag_under_MTU1==1){
			flag_under_MTU1=0;
			INA_G=~INA_G;
			INB_G=~INB_G;
		}

*/
}
  return 0;
}
