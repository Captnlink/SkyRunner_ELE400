/**
    Project : CableCam_Chariot\n
    @file Etat_Led.h
    @brief G�rent la LED d'information selon les erreurs et warnings du systeme
    @author Captnlink
	@author Wsimon
	
    @version 1.0
    @date March 20, 2016
	Afin de visualiser les probl�mes pouvant survenir � l'int�rieur du controlleur
	et les �tats � probl�mes, cette class permet donc de g�rer la LED.


	Il reste � v�rifier la struct controller pour pouvoir utiliser les divers variables
	et � mieux d�finir les �tats pour v�rifier le statut 
	
	bool SetEndOfCourse(t_ledstate* ledstate);	 // Etat: Chariot atteint Fin de course  -> led clignote entre le vert et le jaune
bool SetCantGoSetPoint(t_ledstate* ledstate);
*/

#ifndef EtatLed_H_
#define EtatLed_H_


/**
    @class EtatLed EtatLed.h
    @brief g�re l'�tat de la LED d'information
    @author Captnlink
    @version 1.1
    @date March 20, 2016
    Permet de g�rer les informations du controlleur qui peuvent �tre afficher par la LED.
	
*/


//D�lai du cycle pour regarder l'�tat des led et aussi d�lai de  clignotement
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


int etat_update(int previous_led_flash); // va retourner la dernie�re fois que la led a flash



bool SetBattFaible(t_ledstate* ledstate);	 // Etat: Batterie faible -> led  clignote en vert
bool SetBattTooHot(t_ledstate* ledstate);	 // Etat batterie trop chaude -> led  clignote en rouge
bool SetObjectDetected(t_ledstate* ledstate); // Etat: objecte detecte par capteur -> led clignote entre le vert et le rouge
bool SetEndOfCourse(t_ledstate* ledstate);	 // Etat: Chariot atteint Fin de course  -> led clignote entre le vert et le jaune
bool SetCantGoSetPoint(t_ledstate* ledstate); // Etat: chariot ne peut aller au point voulu -> led  clignote en jaune
bool SetEmergencyStop(t_ledstate* ledstate);  //Etat: arr�t d'urgence -> led reste en rouge 
bool SetNoComms(t_ledstate* ledstate);		 // Etat: le module controle ne re�oit plus de donn�e de la manette-> led reste en jaune


*/





		/*
fn SetBattFaible
Description:La fonction permet de v�rifier si la batterie est faible ou non.

Param�tre d'entr�e:  tension lue de la batterie 
Donn�e retour de la fonction: statut de l'�tat batterie_faible (Vrai= la batterie est faible/Faux= la batterie n'est pas faible)
*/
	bool SetBattFaible(double tension_batterie);


		/*
fn SetBattTooHot
Description:La fonction permet de v�rifier si la temp�rature de la batterie est trop chaude


Param�tre d'entr�e: temperature lu de la battrie
Donn�e retour de la fonction: variable boolean (Vrai=batteriee est trop chaude/Faux= temperature de la batterie est ok)
*/
	bool SetBattTooHot(double temp_batterie);

		/*
fn SetObjectDetected
Description:La fonction permet de v�rifier  si les capteurs ont  d�tect�

Param�tre d'entr�e:  distance_objet_detecte     valeur 0 si rien n'a �t� detect� par les capteurs
Donn�e retour de la fonction: variable boolean (Vrai= un objet a �t� detect�/Faux= aucun n'obstacle a �t� detect�)
*/
	bool SetObjectDetected(double distance_objet_detecte);



		/*
fn SetEndOfCourse
Description:La fonction permet de v�rifier si le chariot a atteint la fin de course

Param�tre d'entr�e:  
Donn�e retour de la fonction: variable boolean (Vrai= le chariot a atteint la fin de course/Faux= le chariot n'a pas atteint la fin de course)
*/

	//bool SetEndOfCourse();// juste clarifier avec quoi l'�valuer



	/*
fn SetCantGoSetPoint
Description:La fonction permet de v�rifier si on  peut  atteindre la position d�sir�e 

Param�tre d'entr�e:  
Donn�e retour de la fonction: variable boolean (Vrai= le chariot ne peux atteindre le point voulu/Faux= le chariot peut atteint le point voulu)
*/
//	bool SetCantGoSetPoint();// juste clarifier avec quoi l'�valuer



		/*
fn  SetEmergencyStop
Description:La fonction permet de v�rifier si l'arr�t d'urgence a �t� enclench�

Param�tre d'entr�e:  statut de l'arret d'urgence
Donn�e retour de la fonction: variable boolean (Vrai= l'arret d'urgence a �t� enclench�/Faux= l'arret d'urgence n'a pas �t� enclench�)
*/
	bool SetEmergencyStop(int arr�t_urgence);


	/*
fn  SetNoComms
Description:La fonction permet de retourner le statut de la communication avec la manettre

Param�tre d'entr�e:  le statut de connexion avec la manette 
Donn�e retour de la fonction: variable boolean (Vrai= Aucune communication avec l'interface/Faux= La communication est pr�sente )
*/
	bool SetNoComms(int statut_connexion_manette);//
	


		/*
fn  etat_led
Description:La fonction permet d'allumer la led qu'on veut, soit la couleur rouge, vert, jaune ou aucune couleur

Param�tre d'entr�e:  les constantes de couleur
Donn�e retour de la fonction: Aucune
*/
	void etat_led(int color);




			/*
fn  etat_update
Description:La fonction permet de v�rifier les diff�rents �tats par la suite, allumer la led en cons�quence
Les �tats sont

Etat: tout va bien ->  led reste en vert 
 Etat: Batterie faible -> led  clignote en vert
 Etat batterie trop chaude -> led  clignote en rouge
 Etat: objecte detecte par capteur -> led clignote entre le vert et le rouge
Etat: Chariot atteint Fin de course  -> led clignote entre le vert et le jaune
 Etat: chariot ne peut aller au point voulu -> led  clignote en jaune
Etat: arr�t d'urgence -> led reste en rouge 
Etat: le module controle ne re�oit plus de donn�e de la manette-> led reste en jaune

Param�tre d'entr�e:  Donn�es du controlleur permettant d'�valuer les �tats
Donn�e retour de la fonction: Aucune
*/
	
	
	
	void etat_update(int previous_led_flash/*, donn�es controlleur*/); // va retourner la dernie�re fois que la led a flash


#endif