/**
Project : CableCam_Chariot\n
@file Etat_Led.cpp
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


#include"Etat_led.h"

#define TENSION_BATTERIE_FAIBLE 11  // tension définit comme trop basse en volt

#define TEMP_BATTERIE_TROP_CHAUDE 70 // temperature définit comme trop chaude en celsius


/* tout d'abord, on va vérifier si le  temps  entre le dernier clignotement et a l'instant présent est plus grand que le délai prévu
si c'est respecté on vérifie les erreurs. si une erreur est détecté alors on modifie le statut erreur à true.
Si aucun erreur est détecté alors, on affiche l'etat tout va bien
*/
void etat_update(t_etat_led_control* etat_led_control/*, données controlleur*/)
{
	long current_millis=millis();

	// définit au déébut qu'il n'y a aucune erreur et vérifie s'il y en 
	etat_led_control->statut_erreur=false;

	// si le temps entre le dernier flash et l'instant présent est plus grand que le délai défini, 
	//on vérifie les état pour modifier les leds
	if(current_millis-etat_led_control->previous_led_flash>DELAY_ETAT_LED)
	{


		// ÉTAT batterie faible , on va clignoté la lumière verte
		if(etat_led_control->m_etape_erreur==1 && SetBattFaible(//double tension_batterie))
		{
			// si la batterie est faible on met statut de l'erreur à 1 pour dire qu'il a bien un probleme qui a été detecté
			etat_led_control->statut_erreur=true;
			// Apres avoir clignoté la lumière verte  pendant 8 cycle de flash, on passe au prochaine état
			if(etat_led_control->m_etape_flash==7) 
			{
				etat_led( NO_LIGHT);
				etat_led_control->m_etape_erreur++; // modifie etape _erreur pour vérifier la prochaine erreur détecté
				etat_led_control->m_etape_flash=0; // remet à 0 le cycle de clignotement
			}
			// si les 8 cycles ne sont pas effectués alors on fait clignoter la led
			else if(etat_led_control->m_etape_flash %2==0)
			{
				etat_led(GREEN);
			}
			else if(etat_led_control->m_etape_flash %2==0)
			{
				etat_led(NO_LIGHT);
			}
		}
		else
		{
			// si l'erreur n'est pas présente alors, on vérifie la prochaine
			etat_led_control->m_etape_erreur++;
		}


		// ÉTAT batterie trop chaude , on va clignoté la lumière rouge
		if(etat_led_control->m_etape_erreur==2 && SetBattTooHot(//double temp_batterie))
		{
			etat_led_control->statut_erreur=true;
			// Apres avoir clignoté la led en rouge  pendant 8 cycle de flash, on passe au prochaine état
			if(etat_led_control->m_etape_flash==7)
			{
				etat_led( NO_LIGHT);
				etat_led_control->m_etape_erreur++;
				etat_led_control->m_etape_flash=0; // remet clignotement à 0
			}
			else if(etat_led_control->m_etape_flash %2==0)
			{
				etat_led(RED);
			}
			else if(etat_led_control->m_etape_flash %2==0)
			{
				etat_led(NO_LIGHT);
			}
		}
		else
		{
			etat_led_control->m_etape_erreur++;
		}

		// ÉTAT objet détecté , on va clignoté la led entre le vert et le rouge
		if(etat_led_control->m_etape_erreur==3 && SetObjectDetected(//double distance_objet_detecte))
		{
			etat_led_control->statut_erreur=true;
			// Apres avoir clignoté entre la led en vert et en rouge pendant 8 cycle de flash, on passe au prochaine état
			if(etat_led_control->m_etape_flash==7)
			{
				etat_led( NO_LIGHT);
				etat_led_control->m_etape_erreur++;
				etat_led_control->m_etape_flash=0;
			}
			else if(etat_led_control->m_etape_flash %2==0)
			{
				etat_led(GREEN);
			}
			else if(etat_led_control->m_etape_flash %2==0)
			{
				etat_led(RED);
			}
		}
		else
		{
			etat_led_control->m_etape_erreur++;
		}





		//ÉTAT l'arret d'urgence a été enclenché  lumière rouge constante
		if(etat_led_control->m_etape_erreur==4 && SetEmergencyStop(//int arrêt_urgence))
		{
			etat_led_control->statut_erreur=true;
			// Apres avoir clignoté entre la led en VERT et en JAUNE  pendant 8 cycle de flash, on passe au prochaine état et on éteint la led
			if(etat_led_control->m_etape_flash==7)
			{
				etat_led( NO_LIGHT);
				etat_led_control->m_etape_erreur++;
				etat_led_control->m_etape_flash=0;
			}
			// tant que les 8 cycles ne sont pas terminés la led est en rouge 
			else 
			{
				etat_led(RED);
			}
		}
		else
		{
			etat_led_control->m_etape_erreur++;
		}


		//ÉTAT le controle ne recoit pas de donnée de la télécommande  lumière jaune constante
		if(etat_led_control->m_etape_erreur==5 && SetNoComms(//int statut_connexion_manette))
		{
			etat_led_control->statut_erreur=0;
			// Apres avoir clignoté entre la led en VERT et en JAUNE  pendant 8 cycle de flash, on passe au prochaine état
			if(etat_led_control->m_etape_flash==7)
			{
				etat_led( NO_LIGHT);
				etat_led_control->m_etape_erreur++;
				etat_led_control->m_etape_flash=0;
			}

			else 
			{
				etat_led(YELLOW);
			}
		}
		else
		{
			etat_led_control->m_etape_erreur++;
		}


		//ÉTAT chassis a atteint la fin de course  clignotemnt vert et jaune
		if(etat_led_control->m_etape_erreur==6 && SetEndOfCourse(//double distance_actuel))
		{
			etat_led_control->statut_erreur=true;
			// Apres avoir clignoté entre la led en VERT et en JAUNE  pendant 8 cycle de flash, on passe au prochaine état
			if(etat_led_control->m_etape_flash==7)
			{
				etat_led( NO_LIGHT);
				etat_led_control->m_etape_erreur++;
				etat_led_control->m_etape_flash=0;
			}
			else if(etat_led_control->m_etape_flash %2==0)
			{
				etat_led(GREEN);
			}
			else if(etat_led_control->m_etape_flash %2==0)
			{
				etat_led(YELLOW);
			}
		}
		else
		{
			etat_led_control->m_etape_erreur++;
		}


		//ÉTAT chassis ne peut aller à la distance voulu  clignotemnt jaune
		if(etat_led_control->m_etape_erreur==7 && SetCantGoSetPoint(//double distance_voulu))
		{
			etat_led_control->statut_erreur=0;
			// Apres avoir clignoté  la led en JAUNE  pendant 8 cycle de flash, on passe au prochaine vérifie le prochain état et on éteint la led
			if(etat_led_control->m_etape_flash==7)
			{
				etat_led( NO_LIGHT);
				etat_led_control->m_etape_erreur++;
				etat_led_control->m_etape_flash=0;
			}
			// permet de faire clignoter la led chaque flash partir, à chaque etape_flash pair c'est jaune
			// à chaque etape_flash impair la led est éteinte
			else if(etat_led_control->m_etape_flash %2==0)
			{
				etat_led(YELLOW);
			}
			else if(etat_led_control->m_etape_flash %2==1)
			{
				etat_led(NO_LIGHT);
			}
		}
		else
		{
			etat_led_control->m_etape_erreur++;
		}


		// SÉTAT  Tout va bien est la led reste en vert
		// si on est pas passé par  les erreurs alors tout va bien
		if(etat_led_control->m_etape_erreur==8 && etat_led_control->statut_erreur==1)
		{

			// Apres que la led reste en vert  pendant 8 cycle de flash, on passe au prochaine état
			if(etat_led_control->m_etape_flash==7)
			{
				etat_led( NO_LIGHT);
				etat_led_control->m_etape_erreur++;
				etat_led_control->m_etape_flash=0;
			}

			else 
			{
				etat_led(GREEN);
			}
		}
		else
		{
			etat_led_control->m_etape_erreur++;
		}


		if(etat_led_control->m_etape_erreur>7)
		{
			etat_led_control->m_etape_erreur=0;
		}

	}



}

void etat_led(int color)
{
	// tester pour s'assurer que les led s'allume


	switch(color)
	{
		//Allumer seulement led rouge
	case RED : digitalWrite(PIN_LD_RED,ON);
		digitalWrite(PIN_LD_GREEN,OFF);
		break;
		//Allumer seulement lumière verte
	case GREEN: digitalWrite(PIN_LD_RED,OFF);
		digitalWrite(PIN_LD_GREEN,ON);
		break;

		//Allumer led rouge et vert pour lumière jaune
	case YELLOW: digitalWrite(PIN_LD_RED,ON);
		digitalWrite(PIN_LD_GREEN,ON);
		break;
		//Éteindre toutes les lumières
	case NO_LIGHT: digitalWrite(PIN_LD_RED,OFF);
		digitalWrite(PIN_LD_GREEN,OFF);
		break;
	}

}

// vérifie si le niveau de tension de la batterie est plus faible que la tension définit faible
bool SetBattFaible(double tension_batterie)
{
	bool etat;

	if(tension_batterie<TENSION_BATTERIE_FAIBLE)
	{

		etat= true;
	}
	else
	{
		etat=false;
	}
	return etat;
}

// vérifie si la temperaturede la batterie est plus faible que la temperature définit comme trop chaude
bool SetBattTooHot(double temp_batterie)
{
	bool etat;

	if(temp_batterie<TEMP_BATTERIE_TROP_CHAUDE)
	{

		etat= true;
	}
	else
	{
		etat=false;
	}
	return etat;
}


// vérifie si la temperaturede la batterie est plus faible que la temperature définit comme trop chaude
bool SetObjectDetected(double distance_objet_detecte)
{
	bool etat;

	if(distance_objet_detecte != 0 )
	{

		etat= true;
	}
	else
	{
		etat=false;
	}
	return etat;
}




// vérifie si la temperaturede la batterie est plus faible que la temperature définit comme trop chaude
bool SetEmergencyStop(int arrêt_urgence)
{
	bool etat;


	if(arrêt_urgence==0)
	{

		etat= false;
	}
	else
	{
		etat=true;
	}
	return etat;
}


// vérifie si la temperaturede la batterie est plus faible que la temperature définit comme trop chaude
bool SetNoComms(int statut_connexion_manette)
{
	bool etat;


	if(statut_connexion_manette==1)
	{

		etat= false;
	}
	else
	{
		etat=true;
	}
	return etat;


}

bool SetEndOfCourse(double distance_actuel)
{
	double distance_max;
	bool etat;

	//si on a 50cm A LA FIN a gauche ou a la fin a droite ,alors on considère qu'on a atteint la fin 
	if(DISTANCE_AVANT_MAX-distance_actuel<0.5 ||DISTANCE_ARRIERE_MAX-distance_actuel<0.5 )
	{
		etat= true;
	}
	else
	{
		etat=false;
	}
	return etat;

}

bool SetCantGoSetPoint(double distance_voulu)
{
	bool etat;
	if(distance_voulu> DISTANCE_AVANT_MAX || distance_voulu> DISTANCE_ARRIERE_MAX)
	{
		etat=true;
	}
	else
	{
		etat=false;
	}
	return etat
}


//initialise etat_led
t_etat_led_control initialiser_etat_led()
{
	t_etat_led_control init_etat_led;
	init_etat_led.statut_erreur=false;
	init_etat_led.m_etape_erreur=0;
	init_etat_led.m_etape_flash=0;
	init_etat_led.previous_led_flash;

}
