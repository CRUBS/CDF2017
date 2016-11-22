/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  rx210                                  */
/*      FILE         :  hardware_setup.c                       */
/*      DESCRIPTION  :  Hardware Initialization                */
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
#ifdef __cplusplus
extern "C"
{
#endif
  extern void HardwareSetup (void);
#ifdef __cplusplus
}
#endif

void
HardwareSetup (void)
{
//Modification de l'horloge
SYSTEM.PRCR.WORD=0xA501; //write enable for clock register
SYSTEM.SCKCR3.BIT.CKSEL=1; //modification de la main clock ( 001 -> HOCO -> 32MHz)
SYSTEM.SCKCR.LONG=0x00000000;
SYSTEM.PRCR.WORD=0xA500; //write disable for all register


//Autoriser l'écriture des registres PFS
MPC.PWPR.BIT.B0WI=0;
MPC.PWPR.BIT.PFSWE=1;

/* Port 1 - LED1 */
PORT1.PODR.BYTE = 0x00 ;    /* */
PORT1.PMR.BYTE  = 0x00 ;    /* All GPIO for now */
MPC.P16PFS.BYTE = 0x00 ;    //
PORT1.PMR.BYTE  = 0x00 ;    // all port use in I/O
PORT1.PODR.BYTE = 0x00 ; 	// all output are low
PORT1.PDR.BYTE = 0xFF ;		// all are output

/* Port 3 - SW1 */
PORT3.PODR.BYTE = 0x00 ;    /* */
PORT3.PMR.BYTE  = 0x00 ;    /* All GPIO for now */
MPC.P31PFS.BYTE = 0x00 ;    //
PORT3.PMR.BYTE  = 0x00 ;    // all port use in I/O
PORT3.PODR.BYTE = 0x00 ; 	// all output are low
PORT3.PDR.BYTE = 0x00 ;		// all are output

/* Port A - MTCLKA & MTCLKB & MTCLKC & MTCLKD */
PORTA.PODR.BYTE = 0x00 ;    /* */
PORTA.PMR.BYTE  = 0x00 ;    /* All GPIO for now */
MPC.PA4PFS.BYTE = 0x02 ;    // port = MTCLKA (input) 16_J3
MPC.PA6PFS.BYTE = 0x02 ;	// port = MTCLKB (input) 14_J3
MPC.PA1PFS.BYTE = 0x02 ;	// port = MTCLKC (input) 19_J3
MPC.PA3PFS.BYTE = 0x02 ;	// port = MTCLKD (input) 25_J3
PORTA.PMR.BYTE  = 0b01011010 ;    // port 6 & 4 & 3 & 1 use as function
PORTA.PODR.BYTE = 0x00 ; 	// all output are low
PORTA.PDR.BYTE = 0x00 ;	// all are input

/* Port B - H driver left and right & RX/TX*/
PORTB.PODR.BYTE = 0x00 ;    /* */
PORTB.PMR.BYTE  = 0x00 ;    /* All GPIO for now */
MPC.PB0PFS.BYTE = 0x00 ;    // port = 0/1 (output)
MPC.PB1PFS.BYTE = 0x00 ;	// port = 0/1 (output)
MPC.PB2PFS.BYTE = 0x00 ;	// port = 0/1 (output)
MPC.PB3PFS.BYTE = 0x00 ;	// port = 0/1 (output)
MPC.PB6PFS.BYTE = 0x10 ;	// port = RXD9 (input)
MPC.PB7PFS.BYTE = 0x10 ;	// port = TXD9 (output)
PORTB.PMR.BYTE  = 0b011000000 ;    // port 6 & 7 use as function
PORTB.PODR.BYTE = 0x00 ; 	// all output are low
PORTB.PDR.BYTE = 0b110111111 ;	// port 6 as input rest as output

/*Port C - MTIOC3A & MTIOC3C */
PORTC.PODR.BYTE = 0x00 ;    /* */
PORTC.PMR.BYTE  = 0x00 ;    /* All GPIO for now */
MPC.PC0PFS.BYTE = 0x01 ;    // port = MTIOC3C (output)
MPC.PC1PFS.BYTE = 0x01 ;	// port = MTIOC3A (output)
PORTC.PMR.BYTE  = 0b00000011 ;    // port 0 & 1 use as function
PORTC.PODR.BYTE = 0x00 ; 	// all output are low
PORTC.PDR.BYTE = 0xFF ;	// all are output

//Fin des droits d'écriture des registres PFS
MPC.PWPR.BIT.B0WI=1;
MPC.PWPR.BIT.PFSWE=0;
}

