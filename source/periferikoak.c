/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"


int tekla; //sakatutako tekla gordetzeko aldagaia



int TeklaDetektatu() 
{
	//TRUE itzultzen du teklaren bat sakatu dela detektatzen badu
    if ((~TEKLAK_DAT & 0x03ff)!=0)
	{
 		return 1;
	} else {
		return 0;
	}
}

int SakatutakoTekla() 
{
	//Sakatutako teklaren balioa itzultzen du: A=0;B=1;Select=2;Start=3;Esk=4;Ezk=5;
	//Gora=6;Behera=7;R=8;L=9;
    switch(~TEKLAK_DAT & 0x03ff)
	{
    case 0x0001: return A; //A
    case 0x0002: return B;
    case 0x0004: return SELECT;
    case 0x0008: return START;
    case 0x0010: return ESKUBI;
    case 0x0020: return EZKER;
    case 0x0040: return GORA;
    case 0x0080: return BEHERA;
    case 0x0100: return R;
    case 0x0200: return L;
    default: return -1;
	}

}
//KONF=0x4003
void konfiguratuTeklatua(int TEK_konf)
{
	//Teklatuaren konfigurazioa bere S/I erregistroak aldatuz
	TEKLAK_KNT = TEKLAK_KNT | TEK_konf;
}

void konfiguratuTenporizadorea(int Latch, int TENP_konf)
{
	//Tenporizadorearen konfigurazioa bere S/I erregistroak aldatuz

	// Erregistroen aldaketa
	DENB0_DAT = Latch;					// Latch-a datu erregistroan gorde
	DENB0_KNT = DENB0_KNT | TENP_konf;  // Konfiguratu kontrol-erregistroa
}

void TekEtenBaimendu()
{
	//Teklatuaren etenak baimendu
	//Lan hau burutzeko lehenengo eten guztiak galarazi behar dira eta bukaeran baimendu 
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE = IE | 0x00001000;
	IME=1;
}

void TekEtenGalarazi()
{
	//Teklatuaren etenak galarazi
	//Lan hau burutzeko lehenengo eten guztiak galarazi behar dira eta bukaeran baimendu 
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE= IE & 0xffffefff;
	IME=1;
}  

void DenbEtenBaimendu()
{

//Denboragailu baten etenak baimendu (Timer0)
//Horretarako lehenengo eten guztiak galarazi eta bukaeran berriro baimendu
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE = IE | 0x00000008;
	IME=1;
}

void DenbEtenGalarazi()
{

//Denboragailu baten etenak galarazi (Timer0)
//Horretarako lehenengo eten guztiak galarazi eta bukaeran berriro baimendu
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE = IE & 0xfffffff7;
	IME=1;

}

void ErlojuaMartxanJarri()
{
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	DENB0_KNT = DENB0_KNT | 0x00000080;
}

void ErlojuaGelditu()
{
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	DenbEtenBaimendu();
}

