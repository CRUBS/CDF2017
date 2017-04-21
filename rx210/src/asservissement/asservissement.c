/* description du fichier et des fonction
*  auteur lebansais yoann
*  date: 22/11/2016
*  pour le CRUBS cdf 2017
*/

#include "asservissement.h"

 PID pid_dist = {5,0,0,0,0};	// initialisation du pid pour la distance
 PID pid_orient = {3,0,0,0,0};	//inititalisation du pid pour l'orientation
 CMD cmd = {0,0,0,0,0,0};

 char transmit_data=0;
/***********************************************************************************************
 * function of communication
 *********************************************************************************************/
void send_pilot_mg( short *pwm)	//send the value of the pmw left cmd
{
	char adresse= 3;
	send_sht(&adresse,&(cmd.pwmG));
}
void send_pilot_md( short *pwm)	// send the value of the pwm right cmd
{
	char adresse = 4;
	send_sht(&adresse,&(cmd.pwmD));
}


void send_pd(float *p)
{
	char adresse = 4;							//send pid p
	send_flt(&adresse,&pid_dist.kp);		//send value of pid distance
}
void send_id(float *i)
{
	char adresse = 5;							//send pid i
	send_flt(&adresse,&pid_dist.ki);		//send value of pid distance
}
void send_dd(float *p)
{
	char adresse = 6;							//send pid p
	send_flt(&adresse,&pid_dist.kd);		//send value of pid distance
}

void send_pa(float *p)		//send value of pid orient
{
	char adr = 10;
	send_flt(&adr,&pid_orient.kp);
}
void send_ia(float *i)
{
	char adr = 11;
	send_flt(&adr,&pid_orient.ki);
}
void send_da(float *d)
{
	char adr = 12;
	send_flt(&adr,&pid_orient.kd);
}
void send_dist()
{
	char adresse = 3;
	int value = (int)(compteur_d+compteur_g)/2;
	send_int(&adresse,&value);
}
void send_angle()
{
	char adr = 5;//5 le temps du debug4;
	int value = compteur_d-compteur_g;
	send_int(&adr,&value);
}
//fonction of receiption
//reprendre ces fonction pour les rentrer dans la reception de int
void load_dist(int *dist){cmd.dist_p += *dist;}

void load_angle(int *angl){cmd.orient_p += *angl;}	//change the value of angle driver

void load_pd(float *p){pid_dist.kp = *p;}		//change value of pid distance
void load_id(float *i){pid_dist.ki = *i;}
void load_dd(float *d){pid_dist.kd = *d;}

void load_pa(float *p){pid_orient.kp = *p;}		//change value of pid orient
void load_ia(float *i){pid_orient.ki = *i;}
void load_da(float *d){pid_orient.kd = *d;}

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
//void charger_distance(int *delta){cmd.dist += *delta;}
//void charger_angle(int *theta){cmd.orient+=*theta;}

//changer cette fonction pour prendre en param de lecture dist et orient
void asservissement(int *c_dist,int *c_angle,int *dist,int *angle)
{ 
	// Calcul des erreurs d'orientation
	pid_orient.err[2]=pid_orient.err[1];
	pid_orient.err[1]=pid_orient.err[0];
    pid_orient.err[0] = *c_angle - *angle;
    pid_orient.delta_err = pid_orient.err[0] - pid_orient.err[1];

	//Calcul des erreurs de distance
	pid_dist.err[2] = pid_dist.err[1];
	pid_dist.err[1] = pid_dist.err[0];
	pid_dist.err[0] = *c_dist - *dist;
	pid_dist.delta_err = pid_dist.err[0] - pid_dist.err[1];

 // PID distance
    cmd.dist = cmd.dist+(pid_dist.kp*pid_dist.delta_err)+(pid_dist.ki*pid_dist.err[0])\
	+(pid_dist.kd*(pid_dist.err[0]-2*pid_dist.err[1]+pid_dist.err[2]));
// PID orientation
    cmd.orient = cmd.orient+(pid_orient.kp*pid_orient.delta_err)+(pid_orient.ki*pid_orient.err[0])+(pid_orient.kd*(pid_orient.err[0]-2*pid_orient.err[1]+pid_orient.err[2]));
    // appliquer les cmds aux moteur
    cmd.pwmG = cmd.dist + cmd.orient;
    cmd.pwmD = cmd.dist - cmd.orient;

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
    double mesure_angl;
	//loadouble value of the position in tck
	transfer_position_pol(&mesure_dist,&mesure_angl);
    //if(transmit_data==1)
    //{
        LED1=~LED1;       //debug
		unsigned char adr = 3;
        send_int(&adr,&mesure_dist);
        adr = 13;
        send_flt(&adr,&mesure_angl);
        /**** bim we start the asserv*******/
		//asservissement(&cmd.dist_p,&cmd.orient_p,&mesure_dist,&mesure_angl);
//	}
	flag_over_te = 0;		//remise à zero du flag
	reset_timer_te;			// remise a la bonne valeur du compteur
}
