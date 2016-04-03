/**
    Project : CableCam_Chariot\n
    @file Etat_Led.cpp
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


#include"Etat_led.h"

#define TENSION_BATTERIE_FAIBLE 11  // tension d�finit comme trop basse en volt

#define TEMP_BATTERIE_TROP_CHAUDE 70 // temperature d�finit comme trop chaude en celsius

void etat_update(int previous_led_flash/*, donn�es controlleur*/)
{
	int m_etape_flash ;
	int m_etape_erreur=0;
	m_etape_flash++;
	
	int statut_controlleur=1; // renvoie 1-> si le controlleur  va bien 0-> s'il a des proble`mes

	


	// �TAT batterie faible , on va clignot� la lumi�re verte
	if(m_etape_erreur==1 && SetBattFaible())
	{
		statut_controlleur=0;
		// Apres avoir clignot� la lumi�re verte  pendant 8 cycle de flash, on passe au prochaine �tat
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


			// �TAT batterie trop chaude , on va clignot� la lumi�re rouge
	if(m_etape_erreur==2 && SetBattTooHot())
	{
		statut_controlleur=0;
		// Apres avoir clignot� la led en rouge  pendant 8 cycle de flash, on passe au prochaine �tat
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

			// �TAT objet d�tect� , on va clignot� la led entre le vert et le rouge
	if(m_etape_erreur==3 && SetObjectDetected())
	{
		statut_controlleur=0;
		// Apres avoir clignot� entre la led en vert et en rouge pendant 8 cycle de flash, on passe au prochaine �tat
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

 
	


		//�TAT l'arret d'urgence a �t� enclench�  lumi�re rouge constante
	if(m_etape_erreur==4 && SetEmergencyStop())
	{
		statut_controlleur=0;
		// Apres avoir clignot� entre la led en VERT et en JAUNE  pendant 8 cycle de flash, on passe au prochaine �tat et on �teint la led
		if(m_etape_flash==7)
		{
			etat_led( NO_LIGHT);
			m_etape_erreur++;
			m_etape_flash=0;
		}
	// tant que les 8 cycles ne sont pas termin�s la led est en rouge 
		else 
		{
			etat_led(RED);
		}
	}
	else
	{
		m_etape_erreur++;
	}


			//�TAT le controle ne recoit pas de donn�e de la t�l�commande  lumi�re jaune constante
	if(m_etape_erreur==5 && SetNoComms())
	{
		statut_controlleur=0;
		// Apres avoir clignot� entre la led en VERT et en JAUNE  pendant 8 cycle de flash, on passe au prochaine �tat
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
	//�TAT chassis a atteint la fin de course  clignotemnt vert et jaune
	if(m_etape_erreur==4 && SetEndOfCourse())
	{
	statut_controlleur=0;
		// Apres avoir clignot� entre la led en VERT et en JAUNE  pendant 8 cycle de flash, on passe au prochaine �tat
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


		//�TAT chassis ne peut aller � la distance voulu  clignotemnt jaune
	if(m_etape_erreur==5 && SetCantGoSetPoint())
	{
	statut_controlleur=0;
		// Apres avoir clignot�  la led en JAUNE  pendant 8 cycle de flash, on passe au prochaine v�rifie le prochain �tat et on �teint la led
		if(m_etape_flash==7)
		{
				etat_led( NO_LIGHT);
			m_etape_erreur++;
			m_etape_flash=0;
		}
		// permet de faire clignoter la led chaque flash partir, � chaque etape_flash pair c'est jaune
		// � chaque etape_flash impair la led est �teinte
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

			// S�TAT  Tout va bien est la led reste en vert
	// si on est pas pass� par  les erreurs alors tout va bien
	if(m_etape_erreur==8 && statut_controlleur==1)
	{
		
		// Apres que la led reste en vert  pendant 8 cycle de flash, on passe au prochaine �tat
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
		//Allumer seulement lumi�re verte
	case GREEN: digitalWrite(PIN_LD_RED,OFF);
				 digitalWrite(PIN_LD_GREEN,ON);
				 break;

		//Allumer led rouge et vert pour lumi�re jaune
	case YELLOW: digitalWrite(PIN_LD_RED,ON);
				 digitalWrite(PIN_LD_GREEN,ON);
				 break;
		//�teindre toutes les lumi�res
	case NO_LIGHT: digitalWrite(PIN_LD_RED,OFF);
				 digitalWrite(PIN_LD_GREEN,OFF);
				 break;
	}

}

// v�rifie si le niveau de tension de la batterie est plus faible que la tension d�finit faible
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

// v�rifie si la temperaturede la batterie est plus faible que la temperature d�finit comme trop chaude
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


// v�rifie si la temperaturede la batterie est plus faible que la temperature d�finit comme trop chaude
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




// v�rifie si la temperaturede la batterie est plus faible que la temperature d�finit comme trop chaude
bool SetEmergencyStop(int arr�t_urgence)
{
	bool etat;

	
	if(arr�t_urgence==0)
	{

		etat= false;
	}
	else
	{
		etat=true;
	}
	return etat;
}


// v�rifie si la temperaturede la batterie est plus faible que la temperature d�finit comme trop chaude
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