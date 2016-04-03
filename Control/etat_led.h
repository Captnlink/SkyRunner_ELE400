/**
    Project : CableCam_Chariot\n
    @file Etat_Led.h
    @brief Gèrent la LED d'information selon les erreurs et warnings du systeme
    @author Captnlink
	@author Wsimon
	
    @version 1.0
    @date March 20, 2016
	Afin de visualiser les problèmes pouvant survenir à l'intérieur du controlleur
	et les états à problèmes, cette class permet donc de gérer la LED.


	Il reste à vérifier la struct controller pour pouvoir utiliser les divers variables
	et à mieux définir les états pour vérifier le statut 
	
	bool SetEndOfCourse(t_ledstate* ledstate);	 // Etat: Chariot atteint Fin de course  -> led clignote entre le vert et le jaune
bool SetCantGoSetPoint(t_ledstate* ledstate);
*/

#ifndef EtatLed_H_
#define EtatLed_H_


/**
    @class EtatLed EtatLed.h
    @brief gère l'état de la LED d'information
    @author Captnlink
    @version 1.1
    @date March 20, 2016
    Permet de gérer les informations du controlleur qui peuvent être afficher par la LED.
	
*/


//Délai du cycle pour regarder l'état des led et aussi délai de  clignotement
#define DELAY_ETAT_LED 250

// Statut des led pour les switch case pour fonction etat-led
#define GREEN 1
#define RED 2
#define YELLOW 3
#define NO_LIGHT 4

// Pin pour les leds sur le Arduino
#define PIN_LD_GREEN 1
#define PIN_LD_RED 2


/*


int etat_update(int previous_led_flash); // va retourner la dernieère fois que la led a flash



bool SetBattFaible(t_ledstate* ledstate);	 // Etat: Batterie faible -> led  clignote en vert
bool SetBattTooHot(t_ledstate* ledstate);	 // Etat batterie trop chaude -> led  clignote en rouge
bool SetObjectDetected(t_ledstate* ledstate); // Etat: objecte detecte par capteur -> led clignote entre le vert et le rouge
bool SetEndOfCourse(t_ledstate* ledstate);	 // Etat: Chariot atteint Fin de course  -> led clignote entre le vert et le jaune
bool SetCantGoSetPoint(t_ledstate* ledstate); // Etat: chariot ne peut aller au point voulu -> led  clignote en jaune
bool SetEmergencyStop(t_ledstate* ledstate);  //Etat: arrêt d'urgence -> led reste en rouge 
bool SetNoComms(t_ledstate* ledstate);		 // Etat: le module controle ne reçoit plus de donnée de la manette-> led reste en jaune


*/
typedef struct {
	int m_etape_flash;
	int m_etape_erreur;
	int previous_led_flash;
	bool statut_erreur; // false= tout va bien /true= il y a des problemes détectes 
}t_etat_led_control;


		/*
fn SetBattFaible
Description:La fonction permet de vérifier si la batterie est faible ou non.

Paramètre d'entrée:  tension lue de la batterie 
Donnée retour de la fonction: statut de l'état batterie_faible (Vrai= la batterie est faible/Faux= la batterie n'est pas faible)
*/
	bool SetBattFaible(double tension_batterie);


		/*
fn SetBattTooHot
Description:La fonction permet de vérifier si la température de la batterie est trop chaude


Paramètre d'entrée: temperature lu de la battrie
Donnée retour de la fonction: variable boolean (Vrai=batteriee est trop chaude/Faux= temperature de la batterie est ok)
*/
	bool SetBattTooHot(double temp_batterie);

		/*
fn SetObjectDetected
Description:La fonction permet de vérifier  si les capteurs ont  détecté

Paramètre d'entrée:  distance_objet_detecte     valeur 0 si rien n'a été detecté par les capteurs
Donnée retour de la fonction: variable boolean (Vrai= un objet a été detecté/Faux= aucun n'obstacle a été detecté)
*/
	bool SetObjectDetected(double distance_objet_detecte);



		/*
fn SetEndOfCourse
Description:La fonction permet de vérifier si le chariot a atteint la fin de course

Paramètre d'entrée:  
Donnée retour de la fonction: variable boolean (Vrai= le chariot a atteint la fin de course/Faux= le chariot n'a pas atteint la fin de course)
*/

	//bool SetEndOfCourse();// juste clarifier avec quoi l'évaluer



	/*
fn SetCantGoSetPoint
Description:La fonction permet de vérifier si on  peut  atteindre la position désirée 

Paramètre d'entrée:  
Donnée retour de la fonction: variable boolean (Vrai= le chariot ne peux atteindre le point voulu/Faux= le chariot peut atteint le point voulu)
*/
//	bool SetCantGoSetPoint();// juste clarifier avec quoi l'évaluer



		/*
fn  SetEmergencyStop
Description:La fonction permet de vérifier si l'arrêt d'urgence a été enclenché

Paramètre d'entrée:  statut de l'arret d'urgence
Donnée retour de la fonction: variable boolean (Vrai= l'arret d'urgence a été enclenché/Faux= l'arret d'urgence n'a pas été enclenché)
*/
	bool SetEmergencyStop(int arrêt_urgence);


	/*
fn  SetNoComms
Description:La fonction permet de retourner le statut de la communication avec la manettre

Paramètre d'entrée:  le statut de connexion avec la manette 
Donnée retour de la fonction: variable boolean (Vrai= Aucune communication avec l'interface/Faux= La communication est présente )
*/
	bool SetNoComms(int statut_connexion_manette);//
	


		/*
fn  etat_led
Description:La fonction permet d'allumer la led qu'on veut, soit la couleur rouge, vert, jaune ou aucune couleur

Paramètre d'entrée:  les constantes de couleur
Donnée retour de la fonction: Aucune
*/
	void etat_led(int color);




			/*
fn  etat_update
Description:La fonction permet de vérifier les différents états par la suite, allumer la led en conséquence
Les états sont

Etat: tout va bien ->  led reste en vert 
 Etat: Batterie faible -> led  clignote en vert
 Etat batterie trop chaude -> led  clignote en rouge
 Etat: objecte detecte par capteur -> led clignote entre le vert et le rouge
Etat: Chariot atteint Fin de course  -> led clignote entre le vert et le jaune
 Etat: chariot ne peut aller au point voulu -> led  clignote en jaune
Etat: arrêt d'urgence -> led reste en rouge 
Etat: le module controle ne reçoit plus de donnée de la manette-> led reste en jaune

Paramètre d'entrée:  Données du controlleur permettant d'évaluer les états
Donnée retour de la fonction: Aucune
*/
	
	
	
	void etat_update(t_etat_led_control* etat_led_control/*, données controlleur*/); // va retourner la dernieère fois que la led a flash
	t_etat_led_control initialiser_etat_led();

#endif
