#include "TobiektGry.h"

TobiektGry::TobiektGry() {
	x = 0;
	y = 0;

	vX = 0;
	vY = 0;

	kierX = 0;
	kierY = 0;

	klatkaOstatnia = 10;
	klatkaObecna = 0;
	klatkaLicznik = 0;
	klatkaOpoznienie = 4;
	klatkaSzerokosc = 100;
	klatkaWysokosc = 100;

	naEkranie = false;
	sprawdzajKolizje = true;
	zyje = true;
	
	aktywny = true;

	obraz = NULL;

	rozowy = al_map_rgba(255, 0, 255, 10);
	zielony = al_map_rgba(0, 200, 0, 10);
	niebieski = al_map_rgba(0, 0, 200, 10);
	czarny = al_map_rgba(0, 0, 0, 80);

}
void TobiektGry::Usun() {

}
void TobiektGry::Tworz(float x, float y, float vX, float vY, int kierX, int kierY) {
	aktywny = true;

	TobiektGry::x = x;
	TobiektGry::y = y;

	TobiektGry::vX = vX;
	TobiektGry::vY = vY;

	TobiektGry::kierX = kierX;
	TobiektGry::kierY = kierY;


}
void TobiektGry::Aktualizuj(int xGracz, int yGracz) {
	if(odleglosc(x, y, xGracz, yGracz) < 100)
		naEkranie = true;
	else
		naEkranie = false;

	x += vX * kierX;
	y += vY * kierY;

	if(++klatkaLicznik >= klatkaOpoznienie) {
		klatkaObecna ++;
		if(klatkaObecna >= klatkaOstatnia)
			klatkaObecna = 0;

		klatkaLicznik = 0;
	}
}
void TobiektGry::Rysuj(int xGracz, int yGracz) {
	int fx = klatkaObecna * klatkaSzerokosc;
	int fy = 0;

	//if(obraz!=NULL)
	al_draw_bitmap_region(obraz, fx, fy, klatkaSzerokosc, klatkaWysokosc,
		SZEROKOSC / 2 + x - klatkaSzerokosc / 2 - xGracz,  WYSOKOSC / 2 + y - klatkaWysokosc / 2 - yGracz, 0);

	if(wypiszProstokatKolizji) {
		ALLEGRO_COLOR jaki = rozowy;
		if(CzyMozeKolidowac() == true)
			jaki = zielony;
		al_draw_filled_rectangle(SZEROKOSC / 2 + x - kolizjaXL - xGracz, WYSOKOSC / 2 + y - kolizjaYG - yGracz, SZEROKOSC / 2 + x + kolizjaXP - xGracz, WYSOKOSC / 2 + y + kolizjaYD - yGracz, jaki);
		al_draw_filled_circle(SZEROKOSC / 2 + x - xGracz, WYSOKOSC / 2 + y - yGracz, 5, czarny);
		

	}

}


bool TobiektGry::CzyKolizja(TobiektGry *innyObiekt) {
	int x2 = innyObiekt->PobierzX();
	int y2 = innyObiekt->PobierzY();

	int kolizjaXL2 = innyObiekt->PobierzKolizjaXL();
	int kolizjaXP2 = innyObiekt->PobierzKolizjaXP();
	int kolizjaYG2 = innyObiekt->PobierzKolizjaYG();
	int kolizjaYD2 = innyObiekt->PobierzKolizjaYD();



	if( x + kolizjaXP > x2 - kolizjaXL2 &&
		x - kolizjaXL < x2 + kolizjaXP2 &&
		y + kolizjaYD > y2 - kolizjaYG2 &&
		y - kolizjaYG < y2 + kolizjaYD2)
		return true;
	else
		return false;
}

void TobiektGry::KolidujeZ(int ID, TobiektGry *zKim) {

}

int TobiektGry::ParametrKolizji() {
	return 0;
}

