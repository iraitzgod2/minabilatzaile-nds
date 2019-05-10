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
int kontagailua =0;
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
		int i;
		int j;
		for (i = -1; i <= 1; i++) {
			for (j = -1; j <= 1; j++) {
				if (((-1 < (m+i) && (m+i) < err) && 
					(-1 < (n+j) && (n+j) < zut)) &&
					(taula[m+i][n+j].minaDu)) 
					{kont++;}
			}
		}
	}

	taula[m][n].zenbatMinaOndoan = kont;
}

void idatziPantailan()
{
	int i;
	int j;
	for (i = 0; i < err; i++) {
	for (j = 0; j < zut; j++) {
		taula[i][j].minaDu ? iprintf("\x1b[%d;%dH*", j, i) : iprintf("\x1b[%d;%dH%d", j, i, taula[i][j].zenbatMinaOndoan);
	}}
}

void erakutsiDena()
{
	int i;
	int j;
	for (i = 10; i < 163; i++){
	for (j = 10; j < 163; j++){
		if (i % 16 == 0 && j % 16 == 0)
			erakutsi(i, j);
	}}
}

// --------------------------------------------------------

void ezabatuPantaila()
{
	int i;
	for (i = 0; i < 24; i++) {
		iprintf("\x1b[%d;0H                                ", i);
	}
}

void taulaNagusiaEzarri()
{
	// Taulako kasila guztiak erazagutu
	int i;
	int j;
	for (i = 0; i < err; i++)
	{
		for (j = 0; j < zut; j++)
		{
			taula[i][j].hautatuta = 0;
			taula[i][j].minaDu = 0;
			taula[i][j].banderaDu = 0;
			taula[i][j].ebatzita = 0;
			taula[i][j].zenbatMinaOndoan = 0;
		}
	}

	// Minak ausaz jarri
	for (i = 0; i < minaKop; i++)
	{
		minakAusazJarri();
	}

	// Taulako kasila guztiei dagozkien zenbakiak ezarri
	for (i = 0; i < err; i++)
	{
		for (j = 0; j < err; j++)
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

void erakutsi(int i, int j)
{
	int m = (i - 16) / 16; // m: (0, 9), i: pixelak
	int n = (j - 16) / 16; // n: (0, 9), j: pixelak
	short unsigned int ind = (m + n * 10) + 1;
	if (!taula[m][n].ebatzita && !taula[m][n].banderaDu)
	{
		int a;
		int b;
		taula[m][n].ebatzita = 1;
		if (taula[m][n].minaDu)
		{
			erakutsiMina(ind, i, j);
		}
		else
		{
			switch (taula[m][n].zenbatMinaOndoan)
			{
				case 0: erakutsiHutsa(ind, i, j);
					kontagailua++;
					// Floodfill algoritmoa
					for (a = -16; a <= 16; a += 16){
					for (b = -16; b <= 16; b += 16){
						if (((15 < (i+a) && (i+a) < 176) && 
							(15 < (j+b) && (j+b) < 176)) &&
							!(a == 0 && b == 0))
						{
							erakutsi(i+a, j+b);
						}
					}
					}
					break;
				case 1: erakutsiBat(ind, i, j);
					kontagailua++;
					break;
				case 2: erakutsiBi(ind, i, j);
					kontagailua++;
					break;
				case 3: erakutsiHiru(ind, i, j);
					kontagailua++;
					break;
				case 4: erakutsiLau(ind, i, j);
					kontagailua++;
					break;
				case 5: erakutsiBost(ind, i, j);
					kontagailua++;
					break;
				case 6: erakutsiSei(ind, i, j);
					kontagailua++;
					break;
				case 7: erakutsiZazpi(ind, i, j);
					kontagailua++;
					break;
				case 8: erakutsiZortzi(ind, i, j);
					kontagailua++;
					break;
			}
		}
	}
}

void banderaJarri(int i, int j)
{
	int m = (i - 16) / 16; // m: (0, 9), i: pixelak
	int n = (j - 16) / 16; // n: (0, 9), j: pixelak
	short unsigned int banderaInd = (m + n * 10) + 1; // kasila bakoitzak bere bandera zenbakia du.
	if (!taula[m][n].ebatzita && !taula[m][n].banderaDu)
	{
		taula[m][n].banderaDu = banderaInd;
		erakutsiBandera(banderaInd, i, j);
		zenbatBandera++;
	}
}

void banderaKendu(int i, int j)
{
	int m = (i - 16) / 16; // m: (0, 9), i: pixelak
	int n = (j - 16) / 16; // n: (0, 9), j: pixelak
	if (taula[m][n].banderaDu)
	{
		ezabatuBandera(taula[m][n].banderaDu, i, j);
		taula[m][n].banderaDu = 0;
		zenbatBandera--;
	}
}

int banderaDu(int i, int j)
{
	return taula[(i-16)/16][(j-16)/16].banderaDu;
}

int minaDu(int i, int j)
{
	return taula[(i-16)/16][(j-16)/16].minaDu;
}

void erakutsiMinak()
{
	int i;
	int j;
	for (i = 10; i < 163; i++){
	for (j = 10; j < 163; j++){
		if ((i % 16 == 0 && j % 16 == 0) && minaDu(i,j))
			erakutsi(i, j);
	}}
}

void ezabatuSpriteGuztiak(){
	int i;
	int j;
	for (i = 10; i < 163; i++){
	for (j = 10; j < 163; j++){
	int m = (i - 16) / 16; // m: (0, 9), i: pixelak
	int n = (j - 16) / 16; // n: (0, 9), j: pixelak
	short unsigned int ind = (m + n * 10) + 1; // kasila bakoitzak bere bandera zenbakia du.
	if (taula[m][n].ebatzita || taula[m][n].banderaDu || taula[m][n].minaDu)
	{
		ezabatuAukera(ind, i, j);
	}
	}}
}

void erakutsiBanderak()
{
	int i;
	int j;
	for (i = 10; i < 163; i++){
	for (j = 10; j < 163; j++){
		if ((i % 16 == 0 && j % 16 == 0) && minaDu(i,j))
			banderaJarri(i, j);
	}}
}


