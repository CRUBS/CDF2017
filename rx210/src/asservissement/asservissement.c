/* description du fichier et des fonction
*  auteur lebansais yoann
*  date: 22/11/2016
*  pour le CRUBS cdf 2017
*/

#include "asservissement.h"
#include "iodefine.h"
#include "RPBRX210.h"
#include "interrupt_handlers.h"
#include "typedefine.h"
#include "pwm_asser_RX210.h"



void init_echant(){

	SYSTEM.PRCR.WORD=0xA502;
	SYSTEM.MSTPCRA.BIT.ACSE=0;
	MSTP(MTU)=0;
	MTU0.TCR.BYTE=0x03;			//clock frequencies divise by 64
	MTU0.TMDR.BYTE=0x00;		//timer in normal mode
	reset_timer_te;	//initialize the value of timer
	MTU0.TIER.BYTE=0x10;		// set the interrupt but don't active the counter
	IEN(MTU0,TCIV0)=1;
	IPR(MTU0,TCIV0)=0x2;
	

	while(MTU0.TIER.BYTE!=0x10);
	SYSTEM.PRCR.WORD=0xA500;

}

void start_echant()
{
	MTU.TSTR.BIT.CST0=1;	// activation du compteur
}

void init_variable_echant(){
	PWMD=0;PWMG=0;
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

    // calcul des commandes
    cmd_dist = ((kp_dist * erreur_dist) + (ki_dist * somme_erreur_dist) + (kd_dist * delta_erreur_dist));    // PID distance
    cmd_orient = ((kp_orient * erreur_orient) + (ki_orient * somme_erreur_orient) + (kd_orient * delta_erreur_orient)); // PID orientation

    // appliquer les commandes aux moteur
    PWMG = cmd_dist - cmd_orient;
    PWMD = cmd_dist + cmd_orient;

    // Normalisation des commandes PWM de sortie (le moteur ne bouge pas avec un pwm < 240)
    if (PWMD < -900) {PWMD = -900;}
    if (PWMD > 900) {PWMD = 900;}
    if (PWMG < -900) {PWMG = -900;}
    if (PWMG > 900) {PWMG = 900;}
    inverser_droit(PWMD);
    inverser_gauche(PWMG);
}

void inverser_droit(int pwm){
  if (pwm > 0) {INA_D=0;INB_D=1;}
  else {INA_D=1;INB_D=0;pwm = -pwm;}
  pwm_d=pwm;}
void inverser_gauche(int pwm){
  if (pwm > 0) {INA_G=0;INB_G=1;}
  else {INA_G=1;INB_G=0;pwm = -pwm;}
  pwm_g=pwm;}
