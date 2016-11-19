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
void PWM1_init( int frequence){
	MTU3.TCR.BYTE=0x48; // CCLR[2,0]=000 : cleaned by TGRA
						// CKEG[1,0]=00  : count on raise front
						// TPSC[2,0]=000 : clk/1
	MTU3.TIORH.BYTE=0x25;	// TGRA down and TGRB up the output signal
	MTU3.TMDR.BYTE=0x02; //MD[3,0]=0010 : pwm mode 1
	MTU3.TGRA=frequence; // used as the TCNT clearing source
}

void PWM2_init(int frequence){
	MTU2.TCR.BYTE=0x48; // CCLR[2,0]=000 : cleaned by TGRA
						// CKEG[1,0]=00  : count on raise front
						// TPSC[2,0]=000 : clk/1
	MTU2.TIOR.BYTE=0x25; 	// TGRA reinitialyse to 0 and TGRB put output at 1
	MTU2.TMDR.BYTE=0x02; //MD[3,0]=0010 : pwm mode 1
	MTU2.TGRA=frequence; // used as the TCNT clearing source
}

// function to start the pwm
void start_pwm1(int valeur)
{
	MTU.TSTR.BIT.CST3=0;//désactive la pwm
	if (valeur > MTU3.TGRA) valeur = MTU3.TGRA ; // tcheck if the value of 'valeur' is ok
	MTU3.TGRB = valeur; // put valeur in TGRB <=> %of pwm
	MTU.TSTR.BIT.CST3=1; // active la pwm
}


void start_pwm2(int valeur)
{
//	TPU3.TGRB=0x0F;
	MTU.TSTR.BIT.CST2=0;

}
