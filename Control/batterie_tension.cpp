
/**
    Project : CableCam_Chariot\n
    @file Batterie_tension.h
    Description: fonction pour lire la tension de la batterie et acc�der au type batterie 
    @author Wsimon
	Note: Il reste � tester la fonction de lecture de tension

    @version 1.0
    @date March 20, 2016
	
*/


#include <stdlib.h>
#include <stdio.h>

#include "batterie_tension.h"





// Voici la fonction permettant d'initialiser les informations de la batterie

double get_tension(batterie batterie)// permet de retourner la tension de la classe batterie
{return batterie.tension;}  


void set_tension(batterie* batterie_tempo,double voltage)
{
	//met la nouvelle tension dans la variable batterie � modifier,
	batterie_tempo->tension=voltage;
}  




batterie initialiser_batterie()
{
	/*cr�e un variable de type batterie et on lui met des donn�es intiales
	 consid�re temperature 0 degr�eC et tension a la valeur maximum*/
	batterie batterie_nouveau;
	batterie_nouveau.temp=0;
	batterie_nouveau.tension=TENSION_BATTERIE_MAX;

	return batterie_nouveau;
}

/* Fonction pour �tablir la communication pour lire les donn�es et afficher � l'�cran
void setup()
{
    Serial.begin(9600);
}
*/

void lire_tension(batterie* batterie_voltage)
{
	int i;
	double echantillons=0;
	double moyenne=0;
	double voltage=0;
  // take N samples in a row, with a slight delay

	/* Tester la lecture de donn�e avec arduino
  for (i=0; i< NB_ECHANTILLON_TENSION ; i++)
  {
   echantillons= echantillons+analogRead(PIN_BATTERIE_TENSION);
   delay(10);
  }
	moyenne=echantillons/NB_ECHANTILLON_TENSION;
	*/
	/* la formule permet de convertir la valeur envoy� par arduino de 0 a 1023, a une valeur
	entre la tension maximum de la batterie mesur�e et  la valeur de la tension quand la batterie mesur�e est �puis�  .*/


  voltage=(((moyenne/1023)*(TENSION_BATTERIE_MAX)));// voltage entre 0 et 15 V(Tension_BAtterie_max)

	if(voltage<TENSION_BATTERIE_EPUISE)
	{
		voltage=0;
	}
	else if(voltage>TENSION_BATTERIE_MAX)
	{
		voltage = 100;
	}
	else if(voltage>TENSION_BATTERIE_EPUISE & voltage<TENSION_BATTERIE_MAX)
	{
		voltage = (voltage-TENSION_BATTERIE_EPUISE)/(TENSION_BATTERIE_MAX-TENSION_BATTERIE_EPUISE)*100;
	}



  set_tension(batterie_voltage,voltage);

}


