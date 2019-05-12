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
	//***************************************************************************************//
	EtenakBaimendu();						// Etenak baimendu behar dira.
	konfiguratuTeklatua(0x42F1);			// Teklatua konfiguratu behar da.	
	konfiguratuTenporizadorea(32764, 0xC3);	// Tenporizadorea konfiguratu behar da.
	TekEtenBaimendu();						// Teklatuaren etenak baimendu behar dira.
	DenbEtenBaimendu();						// Tenporizadorearen etenak baimendu behar dira.
	etenZerbErrutEzarri();					// Etenen zerbitzu errutinak ezarri behar dira.
	//***************************************************************************************//
	
	srand(time(0)); // Partida bakoitzean taula ezberdina lortzeko
	taulaNagusiaEzarri();

	//idatziPantailan(); // Taulako zenbakiak karaktereetan (probak egiteko)

	int aurrekoX = 10, aurrekoY = 10; // Fitxategi honetan bakarrik erabiltzen dira

	kasilaX = 100; // Taulako kasila (0, 9)
	kasilaY = 100;

	// Hasierako pantaila
	erakutsiSarrera();
	while(EGOERA == HASTEKO)
	{
		iprintf("\x1b[12;8HSakatu 'A' botoia");
	}

	ezabatuPantaila(); // Aurreko pantailan idatzitakoaren ezabapena

	// Menuaren pantaila
	kasilaPX = 24; // Hasierako kasilari dagokion pixela
	kasilaPY = 24;

	erakutsiHasiera(20, 24, 24);
	erakutsiHasiera(21, 24, 88);
	erakutsiHasiera(22, 24, 152);

	erakutsiZerrenda(); // Behin bakarrik erakustearekin nahikoa da
	iprintf("\x1b[23;2H Aurrera egiteko sakatu 'A' ");
	while(EGOERA == MENUA)
	{
		touchRead(&PANT_DAT);
		//iprintf("\x1b[23;2H Aurrera egiteko sakatu 'A' ");
		
		// Menuko aukera pantaila bidez kontrolatzeko
		if ((55 < PANT_DAT.px && PANT_DAT.px < 239) &&
			(15 < PANT_DAT.py && PANT_DAT.py < 48))
		{
			kasilaPY = 24;
		}
		if ((55 < PANT_DAT.px && PANT_DAT.px < 240) &&
			(79 < PANT_DAT.py && PANT_DAT.py < 112))
		{
			kasilaPY = 88;
		}
		if ((55 < PANT_DAT.px && PANT_DAT.px < 240) &&
			(143 < PANT_DAT.py && PANT_DAT.py < 176))
		{
			kasilaPY = 152;
		}

		// Menuko aukera mugitzeko kudeaketa
		switch (kasilaPY)
		{
			case 24: erakutsiAukera(0, 24, 24);
				break;
			case 88: erakutsiAukera(0, 24, 88);
				break;
			case 152: erakutsiAukera(0, 24, 152);
				break;
		}
	}
	ezabatuAukera(0, 24, 24);
	ezabatuHasiera(20, 24, 24);
	ezabatuHasiera(21, 24, 88);
	ezabatuHasiera(22, 24, 152);

	kasilaPX = 16; // Kasilari dagokion pixela (16, 32, 48, 64, ...)
	kasilaPY = 16;

	//Aurreko pantailan idatzitakoaren ezabapena
	ezabatuPantaila();

	//idatziPantailan(); // Taulako zenbakiak karaktereetan (probak egiteko)

	// Jokoaren kudeaketa
	iprintf("\x1b[23;7HMina kopurua: 20");
	erakutsiTaula();
	while(EGOERA != BUKATU)
	{
		touchRead(&PANT_DAT);
		// Pantaila ukitzerakoan aldagaiak definitu
		if ((15 < PANT_DAT.px && PANT_DAT.px < 176) &&
			(15 < PANT_DAT.py && PANT_DAT.py < 176))
		{
			kasilaX = (PANT_DAT.px - 16) / 16;
			kasilaY = (PANT_DAT.py - 16) / 16;
			kasilaPX = PANT_DAT.px - (PANT_DAT.px % 16);
			kasilaPY = PANT_DAT.py - (PANT_DAT.py % 16);
		}
		// Pantaila ukitzeari uzterakoan
		if ((kasilaX < 10 && kasilaY < 10) && 
			(PANT_DAT.px == 0 && PANT_DAT.py == 0))
		{
			if (aurrekoX != kasilaX || aurrekoY != kasilaY)
			{
				erakutsiAukera(0, kasilaPX, kasilaPY);
				aurrekoX = kasilaX;
				aurrekoY = kasilaY;
			}
		}

		if (SakatutakoTekla() == R) {
			if (EGOERA != KONTATZEN) {EGOERA = KONTATZEN;}
		//	ezabatuAukera(2, kasilaPX, kasilaPY);
			erakutsi(kasilaPX, kasilaPY);
			// erakutsiAukera(0, kasilaPX, kasilaPY);
			if (minaDu(kasilaPX, kasilaPY)){
				erakutsiMinak();
				iprintf("\x1b[11;9H ----------- ");
				iprintf("\x1b[12;9H| GAME OVER |");
				iprintf("\x1b[13;9H ----------- ");
				EGOERA=BUKATU;//amaiera
			}
		}
		
		if (SakatutakoTekla() == SELECT)
		{
			// Jokoaren amaiera
			EGOERA = BUKATU;
		}

		if (kontagailua == ((err * zut) - minaKop))
		{
			erakutsiBanderak();
			iprintf("\x1b[8;7H ---------------- ");
			iprintf("\x1b[9;7H| IRABAZI DUZU!! |");
			iprintf("\x1b[10;7H ---------------- ");
			EGOERA = BUKATU;//amaiera
		}
	}
	//iprintf("\x1b[23;7H                ");
	while (EGOERA == BUKATU)
	{
		iprintf("\x1b[23;2HSakatu 'A' menura itzultzeko");
	}
	//iprintf("\x1b[11;9H             ");
	//iprintf("\x1b[12;9H             ");
	//iprintf("\x1b[13;9H             ");
	ezabatuPantaila();
}

