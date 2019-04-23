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
#include "spriteak.h"


void jokoa01()
{	
	//aldagai baten definizioa
	int i = 50;
	int tekla = 0;

	int kasilaX = 100, kasilaY = 100;
	int kasilaPX = 16, kasilaPY = 16;
	
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
	
	erakutsiTaula();
//Inkesta egin behar da. SELECT tekla sakatzean 
//Egoera aldatu eta programa bukatu
	while(EGOERA != BUKATU)
	{
		touchRead(&PANT_DAT);
		iprintf("\x1b[0;0H01234567890123456789012345678901");
		iprintf("\x1b[4;0H     Pantailan x koord: %d  ", PANT_DAT.px);
		iprintf("\x1b[5;0H     Pantailan y koord: %d  ", PANT_DAT.py);
		
		if ((15 < PANT_DAT.px && PANT_DAT.px < 175) &&
		 (15 < PANT_DAT.py && PANT_DAT.py < 175))
		{
			kasilaX = (PANT_DAT.px - 16) / 16;
			kasilaY = (PANT_DAT.py - 16) / 16;
			kasilaPX = PANT_DAT.px - (PANT_DAT.px % 16);
			kasilaPY = PANT_DAT.py - (PANT_DAT.py % 16);
			iprintf("\x1b[7;0H     Kasila koord: %d, %d  ", kasilaX, kasilaY);
		}
		
		if ((kasilaX < 16 && kasilaY < 16) && 
			(PANT_DAT.px == 0 && PANT_DAT.py == 0))
		{
			iprintf("\x1b[9;0H     Sakatutako kasila: %d, %d  ", kasilaX, kasilaY);
			iprintf("\x1b[10;0H     Sakatutako kasila: %d, %d  ", kasilaPX, kasilaPY);
			erakutsiAukera(0, kasilaPX, kasilaPY);
			//ebatzi(kasilaX, kasilaY);
		}
	}

}

