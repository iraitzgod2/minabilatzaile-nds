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
			if (((-1 < (m+i) && (m+i) < err) && 
				(-1 < (n+j) && (n+j) < zut)) &&
				(taula[m+i][n+j].minaDu)) 
				{kont++;}
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
			taula[i][j].zenbatMinaOndoan = 0;
		}
	}

	// Minak ausaz jarri
	for (int i = 0; i < minaKop; i++)
	{
		minakAusazJarri();
	}

	// Taulako kasila guztiei dagozkien zenbakiak ezarri
	for (int i = 0; i < err; i++)
	{
		for (int j = 0; j < err; j++)
		{
			kontatuOndokoMinak(i, j);
		}
	}

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

void idatziPantailan()
{
	for (int i = 0; i < err; i++){
	for (int j = 0; j < zut; j++){
		if (taula[i][j].minaDu)
		{
			iprintf("\x1b[%d;%dH*", j, i);
		}
		else
		{
			iprintf("\x1b[%d;%dH%d", j, i, taula[i][j].zenbatMinaOndoan);
		}
	}}
}

void erakutsi(int m, int n)
{
	static short unsigned ind = 0;
	if (taula[(m-16)/16][(n-16)/16].minaDu)
	{
		erakutsiMina(ind, m, n);
	}
	else
	{
		switch (taula[(m-16)/16][(n-16)/16].zenbatMinaOndoan)
		{
			case 1: erakutsiBat(ind, m, n);
				break;
			case 2: erakutsiBi(ind, m, n);
				break;
			case 3: erakutsiHiru(ind, m, n);
				break;
			case 4: erakutsiLau(ind, m, n);
				break;
			case 5: erakutsiBost(ind, m, n);
				break;
			case 6: erakutsiSei(ind, m, n);
				break;
			case 7: erakutsiZazpi(ind, m, n);
				break;
			case 8: erakutsiZortzi(ind, m, n);
				break;
		}
	}
	ind++;
}

void erakutsiDena()
{
	for (int i = 10; i < 163; i++){
	for (int j = 10; j < 163; j++){
		if (i % 16 == 0 && j % 16 == 0)
			erakutsi(i, j);
	}}
}
