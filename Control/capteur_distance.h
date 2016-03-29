
﻿
/**
    Project : CableCam_Chariot\n
    @file capteur_distance.h
    Description  fonction pour la lecture de distance et définition des configuration des capteurs sur le 
		chariot 
		
		Attention ne pas oublier d'inclure le fichier NewPing.h et NewPing.cpp qui est la library avec les foncitons de base 
		pour les capteurs
    @author Wsimon
	
    @version 1.0
    @date March 25, 2016

Note: Tester les fonctions avec le arduino
	
*/



#ifndef CAPTEUR_DISTANCE //  pour éviter la double-complication 
#define CAPTEUR_DISTANCE


#include "NewPing.h"

#include "Arduino.h"

//Pin trigger et echo pour capteur devantvle chassis
#define C_F_TRIGGER_PIN 1 
#define C_F_ECHO_PIN 2

//Pin trigger et echo pour capteur derriere le chassis
#define C_B_TRIGGER_PIN 3
#define C_B_ECHO_PIN 4


#define MAX_DISTANCE 500 //distance maximale où on peut détecter un objet pour lire sa distance du cpateur


typedef struct NewPing*  p_new_ping;//permet de conserver l'adresse d'une classe NewPing de la librairie Newping.h


typedef struct 
{
  p_new_ping configuration;/* conserve les configurations telle numéro des pin Trigger et Echo  du capteur de distanc sur le arduino, ainsi quie
                            la distance maximale que le capteur peut détecter*/
  float distance_obstacle; //distance de l'obstacle en cm

}t_capteur; 


typedef struct  // garde les donnée pour les capteur à droite et à gauche du chariot
{
  t_capteur  devant;
  t_capteur  derriere;
}t_liste_capteur;



/*
Description:La fonction permet d'initialiser les capteurs à la valeur d'origine,
au démarrage du controlleur. on insère les configuration des pins trigger et echo
pour chacun des capteurs du chassis.
Paramètre d'entrée: aucun
Donnée retour de la fonction: variabble de type struct t_liste_capteur 
*/
t_liste_capteur initialiser_capteur();



/*
Description:la fonction permet de renvoyer la distance à laquelle le capteur détecte un objet.
La valeur inscrite dans la variable cpatuer est entre 0 et la distance maximale de détection
S'il ne détecte pas d'objet, la fonction ecrit une distance de 0 dans la variable capteur
Paramètre d'entrée: adresse vers une variable capteur
Donnée retour de la fonction: aucun 
*/
void get_distance(t_capteur* capteur_actif);




#endif
