/* description du fichier */



#ifndef H_DEF_ECHANTILLONNAGE		//si la constante n'a pas été définie le fichier n'a pas été ouvert
#define H_DEF_ECHANTILLONNAGE		// on défini la constante

#include "iodefine.h"
#include "RPBRX210.h"
#include "interrupt_handlers.h"
#include "typedefine.h"
#include "pwm_asser_RX210.h"
#include "uart.h"
#include "odometrie.h"
#include "math.h"

//definition des différentes flags
#define flag_over_te IR(MTU0,TCIV0)	//flag overflow timer

//definition activation/désactivation timer echantillonnage
#define echant_on MTU0.TIER.BYTE=0x10
#define echant_off MTU0.TIER.BYTE=0x00

// definition du compteur
#define reset_timer_te MTU0.TCNT=60535//donc le compteur comptera 5000 avant de déborder soit pour 32Mhz/64 10ms

/**********************************************************
*		Struct define
**********************************************************/

typedef struct PID PID;
struct PID{
	float kp;
	float ki;
	float kd;
	int err[2];
	int sum_err;

};
typedef struct CMD CMD;
struct CMD{
	int distance;
	int angle;
	short pwmG;
	short pwmD;
};

//définition de toutes les variables necessaires au fonctionnement de la fonction d'asservissement
int erreur_prec_dist;int erreur_prec_orient;
int somme_erreur_dist;int somme_erreur_orient;
int mesure_dist;
int mesure_orient;
int cmd_dist;int cmd_orient;
int mesure_dist;int mesure_orient;
int erreur_dist;int erreur_orient;
int erreur_prec_dist;int erreur_prec_orient;
int erreur_prec_dist_2;int erreur_prec_orient_2;
int delta_erreur_dist;int delta_erreur_orient;
//communication

void send_pilot_mg(unsigned short *pwm);	//send the value of the pmw left cmd
void send_pilot_md(unsigned short *pwm);	// send the value of the pwm right cmd

void load_dist_pid(unsigned short *dist);//change the value of distance pilotage
void load_ang_pid(unsigned short *angl);	//change the value of angle driver

void send_pa(float *p);		//send value of pid orient
void send_ia(float *i);
void send_da(float *d);

void send_dist();			//fonction de reglage de l'asserve
void send_angl();			//idem

void load_pd(float *p);		//change value of pid distance
void load_id(float *i);
void load_dd(float *d);

void send_pd(float *p);		//send value of pid distance
void send_id(float *i);
void send_dd(float *d);

void load_pa(float *p);		//change value of pid orient
void load_ia(float *i);
void load_da(float *d);

void transmission_data(char *value);	//active la transmission des données

//hardware
void init_echant(void);			// Configuration des registres
void start_echant(void);		// activation du compteur
void init_variable_echant(void);// initialisation des variables
//asserv
void asservissement(int consigne_dist,int consigne_orient,int*dist,float *angl); // Fonction d'asservissement
void inverser_droit(int pwm); 	// inverse le sens de rot du moteur droit en fonction du signe de pwm
void inverser_gauche(int pwm);	// inverse le sens de rot du moteur gauche en fonction du signe de pwm
void deplacement(int x,int y);

#endif
