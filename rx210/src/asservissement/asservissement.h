/* description du fichier */





#ifndef DEF_ECHANTILLONNAGE		//si la constante n'a pas été définie le fichier n'a pas été ouvert
#define DEF_ECHANTILLONNAGE		// on défini la constante



//definition des différentes flags
#define flag_over_te IR(MTU0,TCIV0)	//flag overflow timer

//definition activation/désactivation timer echantillonnage
#define echant_on MTU0.TIER.BYTE=0x10
#define echant_off MTU0.TIER.BYTE=0x00

// definition du compteur
#define compteur_timer_te MTU0.TSTR.CST0
#define valeur_compteur 60535			//donc le compteur comptera 5000 avant de déborder soit pour 32Mhz/64 10ms

void init_echant(void);		// temps échantillonnage en seconde
void start_echant(void);		// active le compteur

#endif
