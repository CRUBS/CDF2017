/* description du fichier et des fonction
*  auteur lebansais yoann
*  date: 22/11/2016
*  pour le CRUBS cdf 2017
*/

#include "asservissement.h"

//#include "odometrie.h"
//#include "math.h"

volatile PID PID_distance = {2.4,0,0};	// initialisation du pid pour la distance
volatile PID PID_orient = {1.2,0,0};	//inititalisation du pid pour l'orientation
volatile CMD cmd = {0x8000,0,0,0};

/***********************************************************************************************
 * function of communication
 *********************************************************************************************/
void send_pilot_mg(short *pwm){*pwm=cmd.pwmG;}	//send the value of the pmw left cmd
void send_pilot_md(short *pwm){*pwm=cmd.pwmD;}	// send the value of the pwm right cmd

void load_dist_pid(short *dist){cmd.distance=*dist;}//change the value of distance pilotage
void load_ang_pid(short *angl){cmd.angle = *angl;}	//change the value of angle driver

void load_pd(float *p){PID_distance.kp = *p;}		//change value of pid distance
void load_id(float *i){PID_distance.ki = *i;}
void load_dd(float *d){PID_distance.kd = *d;}

void send_pd(float *p){*p = PID_distance.kp;}		//send value of pid distance
void send_id(float *i){*i = PID_distance.ki;}
void send_dd(float *d){*d = PID_distance.kd;}

void load_pa(float *p){PID_orient.kp = *p;}		//change value of pid orient
void load_ia(float *i){PID_orient.ki = *i;}
void load_da(float *d){PID_orient.kd = *d;}

void send_pa(float *p){*p = PID_orient.kp;}		//send value of pid orient
void send_ia(float *i){*i = PID_orient.ki;}
void send_da(float *d){*d = PID_orient.kd;}


/**********************************************************************************************
 * function of asservissement
**********************************************************************************************/
void init_variable_echant(){
	mesure_dist=0;
	mesure_orient=0;
	erreur_dist=0;erreur_orient=0;
	delta_erreur_dist=0;delta_erreur_orient=0;
	cmd_dist=0;cmd_orient=0;
}
void asservissement(int consigne_dist,int consigne_orient,int compteur_droit,int compteur_gauche)
{
    mesure_dist = (compteur_droit + compteur_gauche)/2;
    mesure_orient = compteur_droit - compteur_gauche;

    // Calcul des erreurs de distance
    erreur_dist = consigne_dist - mesure_dist;
    somme_erreur_dist += erreur_dist;
    delta_erreur_dist = erreur_dist - erreur_prec_dist;
    // mise à jour de l'erreur précédente
    erreur_prec_dist = erreur_dist;

    // Calcul des erreurs d'orientation
    erreur_orient = consigne_orient - mesure_orient;
    somme_erreur_orient += erreur_orient;
    delta_erreur_orient = erreur_orient - erreur_prec_orient;
    // mise à jour de l'erreur précédente
    erreur_prec_orient = erreur_orient;

    // calcul des cmds
    cmd_dist = ((PID_distance.kp * erreur_dist) + (PID_distance.ki  * somme_erreur_dist) + (PID_distance.kd  * delta_erreur_dist));    // PID distance
    cmd_orient = ((PID_orient.kp * erreur_orient) + (PID_orient.ki  * somme_erreur_orient) + (PID_orient.kd * delta_erreur_orient)); // PID orientation

    // appliquer les cmds aux moteur
    cmd.pwmG = cmd_dist - cmd_orient;
    cmd.pwmD = cmd_dist + cmd_orient;

    // Normalisation des cmds PWM de sortie (le moteur ne bouge pas avec un pwm < 240)
    if (cmd.pwmD < -900) {cmd.pwmD = -900;}
    else if (cmd.pwmD > 900) {cmd.pwmD = 900;}
    if (cmd.pwmG < -900) {cmd.pwmG = -900;}
    else if (cmd.pwmG > 900) {cmd.pwmG = 900;}
    inverser_droit(cmd.pwmD);
    inverser_gauche(cmd.pwmG);
}

void inverser_droit(int pwm){
  if (pwm > 0) {INA_D=0;INB_D=1;}
  else {INA_D=1;INB_D=0;pwm = -pwm;}
  pwm_d=pwm;}
void inverser_gauche(int pwm){
  if (pwm > 0) {INA_G=0;INB_G=1;}
  else {INA_G=1;INB_G=0;pwm = -pwm;}
  pwm_g=pwm;}


void Excep_MTU0_TCIV0(void) {
	LED0=~LED0;
	flag_over_te = 0;
	reset_timer_te;
	int a = compteur_d;
	int b = compteur_g;
	asservissement(cmd.distance,cmd.angle,a,b);
}
