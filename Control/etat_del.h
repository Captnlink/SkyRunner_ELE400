/**
    Project : CableCam_Chariot\n
    @file etat_del.h
    Description fonction pour affichder l'état des del dépendamment de l'état du controlleur
	Il reste à tester les fonctions sur un montage physique 
    @author Wsimon
	
    @version 1.0
    @date March 28, 2016
	
*/




#ifndef EtatLed
#define EtatLed

/*
t_ledstate initialiser_ledstate();			 // initialiser la struct ledstate

void set_etat_controller(t_ledstate* ledstate, char etat);  //permet de modifier l'etat des dels en fonction de l'etat du controlleur

void SetGood(t_ledstate* ledstate);			 //Etat: tout va bien ->  led reste en vert 
void SetBattFaible(t_ledstate* ledstate);	 // Etat: Batterie faible -> led  clignote en vert
void SetBattTooHot(t_ledstate* ledstate);	 // Etat batterie trop chaude -> led  clignote en rouge
void SetObjectDetected(t_ledstate* ledstate); // Etat: objecte detecte par capteur -> led clignote entre le vert et le rouge
void SetEndOfCourse(t_ledstate* ledstate);	 // Etat: Chariot atteint Fin de course  -> led clignote entre le vert et le jaune
void SetCantGoSetPoint(t_ledstate* ledstate); // Etat: chariot ne peut aller au point voulu -> led  clignote en jaune
void SetEmergencyStop(t_ledstate* ledstate);  //Etat: arrêt d'urgence -> led reste en rouge 
void SetNoComms(t_ledstate* ledstate);		 // Etat: le module controle ne reçoit plus de donnée de la manette-> led reste en jaune
*/

//Me rappeler de mettre les definitions d'état dans la configuration par défaut
#define STATE_GOOD 'A'			//Etat: tout va bien 
#define STATE_BattFaible 'B'	// Etat: Batterie faibl
#define STATE_BattTooHot 'C'	// Etat batterie trop chaude
#define STATE_ObjectDetected 'D' // Etat: objecte detecte par capteur
#define STATE_EndOfCourse 'E'	 // Etat: Chariot atteint Fin de course
#define STATE_CantGoSetPoint 'F'// Etat: chariot ne peut aller au point voulu
#define STATE_EmergencyStop 'G' //Etat: arrêt d'urgence rouge 
#define STATE_NoComms 'H'		// Etat: le module controle ne reçoit plus de donnée de la manette

// valeur pour l'etat de la del ON= allumé OFF= pas allumé
#define ON true
#define OFF false

//Pin pour la led bicouleur
#define PIN_LD_GREEN 1
#define PIN_LD_RED 2

// Délay pour le clignotement des del 
#define DELAY_CLIGNOTEMENT 1000

typedef struct t_ledstate* p_ledstate;
struct t_ledstate
{
	/* défini si la led rouge ou vert est allumé ou non
	 si les deux dels sont allumés la lumière est jaune*/
	bool red ;
	bool green ;
	char etat_controller;
	/*A = fonctionnement normal   B= Batterie Faible C= batterie trop chaude D=Objet_détecté E= fin de cours 
	F= Peut pas aller à la distance détermine  G= arrêt d'urgence H= pas de communication
	*/
	unsigned long previousMillis; // temps du dernier clignotement

};


/*
fn initialiser_ledstate
Description:La fonction permet d'initialiser la variable pour l'état des leds

Paramètre d'entrée: aucun
Donnée retour de la fonction: variable de type struct pointeur vers t_ledstate
*/
t_ledstate initialiser_ledstate();


/*
fn set_etat_controller
Description:La fonction permet de modifier l'état du controller pour afficher l'etat des del

Paramètre d'entrée: pointeur qu'on veut modifier , l'état du controlleur
Donnée retour de la fonction: Aucun
*/
void set_etat_controller(t_ledstate* ledstate, char etat);


/*
fn setGood
Description:La fonction permet de mettre la led en vert pout montrer que le control va bien

Paramètre d'entrée:  pointeur pour une variable état des del
Donnée retour de la fonction: Aucun
*/
void SetGood(t_ledstate* ledstate); //vert



/*
fn SetBattFaible
Description:La fonction permet de faire clignoter la led en vert pout montrer que la batterie du controle est faible

Paramètre d'entrée:  pointeur pour une variable état des del
Donnée retour de la fonction: Aucun
*/
void SetBattFaible(t_ledstate* ledstate); // clignotemtn vert

/*
fn SetBattTooHot
Description:La fonction permet de faire clignoter la led en rouge pout montrer que la température de la batterie
est trop chaude

Paramètre d'entrée:  pointeur pour une variable état des del
Donnée retour de la fonction: Aucun
*/
void SetBattTooHot(t_ledstate* ledstate); //  clignotmeetn rouge

/*
fn SetObjectDetected
Description:La fonction permet de faire clignoter la led en alternant vert et rouge pout montrer qu'un
objet a été détecté

Paramètre d'entrée:  pointeur pour une variable état des del
Donnée retour de la fonction: Aucun
*/
void SetObjectDetected(t_ledstate* ledstate); // clignotemtn vert et rouge


/*
fn SetEndOfCourse
Description:La fonction permet de faire clignoter la led en alternant vert et jaune pout montrer 
qu'on a atteint la fin de course

Paramètre d'entrée:  pointeur pour une variable état des del
Donnée retour de la fonction: Aucun
*/
void SetEndOfCourse(t_ledstate* ledstate); // clignotement vert et jaune

/*
fn SetCantGoSetPoint
Description:La fonction permet de faire clignoter la led en  jaune pout montrer 
qu'on ne peut atteindre la position désirée 

Paramètre d'entrée:  pointeur pour une variable état des del
Donnée retour de la fonction: Aucun
*/
void SetCantGoSetPoint(t_ledstate* ledstate);// clignotement jaune

/*
fn  SetEmergencyStop
Description:La fonction permet d'allumer la led en rouge constant pour signaler
qu'il y a un arrêt d'urgence

Paramètre d'entrée:  pointeur pour une variable état des del
Donnée retour de la fonction: Aucun
*/
void SetEmergencyStop(t_ledstate* ledstate);

/*
fn  SetNoComms
Description:La fonction permet d'allumer la led en jaune constant pour signaler
que le controle ne reçoit pas de donnée de l'interface

Paramètre d'entrée:  pointeur pour une variable état des del
Donnée retour de la fonction: Aucun
*/
void SetNoComms(t_ledstate* ledstate);




#endif
