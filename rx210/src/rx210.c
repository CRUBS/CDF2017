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
//#include "odometrie.h"


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


int main(void)
{
	LED1_OFF;LED0_OFF;LED2_OFF;//extinction de toutes les leds
	mtclk_init();			// fonction d'initialisation du module de comptage
	mtclk_start();			// démarre le décodage en quadrature
	PWM_asser_init(0x03E8);
	INA_D=0;INB_D=~INA_D;	//mise en marche avant par defaut
	INA_G=0;INB_G=~INA_G;	//mise en marche avant par defaut
	init_echant();
	start_echant();
	init_variable_echant();
//	odo.cmp_d=0x10;
	while(1){

	}
  return 0;
}
