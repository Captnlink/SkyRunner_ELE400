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

#define NB_ECHANTILLON_TENSION 5  //quantité d'échantillon pour renvoyer la valeur de la tension
#define PIN_BATTERIE_TENSION	// PIN où LIRE LA TENSION DE LA BATTERIE
#define TENSION_BATTERIE_MAX 15 //Valeur de la tension maximum de la batterie a mesuré
#define TENSION_BATTERIE_FAIBLE 12 //Valeur de la tension où on considère que la batterie a mesuré est faible
#define TENSION_BATTERIE_EPUISE 11 //Valeur de la tension où on considère que la batterie a mesuré est épuisé


//type batterie
typedef struct
{
	double tension;
	double temp;
}batterie;


/* get_tension permet de renvoyer la valeur de la tension d'une variable de type <batterie> .
Paramètre d'entrée:  variable de type batterie
Donnée Retour de la fonction: la tension de la variable batterie
*/
double get_tension(batterie batterie);// permet de retourner la tension du type batterie
  

/* set_tension permet de modifier la valeur d'une variable de type <batterie> .
Paramètre d'entrée: Adresse d'une variable de type batterie, valeur de la 
nouvelle tension a mettre dans la variable
Donnée Retour de la fonction: Aucun
*/
void set_tension(batterie* batterie_tempo,double voltage); // permet de modifier la tension du type batterie



/* initialiser_batterie permet d'initialiser la valeur d'une variable de type <batterie> .
À la fin de la fonction, on retourne les données d'initialisation.
Paramètre d'entrée: Aucun
Donnée Retour de la fonction: les données intiale du type batterie
*/
batterie initialiser_batterie(); //permet d'insérer les valeurs de base


/* lire_tension permet de lire la tension de la batterie .
À la fin de la fonction, on va modifier la valeur de la tension de la variable d'entrée
Paramètre d'entrée: l'adresse des données batteries
Donnée Retour de la fonction: Aucun
*/
 void lire_tension(batterie* batterie_voltage);


#endif
