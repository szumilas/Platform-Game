#include "Tblok.h"

Tblok::Tblok() {
	Tblok(0, 0, 0, 0, 0, 0, NULL, 0);

}

Tblok::Tblok(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki) {
	Tworz(x, y, vX, vY, kierX, kierY, obraz, numerKlatki);
	
}

void Tblok::Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki) {
	TobiektGry::Tworz(x, y, vX, vY, kierX, kierY);

	NadajID(BLOK);

	mozeKolidowac = true;

	klatkaOstatnia = 1;
	klatkaObecna = numerKlatki;
	klatkaLicznik = 0;
	klatkaOpoznienie = 1;
	klatkaSzerokosc = 85;
	klatkaWysokosc = 85;

	if(numerKlatki > 26) {
		kolizjaXL = 25;
		kolizjaXP = 25;
	}
	else {
		kolizjaXL = 42;
		kolizjaXP = 43;
	}
	kolizjaYG = 42;
	kolizjaYD = 43;

	
	if(obraz != NULL)
		TobiektGry::obraz = obraz;
}

void Tblok::Usun() {

}

void Tblok::Aktualizuj(int xGracz, int yGracz) {
	if(odleglosc(x, y, xGracz, yGracz) < 150) {
		naEkranie = true;
		sprawdzajKolizje = true;
	}
	else {
		sprawdzajKolizje = false;
		if(odleglosc(x, y, xGracz, yGracz) < 800)
			naEkranie = true;
		else
			naEkranie = false;
	}


}