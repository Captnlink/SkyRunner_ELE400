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

void etat_update(int previous_led_flash/*, données controlleur*/)
{
	int m_etape_flash ;
	int m_etape_erreur=0;
	m_etape_flash++;
	
	int statut_controlleur=1; // renvoie 1-> si le controlleur  va bien 0-> s'il a des proble`mes

	


	// ÉTAT batterie faible , on va clignoté la lumière verte
	if(m_etape_erreur==1 && SetBattFaible())
	{
		statut_controlleur=0;
		// Apres avoir clignoté la lumière verte  pendant 8 cycle de flash, on passe au prochaine état
		if(m_etape_flash==7)
		{
			etat_led( NO_LIGHT);
			m_etape_erreur++;
			m_etape_flash=0;
		}
		else if(m_etape_flash %2==0)
		{
			etat_led(GREEN);
		}
		else if(m_etape_flash %2==0)
		{
			etat_led(NO_LIGHT);
		}
	}
	else
	{
		m_etape_erreur++;
	}


			// ÉTAT batterie trop chaude , on va clignoté la lumière rouge
	if(m_etape_erreur==2 && SetBattTooHot())
	{
		statut_controlleur=0;
		// Apres avoir clignoté la led en rouge  pendant 8 cycle de flash, on passe au prochaine état
		if(m_etape_flash==7)
		{
			etat_led( NO_LIGHT);
			m_etape_erreur++;
			m_etape_flash=0;
		}
		else if(m_etape_flash %2==0)
		{
			etat_led(RED);
		}
		else if(m_etape_flash %2==0)
		{
			etat_led(NO_LIGHT);
		}
	}
	else
	{
		m_etape_erreur++;
	}

			// ÉTAT objet détecté , on va clignoté la led entre le vert et le rouge
	if(m_etape_erreur==3 && SetObjectDetected())
	{
		statut_controlleur=0;
		// Apres avoir clignoté entre la led en vert et en rouge pendant 8 cycle de flash, on passe au prochaine état
		if(m_etape_flash==7)
		{
			etat_led( NO_LIGHT);
			m_etape_erreur++;
			m_etape_flash=0;
		}
		else if(m_etape_flash %2==0)
		{
			etat_led(GREEN);
		}
		else if(m_etape_flash %2==0)
		{
			etat_led(RED);
		}
	}
	else
	{
		m_etape_erreur++;
	}

 
	


		//ÉTAT l'arret d'urgence a été enclenché  lumière rouge constante
	if(m_etape_erreur==4 && SetEmergencyStop())
	{
		statut_controlleur=0;
		// Apres avoir clignoté entre la led en VERT et en JAUNE  pendant 8 cycle de flash, on passe au prochaine état et on éteint la led
		if(m_etape_flash==7)
		{
			etat_led( NO_LIGHT);
			m_etape_erreur++;
			m_etape_flash=0;
		}
	// tant que les 8 cycles ne sont pas terminés la led est en rouge 
		else 
		{
			etat_led(RED);
		}
	}
	else
	{
		m_etape_erreur++;
	}


			//ÉTAT le controle ne recoit pas de donnée de la télécommande  lumière jaune constante
	if(m_etape_erreur==5 && SetNoComms())
	{
		statut_controlleur=0;
		// Apres avoir clignoté entre la led en VERT et en JAUNE  pendant 8 cycle de flash, on passe au prochaine état
		if(m_etape_flash==7)
		{
			etat_led( NO_LIGHT);
			m_etape_erreur++;
			m_etape_flash=0;
		}
	
		else 
		{
			etat_led(YELLOW);
		}
	}
	else
	{
		m_etape_erreur++;
	}

	/*
	//ÉTAT chassis a atteint la fin de course  clignotemnt vert et jaune
	if(m_etape_erreur==4 && SetEndOfCourse())
	{
	statut_controlleur=0;
		// Apres avoir clignoté entre la led en VERT et en JAUNE  pendant 8 cycle de flash, on passe au prochaine état
		if(m_etape_flash==7)
		{
				etat_led( NO_LIGHT);
			m_etape_erreur++;
			m_etape_flash=0;
		}
		else if(m_etape_flash %2==0)
		{
			etat_led(GREEN);
		}
		else if(m_etape_flash %2==0)
		{
			etat_led(YELLOW);
		}
	}
	else
	{
		m_etape_erreur++;
	}


		//ÉTAT chassis ne peut aller à la distance voulu  clignotemnt jaune
	if(m_etape_erreur==5 && SetCantGoSetPoint())
	{
	statut_controlleur=0;
		// Apres avoir clignoté  la led en JAUNE  pendant 8 cycle de flash, on passe au prochaine vérifie le prochain état et on éteint la led
		if(m_etape_flash==7)
		{
				etat_led( NO_LIGHT);
			m_etape_erreur++;
			m_etape_flash=0;
		}
		// permet de faire clignoter la led chaque flash partir, à chaque etape_flash pair c'est jaune
		// à chaque etape_flash impair la led est éteinte
		else if(m_etape_flash %2==0)
		{
			etat_led(YELLOW);
		}
		else if(m_etape_flash %2==1)
		{
			etat_led(NO_LIGHT);
		}
	}
	else
	{
		m_etape_erreur++;
	}
	*/

			// SÉTAT  Tout va bien est la led reste en vert
	// si on est pas passé par  les erreurs alors tout va bien
	if(m_etape_erreur==8 && statut_controlleur==1)
	{
		
		// Apres que la led reste en vert  pendant 8 cycle de flash, on passe au prochaine état
		if(m_etape_flash==7)
		{
			etat_led( NO_LIGHT);
			m_etape_erreur++;
			m_etape_flash=0;
		}
	
		else 
		{
			etat_led(GREEN);
		}
	}
	else
	{
		m_etape_erreur++;
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