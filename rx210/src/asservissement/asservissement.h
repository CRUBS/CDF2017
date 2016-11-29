/* description du fichier */





#ifndef DEF_ECHANTILLONNAGE		//si la constante n'a pas été définie le fichier n'a pas été ouvert
#define DEF_ECHANTILLONNAGE		// on défini la constante

#define clock 32000000			//definie la valeur de la clock dispo pour peripherical moduls
#define pre_diviseur 1			//definition du prédiviseur sur la clock
#define post_diviseur 64		//definition du post diviseur sur la clock soit un signal de 62.5 kHz en sortie et comptable sur 16 bits avec une plage de 160us à 1.04856s


//definition des différentes flags
#define flag_over_te IR(MTU0,TCIV0)	//flag overflow timer

//definition activation/désactivation timer echantillonnage
#define echant_on MTU0.TIER.BYTE=0x10
#define echant_off MTU0.TIER.BYTE=0x00

// definition du compteur
#define compteur_timer_te MTU0.TSTR.CST0

void init_echant(double t_echant);		// temps échantillonnage en seconde
void start_echant(void);		// active le compteur

#endif
