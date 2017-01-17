/* description du fichier */



#ifndef DEF_ECHANTILLONNAGE		//si la constante n'a pas été définie le fichier n'a pas été ouvert
#define DEF_ECHANTILLONNAGE		// on défini la constante



//definition des différentes flags
#define flag_over_te IR(MTU0,TCIV0)	//flag overflow timer

//definition activation/désactivation timer echantillonnage
#define echant_on MTU0.TIER.BYTE=0x10
#define echant_off MTU0.TIER.BYTE=0x00

// definition du compteur
#define reset_timer_te MTU0.TCNT=60535//donc le compteur comptera 5000 avant de déborder soit pour 32Mhz/64 10ms

void init_echant(void);		// temps échantillonnage en seconde
void start_echant(void);		// active le compteur
void asservissement(int consigne_dist,int consigne_orient,int compteur_droit,int compteur_gauche); //asservi le système
void inverser_droit(int pwm); //inverse le sens de rot du moteur droit en fonction du signe de pwm
void inverser_gauche(int pwm);//inverse le sens de rot du moteur gauche en fonction du signe de pwm
void init_variable_echant(void);// initialisation des variables

//définition des constantes du PID pour la commande en distance
#define kp_dist 2.4
#define ki_dist 0
#define kd_dist 0
//définition des constantes du PID pour la commande angulaire
#define kp_orient 1.2
#define ki_orient 0
#define kd_orient 0

//définition de toutes les variables necessaires au fonctionnement de la fonction d'asservissement
int erreur_prec_dist;int erreur_prec_orient;
int somme_erreur_dist;int somme_erreur_orient;
int PWMD;int PWMG;
int mesure_dist;
int mesure_orient;
int erreur_dist;int erreur_orient;
int delta_erreur_dist;int delta_erreur_orient;
int cmd_dist;int cmd_orient;
#endif
