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
#include "stdlib.h"


//definition des différentes flags
#define flag_over_te IR(MTU4,TCIV4)	//flag overflow timer

//definition activation/désactivation timer echantillonnage
#define echant_on MTU4.TIER.BYTE=0x10
#define echant_off MTU4.TIER.BYTE=0x00

//definition du compteur
#define reset_timer_te MTU4.TCNT=60535//donc le compteur comptera 5000 avant de déborder soit pour 32Mhz/64 10ms

int match_counter;
/**********************************************************
*		Struct define
**********************************************************/

typedef struct PID PID;
struct PID{
	float kp;
	float ki;
	float kd;
	int err[3];
	int delta_err;

};
typedef struct CMD CMD;
struct CMD{
    int dist_p;
    int orient_p;
	int dist;
	int orient;
    int pwmG[2];
	int pwmD[2];
};

//communication

void send_pilot_mg( short *pwm);	//send the value of the pmw left cmd
void send_pilot_md( short *pwm);	// send the value of the pwm right cmd

void load_dist(int *dist);//change the value of distance pilotage
void load_angle(int *angl);	//change the value of angle driver

void send_pa(float *p);		//send value of pid orient
void send_ia(float *i);
void send_da(float *d);

void send_dist();			//fonction de reglage de l'asserve
void send_angle();			//idem

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

/**********************************************************
//hardware
**********************************************************/
void init_echant(void);			// Configuration des registres
void start_asserv(void);		// activation du compteur
void stop_asserv(void);

/**********************************************************
//asserv
**********************************************************/

void asservissement(int *c_dist,int *c_angle,int*dist,int *angle); // Fonction d'asservissement
void inverser_droit(int pwm); 	// inverse le sens de rot du moteur droit en fonction du signe de pwm
void inverser_gauche(int pwm);	// inverse le sens de rot du moteur gauche en fonction du signe de pwm

/**********************************************************
* gestion match
**********************************************************/

void init_base_temps(void);
void start_match(void);
int time_end(void);
#endif
