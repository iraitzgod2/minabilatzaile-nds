/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		//nds-rako garatuta dagoen liburutegia
#include <stdio.h>		//c-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		//c-ko liburutegi estandarra memoria erreserbak eta zenbaki konbertsioak egiteko
#include <unistd.h>		//Sistema eragileen arteko konpatibilitatea ziurtatzeko liburutegia

//Geuk garatutako fitxategiak
	
#include "definizioak.h"
#include "periferikoak.h"
#include "zerbitzuErrutinak.h"
#include "fondoak.h"


void jokoa01()
{	
	//aldagai baten definizioa
	int i = 50;
	int tekla = 0;
	
	iprintf("\x1b[22;5HHau idazte proba bat da");	//Honek, 22 lerroan eta 5 zutabean hasiko da idazten.
													//Aldagai baten idatzi nahi izanez gero, %d komatxoen barruan eta 
													 //komatxoen kanpoan aldagaiaren balioa.
	iprintf("\x1b[23;5HAldagai proba. Balioa=%d", i);

	//***************************************************************************************//
	// Etenak baimendu behar dira.
	// Teklatua konfiguratu behar da.	
	// Tenporizadorea konfiguratu behar da.
	// Teklatuaren etenak baimendu behar dira.
	// Tenporizadorearen etenak baimendu behar dira.
	// Etenen zerbitzu errutinak ezarri behar dira.
	//***************************************************************************************//
	EtenakBaimendu();
	konfiguratuTeklatua(0x4003);
	konfiguratuTenporizadorea(32764, 0xC3);
	TekEtenBaimendu();
	DenbEtenBaimendu();
	etenZerbErrutEzarri();
	
	erakutsiAtea();
//Inkesta egin behar da. SELECT tekla sakatzean 
//Egoera aldatu eta programa bukatu
	while(EGOERA != BUKATU)
	{
		touchRead(&PANT_DAT);
		iprintf("\x1b[0;0H01234567890123456789012345678901");
		iprintf("\x1b[4;0H     Pantailan x koord: %d  ", PANT_DAT.px);
		iprintf("\x1b[5;0H     Pantailan y koord: %d  ", PANT_DAT.py);
		//iprintf("\x1b[15;2HSakatutako Tekla: %d", EGOERA);
		/*if (EGOERA == L)
		{
			erakutsiAtea();
		}
		if (EGOERA == R)
		{
			erakutsiAteaIrekita();
		}*/
	}

}

