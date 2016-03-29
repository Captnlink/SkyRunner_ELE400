

/**
    Project : CableCam_Chariot\n
    @file etat_del.cpp
    Description fonction pour afficher l'état des del dépendamment de l'état du controlleur
	Il reste à tester sur un montage physique
    @author Wsimon
	
    @version 1.0
    @date March 28, 2016
	
*/

#include "etat_del.h"
#include "Arduino.h"


void set_etat_controller(t_ledstate* ledstate, char etat)
{
	// modifie la valeur de l'etat des dels par rapport à celui du controleur
	ledstate->etat_controller=etat;

}

// initilialiser l'etat des led avec paramètre par  défaut

t_ledstate initialiser_ledstate()
{
	t_ledstate init_ledstate;
	init_ledstate.green=ON; //considère qu'au début la led est vert
	init_ledstate.red=OFF;
	init_ledstate.etat_controller=STATE_GOOD;//considère qu'au l'etat est "tout va bien"
	init_ledstate.previousMillis=0;// la valeur du dernier clignotement mis a 

	return init_ledstate;
}



//ÉTAT tout va bien= LUMIère verte costante
void SetGood(t_ledstate* ledstate) //OK
{
	/* On modifie modifie l'état de led en étatn sure de
	couper l'alimentation pour la lumière rouge s'il état alumé avant
	et d'afficher la lumière vert*/

	if(ledstate->red != OFF)
	{
		ledstate->red=OFF;
		digitalWrite(PIN_LD_RED,ledstate->red);
	}

	/*Affiche la del est verte si il l'était pas encore */
	if(ledstate->green != ON)
	{
		ledstate->green=ON;
		digitalWrite(PIN_LD_GREEN,ledstate->green); 
	}
	// si les paramètres n'entre dans aucune condition, alors on garde les meme paramètres etla led reste au meme etat
}



//ÉTAT batterie faible LUMIère verte clignotante
void SetBattFaible(t_ledstate* ledstate)
{
	// s'assure que la lumière rouge soit pas actif pour avoir la lumière verte 
	if(ledstate->red != OFF)
	{
		ledstate->red=OFF;
		digitalWrite(PIN_LD_RED,ledstate->red);
	}

	/*la lumière verte va s'allumer ou se fermer  si le
	délai entre le moment présent et la dernie`re ou il a clignoter
	et plus grand que le délai de clingotment*/
	unsigned long currentMillis= millis();
	if(ledstate->green==ON && (currentMillis-ledstate->previousMillis >= DELAY_CLIGNOTEMENT))
	{
		ledstate->green=OFF;
		digitalWrite(PIN_LD_GREEN,ledstate->green);
		ledstate->previousMillis=currentMillis;
	}
	else if(ledstate->green==OFF && (currentMillis-ledstate->previousMillis >= DELAY_CLIGNOTEMENT))
	{
		ledstate->green=ON;
		digitalWrite(PIN_LD_GREEN,ledstate->green);
		ledstate->previousMillis=currentMillis;
	}
	// si les paramètres n'entre dans aucune condition, alors on garde les meme paramètres etla led reste au meme etat
}



//ÉTAT batterie trop chaude LUMIère rouge clignotante
void SetBattTooHot(t_ledstate* ledstate)
{

	// s'assure que la lumière verte soit pas actif  
	if(ledstate->green != OFF)
	{
		ledstate->green=OFF;
		digitalWrite(PIN_LD_GREEN,ledstate->green);

	}

	/*la lumière rouge va s'allumer ou se fermer  si le
	délai entre le moment présent et la dernie`re ou il a clignoter
	et plus grand que le délai de clingotment*/
	unsigned long currentMillis= millis();
	if(ledstate->red==ON && (currentMillis-ledstate->previousMillis >= DELAY_CLIGNOTEMENT))
	{
		ledstate->red=OFF;
		digitalWrite(PIN_LD_RED,ledstate->red);
		ledstate->previousMillis=currentMillis;
	}
	else if(ledstate->red==OFF && (currentMillis-ledstate->previousMillis >= DELAY_CLIGNOTEMENT))
	{
		ledstate->red=ON;
		digitalWrite(PIN_LD_RED,ledstate->red);
		ledstate->previousMillis=currentMillis;
	}
	// si les paramètres n'entre dans aucune condition, alors on garde les meme paramètres etla led reste au meme etat
}


//ÉTAT object détecté  clignotemtn vert et rouge
void SetObjectDetected(t_ledstate* ledstate)
{
	/*la lumière va s'allumer ou se fermer  si le
	délai entre le moment présent et la dernie`re ou il a clignoter
	et plus grand que le délai de clingotment*/



	unsigned long currentMillis= millis();
	/* Défini que si la led est jaune en passe au vert sans délai
	*/
	if((ledstate->green==ON && ledstate->red==ON) )
	{
		ledstate->red=OFF;
		digitalWrite(PIN_LD_RED,ledstate->red);

		digitalWrite(PIN_LD_GREEN,ledstate->green);

		ledstate->previousMillis=currentMillis;
	}
	// Défini que si la led est verte en passe au rouge apres le delai de clignotement
	else if((ledstate->green==ON && ledstate->red==OFF) && (currentMillis-ledstate->previousMillis >= DELAY_CLIGNOTEMENT))
	{
		ledstate->green=OFF;
		digitalWrite(PIN_LD_GREEN,ledstate->green);

		ledstate->red=ON;
		digitalWrite(PIN_LD_RED,ledstate->red);

		ledstate->previousMillis=currentMillis;
	}
	//Défini que si la led est rouge en passe au vert apres le delai de clignotement
	else if((ledstate->green==OFF && ledstate->red==ON) && (currentMillis-ledstate->previousMillis >= DELAY_CLIGNOTEMENT))
	{

		ledstate->red=OFF;
		digitalWrite(PIN_LD_RED,ledstate->red);

		ledstate->green=ON;
		digitalWrite(PIN_LD_GREEN,ledstate->green);

		ledstate->previousMillis=currentMillis;
	}
	else if((ledstate->green==OFF && ledstate->red==OFF) )
	{
		ledstate->green=ON;
		digitalWrite(PIN_LD_GREEN,ledstate->green);


		ledstate->previousMillis=currentMillis;
	}
	// si les paramètres n'entre dans aucune condition, alors on garde les meme paramètres et la led reste au meme etat
}


//ÉTAT chassis a atteint la fin de course  clignotemnt vert et jaune
void SetEndOfCourse(t_ledstate* ledstate)
{


	unsigned long currentMillis= millis();
	/* Défini que si la led est jaune en passe au vert sans délai
	*/

	/*la lumière va s'allumer ou se fermer  si le
	délai entre le moment présent et la dernie`re ou il a clignoter
	et plus grand que le délai de clingotment*/
	if((ledstate->green==ON && ledstate->red==ON) && (currentMillis-ledstate->previousMillis >= DELAY_CLIGNOTEMENT))
	{
		ledstate->red=OFF;
		digitalWrite(PIN_LD_RED,ledstate->red);

		digitalWrite(PIN_LD_GREEN,ledstate->green);

		ledstate->previousMillis=currentMillis;
	}
	// Défini que si la led est verte en passe au jaune
	else if((ledstate->green==ON && ledstate->red==OFF) && (currentMillis-ledstate->previousMillis >= DELAY_CLIGNOTEMENT))
	{
		ledstate->red=ON;
		digitalWrite(PIN_LD_RED,ledstate->red);

		digitalWrite(PIN_LD_GREEN,ledstate->green);

		ledstate->previousMillis=currentMillis;
	}
	//Défini que si la led est rouge en passe au vert
	else if((ledstate->green==OFF && ledstate->red==ON) && (currentMillis-ledstate->previousMillis >= DELAY_CLIGNOTEMENT))
	{


		ledstate->green=ON;
		digitalWrite(PIN_LD_GREEN,ledstate->green);

		digitalWrite(PIN_LD_RED,ledstate->red);

		ledstate->previousMillis=currentMillis;
	}// si la led n'est pas allumé  en  passe au vert
	else if((ledstate->green==OFF && ledstate->red==OFF) )
	{
		ledstate->green=ON;
		digitalWrite(PIN_LD_GREEN,ledstate->green);

		digitalWrite(PIN_LD_RED,ledstate->red);

		ledstate->previousMillis=currentMillis;
	}

	// si les paramètres n'entre dans aucune condition, alors on garde les meme paramètres etla led reste au meme etat
}


//ÉTAT chassis ne peut aller à la distance voulu  clignotemtn jaune
void SetCantGoSetPoint(t_ledstate* ledstate)
{
	// s'assure que la lumière soit jaune s'il n'étaiti pas avant
	if(ledstate->red)
	{
		ledstate->red=ON;
		digitalWrite(PIN_LD_RED,ledstate->red);

		ledstate->red=ON;
		digitalWrite(PIN_LD_RED,ledstate->red);
	}

	/*la lumière jaune va s'allumer ou se fermer  si le
	délai entre le moment présent et la dernie`re ou il a clignoter
	et plus grand que le délai de clingotment*/
	unsigned long currentMillis= millis();
	if((ledstate->green==ON && ledstate->red==ON)  && (currentMillis-ledstate->previousMillis >= DELAY_CLIGNOTEMENT))
	{
		ledstate->green=OFF;
		digitalWrite(PIN_LD_GREEN,ledstate->green);
		ledstate->previousMillis=currentMillis;
	}
	else if(ledstate->green==OFF && (currentMillis-ledstate->previousMillis >= DELAY_CLIGNOTEMENT))
	{
		ledstate->green=ON;
		digitalWrite(PIN_LD_GREEN,ledstate->green);
		ledstate->previousMillis=currentMillis;
	}
	// défini que si la led est verte en passe au jaune
	else if(ledstate->green==ON && ledstate->red==OFF)
	{
		ledstate->red=ON;
		digitalWrite(PIN_LD_RED,ledstate->red);
	}
	// défini que si led était rouge en passe au vert
	else if(ledstate->green==OFF && ledstate->red==ON)
	{

		ledstate->red=ON;
		digitalWrite(PIN_LD_RED,ledstate->red);

		ledstate->green=ON;
		digitalWrite(PIN_LD_GREEN,ledstate->green);
	}
	// si les paramètres n'entre dans aucune condition, alors on garde les meme paramètres etla led reste au meme etat
}

//ÉTAT l'arret d'urgence a été enclenché  lumière rouge constante
void SetEmergencyStop(t_ledstate* ledstate)
{
	/* On modifie modifie l'état de led en état sûr de
	couper l'alimentation pour la lumière vert s'il état alumé avant
	et ensuite d'afficher la lumière rouge*/

	if(ledstate->green != OFF)
	{
		ledstate->green=OFF;
		digitalWrite(PIN_LD_GREEN,ledstate->green); 
	}

	if(ledstate->red != ON)
	{
		ledstate->red=ON;
		digitalWrite(PIN_LD_RED,ledstate->red);
	}

	// si les paramètres n'entre dans aucune condition, alors on garde les meme paramètres etla led reste au meme etat
}



//ÉTAT le controle ne recoit pas de donnée de la télécommande  lumière jaune constante
void SetNoComms(t_ledstate* ledstate)
{
	/* On modifie modifie l'état de led en état sûr de
	couper l'alimentation pour la lumière vert s'il état alumé 
	et ensuite d'afficher la lumière rouge*/

	if(!(ledstate->green == ON) && (ledstate->red == ON))
	{
		ledstate->green=ON;
		digitalWrite(PIN_LD_GREEN,ledstate->green); 

		ledstate->red=ON;
		digitalWrite(PIN_LD_RED,ledstate->red);
	}
	// si les paramètres n'entre dans aucune condition, alors on garde les meme paramètres etla led reste au meme etat
}


