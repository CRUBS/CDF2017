/* description of the file 
*/



#ifndef DEF_PWM_ASSER	// si la constante n'a pas été définie le fichier n'a jamais été inclus

#define DEF_PWM_ASSER	// on def la constante

// declaration des fonctions
void PWM_asser_init(int frequence);
#define pwm_g MTU3.TGRB //port PC1
#define pwm_d MTU3.TGRD //port PC0
#endif
