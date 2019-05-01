/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		//nds-rako garatuta dagoen liburutegia
#include <stdio.h>		//c-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		//c-ko liburutegi estandarra memoria erreserbak eta zenbaki konbertsioak egiteko
#include <unistd.h>		//Sistema eragileen arteko konpatibilitatea ziurtatzeko liburutegia
#include <time.h>		//Ausazko taula sortzeko liburutegia

//Geuk garatutako fitxategiak
	
#include "definizioak.h"
#include "periferikoak.h"
#include "zerbitzuErrutinak.h"
#include "fondoak.h"
#include "spriteak.h"

#include "eragiketak.h"

void jokoa01()
{	
	//aldagai baten definizioa
	int i = 50;
	int tekla = 0;

	int aurrekoX = 10, aurrekoY = 10; // Fitxategi honetan bakarrik erabiltzen dira

	kasilaX = 100;
	kasilaY = 100;
	kasilaPX = 16;
	kasilaPY = 16;
	
	EGOERA = HASTEKO;
	
	iprintf("\x1b[22;5HHau idazte proba bat da");	//Honek, 22 lerroan eta 5 zutabean hasiko da idazten.
													//Aldagai baten idatzi nahi izanez gero, %d komatxoen barruan eta 
													 //komatxoen kanpoan aldagaiaren balioa.
	iprintf("\x1b[23;5HAldagai proba. Balioa=%d", i);

	//***************************************************************************************//
	EtenakBaimendu();						// Etenak baimendu behar dira.
	konfiguratuTeklatua(0x40F3);			// Teklatua konfiguratu behar da.	
	konfiguratuTenporizadorea(32764, 0xC3);	// Tenporizadorea konfiguratu behar da.
	TekEtenBaimendu();						// Teklatuaren etenak baimendu behar dira.
	DenbEtenBaimendu();						// Tenporizadorearen etenak baimendu behar dira.
	etenZerbErrutEzarri();					// Etenen zerbitzu errutinak ezarri behar dira.
	//***************************************************************************************//
	
	srand(time(0)); // Partida bakoitzean taula ezberdina lortzeko
	taulaNagusiaEzarri();
	erakutsiTaula(); // Fondoa
	erakutsiAukera(2, kasilaPX, kasilaPY); // Lehenengo posizioa (0, 0)

	idatziPantailan(); // Taulako zenbakiak karaktereetan (probak egiteko)
//Inkesta egin behar da. SELECT tekla sakatzean 
//Egoera aldatu eta programa bukatu
	while(EGOERA != BUKATU)
	{	
		touchRead(&PANT_DAT);
		iprintf("\x1b[10;0H--------------------------------");
		iprintf("\x1b[14;0H     Pantailan x koord: %d  ", PANT_DAT.px);
		iprintf("\x1b[15;0H     Pantailan y koord: %d  ", PANT_DAT.py);
		
		if ((15 < PANT_DAT.px && PANT_DAT.px < 176) &&
		 (15 < PANT_DAT.py && PANT_DAT.py < 176))
		{
			EGOERA = KONTATZEN;
			kasilaX = (PANT_DAT.px - 16) / 16;
			kasilaY = (PANT_DAT.py - 16) / 16;
			kasilaPX = PANT_DAT.px - (PANT_DAT.px % 16);
			kasilaPY = PANT_DAT.py - (PANT_DAT.py % 16);
			iprintf("\x1b[17;0H     Kasila koord: %d, %d  ", kasilaX, kasilaY);
		}
		
		if ((kasilaX < 10 && kasilaY < 10) && 
			(PANT_DAT.px == 0 && PANT_DAT.py == 0))
		{
			iprintf("\x1b[19;0H     Sakatutako kasila: %d, %d  ", kasilaX, kasilaY);
			iprintf("\x1b[20;0H     Sakatutako kasila: %d, %d  ", kasilaPX, kasilaPY);
			if (aurrekoX != kasilaX || aurrekoY != kasilaY)
			{
				erakutsiAukera(2, kasilaPX, kasilaPY);
				hautatu(kasilaX, kasilaY);
				aurrekoX = kasilaX;
				aurrekoY = kasilaY;
			}
			//ebatzi(kasilaX, kasilaY);
		}
	}

}

