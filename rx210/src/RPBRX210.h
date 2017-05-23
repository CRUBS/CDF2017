/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*******************************************************************************/
/* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.   */
/*******************************************************************************
* File Name		: rsk_defines.h
* Version 		: 1.00
* Device 		: R5F52108DFP
* Tool-Chain 	: RX Family C Compiler
* H/W Platform	: RPBRX210
* Description   : Defines for RPB Hardware
*******************************************************************************/
/*******************************************************************************
* History 		: 13.08.2011  Ver. 1.00 First Release
*******************************************************************************/
/* Multiple inclusion prevention */
#ifndef RPBRX210_H_
#define RPBRX210_H_

/******************************************************************************
   Specify the desired CPU operation mode
   The options are:
    ---------------------------------------------------------------------------
    CPU_MIN
    ---------------------------------------------------------------------------
    Peripheral clock supply : STOP
    Clock Divider           : FCLK : ICLK : BCLK : PCLKB : PCLKD  
     (n: clock source freq)     64 : n    : 64   : 64    : 64      
    CPU operation           : NOP-LOOP 
    Peripheral function     : stop

    ---------------------------------------------------------------------------
    CPU_TYP
    ---------------------------------------------------------------------------
    Peripheral clock supply : Supply to all peripheral
    Clock divider           : FCLK : ICLK : BCLK : PCLKB : PCLKD 
     (n: clock source freq)     2n : n    : 2n   : 2n    : n       
    CPU operation           : NOP-LOOP 
    Peripheral function     : stop
       
    ---------------------------------------------------------------------------
    CPU_MAX
    ---------------------------------------------------------------------------
    Peripheral clock supply : Supply to all peripheral
    Clock divider           : FCLK : ICLK : BCLK : PCLKB : PCLKD 
     (n: clock source freq)     2n : n : 2n : 2n : n               
    CPU operation           : MUL operation - LOOP, DMAC operation 
    Peripheral function     : CMT / MTU2 - all ch operating    

******************************************************************************/

/* LED2 Port Direction Register */
#define        LED2_PDR    PORT1.PDR.BIT.B5
/* LED1 Port Direction Register */
#define        LED1_PDR    PORT1.PDR.BIT.B6
/* LED0 Port Direction Register */
#define        LED0_PDR    PORT1.PDR.BIT.B7

/* LED2 Port Output Data Registers */
#define        LED2        PORT1.PODR.BIT.B5
/* LED1 Port Output Data Registers */
#define        LED1        PORT1.PODR.BIT.B6
/* LED0 Port Output Data Registers */
#define        LED0        PORT1.PODR.BIT.B7

/* Switch LED2 on macro */
#define LED2_ON        PORT1.PODR.BIT.B5 = 0
/* Switch LED2 off macro */
#define LED2_OFF    PORT1.PODR.BIT.B5 = 1
/* Switch LED1 on macro */
#define LED1_ON        PORT1.PODR.BIT.B6 = 0
/* Switch LED1 off macro */
#define LED1_OFF    PORT1.PODR.BIT.B6 = 1
/* Switch LED0 on macro */
#define LED0_ON        PORT1.PODR.BIT.B7 = 0
/* Switch LED0 off macro */
#define LED0_OFF    PORT1.PODR.BIT.B7 = 1

/* LED0 Bit Mask Value */
#define LED0Mask    0x01
/* LED1 Bit Mask Value */
#define LED1Mask    0x02
/* LED2 Bit Mask Value */
#define LED2Mask    0x04

/* Port Direction define: Output */
#define     OUTPUT      1
/* Port Direction define: Input */
#define     INPUT       0

/* Switch Input Port define: Not pressed */
#define     NOT_PRESSED 1
/* Switch Input Port define: Pressed */
#define     PRESSED     0

/* Set LED and IIC ports as inputs */
#define PORTS_OFF   PORT1.PODR.BIT.B2 = 1;\
                    PORT1.PODR.BIT.B3 = 1;\
                    PORT1.PODR.BIT.B4 = 1;\
                    PORT1.PODR.BIT.B5 = 1;\
                    PORT1.PODR.BIT.B6 = 1;\
                    PORT1.PODR.BIT.B7 = 1;
                    
/* Switch Port Direction Registers */
#define        SW1_PDR        PORT3.PDR.BIT.B1

/* Switch Port Input Data Registers */
#define        SW1               PORT3.PIDR.BIT.B1
#define        SW_RMZ_ODO        PORTC.PIDR.BIT.B2
#define        SW_INIT_ROBOT     PORTC.PIDR.BIT.B3
#define        SW_RUN            PORTC.PIDR.BIT.B4
#define        SW_AU             PORTC.PIDR.BIT.B5
#define        INT_DETECT        PORTC.PIDR.BIT.B6

/*  LED on the big robot */
#define         LED_ASSERV       PORT5.PODR.BIT.B0
#define         LED_R1           PORT5.PODR.BIT.B1
#define         LED_R2           PORT5.PODR.BIT.B2
#define         LED_R3           PORT5.PODR.BIT.B3
#define         LED_RUN          PORT5.PODR.BIT.B4
/*  LED to display time */
#define         LED_T1
/* Main menu options enumeration */
enum enum_Main_Menu
{
    RTC_MENU   = 0,
    SUB_32k    = 1,
    LOCO_125k  = 2,
    HOCO_1M    = 3,
    HOCO_50M   = 4,
    SW_SLEEP   = 5,
    SW_STBY    = 6,
    SW_DP_STBY = 7,
};

/* Real Time Clock menu options enumeration */
enum enum_RTC_Options_Menu
{
    OUTPUT_RTC = 1,
    RESET_RTC  = 2,
    START_RTC  = 3,
    STOP_RTC   = 4
};

/* CPU Load menu options enumeration */
enum enum_CPU_Options_Menu
{
    CPU_MIN = 1,
    CPU_TYP = 2,
    CPU_MAX = 3
};

/* End of multiple inclusion prevention macro */
#endif 

/* End of file */
