/* description of the file 
*/



#ifndef DEF_PWM_ASSER	// si la constante n'a pas été définie le fichier n'a jamais été inclus

#define DEF_PWM_ASSER	// on def la constante

// declaration des fonctions

void PWM1_init(int frequence);
void PWM2_init(int frequence);
void start_pwm1(int valeur);
void start_pwm2(int valeur);

#endif
