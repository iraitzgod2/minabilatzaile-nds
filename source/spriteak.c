/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		//nds-rako garatuta dagoen liburutegia
#include <stdio.h>		//c-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		//c-ko liburutegi estandarra memoria erreserbak eta zenbaki konbertsioak egiteko
#include <unistd.h>		//Sistema eragileen arteko konpatibilitatea ziurtatzeko liburutegia
#include "spriteak.h"
#include "definizioak.h"

u16 * gfxhasiera;
u16 * gfxaukera;
u16 * gfxbandera;
u16 * gfxhutsa;
u16 * gfxmina;
u16 * gfxbat;
u16 * gfxbi;
u16 * gfxhiru;
u16 * gfxlau;
u16 * gfxbost;
u16 * gfxsei;
u16 * gfxzazpi;
u16 * gfxzortzi;


/* Pantailan erakutsi nahi den sprite bakoitzeko memoria erreserbatu.*/
void memoriaErreserbatu()
{
	/* Pantaila nagusian gehitu nahi den sprite bakoitzarentzako horrelako bat egin behar da. */
	gfxhasiera = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxaukera = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxbandera = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxhutsa = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxmina = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxbat = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxbi = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxhiru = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxlau = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxbost = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxsei = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxzazpi = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxzortzi = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
}

/* Pixel bakoitzak har ditzakeen 256 balioetako bakoitzari kolore bat esleitu PANTAILA NAGUSIAN. 0 balioa gardena da 
   eta definitu gabeko balioak beltzak. SPRITEARI KOLOREAK ESLEITZEKO ALDATU*/
void paletaNagusiaEzarri()
{
	SPRITE_PALETTE[1] = RGB15(0, 0, 31); // Urdina: 1 zenbakiaren kolorea
	SPRITE_PALETTE[2] = RGB15(0, 16, 0); // Berdea: 2 zenbakiaren kolorea
	SPRITE_PALETTE[3] = RGB15(31, 0, 0); // Gorria: 3 zenbakiaren kolorea
	SPRITE_PALETTE[4] = RGB15(0, 0, 16); // Urdin iluna: 4 zenbakiaren kolorea
	SPRITE_PALETTE[5] = RGB15(16, 0, 0); // Granate: 5 zenbakiaren kolorea
	SPRITE_PALETTE[6] = RGB15(0, 16, 16); // Esmeralda: 6 zenbakiaren kolorea
	SPRITE_PALETTE[7] = RGB15(0, 0, 0); // Beltza: 7 zenbakiaren kolorea
	SPRITE_PALETTE[8] = RGB15(16, 16, 16); // Grisa: 8 zenbakiaren kolorea
	SPRITE_PALETTE[9] = RGB15(24, 24, 24); // Gris paletak, kasilentzako
	SPRITE_PALETTE[10] = RGB15(15, 15, 15);
	SPRITE_PALETTE[11] = RGB15(20, 20, 20);
	SPRITE_PALETTE[12] = RGB15(30, 30, 30);
	SPRITE_PALETTE[13] = RGB15(18, 18, 18);
	SPRITE_PALETTE[14] = RGB15(31, 31, 31); // Zuria
//	SPRITE_PALETTE[14] = RGB15(0, 0, 0); // Transparentea
}

/* 16x16 pixeleko Sprite baten definizioa erronbo bat marrazteko */
/* Memoriako bankuek duten lan egiteko modua dela eta, lehenengo lau lerroak goiko
   ezkerreko koadrantean erakusten dira, hurrengo lauak goiko eskuineko kuadrantean,
   hurrengo lauak beheko ezkerreko koadrantean eta azkeneko lauak beheko ezkerreko koadrantean. 
   Alboko irudian ikusten den bezala. */

u8 hasiera[256] =
{
0, 14, 14, 14, 14, 14, 14, 14, 14, 12, 12, 12, 12, 12, 12, 12, 
0, 12, 9, 9, 9, 9, 9, 9, 14, 12, 9, 9, 9, 9, 9, 9, 
0, 12, 9, 9, 9, 9, 9, 9, 14, 12, 9, 9, 9, 9, 9, 9, 
0, 12, 9, 9, 9, 9, 9, 9, 14, 12, 9, 9, 9, 9, 9, 9, 
0, 14, 14, 14, 14, 14, 14, 9, 12, 12, 12, 12, 12, 12, 9, 10, 
9, 9, 9, 9, 9, 9, 13, 10, 9, 9, 9, 9, 9, 9, 13, 10, 
9, 9, 9, 9, 9, 9, 13, 10, 9, 9, 9, 9, 9, 9, 13, 10, 
9, 9, 9, 9, 9, 9, 13, 10, 9, 9, 9, 9, 9, 9, 13, 10, 
0, 12, 9, 9, 9, 9, 9, 9, 14, 12, 9, 9, 9, 9, 9, 9, 
0, 12, 9, 9, 9, 9, 9, 9, 14, 12, 9, 9, 9, 9, 9, 9, 
0, 12, 9, 9, 9, 9, 9, 9, 14, 12, 9, 9, 9, 9, 9, 9, 
0, 9, 13, 13, 13, 13, 13, 13, 9, 10, 10, 10, 10, 10, 10, 10, 
9, 9, 9, 9, 9, 9, 13, 10, 9, 9, 9, 9, 9, 9, 13, 10, 
9, 9, 9, 9, 9, 9, 13, 10, 9, 9, 9, 9, 9, 9, 13, 10, 
9, 9, 9, 9, 9, 9, 13, 10, 9, 9, 9, 9, 9, 9, 13, 10, 
13, 13, 13, 13, 13, 13, 13, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
};

/*u8 aukera[256] =
{
3, 3, 3, 3, 3, 3, 3, 3, 3, 12, 12, 12, 12, 12, 12, 12, 
3, 12, 9, 9, 9, 9, 9, 9, 3, 12, 9, 9, 9, 9, 9, 9, 
3, 12, 9, 9, 9, 9, 9, 9, 3, 12, 9, 9, 9, 9, 9, 9, 
3, 12, 9, 9, 9, 9, 9, 9, 3, 12, 9, 9, 9, 9, 9, 9, 
3, 3, 3, 3, 3, 3, 3, 3, 12, 12, 12, 12, 12, 12, 9, 3, 
9, 9, 9, 9, 9, 9, 13, 3, 9, 9, 9, 9, 9, 9, 13, 3, 
9, 9, 9, 9, 9, 9, 13, 3, 9, 9, 9, 9, 9, 9, 13, 3, 
9, 9, 9, 9, 9, 9, 13, 3, 9, 9, 9, 9, 9, 9, 13, 3, 
3, 12, 9, 9, 9, 9, 9, 9, 3, 12, 9, 9, 9, 9, 9, 9, 
3, 12, 9, 9, 9, 9, 9, 9, 3, 12, 9, 9, 9, 9, 9, 9, 
3, 12, 9, 9, 9, 9, 9, 9, 3, 12, 9, 9, 9, 9, 9, 9, 
3, 9, 13, 13, 13, 13, 13, 13, 3, 3, 3, 3, 3, 3, 3, 3, 
9, 9, 9, 9, 9, 9, 13, 3, 9, 9, 9, 9, 9, 9, 13, 3, 
9, 9, 9, 9, 9, 9, 13, 3, 9, 9, 9, 9, 9, 9, 13, 3, 
9, 9, 9, 9, 9, 9, 13, 3, 9, 9, 9, 9, 9, 9, 13, 3, 
13, 13, 13, 13, 13, 13, 13, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
};*/

u8 aukera[256] =
{
3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 
3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 
3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 
3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 
3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 3, 
0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 
0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 
0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 
3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 
3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 
3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 
3, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 
0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 
0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 
0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 
0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
};

u8 bandera[256] = 
{
0, 14, 14, 14, 14, 14, 14, 14, 14, 12, 12, 12, 12, 12, 12, 12, 
0, 12, 9, 9, 9, 9, 9, 9, 14, 12, 9, 9, 9, 9, 9, 3, 
0, 12, 9, 9, 9, 3, 3, 3, 14, 12, 9, 9, 3, 3, 3, 3, 
0, 12, 9, 9, 9, 3, 3, 3, 14, 12, 9, 9, 9, 9, 9, 3, 
0, 14, 14, 14, 14, 14, 14, 9, 12, 12, 12, 12, 12, 12, 9, 10, 
9, 9, 9, 9, 9, 9, 13, 10, 3, 9, 9, 9, 9, 9, 13, 10, 
3, 9, 9, 9, 9, 9, 13, 10, 3, 9, 9, 9, 9, 9, 13, 10, 
3, 9, 9, 9, 9, 9, 13, 10, 3, 9, 9, 9, 9, 9, 13, 10, 
0, 12, 9, 9, 9, 9, 9, 9, 14, 12, 9, 9, 9, 9, 9, 9, 
0, 12, 9, 9, 9, 9, 7, 7, 14, 12, 9, 9, 7, 7, 7, 7, 
0, 12, 9, 9, 7, 7, 7, 7, 14, 12, 9, 9, 9, 9, 9, 9, 
0, 9, 13, 13, 13, 13, 13, 13, 9, 10, 10, 10, 10, 10, 10, 10, 
7, 9, 9, 9, 9, 9, 13, 10, 7, 9, 9, 9, 9, 9, 13, 10, 
7, 7, 9, 9, 9, 9, 13, 10, 7, 7, 7, 7, 9, 9, 13, 10, 
7, 7, 7, 7, 9, 9, 13, 10, 9, 9, 9, 9, 9, 9, 13, 10, 
13, 13, 13, 13, 13, 13, 13, 10, 10, 10, 10, 10, 10, 10, 10, 10, 
};

u8 hutsa[256] = 
{
10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
};

u8 mina[256] = 
{
10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 7, 9, 7, 7, 10, 11, 9, 9, 9, 7, 7, 7, 
10, 11, 9, 9, 7, 7, 14, 14, 10, 11, 7, 7, 7, 7, 14, 14, 
10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 
7, 9, 9, 9, 9, 9, 9, 9, 7, 9, 9, 9, 9, 9, 9, 9, 
7, 7, 9, 7, 9, 9, 9, 9, 7, 7, 7, 9, 9, 9, 9, 9, 
7, 7, 7, 7, 9, 9, 9, 9, 7, 7, 7, 7, 9, 9, 9, 9, 
10, 11, 9, 9, 7, 7, 7, 7, 10, 11, 9, 9, 7, 7, 7, 7, 
10, 11, 9, 9, 9, 7, 7, 7, 10, 11, 9, 9, 7, 9, 7, 7, 
10, 11, 9, 9, 9, 9, 9, 7, 10, 11, 9, 9, 9, 9, 9, 7, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
7, 7, 7, 7, 7, 7, 9, 9, 7, 7, 7, 7, 9, 9, 9, 9, 
7, 7, 7, 9, 9, 9, 9, 9, 7, 7, 9, 7, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
};

u8 bat[256] = 
{
10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 1, 
10, 11, 9, 9, 9, 9, 1, 1, 10, 11, 9, 9, 9, 1, 1, 1, 
10, 11, 9, 9, 9, 9, 9, 1, 10, 11, 9, 9, 9, 9, 9, 1, 
10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 
9, 9, 9, 9, 9, 9, 9, 9, 1, 9, 9, 9, 9, 9, 9, 9, 
1, 9, 9, 9, 9, 9, 9, 9, 1, 9, 9, 9, 9, 9, 9, 9, 
1, 9, 9, 9, 9, 9, 9, 9, 1, 9, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 1, 10, 11, 9, 9, 9, 9, 9, 1, 
10, 11, 9, 9, 9, 9, 9, 1, 10, 11, 9, 9, 9, 1, 1, 1, 
10, 11, 9, 9, 9, 1, 1, 1, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
1, 9, 9, 9, 9, 9, 9, 9, 1, 9, 9, 9, 9, 9, 9, 9, 
1, 9, 9, 9, 9, 9, 9, 9, 1, 1, 1, 9, 9, 9, 9, 9, 
1, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
};

u8 bi[256] = 
{
10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 2, 2, 2, 
10, 11, 9, 9, 2, 2, 2, 2, 10, 11, 9, 9, 2, 2, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 
9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 9, 9, 9, 9, 9, 
2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 2, 2, 9, 9, 9, 9, 
9, 9, 2, 2, 9, 9, 9, 9, 2, 2, 2, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 2, 2, 10, 11, 9, 9, 9, 2, 2, 2, 
10, 11, 9, 9, 2, 2, 2, 9, 10, 11, 9, 9, 2, 2, 2, 2, 
10, 11, 9, 9, 2, 2, 2, 2, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
2, 2, 9, 9, 9, 9, 9, 9, 2, 9, 9, 9, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 2, 2, 2, 2, 9, 9, 9, 9, 
2, 2, 2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
};

u8 hiru[256] = 
{
10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 3, 3, 3, 3, 
10, 11, 9, 9, 3, 3, 3, 3, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 3, 3, 
10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 
9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 3, 9, 9, 9, 9, 9, 
3, 3, 3, 3, 9, 9, 9, 9, 9, 9, 3, 3, 9, 9, 9, 9, 
9, 9, 3, 3, 9, 9, 9, 9, 3, 3, 3, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 3, 3, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 3, 3, 3, 3, 
10, 11, 9, 9, 3, 3, 3, 3, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
3, 3, 3, 9, 9, 9, 9, 9, 9, 9, 3, 3, 9, 9, 9, 9, 
9, 9, 3, 3, 9, 9, 9, 9, 3, 3, 3, 3, 9, 9, 9, 9, 
3, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
};

u8 lau[256] = 
{
10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 4, 4, 
10, 11, 9, 9, 9, 9, 4, 4, 10, 11, 9, 9, 9, 4, 4, 9, 
10, 11, 9, 9, 9, 4, 4, 9, 10, 11, 9, 9, 4, 4, 4, 4, 
10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 
9, 9, 9, 9, 9, 9, 9, 9, 9, 4, 4, 9, 9, 9, 9, 9, 
9, 4, 4, 9, 9, 9, 9, 9, 9, 4, 4, 9, 9, 9, 9, 9, 
9, 4, 4, 9, 9, 9, 9, 9, 4, 4, 4, 4, 9, 9, 9, 9, 
10, 11, 9, 9, 4, 4, 4, 4, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
4, 4, 4, 4, 9, 9, 9, 9, 9, 4, 4, 9, 9, 9, 9, 9, 
9, 4, 4, 9, 9, 9, 9, 9, 9, 4, 4, 9, 9, 9, 9, 9, 
9, 4, 4, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
};

u8 bost[256] = 
{
10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 5, 5, 5, 5, 
10, 11, 9, 9, 5, 5, 5, 5, 10, 11, 9, 9, 5, 5, 9, 9, 
10, 11, 9, 9, 5, 5, 9, 9, 10, 11, 9, 9, 5, 5, 5, 5, 
10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 
9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 5, 9, 9, 9, 9, 
5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 5, 5, 5, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 5, 5, 5, 5, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 5, 5, 5, 5, 
10, 11, 9, 9, 5, 5, 5, 5, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
5, 5, 5, 5, 9, 9, 9, 9, 9, 9, 5, 5, 9, 9, 9, 9, 
9, 9, 5, 5, 9, 9, 9, 9, 5, 5, 5, 5, 9, 9, 9, 9, 
5, 5, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
};

u8 sei[256] = 
{
10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 6, 6, 6, 
10, 11, 9, 9, 6, 6, 6, 6, 10, 11, 9, 9, 6, 6, 9, 9, 
10, 11, 9, 9, 6, 6, 9, 9, 10, 11, 9, 9, 6, 6, 6, 6, 
10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 
9, 9, 9, 9, 9, 9, 9, 9, 6, 6, 6, 9, 9, 9, 9, 9, 
6, 6, 6, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 6, 6, 6, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 6, 6, 6, 6, 10, 11, 9, 9, 6, 6, 9, 9, 
10, 11, 9, 9, 6, 6, 9, 9, 10, 11, 9, 9, 6, 6, 6, 6, 
10, 11, 9, 9, 9, 6, 6, 6, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
6, 6, 6, 6, 9, 9, 9, 9, 9, 9, 6, 6, 9, 9, 9, 9, 
9, 9, 6, 6, 9, 9, 9, 9, 6, 6, 6, 6, 9, 9, 9, 9, 
6, 6, 6, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
};

u8 zazpi[256] = 
{
10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 7, 7, 7, 7, 
10, 11, 9, 9, 7, 7, 7, 7, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 
9, 9, 9, 9, 9, 9, 9, 9, 7, 7, 7, 7, 9, 9, 9, 9, 
7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 7, 7, 9, 9, 9, 9, 
9, 9, 7, 7, 9, 9, 9, 9, 9, 7, 7, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 7, 
10, 11, 9, 9, 9, 9, 9, 7, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
9, 7, 7, 9, 9, 9, 9, 9, 7, 7, 9, 9, 9, 9, 9, 9, 
7, 7, 9, 9, 9, 9, 9, 9, 7, 9, 9, 9, 9, 9, 9, 9, 
7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
};

u8 zortzi[256] = 
{
10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 8, 8, 8, 
10, 11, 9, 9, 8, 8, 8, 8, 10, 11, 9, 9, 8, 8, 9, 9, 
10, 11, 9, 9, 8, 8, 9, 9, 10, 11, 9, 9, 9, 8, 8, 8, 
10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 
9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 9, 9, 9, 9, 9, 
8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 9, 9, 9, 9, 
9, 9, 8, 8, 9, 9, 9, 9, 8, 8, 8, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 8, 8, 8, 10, 11, 9, 9, 8, 8, 9, 9, 
10, 11, 9, 9, 8, 8, 9, 9, 10, 11, 9, 9, 8, 8, 8, 8, 
10, 11, 9, 9, 9, 8, 8, 8, 10, 11, 9, 9, 9, 9, 9, 9, 
10, 11, 9, 9, 9, 9, 9, 9, 10, 11, 9, 9, 9, 9, 9, 9, 
8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 8, 8, 9, 9, 9, 9, 
9, 9, 8, 8, 9, 9, 9, 9, 8, 8, 8, 8, 9, 9, 9, 9, 
8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
};


/* Irudikatutako Spriteak memorian kargatzen ditu. SPRITE bat baino gehiago erakusteko
for bana egin behar da.*/

void spriteakMemorianGorde()
{
	//16*16ko spriteentzako
	for(int i = 0; i < 16 * 16 / 2; i++) 
	{
		gfxhasiera[i] = hasiera[i*2] | (hasiera[(i*2)+1]<<8);
		gfxaukera[i] = aukera[i*2] | (aukera[(i*2)+1]<<8);
		gfxbandera[i] = bandera[i*2] | (bandera[(i*2)+1]<<8);
		gfxhutsa[i] = hutsa[i*2] | (hutsa[(i*2)+1]<<8);
		gfxmina[i] = mina[i*2] | (mina[(i*2)+1]<<8);
		gfxbat[i] = bat[i*2] | (bat[(i*2)+1]<<8);
		gfxbi[i] = bi[i*2] | (bi[(i*2)+1]<<8);
		gfxhiru[i] = hiru[i*2] | (hiru[(i*2)+1]<<8);
		gfxlau[i] = lau[i*2] | (lau[(i*2)+1]<<8);
		gfxbost[i] = bost[i*2] | (bost[(i*2)+1]<<8);
		gfxsei[i] = sei[i*2] | (sei[(i*2)+1]<<8);
		gfxzazpi[i] = zazpi[i*2] | (zazpi[(i*2)+1]<<8);
		gfxzortzi[i] = zortzi[i*2] | (zortzi[(i*2)+1]<<8);
	}
}

/* Funtzio honek erronbo bat irudikatuko dut pantailako x-y posizioan. Pantailan ateratzea nahi den erronbo 
   bakoitzari indize desberdin bat esleitu behar zaio, 0 eta 126 balioen arteko indizea izan daiteke. */

void erakutsiHasiera(int indizea, int x, int y)
{
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color,
		gfxhasiera,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain);  
}

/*Funtzio honek erronbo baten indizea pasata pantailatik ezabatzen du*/
void ezabatuHasiera(int indizea, int x, int y)
{
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxhasiera,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}

void erakutsiAukera(int indizea, int x, int y)
{ 
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxaukera,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain);
}

void ezabatuAukera(int indizea, int x, int y)
{
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxaukera,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}

void erakutsiBandera(int indizea, int x, int y)
{ 
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxbandera,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain);
}

void ezabatuBandera(int indizea, int x, int y)
{
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxbandera,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}

void erakutsiHutsa(int indizea, int x, int y)
{ 
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxhutsa,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain);
}

void ezabatuHutsa(int indizea, int x, int y)
{
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxhutsa,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}

void erakutsiMina(int indizea, int x, int y)
{ 
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxmina,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain);
}

void ezabatuMina(int indizea, int x, int y)
{
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxmina,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}

void erakutsiBat(int indizea, int x, int y)
{ 
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxbat,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain);
}

void ezabatuBat(int indizea, int x, int y)
{
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxbat,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}

void erakutsiBi(int indizea, int x, int y)
{ 
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxbi,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain);
}

void ezabatuBi(int indizea, int x, int y)
{
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxbi,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}

void erakutsiHiru(int indizea, int x, int y)
{ 
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxhiru,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain);
}

void ezabatuHiru(int indizea, int x, int y)
{
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxhiru,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}

void erakutsiLau(int indizea, int x, int y)
{ 
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxlau,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain);
}

void ezabatuLau(int indizea, int x, int y)
{
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxlau,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}

void erakutsiBost(int indizea, int x, int y)
{ 
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxbost,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain);
}

void ezabatuBost(int indizea, int x, int y)
{
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxbost,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}

void erakutsiSei(int indizea, int x, int y)
{ 
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxsei,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain);
}

void ezabatuSei(int indizea, int x, int y)
{
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxsei,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}

void erakutsiZazpi(int indizea, int x, int y)
{ 
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxzazpi,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain);
}

void ezabatuZazpi(int indizea, int x, int y)
{
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxzazpi,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}

void erakutsiZortzi(int indizea, int x, int y)
{ 
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxzortzi,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain);
}

void ezabatuZortzi(int indizea, int x, int y)
{
	oamSet(&oamMain, //main graphics engine context
		indizea,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxzortzi,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	oamUpdate(&oamMain); 
}


