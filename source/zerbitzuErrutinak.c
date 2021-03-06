/*-------------------------------------
zerbitzuErrutiank.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"
#include "periferikoak.h"
#include "fondoak.h"
#include "spriteak.h"
#include "zerbitzuErrutinak.h"

#include "eragiketak.h"

int EGOERA;
int kasilaX, kasilaY;
int kasilaPX, kasilaPY;

void kontrolaInprimatu()
{
	iprintf("\x1b[4;7HBOTOIEN KONTROLA");
	iprintf("\x1b[5;7H----------------");
	iprintf("\x1b[7;3H'R'  ------------>  Ebatzi");
	iprintf("\x1b[9;3H'L'  ----------->  Bandera");
	iprintf("\x1b[11;3H'GORA'  ----------->  Gora");
	iprintf("\x1b[13;3H'BEHERA'  ------->  Behera");
	iprintf("\x1b[15;3H'EZKER'  ----->  Ezkerrera");
	iprintf("\x1b[17;3H'ESKUBI'  ----->  Eskubira");
	iprintf("\x1b[19;3H'SELECT'  ------>  Amaiera");
	iprintf("\x1b[23;2H Aurrera egiteko sakatu 'A' ");
}

void kredituakInprimatu()
{
	iprintf("\x1b[4;7H    KREDITUAK   ");
	iprintf("\x1b[5;7H    ---------   ");
	iprintf("\x1b[7;3H EHUko Ingeniaritza Infor-");
	iprintf("\x1b[8;3Hmatika graduko hainbat    ");
	iprintf("\x1b[9;3Hikaslek burutua izan da.  ");
	iprintf("\x1b[10;3H'Buscaminas' joko famatua-");
	iprintf("\x1b[11;3Hren bertsio bat da.       ");
	iprintf("\x1b[13;3H Jokoaren helburua taula  ");
	iprintf("\x1b[14;3Hahalik eta azkarren amai- ");
	iprintf("\x1b[15;3Htzea da, minak ez dauden  ");
	iprintf("\x1b[16;3Hlaukiak aukeratuz.        ");
	iprintf("\x1b[23;2H Aurrera egiteko sakatu 'A' ");
}

void tekEten()
{
	if (EGOERA == HASTEKO){
		if (SakatutakoTekla() == A){
			EGOERA = MENUA;
		}
	}

	if (EGOERA == MENUA){
		if (SakatutakoTekla() == BEHERA && kasilaPY < 152) {kasilaPY += 64;}
		if (SakatutakoTekla() == GORA && kasilaPY > 24) {kasilaPY -= 64;}
		if (SakatutakoTekla() == A)
		{
			ezabatuPantaila();
			switch(kasilaPY)
			{
				case 24:
					EGOERA = JOKOA;
					break;

				case 88:
					kontrolaInprimatu();
					break;

				case 152:
					kredituakInprimatu();
					break;
			}
		}
	}	

	if (EGOERA == JOKOA || EGOERA == KONTATZEN)
	{	
		if (SakatutakoTekla() == ESKUBI && ((15 < kasilaPX && kasilaPX < 145) && (15 < kasilaPY && kasilaPY < 161))) {kasilaPX += 16;}
		if (SakatutakoTekla() == EZKER && ((31 < kasilaPX && kasilaPX < 161) && (15 < kasilaPY && kasilaPY < 161))) {kasilaPX -= 16;}
		if (SakatutakoTekla() == GORA && ((31 < kasilaPY && kasilaPY < 161) && (15 < kasilaPX && kasilaPX < 161))) {kasilaPY -= 16;}
		if (SakatutakoTekla() == BEHERA && ((15 < kasilaPY && kasilaPY < 145) && (15 < kasilaPX && kasilaPX < 161))) {kasilaPY += 16;}
		
		kasilaX = (kasilaPX / 16) - 1;
		kasilaY = (kasilaPY / 16) - 1;

		if (SakatutakoTekla() == L)
		{
			banderaDu(kasilaPX, kasilaPY) ? banderaKendu(kasilaPX, kasilaPY) : banderaJarri(kasilaPX, kasilaPY);
			iprintf("\x1b[21;6HBandera kopurua: %d ", zenbatBandera);
		}

		erakutsiAukera(0, kasilaPX, kasilaPY);
	}

	if (EGOERA == KONTATZEN)
	{
		ErlojuaMartxanJarri();
	}

	if (EGOERA == BUKATU)
	{
		ErlojuaGelditu();
		if (SakatutakoTekla() == A)
		{
			ezabatuSpriteGuztiak();
			ezabatuPantaila();
			kontagailua = 0;
			zenbatBandera=0;
			EGOERA = MENUA;
		}
	}
}

void tenpEten()
{
	static int seg = 0;
	static int min = 0;

	if (EGOERA == KONTATZEN)
	{
		seg++;
		if (seg==60){
			seg = 0;
			min++;
		}
		iprintf("\x1b[12;9H %d min %d seg ", min, seg);
	}
	
	if (EGOERA == MENUA)
	{
		seg = 0;
		min = 0;
	}
}

void etenZerbErrutEzarri()
{
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	irqSet(IRQ_KEYS, tekEten);
	irqSet(IRQ_TIMER0, tenpEten);
}

