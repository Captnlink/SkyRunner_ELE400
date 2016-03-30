
/**
    Project : CableCam_Chariot\n
    @file etat_del.cpp
    Description fonction pour afficher l'�tat des del d�pendamment de l'�tat du controlleur
	Il reste � tester sur un montage physique
    @author Wsimon
	
    @version 1.0
    @date March 28, 2016
	
*/

#include "etat_del.h"
#include "Arduino.h"


void set_etat_controller(t_ledstate* ledstate, char etat)
{
	// modifie la valeur de l'etat des dels par rapport � celui du controleur
	ledstate->etat_controller=etat;

}

// initilialiser l'etat des led avec param�tre par  d�faut

t_ledstate initialiser_ledstate()
{
	t_ledstate init_ledstate;
	init_ledstate.green=ON; //consid�re qu'au d�but la led est vert
	init_ledstate.red=OFF;
	init_ledstate.etat_controller=STATE_GOOD;//consid�re qu'au l'etat est "tout va bien"
	init_ledstate.previousMillis=0;// la valeur du dernier clignotement mis a 

	return init_ledstate;
}



//�TAT tout va bien= LUMI�re verte costante
void SetGood(t_ledstate* ledstate) //OK
{
	/* On modifie modifie l'�tat de led en �tatn sure de
	couper l'alimentation pour la lumi�re rouge s'il �tat alum� avant
	et d'afficher la lumi�re vert*/

	if(ledstate->red != OFF)
	{
		ledstate->red=OFF;
		digitalWrite(PIN_LD_RED,ledstate->red);
	}

	/*Affiche la del est verte si il l'�tait pas encore */
	if(ledstate->green != ON)
	{
		ledstate->green=ON;
		digitalWrite(PIN_LD_GREEN,ledstate->green); 
	}
	// si les param�tres n'entre dans aucune condition, alors on garde les meme param�tres etla led reste au meme etat
}



//�TAT batterie faible LUMI�re verte clignotante
void SetBattFaible(t_ledstate* ledstate)
{
	// s'assure que la lumi�re rouge soit pas actif pour avoir la lumi�re verte 
	if(ledstate->red != OFF)
	{
		ledstate->red=OFF;
		digitalWrite(PIN_LD_RED,ledstate->red);
	}

	/*la lumi�re verte va s'allumer ou se fermer  si le
	d�lai entre le moment pr�sent et la dernie`re ou il a clignoter
	et plus grand que le d�lai de clingotment*/
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
	// si les param�tres n'entre dans aucune condition, alors on garde les meme param�tres etla led reste au meme etat
}



//�TAT batterie trop chaude LUMI�re rouge clignotante
void SetBattTooHot(t_ledstate* ledstate)
{

	// s'assure que la lumi�re verte soit pas actif  
	if(ledstate->green != OFF)
	{
		ledstate->green=OFF;
		digitalWrite(PIN_LD_GREEN,ledstate->green);

	}

	/*la lumi�re rouge va s'allumer ou se fermer  si le
	d�lai entre le moment pr�sent et la dernie`re ou il a clignoter
	et plus grand que le d�lai de clingotment*/
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
	// si les param�tres n'entre dans aucune condition, alors on garde les meme param�tres etla led reste au meme etat
}


//�TAT object d�tect�  clignotemtn vert et rouge
void SetObjectDetected(t_ledstate* ledstate)
{
	/*la lumi�re va s'allumer ou se fermer  si le
	d�lai entre le moment pr�sent et la dernie`re ou il a clignoter
	et plus grand que le d�lai de clingotment*/



	unsigned long currentMillis= millis();
	/* D�fini que si la led est jaune en passe au vert sans d�lai
	*/
	if((ledstate->green==ON && ledstate->red==ON) )
	{
		ledstate->red=OFF;
		digitalWrite(PIN_LD_RED,ledstate->red);

		digitalWrite(PIN_LD_GREEN,ledstate->green);

		ledstate->previousMillis=currentMillis;
	}
	// D�fini que si la led est verte en passe au rouge apres le delai de clignotement
	else if((ledstate->green==ON && ledstate->red==OFF) && (currentMillis-ledstate->previousMillis >= DELAY_CLIGNOTEMENT))
	{
		ledstate->green=OFF;
		digitalWrite(PIN_LD_GREEN,ledstate->green);

		ledstate->red=ON;
		digitalWrite(PIN_LD_RED,ledstate->red);

		ledstate->previousMillis=currentMillis;
	}
	//D�fini que si la led est rouge en passe au vert apres le delai de clignotement
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
	// si les param�tres n'entre dans aucune condition, alors on garde les meme param�tres et la led reste au meme etat
}


//�TAT chassis a atteint la fin de course  clignotemnt vert et jaune
void SetEndOfCourse(t_ledstate* ledstate)
{


	unsigned long currentMillis= millis();
	/* D�fini que si la led est jaune en passe au vert sans d�lai
	*/

	/*la lumi�re va s'allumer ou se fermer  si le
	d�lai entre le moment pr�sent et la dernie`re ou il a clignoter
	et plus grand que le d�lai de clingotment*/
	if((ledstate->green==ON && ledstate->red==ON) && (currentMillis-ledstate->previousMillis >= DELAY_CLIGNOTEMENT))
	{
		ledstate->red=OFF;
		digitalWrite(PIN_LD_RED,ledstate->red);

		digitalWrite(PIN_LD_GREEN,ledstate->green);

		ledstate->previousMillis=currentMillis;
	}
	// D�fini que si la led est verte en passe au jaune
	else if((ledstate->green==ON && ledstate->red==OFF) && (currentMillis-ledstate->previousMillis >= DELAY_CLIGNOTEMENT))
	{
		ledstate->red=ON;
		digitalWrite(PIN_LD_RED,ledstate->red);

		digitalWrite(PIN_LD_GREEN,ledstate->green);

		ledstate->previousMillis=currentMillis;
	}
	//D�fini que si la led est rouge en passe au vert
	else if((ledstate->green==OFF && ledstate->red==ON) && (currentMillis-ledstate->previousMillis >= DELAY_CLIGNOTEMENT))
	{


		ledstate->green=ON;
		digitalWrite(PIN_LD_GREEN,ledstate->green);

		digitalWrite(PIN_LD_RED,ledstate->red);

		ledstate->previousMillis=currentMillis;
	}// si la led n'est pas allum�  en  passe au vert
	else if((ledstate->green==OFF && ledstate->red==OFF) )
	{
		ledstate->green=ON;
		digitalWrite(PIN_LD_GREEN,ledstate->green);

		digitalWrite(PIN_LD_RED,ledstate->red);

		ledstate->previousMillis=currentMillis;
	}

	// si les param�tres n'entre dans aucune condition, alors on garde les meme param�tres etla led reste au meme etat
}


//�TAT chassis ne peut aller � la distance voulu  clignotemtn jaune
void SetCantGoSetPoint(t_ledstate* ledstate)
{
	// s'assure que la lumi�re soit jaune s'il n'�taiti pas avant
	if(ledstate->red)
	{
		ledstate->red=ON;
		digitalWrite(PIN_LD_RED,ledstate->red);

		ledstate->red=ON;
		digitalWrite(PIN_LD_RED,ledstate->red);
	}

	/*la lumi�re jaune va s'allumer ou se fermer  si le
	d�lai entre le moment pr�sent et la dernie`re ou il a clignoter
	et plus grand que le d�lai de clingotment*/
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
	// d�fini que si la led est verte en passe au jaune
	else if(ledstate->green==ON && ledstate->red==OFF)
	{
		ledstate->red=ON;
		digitalWrite(PIN_LD_RED,ledstate->red);
	}
	// d�fini que si led �tait rouge en passe au vert
	else if(ledstate->green==OFF && ledstate->red==ON)
	{

		ledstate->red=ON;
		digitalWrite(PIN_LD_RED,ledstate->red);

		ledstate->green=ON;
		digitalWrite(PIN_LD_GREEN,ledstate->green);
	}
	// si les param�tres n'entre dans aucune condition, alors on garde les meme param�tres etla led reste au meme etat
}

//�TAT l'arret d'urgence a �t� enclench�  lumi�re rouge constante
void SetEmergencyStop(t_ledstate* ledstate)
{
	/* On modifie modifie l'�tat de led en �tat s�r de
	couper l'alimentation pour la lumi�re vert s'il �tat alum� avant
	et ensuite d'afficher la lumi�re rouge*/

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

	// si les param�tres n'entre dans aucune condition, alors on garde les meme param�tres etla led reste au meme etat
}



//�TAT le controle ne recoit pas de donn�e de la t�l�commande  lumi�re jaune constante
void SetNoComms(t_ledstate* ledstate)
{
	/* On modifie modifie l'�tat de led en �tat s�r de
	couper l'alimentation pour la lumi�re vert s'il �tat alum� 
	et ensuite d'afficher la lumi�re rouge*/

	if(!(ledstate->green == ON) && (ledstate->red == ON))
	{
		ledstate->green=ON;
		digitalWrite(PIN_LD_GREEN,ledstate->green); 

		ledstate->red=ON;
		digitalWrite(PIN_LD_RED,ledstate->red);
	}
	// si les param�tres n'entre dans aucune condition, alors on garde les meme param�tres etla led reste au meme etat
}


