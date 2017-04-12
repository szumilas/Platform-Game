#include "Tkolce.h"

Tkolce::Tkolce() {
	Tkolce(0, 0, 0, 0, 0, 0, NULL, 0);

}

Tkolce::Tkolce(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki) {
	Tworz(x, y, vX, vY, kierX, kierY, obraz, numerKlatki);
	
}

void Tkolce::Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki) {
	TobiektGry::Tworz(x, y, vX, vY, kierX, kierY);

	NadajID(KOLCE);

	mozeKolidowac = true;

	klatkaOstatnia = 1;
	klatkaObecna = numerKlatki;
	klatkaLicznik = 0;
	klatkaOpoznienie = 1;
	klatkaSzerokosc = 85;
	klatkaWysokosc = 85;


	if(numerKlatki == 0) {
		kolizjaXL = 35;
		kolizjaXP = 35;
		kolizjaYG = 0;
		kolizjaYD = 43;
	} else if(numerKlatki == 1) {
		kolizjaXL = 35;
		kolizjaXP = 35;
		kolizjaYG = 43;
		kolizjaYD = -20;
	} else if(numerKlatki == 2) {
		kolizjaXL = 35;
		kolizjaXP = 35;
		kolizjaYG = 43;
		kolizjaYD = 0;
	}
	else {
		kolizjaXL = 0;
		kolizjaXP = 0;
		kolizjaYG = 0;
		kolizjaYD = 0;
	}


	
	if(obraz != NULL)
		TobiektGry::obraz = obraz;

}

void Tkolce::Aktualizuj(int xGracz, int yGracz) {
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