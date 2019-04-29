/*-----------------------------------
 Taulako kasilak maneiatzeko eragiketak
-------------------------------------*/

#include <nds.h> 		//nds-rako garatuta dagoen liburutegia
#include <stdio.h>		//c-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		//c-ko liburutegi estandarra memoria erreserbak eta zenbaki konbertsioak egiteko
#include <unistd.h>		//Sistema eragileen arteko konpatibilitatea ziurtatzeko liburutegia

#include "eragiketak.h"
#include "grafikoak.h"		
#include "definizioak.h"
#include "spriteak.h"

// Jokoa kontrolatzeko parametroak
// -------------------------------

int zenbatMina = 0;
int zenbatBandera = 0;
// -------------------------------

struct Kasila
{
	//int x, y;
	int hautatuta;
	int minaDu;
	int banderaDu;
	int ebatzita;
	int zenbatMinaOndoan; // Aldagai boolear bat bezala erabil dezakegu
};

struct Kasila taula[err][zut];

// Funtzio hauek fitxategi honetan erabiltzen dira bakarrik
// --------------------------------------------------------
void minakAusazJarri()
{
	int i = rand() % err;
	int j = rand() % zut;
	!taula[i][j].minaDu ? taula[i][j].minaDu = 1 : minakAusazJarri();
}

void kontatuOndokoMinak(int m, int n)
{
	short unsigned int kont = 0;

	if (!taula[m][n].minaDu)
	{
		for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (taula[m+i][n+j].minaDu) {kont++;}
		}}
	}

	taula[m][n].zenbatMinaOndoan = kont;
}
// --------------------------------------------------------

void taulaNagusiaEzarri()
{
	// Taulako kasila guztiak erazagutu
	for (int i = 0; i < err; i++)
	{
		for (int j = 0; j < zut; j++)
		{
			taula[i][j].hautatuta = 0;
			taula[i][j].minaDu = 0;
			taula[i][j].banderaDu = 0;
			taula[i][j].ebatzita = 0;
		}
	}

	// Minak ausaz jarri
	for (int i = 0; i < minaKop; i++)
	{
		minakAusazJarri();
	}

	// Taulako barrualdeko kasila guztiei dagozkien zenbakiak ezarri
	for (int i = 1; i < err - 1; i++)
	{
		for (int j = 1; j < err - 1; j++)
		{
			kontatuOndokoMinak(i, j);
		}
	}

	// Taulako kanpoaldeko kasila guztiei dagozkien zenbakiak ezarri
	// Amaitzeke
}

void hautatu(int m, int n)
{
	static int aurM = 0;
	static int aurN = 0;

	taula[aurM][aurN].hautatuta = 0;
	taula[m][n].hautatuta = 1;

	aurM = m;
	aurN = n;
}

int hautatuta(int m, int n)
{
	return taula[m][n].hautatuta;
}




