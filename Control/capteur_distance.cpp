
/**
    Project : CableCam_Chariot\n
    @file capteur_distance.cpp
    Description définition de fonction pour la lecture de distance 
    @author Wsimon
	
    @version 1.0
    @date March 25, 2016

Note: Tester les fonctions avec le arduino
*/


#include <stdlib.h>
#include <stdio.h>
#include "NewPing.h"
#include "capteur_distance.h"
#include "Arduino.h"

///fonction pour envoyer la distanc lue par le capteur de distance

// On initalise les capteur
t_liste_capteur initialiser_capteur()
{
  t_liste_capteur init_capteur;

// utilisation de la librairie NewPing pour cconifugurer les capteurs et les mettres dans la variable définissant nos capteurs droit et gauche.

   //on definit les configuration des pins et de la distance maximal pour utiliser la librairie newping.h
   // de plus, on intialise la distance_obtacle à 0
   NewPing conf_capteur_devant = NewPing(C_F_TRIGGER_PIN, C_F_ECHO_PIN, MAX_DISTANCE);
  init_capteur.devant.configuration = &conf_capteur_devant;
  init_capteur.devant.distance_obstacle = 0;

  NewPing conf_capteur_derriere = NewPing(C_B_TRIGGER_PIN, C_B_ECHO_PIN, MAX_DISTANCE);
  init_capteur.derriere.configuration = &conf_capteur_derriere;
  init_capteur.derriere.distance_obstacle = 0;


  return init_capteur;
}


// Fonction sert à utiliser la fonction lire la distance de la librairie NewPing
void get_distance(t_capteur* capteur_actif)
{
  //conserve la donnée lue par le capteur par la librarie 
  capteur_actif->distance_obstacle=capteur_actif->configuration->ping_cm();
  
}


