/*******************************************************************************		
				DESCRIPTION 

*******************************************************************************/
/*******************************************************************************
* Autor			: leconte mickael & lebansais yoann	
*
* File Name		: odometrie.h
* Version 		: 1 
* Device 		:rx210
* Description 		: file of functions to manage odometrie
*******************************************************************************/
/*******************************************************************************
* History       : DD.MM.YYYY     Version     Description
*                 17.01.2017     Ver. 1 
*******************************************************************************/
#ifndef DEF_ODOMETRIE// multiple inclusion guard
#define DEF_ODOMETRIE

/******************************************************************************
INCLUDE
*******************************************************************************/
/*******************************************************************************
Macro definitions
*******************************************************************************/


/*******************************************************************************
Exported global functions (to be accessed by other files)
*******************************************************************************/

// struct to define parametre en odometrie
typedef struct odometrie odometrie;
struct odometrie{
// calcul in plan mode
	short x;
	short y;
// calcul en tick 
	int cmp_g;
	int cmp_d;
// calcul in polaire mode
	int distance;
	int angle;
};

/*******************************************************************************
*
* Function
*
*******************************************************************************/

void overflow_mtu1(void);		//function to manage the over&underflow of mtu1
void overflow_mtu2(void);		//function to manage the over&underflow of mtu2
	
#endif
