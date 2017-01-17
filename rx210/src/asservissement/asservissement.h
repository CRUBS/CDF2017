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

void init_echant(void);			// Configuration des registres
void start_echant(void);		// activation du compteur
void init_variable_echant(void);// initialisation des variables
void asservissement(int consigne_dist,int consigne_orient,int compteur_droit,int compteur_gauche); // Fonction d'asservissement
void inverser_droit(int pwm); 	// inverse le sens de rot du moteur droit en fonction du signe de pwm
void inverser_gauche(int pwm);	// inverse le sens de rot du moteur gauche en fonction du signe de pwm
void deplacement(int x,int y);



typedef struct PID PID;
struct PID{
	short kp;
	short ki;
	short kd;
};
typedef struct CMD CMD;
struct CMD{
	short distance;
	short angle;
};

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
