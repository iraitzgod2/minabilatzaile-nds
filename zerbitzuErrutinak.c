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

int EGOERA=HASTEKO;

void tekEten()
{
	//if (EGOERA == HASTEKO)
	//{	
		if (EGOERA == KONTATZEN)
		{
			ErlojuaMartxanJarri();
		} else {
			EGOERA = HASTEKO;
			ErlojuaGelditu();
			iprintf("\x1b[13;5HDenboragailua geldirik");

		}
		iprintf("\x1b[17;5HSakatutako tekla: %d \nds", SakatutakoTekla());
	//}
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
			iprintf("\x1b[14;5HPasa diren segunduak: %d ", seg);
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

