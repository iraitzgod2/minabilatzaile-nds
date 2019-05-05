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

void idatziPantailan()
{
	for (int i = 0; i < err; i++) {
	for (int j = 0; j < zut; j++) {
		taula[i][j].minaDu ? iprintf("\x1b[%d;%dH*", j, i) : iprintf("\x1b[%d;%dH%d", j, i, taula[i][j].zenbatMinaOndoan);
	}}
}

void erakutsiDena()
{
	for (int i = 10; i < 163; i++){
	for (int j = 10; j < 163; j++){
		if (i % 16 == 0 && j % 16 == 0)
			erakutsi(i, j);
	}}
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

void erakutsi(int i, int j)
{
	static short unsigned ind = 0;
	int m = (i - 16) / 16; // m: (0, 9), i: pixelak
	int n = (j - 16) / 16; // n: (0, 9), j: pixelak
	if (!taula[m][n].ebatzita)
	{
		ind++;
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
					// Floodfill algoritmoa
					for (int a = -16; a <= 16; a += 16){
					for (int b = -16; b <= 16; b += 16){
						if (((15 < (i+a) && (i+a) < 176) && 
							(15 < (j+b) && (j+b) < 176)) &&
							!(a == 0 && b == 0))
						{
							erakutsi(i+a, j+b);
						}
					}}
					break;
				case 1: erakutsiBat(ind, i, j);
					break;
				case 2: erakutsiBi(ind, i, j);
					break;
				case 3: erakutsiHiru(ind, i, j);
					break;
				case 4: erakutsiLau(ind, i, j);
					break;
				case 5: erakutsiBost(ind, i, j);
					break;
				case 6: erakutsiSei(ind, i, j);
					break;
				case 7: erakutsiZazpi(ind, i, j);
					break;
				case 8: erakutsiZortzi(ind, i, j);
					break;
			}
		}
	}
}

void banderaJarri(int i, int j)
{

}
