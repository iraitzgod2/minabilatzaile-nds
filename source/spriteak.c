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


/* Pantailan erakutsi nahi den sprite bakoitzeko memoria erreserbatu.*/
void memoriaErreserbatu()
{
	/* Pantaila nagusian gehitu nahi den sprite bakoitzarentzako horrelako bat egin behar da. */
	gfxhasiera = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxaukera = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
}

/* Pixel bakoitzak har ditzakeen 256 balioetako bakoitzari kolore bat esleitu PANTAILA NAGUSIAN. 0 balioa gardena da 
   eta definitu gabeko balioak beltzak. SPRITEARI KOLOREAK ESLEITZEKO ALDATU*/
void paletaNagusiaEzarri()
{
	SPRITE_PALETTE[0] = RGB15(255, 255, 255); // Zuria
	SPRITE_PALETTE[1] = RGB15(0, 0, 255); // Urdina: 1 zenbakiaren kolorea
	SPRITE_PALETTE[2] = RGB15(0, 128, 0); // Berdea: 2 zenbakiaren kolorea
	SPRITE_PALETTE[3] = RGB15(255, 0, 0); // Gorria: 3 zenbakiaren kolorea
	SPRITE_PALETTE[4] = RGB15(0, 0, 128); // Urdin iluna: 4 zenbakiaren kolorea
	SPRITE_PALETTE[5] = RGB15(128, 0, 0); // Granate: 5 zenbakiaren kolorea
	SPRITE_PALETTE[6] = RGB15(0, 128, 128); // Esmeralda: 6 zenbakiaren kolorea
	SPRITE_PALETTE[7] = RGB15(0, 0, 0); // Beltza: 7 zenbakiaren kolorea
	SPRITE_PALETTE[8] = RGB15(128, 128, 128); // Grisa: 8 zenbakiaren kolorea
	SPRITE_PALETTE[9] = RGB15(189, 189, 189); // Gris paletak, kasilentzako
	SPRITE_PALETTE[10] = RGB15(123, 123, 123);
	SPRITE_PALETTE[11] = RGB15(162, 162, 162);
	SPRITE_PALETTE[12] = RGB15(238, 238, 238);
	SPRITE_PALETTE[13] = RGB15(144, 144, 144);
}

/* 16x16 pixeleko Sprite baten definizioa erronbo bat marrazteko */
/* Memoriako bankuek duten lan egiteko modua dela eta, lehenengo lau lerroak goiko
   ezkerreko koadrantean erakusten dira, hurrengo lauak goiko eskuineko kuadrantean,
   hurrengo lauak beheko ezkerreko koadrantean eta azkeneko lauak beheko ezkerreko koadrantean. 
   Alboko irudian ikusten den bezala. */

u8 hasiera[256] =
{

};

u8 aukera[256] =
{

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
	}
	//32*32ko spriteentzako
/*	for(i = 0; i < 32 * 32 / 2; i++) 
	{	
		gfxerronboHandia[i] = erronboHandia[i*2] | (erronboHandia[(i*2)+1]<<8);				
	}*/
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
		SpriteSize_32x32,     
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

