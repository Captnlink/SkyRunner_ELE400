/**
    Project : CableCam_Chariot\n
    @file main.c
    @brief G�rent la r�partition des donn�es entre les diff�rents modules 

    @author Captnlink
	@author Wsimon
	
    @version 1.0
    @date March 20, 2016

	Lorsque le controlleur d�marre, il donne les configurations par default.
	Fait la gestion des tram de communication entrant/sortant.
	Contient la routine de contr�le.
	
*/


/**
	@fn changementConfig
	@brief v�rifie s'il y a un changement de configurations re�u de l'interface
	@Param [Name1] Trame de communication re�u
	@return bool true = changement, false = Aucun changement
	
	Permettant de v�rifier les diff�rences entre la trame re�u de l'interface 
	et la configuration actuel du contr�leur. 
	S'il a des diff�rences, on apporte  les modifications n�cessaires 

*/
bool changementConfig(){
	
	return false;
}

/**
	@fn etatLed
	@brief Envoie l'information du  controller � l'interface LED
	@Param [Name1] Information controlleur
	@return char binaire des erreurs
	
	La Led affiche un code de couleur et de flash pour indiquer
	les codes d'erreurs

*/
bool etatLed(){
	
	return false;
}