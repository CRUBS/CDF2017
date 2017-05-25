/* description du fichier et des fonction
*  auteur lebansais yoann
*  date: 22/11/2016
*  pour le CRUBS cdf 2017
*/

#include "asservissement.h"

#define ACC_LIMIT 5
#define PWM_MAX 500
#define PWM_MIN 100
#define PWM_ZERO 100
#define MIN_ERR 50



 PID pid_dist = {8.0,0.0,18.0,0,0};	// initialisation du pid pour la distance
 PID pid_orient = {5.0,0.0,25.0,0,0};	//inititalisation du pid pour l'orientation
 CMD cmd = {0,0,0,0,0,0};

 char transmit_data=0;
 extern int match_counter;

/* tableau de trajectoire à l'arrache comme dab ;) */
#define TAILLE_TAB_TRAJ 18

int traj_dist[TAILLE_TAB_TRAJ]={0,0,200,0,200,0,0,0,4500,0,450,0,5000,0,3000,0,4000,0};
int traj_orient[TAILLE_TAB_TRAJ]={0,600,0,600,0,600,0,450,0,0,0,4000,0,6000,0,6000,0,0};

//int traj_dist[TAILLE_TAB_TRAJ]={0,0,200,0,200,0,100,0,1000,0,0};
//int traj_orient[TAILLE_TAB_TRAJ]={0,660,0,660,0,660,0,660,0,350,0};

int j = 0;


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


/* function to enable asservissement by uart */

void transmission_data(char *value){
    if(*value == 1){start_asserv();}
    else{ stop_asserv();}
}




/**********************************************************************************************
 * function of asservissement
**********************************************************************************************/

/**********************************************************************************************
*	I/O functions
*********************************************************************************************/
//function to load the new distance cmd without forget the last
//void charger_distance(int *delta){cmd.dist += *delta;}
//void charger_angle(int *theta){cmd.orient+=*theta;}

//changer cette fonction pour prendre en param de lecture dist et orient
void asservissement(int *c_dist,int *c_angle,int *dist,int *angle)
{ 
    int vitesse_d=0,vitesse_g=0;

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
    cmd.dist = (int) cmd.dist+(pid_dist.kp*pid_dist.delta_err)+(pid_dist.ki*pid_dist.err[0])\
	+(pid_dist.kd*(pid_dist.err[0]-2*pid_dist.err[1]+pid_dist.err[2]));
// PID orientation
    cmd.orient = (int) cmd.orient+(pid_orient.kp*pid_orient.delta_err)+(pid_orient.ki*pid_orient.err[0])+(pid_orient.kd*(pid_orient.err[0]-2*pid_orient.err[1]+pid_orient.err[2]));
    // appliquer les cmds aux moteur
    cmd.pwmG[0] = cmd.dist - cmd.orient;
    cmd.pwmD[0] = cmd.dist + cmd.orient;




    // Normalisation des cmds PWM de sortie (le moteur ne bouge pas avec un pwm < 240)if (cmd.pwmD < -800) {cmd.pwmD = -800;}
    if (cmd.pwmD[0] < -PWM_MAX) {cmd.pwmD[0] = -PWM_MAX;}
    else if (cmd.pwmD[0] > PWM_MAX) {cmd.pwmD[0] = PWM_MAX;}
    else if ((cmd.pwmD[0] >-PWM_MIN) && (cmd.pwmD[0] <= -PWM_ZERO)){cmd.pwmD[0] = -260;}
    else if ((cmd.pwmD[0]<PWM_MIN) && cmd.pwmD[0] >= PWM_ZERO){cmd.pwmD[0] = PWM_MIN;}
    else if (abs(cmd.pwmD[0])<PWM_ZERO){cmd.pwmD[0] = 0;}

    if (cmd.pwmG[0] < -PWM_MAX) {cmd.pwmG[0] = -PWM_MAX;}
    else if (cmd.pwmG[0] > PWM_MAX) {cmd.pwmG[0] = PWM_MAX;}
    else if (cmd.pwmG[0] <PWM_MIN && cmd.pwmG[0] >= PWM_ZERO){cmd.pwmG[0] = PWM_MIN;}
    else if (cmd.pwmG[0] >-PWM_MIN && cmd.pwmG[0] <=-PWM_ZERO){cmd.pwmG[0] = -PWM_MIN;}
    else if (abs(cmd.pwmG[0])<PWM_ZERO){cmd.pwmG[0] = 0;}

        
    inverser_droit(cmd.pwmD[0]);
    inverser_gauche(cmd.pwmG[0]);

}

void inverser_droit(int pwm){
  if (pwm > 0) {INA_D=1;INB_D=0;}
  else {INA_D=0;INB_D=1;pwm = -pwm;}
  pwm_d=pwm;}
void inverser_gauche(int pwm){
  if (pwm > 0) {INA_G=1;INB_G=0;}
  else {INA_G=0;INB_G=1;pwm = -pwm;}
  pwm_g=pwm;}

/*=============================================================
*
*	Interuption timer d'echantillonnage 
*	reglage à 10ms
*============================================================*/

void Excep_MTU4_TCIV4(void) {
//    LED1=~LED1;       //debug
    int mesure_dist, mesure_angl;

    /*  get value from coder */
    transfer_position_pol(&mesure_dist,&mesure_angl);


    /* part of the function that allow to stop robot at 90 sec */
    if(transmit_data==1)
    {
        match_counter ++;
    }
#if UART
   unsigned char adr = 3;
//    send_int(&adr,&cmd.pwmG);
    send_int(&adr,&mesure_angl);
//    send_int(&adr,&mesure_dist);
    adr = 5;
    send_int(&adr,&mesure_dist);
//    send_int(&adr,&cmd.orient_p);
//    send_int(&adr,&cmd.dist_p);
//    send_int(&adr,&cmd.pwmD);

#endif

    /* get the next trajectory point */

    if(INT_DETECT!=1)
    {
        if((pid_dist.err[0] < MIN_ERR) && (pid_orient.err[0] < MIN_ERR))
        {
            cmd.orient_p -=traj_orient[j];
            cmd.dist_p += traj_dist[j];
            j++;
            if(j >= TAILLE_TAB_TRAJ){j--;}

        }
    }
    /**** bim we start the asserv*******/
    asservissement(&cmd.dist_p,&cmd.orient_p,&mesure_dist,&mesure_angl);

    /* reset du timer */
    flag_over_te = 0;   //remise à zero du flag
    reset_timer_te;     // remise a la bonne valeur du compteur
//    LED1_OFF;       //debug
}


/***************************************************
* function to manage time
***************************************************/

int time_end(void)
{
    if(match_counter<9000){return 1;}
    else{return 0;}
}
