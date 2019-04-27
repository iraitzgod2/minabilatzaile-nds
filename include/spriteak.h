extern u16* gfx;
extern u16* gfx2;
extern u16* gfx3;
extern u16* gfxSub;

extern void memoriaErreserbatu();

/* Pixel bakoitzak har ditzakeen 256 balioetako bakoitzari kolore bat esleitu pantaila nagusian. 0 balioa gardena da 
   eta definitu gabeko balioak beltzak. */

extern void paletaNagusiaEzarri();

/* Pixel bakoitzak har ditzakeen 256 balioetako bakoitzari kolore bat esleitu bigarren pantailan. 0 balioa 
   gardena da eta definitu gabeko balioak beltzak. */

extern void bigarrenPaletaEzarri();

/* Irudikatutako Spriteak memorian kargatzen ditu.*/

extern void spriteakMemorianGorde();

/* Funtzio honek erronbo bat irudikatuko dut pantailako x-y posizioan. Pantailan ateratzea nahi den erronbo 
   bakoitzari indize desberdin bat esleitu behar zaio, 0 eta 126 balioen arteko indizea izan daiteke. */

extern void erakutsiHasiera(int indizea, int x, int y);

/*Funtzio honek erronbo baten indizea pasata pantailatik ezabatzen du*/

extern void ezabatuHasiera(int indizea, int x, int y);

extern void erakutsiAukera(int indizea, int x, int y);
extern void ezabatuAukera(int indizea, int x, int y);

extern void erakutsiBandera(int indizea, int x, int y);
extern void ezabatuBandera(int indizea, int x, int y);

extern void erakutsiHutsa(int indizea, int x, int y);
extern void ezabatuHutsa(int indizea, int x, int y);

extern void erakutsiMina(int indizea, int x, int y);
extern void ezabatuMina(int indizea, int x, int y);

extern void erakutsiBat(int indizea, int x, int y);
extern void ezabatuBat(int indizea, int x, int y);

extern void erakutsiBi(int indizea, int x, int y);
extern void ezabatuBi(int indizea, int x, int y);

extern void erakutsiHiru(int indizea, int x, int y);
extern void ezabatuHiru(int indizea, int x, int y);

extern void erakutsiLau(int indizea, int x, int y);
extern void ezabatuLau(int indizea, int x, int y);

extern void erakutsiBost(int indizea, int x, int y);
extern void ezabatuBost(int indizea, int x, int y);

extern void erakutsiSei(int indizea, int x, int y);
extern void ezabatuSei(int indizea, int x, int y);

extern void erakutsiZazpi(int indizea, int x, int y);
extern void ezabatuZazpi(int indizea, int x, int y);

extern void erakutsiZortzi(int indizea, int x, int y);
extern void ezabatuZortzi(int indizea, int x, int y);
