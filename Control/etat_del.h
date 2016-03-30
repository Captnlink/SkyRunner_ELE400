

/**
    Project : CableCam_Chariot\n
    @file etat_del.h
    Description fonction pour affichder l'�tat des del d�pendamment de l'�tat du controlleur
	Il reste � tester les fonctions sur un montage physique 
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
void SetEmergencyStop(t_ledstate* ledstate);  //Etat: arr�t d'urgence -> led reste en rouge 
void SetNoComms(t_ledstate* ledstate);		 // Etat: le module controle ne re�oit plus de donn�e de la manette-> led reste en jaune
*/

//Me rappeler de mettre les definitions d'�tat dans la configuration par d�faut
#define STATE_GOOD 'A'			//Etat: tout va bien 
#define STATE_BattFaible 'B'	// Etat: Batterie faibl
#define STATE_BattTooHot 'C'	// Etat batterie trop chaude
#define STATE_ObjectDetected 'D' // Etat: objecte detecte par capteur
#define STATE_EndOfCourse 'E'	 // Etat: Chariot atteint Fin de course
#define STATE_CantGoSetPoint 'F'// Etat: chariot ne peut aller au point voulu
#define STATE_EmergencyStop 'G' //Etat: arr�t d'urgence rouge 
#define STATE_NoComms 'H'		// Etat: le module controle ne re�oit plus de donn�e de la manette

// valeur pour l'etat de la del ON= allum� OFF= pas allum�
#define ON true
#define OFF false

//Pin pour la led bicouleur
#define PIN_LD_GREEN 1
#define PIN_LD_RED 2

// D�lay pour le clignotement des del 
#define DELAY_CLIGNOTEMENT 1000

typedef struct t_ledstate* p_ledstate;
struct t_ledstate
{
	/* d�fini si la led rouge ou vert est allum� ou non
	 si les deux dels sont allum�s la lumi�re est jaune*/
	bool red ;
	bool green ;
	char etat_controller;
	/*A = fonctionnement normal   B= Batterie Faible C= batterie trop chaude D=Objet_d�tect� E= fin de cours 
	F= Peut pas aller � la distance d�termine  G= arr�t d'urgence H= pas de communication
	*/
	unsigned long previousMillis; // temps du dernier clignotement

};


/*
fn initialiser_ledstate
Description:La fonction permet d'initialiser la variable pour l'�tat des leds

Param�tre d'entr�e: aucun
Donn�e retour de la fonction: variable de type struct pointeur vers t_ledstate
*/
t_ledstate initialiser_ledstate();


/*
fn set_etat_controller
Description:La fonction permet de modifier l'�tat du controller pour afficher l'etat des del

Param�tre d'entr�e: pointeur qu'on veut modifier , l'�tat du controlleur
Donn�e retour de la fonction: Aucun
*/
void set_etat_controller(t_ledstate* ledstate, char etat);


/*
fn setGood
Description:La fonction permet de mettre la led en vert pout montrer que le control va bien

Param�tre d'entr�e:  pointeur pour une variable �tat des del
Donn�e retour de la fonction: Aucun
*/
void SetGood(t_ledstate* ledstate); //vert



/*
fn SetBattFaible
Description:La fonction permet de faire clignoter la led en vert pout montrer que la batterie du controle est faible

Param�tre d'entr�e:  pointeur pour une variable �tat des del
Donn�e retour de la fonction: Aucun
*/
void SetBattFaible(t_ledstate* ledstate); // clignotemtn vert

/*
fn SetBattTooHot
Description:La fonction permet de faire clignoter la led en rouge pout montrer que la temp�rature de la batterie
est trop chaude

Param�tre d'entr�e:  pointeur pour une variable �tat des del
Donn�e retour de la fonction: Aucun
*/
void SetBattTooHot(t_ledstate* ledstate); //  clignotmeetn rouge

/*
fn SetObjectDetected
Description:La fonction permet de faire clignoter la led en alternant vert et rouge pout montrer qu'un
objet a �t� d�tect�

Param�tre d'entr�e:  pointeur pour une variable �tat des del
Donn�e retour de la fonction: Aucun
*/
void SetObjectDetected(t_ledstate* ledstate); // clignotemtn vert et rouge


/*
fn SetEndOfCourse
Description:La fonction permet de faire clignoter la led en alternant vert et jaune pout montrer 
qu'on a atteint la fin de course

Param�tre d'entr�e:  pointeur pour une variable �tat des del
Donn�e retour de la fonction: Aucun
*/
void SetEndOfCourse(t_ledstate* ledstate); // clignotement vert et jaune

/*
fn SetCantGoSetPoint
Description:La fonction permet de faire clignoter la led en  jaune pout montrer 
qu'on ne peut atteindre la position d�sir�e 

Param�tre d'entr�e:  pointeur pour une variable �tat des del
Donn�e retour de la fonction: Aucun
*/
void SetCantGoSetPoint(t_ledstate* ledstate);// clignotement jaune

/*
fn  SetEmergencyStop
Description:La fonction permet d'allumer la led en rouge constant pour signaler
qu'il y a un arr�t d'urgence

Param�tre d'entr�e:  pointeur pour une variable �tat des del
Donn�e retour de la fonction: Aucun
*/
void SetEmergencyStop(t_ledstate* ledstate);

/*
fn  SetNoComms
Description:La fonction permet d'allumer la led en jaune constant pour signaler
que le controle ne re�oit pas de donn�e de l'interface

Param�tre d'entr�e:  pointeur pour une variable �tat des del
Donn�e retour de la fonction: Aucun
*/
void SetNoComms(t_ledstate* ledstate);




#endif