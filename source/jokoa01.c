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
	konfiguratuTenporizadorea(60075, 0xC3);	// Tenporizadorea konfiguratu behar da.
	TekEtenBaimendu();						// Teklatuaren etenak baimendu behar dira.
	DenbEtenBaimendu();						// Tenporizadorearen etenak baimendu behar dira.
	etenZerbErrutEzarri();					// Etenen zerbitzu errutinak ezarri behar dira.
	//***************************************************************************************//
	
	srand(time(0)); // Partida bakoitzean taula ezberdina lortzeko
	taulaNagusiaEzarri();
	//erakutsiTaula(); // Fondoa
	//erakutsiAukera(0, kasilaPX, kasilaPY); // Lehenengo posizioa (0, 0)

	//idatziPantailan(); // Taulako zenbakiak karaktereetan (probak egiteko)

	//aldagai baten definizioa
	int tekla = 0;
	int kont = 0;

	int aurrekoX = 10, aurrekoY = 10; // Fitxategi honetan bakarrik erabiltzen dira

	kasilaX = 100; // Taulako kasila (0, 9)
	kasilaY = 100;
	
	EGOERA = HASTEKO;

	//hasierako pantaila
	erakutsiSarrera();
	while((EGOERA == HASTEKO)){
		iprintf("\x1b[12;8HSakatu 'A' botoia");
	}

	//menuaren pantaila
	kasilaPX = 24;// hasierako kasilari dagokion pixela
	kasilaPY = 24;
	iprintf("\x1b[12;8H                 ");//Aurreko pantailan idatzitakoaren ezabapena
	iprintf("\x1b[23;3HAurrera egiteko sakatu 'A'");
	erakutsiZerrenda();
	erakutsiAukera(0, 24, 24);
	erakutsiHasiera(21, 24, 88);
	erakutsiHasiera(22, 24, 152);
	while((EGOERA == MENUA)){
		touchRead(&PANT_DAT);
		if (kasilaPY==24){
			erakutsiAukera(0, 24, 24);
			erakutsiHasiera(21, 24, 88);
			erakutsiHasiera(22, 24, 152);
		}
		if (kasilaPY==88){
			erakutsiHasiera(20, 24, 24);
			erakutsiAukera(0, 24, 88);
			erakutsiHasiera(22, 24, 152);
		}
		if (kasilaPY==152){
			erakutsiHasiera(20, 24, 24);
			erakutsiHasiera(21, 24, 88);
			erakutsiAukera(0, 24, 152);
		}
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
		if (SakatutakoTekla()==SELECT){//Jokoaren amaiera
			EGOERA=BUKATU;
		}
	}
	ezabatuAukera(20, 24, 24);
	ezabatuHasiera(21, 24, 88);
	ezabatuHasiera(22, 24, 152);

//Inkesta egin behar da. SELECT tekla sakatzean 
//Egoera aldatu eta programa bukatu
	kasilaPX = 16; // Kasilari dagokion pixela (16, 32, 48, 64, ...)
	kasilaPY = 16;

	//Aurreko pantailan idatzitakoaren ezabapena
	iprintf("\x1b[4;7H                ");
	iprintf("\x1b[5;7H                ");
	iprintf("\x1b[7;3H                          ");
	iprintf("\x1b[8;3H                          ");
	iprintf("\x1b[9;3H                          ");
	iprintf("\x1b[10;3H                          ");
	iprintf("\x1b[11;3H                          ");
	iprintf("\x1b[13;3H                          ");
	iprintf("\x1b[14;3H                          ");
	iprintf("\x1b[15;3H                          ");
	iprintf("\x1b[16;3H                          ");
	iprintf("\x1b[17;3H                          ");
	iprintf("\x1b[19;3H                          ");
	iprintf("\x1b[23;3H                          ");

	idatziPantailan(); // Taulako zenbakiak karaktereetan (probak egiteko)
	iprintf("\x1b[23;7HMina kopurua: 20");
	while(EGOERA != BUKATU)
	{	
		erakutsiTaula();
		touchRead(&PANT_DAT);
		//iprintf("\x1b[10;0H--------------------------------");
		//iprintf("\x1b[14;0H     Pantailan x koord: %d  ", PANT_DAT.px);
		//iprintf("\x1b[15;0H     Pantailan y koord: %d  ", PANT_DAT.py);
		if (SakatutakoTekla()==R) {
			EGOERA=KONTATZEN;
		//	ezabatuAukera(2, kasilaPX, kasilaPY);
			erakutsi(kasilaPX, kasilaPY);
			erakutsiAukera(0, kasilaPX, kasilaPY);
			if (minaDu(kasilaPX, kasilaPY)){
				erakutsiMinak();
				EGOERA=BUKATU;//amaiera
			}
		//	erakutsiZazpi(5, kasilaPX, kasilaPY);
		}
		
		if ((15 < PANT_DAT.px && PANT_DAT.px < 176) &&
			(15 < PANT_DAT.py && PANT_DAT.py < 176)) // Pantaila ukitzerakoan aldagaiak definitu
		{
			kasilaX = (PANT_DAT.px - 16) / 16;
			kasilaY = (PANT_DAT.py - 16) / 16;
			kasilaPX = PANT_DAT.px - (PANT_DAT.px % 16);
			kasilaPY = PANT_DAT.py - (PANT_DAT.py % 16);
			//iprintf("\x1b[17;0H     Kasila koord: %d, %d  ", kasilaX, kasilaY);
		}
		
		if ((kasilaX < 10 && kasilaY < 10) && 
			(PANT_DAT.px == 0 && PANT_DAT.py == 0)) // Pantaila ukitzeari uzterakoan
		{
			//iprintf("\x1b[19;0H     Sakatutako kasila: %d, %d  ", kasilaX, kasilaY);
			//iprintf("\x1b[20;0H     Sakatutako kasila: %d, %d  ", kasilaPX, kasilaPY);
			if (aurrekoX != kasilaX || aurrekoY != kasilaY)
			{
				erakutsiAukera(0, kasilaPX, kasilaPY);
				aurrekoX = kasilaX;
				aurrekoY = kasilaY;
			}
			//ebatzi(kasilaX, kasilaY);
		}
		if (SakatutakoTekla()==SELECT){//Jokoaren amaiera
			EGOERA=BUKATU;
		}
	}
	if (EGOERA == BUKATU)
	{
		//spriteGuztiakEzabatu();
		//denboragailuaEzabatu();
	}
}

