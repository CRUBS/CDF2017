/* Description du projet
   15/11/2016
   autor : leconte mickael
*/

#include "pwm_asser_RX210.h"
#include "iodefine.h"
#include "RPBRX210.h"
#include "typedefine.h"


// function which initialyze the PWM of motor driver
// it take a parameter which is the frequencie (between 0x0000 & 0xFFFF) of mcu speed
void PWM_asser_init( int frequence){
	MTU3.TCR.BYTE=0x20; // CCLR[2,0]=001 : cleaned by TGRA
						// CKEG[1,0]=00  : count on raise front
						// TPSC[2,0]=000 : clk/1
	MTU3.TIORH.BYTE=0x52;	// TGRA up and TGRB down the output signal
	MTU3.TIORL.BYTE=0x52;	// TGRC up and TGRD down the output signal
	MTU3.TMDR.BYTE=0x02; //MD[3,0]=0010 : pwm mode 1
	MTU3.TGRA=frequence; //définie la frequence du pwm par rapport à la fréquence du conteur
	MTU3.TGRC=frequence; //définie la frequence du pwm par rapport à la fréquence du conteur
	MTU3.TGRB=0; // duty cycle pwm 1 = 0%
	MTU3.TGRD=0; // duty cylce pwm 2 = 0%
	MTU.TSTR.BIT.CST3=1; // active la pwm


	}
