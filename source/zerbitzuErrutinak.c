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
void tekEten()
{
	if (EGOERA == HASTEKO){
		if (SakatutakoTekla()==A){
			EGOERA = MENUA;
		}
	}
	if (EGOERA == MENUA){
		if (SakatutakoTekla()==BEHERA && kasilaPY==88){
			kasilaPY = 152;
		}
		if (SakatutakoTekla()==BEHERA && kasilaPY==24){
			kasilaPY = 88;
		}
		if (SakatutakoTekla()==GORA && kasilaPY==88){
			kasilaPY = 24;
		}
		if (SakatutakoTekla()==GORA && kasilaPY==152){
			kasilaPY = 88;
		}
		if (SakatutakoTekla()==A && kasilaPY==24){
			EGOERA = JOKOA;
		}
		if (SakatutakoTekla()==A && kasilaPY==88){
			iprintf("\x1b[4;7HBOTOIEN KONTROLA");
			iprintf("\x1b[5;7H----------------");
			iprintf("\x1b[7;3H'L'  ------------>  Ebatzi");
			iprintf("\x1b[8;3H                          ");
			iprintf("\x1b[9;3H'R'  ----------->  Bandera");
			iprintf("\x1b[10;3H                          ");
			iprintf("\x1b[11;3H'GORA'  ----------->  Gora");
			iprintf("\x1b[13;3H'BEHERA'  ------->  Behera");
			iprintf("\x1b[14;3H                          ");
			iprintf("\x1b[15;3H'EZKER'  ----->  Ezkerrera");
			iprintf("\x1b[16;3H                          ");
			iprintf("\x1b[17;3H'ESKUBI'  ----->  Eskubira");
			iprintf("\x1b[19;3H'SELECT'  ------>  Amaiera");
		}
		if (SakatutakoTekla()==A && kasilaPY==152){
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
			iprintf("\x1b[17;3H                          ");
			iprintf("\x1b[19;3H                          ");
		}
	}	

	if (EGOERA == JOKOA)
	{	
		if (SakatutakoTekla()==ESKUBI && ((15 < kasilaPX && kasilaPX < 145) && (15 < kasilaPY && kasilaPY < 161))){
			kasilaPX += 16;
		}
		if (SakatutakoTekla()==EZKER && ((31 < kasilaPX && kasilaPX < 161) && (15 < kasilaPY && kasilaPY < 161))){
			kasilaPX -= 16;
		}
		if (SakatutakoTekla()==GORA && ((31 < kasilaPY && kasilaPY < 161) && (15 < kasilaPX && kasilaPX < 161))){
			kasilaPY -= 16;
		}
		if (SakatutakoTekla()==BEHERA && ((15 < kasilaPY && kasilaPY < 145) && (15 < kasilaPX && kasilaPX < 161))){
			kasilaPY += 16;
		}
		
		kasilaX = (kasilaPX / 16) - 1;
		kasilaY = (kasilaPY / 16) - 1;
		
		erakutsiAukera(2, kasilaPX, kasilaPY);
		
		//if (SakatutakoTekla()==A) {
		//	ezabatuAukera(2, kasilaPX, kasilaPY);
		//	erakutsi(kasilaPX, kasilaPY);
		//	erakutsiAukera(2, kasilaPX, kasilaPY);
		//	erakutsiZazpi(5, kasilaPX, kasilaPY);
		//} else if (SakatutakoTekla()==B) {
		//	banderaDu(kasilaPX, kasilaPY) ? banderaKendu(kasilaPX, kasilaPY) : banderaJarri(kasilaPX, kasilaPY);
		//	erakutsiAukera(2, kasilaPX, kasilaPY);
		//}
		if (SakatutakoTekla()==L) {
			banderaDu(kasilaPX, kasilaPY) ? banderaKendu(kasilaPX, kasilaPY) : banderaJarri(kasilaPX, kasilaPY);
			erakutsiAukera(2, kasilaPX, kasilaPY);
		}
		if (EGOERA == KONTATZEN)
		{
			ErlojuaMartxanJarri();
		} else {
			ErlojuaGelditu();
			iprintf("\x1b[13;5HDenboragailua geldirik");

		}
		iprintf("\x1b[17;5HSakatutako tekla: %d \nds", SakatutakoTekla());
	}
}

void tenpEten()
{
	static int tik = 0;
	static int seg = 0;

	if (EGOERA==KONTATZEN)
	{
		iprintf("\x1b[13;5HDenboragailua martxan");
		tik++;
		if (tik==3)
		{
			seg++;
			iprintf("\x1b[11;5HPasa diren segunduak: %d ", seg);
			tik=0;
		}		
	}
}

void etenZerbErrutEzarri()
{
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	irqSet(IRQ_KEYS, tekEten);
	irqSet(IRQ_TIMER0, tenpEten);
}

