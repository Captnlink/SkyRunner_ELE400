/**
    Project : CableCam_Chariot\n
    @file Batterie_tension.h
    Description fonction pour utliser le type batterie et lire la tension de la batterie 
    @author Wsimon
	
    @version 1.0
    @date March 20, 2016
	
*/
#ifndef OK_BATTERIE // pour empecher la double-compilation 
#define OK_BATTERIE 

#define NB_ECHANTILLON_TENSION 5  //quantit� d'�chantillon pour renvoyer la valeur de la tension
#define PIN_BATTERIE_TENSION	// PIN o� LIRE LA TENSION DE LA BATTERIE
#define TENSION_BATTERIE_MAX 15 //Valeur de la tension maximum de la batterie a mesur�
#define TENSION_BATTERIE_FAIBLE 12 //Valeur de la tension o� on consid�re que la batterie a mesur� est faible
#define TENSION_BATTERIE_EPUISE 11 //Valeur de la tension o� on consid�re que la batterie a mesur� est �puis�


//type batterie
typedef struct
{
	double tension;
	double temp;
}batterie;


/* get_tension permet de renvoyer la valeur de la tension d'une variable de type <batterie> .
Param�tre d'entr�e:  variable de type batterie
Donn�e Retour de la fonction: la tension de la variable batterie
*/
double get_tension(batterie batterie);// permet de retourner la tension du type batterie
  

/* set_tension permet de modifier la valeur d'une variable de type <batterie> .
Param�tre d'entr�e: Adresse d'une variable de type batterie, valeur de la 
nouvelle tension a mettre dans la variable
Donn�e Retour de la fonction: Aucun
*/
void set_tension(batterie* batterie_tempo,double voltage); // permet de modifier la tension du type batterie



/* initialiser_batterie permet d'initialiser la valeur d'une variable de type <batterie> .
� la fin de la fonction, on retourne les donn�es d'initialisation.
Param�tre d'entr�e: Aucun
Donn�e Retour de la fonction: les donn�es intiale du type batterie
*/
batterie initialiser_batterie(); //permet d'ins�rer les valeurs de base


/* lire_tension permet de lire la tension de la batterie .
� la fin de la fonction, on va modifier la valeur de la tension de la variable d'entr�e
Param�tre d'entr�e: l'adresse des donn�es batteries
Donn�e Retour de la fonction: Aucun
*/
 void lire_tension(batterie* batterie_voltage);


#endif
