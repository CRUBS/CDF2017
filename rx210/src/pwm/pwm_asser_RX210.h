/* description of the file 
*/



#ifndef DEF_PWM_ASSER	// si la constante n'a pas été définie le fichier n'a jamais été inclus
#define DEF_PWM_ASSER	// on def la constante

#define pwm_d MTU3.TGRB //port PC1 1_J3
#define pwm_g MTU3.TGRD //port PC0 2_J3
#define INA_D PORTB.PODR.BIT.B0 // 11_J3
#define	INB_D PORTB.PODR.BIT.B1 //  9_J3
#define INA_G PORTB.PODR.BIT.B2 //  8_J3
#define INB_G PORTB.PODR.BIT.B4//  6_J3

// declaration des fonctions

void init_pwm_asser(void);//initialisation des registres
void init_pwm_funny(void);
void send_funny(void);


#endif
