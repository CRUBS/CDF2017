/* description du fichier et des fonction
*  auteur lebansais yoann
*  date: 22/11/2016
*  pour le CRUBS cdf 2017
*/

#include "asservissement.h"

 PID PID_distance = {2.4,0,0};	// initialisation du pid pour la distance
 PID PID_orient = {1.2,0,0};	//inititalisation du pid pour l'orientation
 CMD cmd = {0x8000,0,0,0};


 char transmit_data=0;
/***********************************************************************************************
 * function of communication
 *********************************************************************************************/
void send_pilot_mg(unsigned short *pwm)	//send the value of the pmw left cmd
{
	char adresse= 3;
	send_sht(&adresse,&(cmd.pwmG));
}
void send_pilot_md(unsigned short *pwm)	// send the value of the pwm right cmd
{
	char adresse = 4;
	send_sht(&adresse,&(cmd.pwmD));
}


void send_pd(float *p)
{
	char adresse = 4;							//send pid p
	send_flt(&adresse,&PID_distance.kp);		//send value of pid distance
}
void send_id(float *i)
{
	char adresse = 5;							//send pid i
	send_flt(&adresse,&PID_distance.ki);		//send value of pid distance
}
void send_dd(float *p)
{
	char adresse = 6;							//send pid p
	send_flt(&adresse,&PID_distance.kd);		//send value of pid distance
}

void send_pa(float *p)		//send value of pid orient
{
	char adr = 10;
	send_flt(&adr,&PID_orient.kp);
}
void send_ia(float *i)
{
	char adr = 11;
	send_flt(&adr,&PID_orient.ki);
}
void send_da(float *d)
{
	char adr = 12;
	send_flt(&adr,&PID_orient.kd);
}
void send_dist()
{
	char adresse = 7;
	int value = (int)(compteur_d+compteur_g)/2;
	send_int(&adresse,&value);
}
void send_angl()
{
	char adr = 8;
	int value =(int) compteur_d-compteur_g/10;
	send_int(&adr,&value);
}
//fonction of receiption
//reprendre ces fonction pour les rentrer dans la reception de int
void load_dist_pid(unsigned short *dist){cmd.distance +=(int) *dist;}

void load_ang_pid(unsigned short *angl){cmd.angle += (int)*angl;}	//change the value of angle driver

void load_pd(float *p){PID_distance.kp = *p;}		//change value of pid distance
void load_id(float *i){PID_distance.ki = *i;}
void load_dd(float *d){PID_distance.kd = *d;}

void load_pa(float *p){PID_orient.kp = *p;}		//change value of pid orient
void load_ia(float *i){PID_orient.ki = *i;}
void load_da(float *d){PID_orient.kd = *d;}

void transmission_data(char *value){transmit_data = *value;}




/**********************************************************************************************
 * function of asservissement
**********************************************************************************************/
void init_variable_echant(){
	mesure_dist=0;
	mesure_orient=0;
	erreur_dist=0;erreur_orient=0;
	erreur_prec_dist=0;
	erreur_prec_dist_2=0;erreur_prec_orient=0;
	cmd_dist=0;cmd_orient=0;erreur_prec_orient_2=0;
}

/**********************************************************************************************
*	I/O functions
*********************************************************************************************/
//function to load the new distance cmd without forget the last
void charger_distance(int *delta){cmd.distance += *delta;}
void charger_angle(int *theta){cmd.angle+=*theta;}

//changer cette fonction pour prendre en param de lecture dist et orient
void asservissement(int consigne_dist,int consigne_orient,int *dist,float *angl)
{
   // mesure_dist = (compteur_droit + compteur_gauche)/2;
   // mesure_orient = compteur_droit - compteur_gauche;
    
	// Calcul des erreurs d'orientation
    erreur_orient = consigne_orient - mesure_orient;
    delta_erreur_orient = erreur_orient - erreur_prec_orient;
    // mise à jour de l'erreur précédente
    erreur_prec_orient_2 = erreur_prec_orient;
    erreur_prec_orient = erreur_orient;

/*    // calcul des cmds
    cmd_dist = ((PID_distance.kp * erreur_dist) + (PID_distance.ki  * somme_erreur_dist) + (PID_distance.kd  * delta_erreur_dist));    // PID distance
    cmd_orient = ((PID_orient.kp * erreur_orient) + (PID_orient.ki  * somme_erreur_orient) + (PID_orient.kd * delta_erreur_orient)); // PID orientation
*/
    // calcul des commandes
    cmd_dist = cmd_dist+(PID_distance.kp*delta_erreur_dist)+(PID_distance.ki*erreur_dist)+(PID_distance.kd *(erreur_dist-2*erreur_prec_dist+erreur_prec_dist_2));    // PID distance
    cmd_orient = cmd_orient+(PID_orient.kp*delta_erreur_orient)+(PID_orient.ki*erreur_orient)+(PID_orient.kd*(erreur_orient-2*erreur_prec_orient+erreur_prec_orient_2)); // PID orientation
    // appliquer les cmds aux moteur
    cmd.pwmG = cmd_dist + cmd_orient;
    cmd.pwmD = cmd_dist - cmd_orient;

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

/*=============================================================
*
*	Interuption timer d'echantillonnage 
*	reglage à 10ms
*============================================================*/

void Excep_MTU0_TCIV0(void) {
	int mesure_dist;
	float mesure_angl;
	//load the value of the position in tck
	transfer_position_pol(&mesure_dist,&mesure_angl);
	if(transmit_data==1)
	{
		unsigned char adr = 6;
		send_dist();//fonction qui envoi le somme de (compteur_d + compteur_g)/2
		send_int(&adr,&cmd.distance);
 		//send_angl();
		asservissement(cmd.distance,cmd.angle,&mesure_dist,&mesure_angl);
	}
	flag_over_te = 0;		//remise à zero du flag
	reset_timer_te;			// remise a la bonne valeur du compteur
}
