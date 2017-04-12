#include "Tplatforma.h"

Tplatforma::Tplatforma() {
	Tplatforma(0, 0, 0, 0, 0, 0, NULL, 0);

}

Tplatforma::Tplatforma(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki) {
	Tworz(x, y, vX, vY, kierX, kierY, obraz, numerKlatki);
	
}

void Tplatforma::Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki) {
	TobiektGry::Tworz(x, y, vX, vY, kierX, 1);

	NadajID(PLATFORMA);

	
	poczatkoweY = y;

	if(kierX < 0) {
		jakDaleko = -kierX;
		poczatkoweX = x - 85 * (-1 - kierX);
	}
	else {
		jakDaleko = kierX;
		poczatkoweX = x;
	}

	klatkaOstatnia = 1;
	klatkaObecna = numerKlatki;
	klatkaLicznik = 0;
	klatkaOpoznienie = 1;
	klatkaSzerokosc = 85;
	klatkaWysokosc = 85;

	if(numerKlatki >= 1) {
		mozeKolidowac = false;
		
		kolizjaYG = 0;
		kolizjaYD = 0;

		kolizjaXL = 0;
		kolizjaXP = 0;
	}
	else {
		mozeKolidowac = true;
		kolizjaYG = 42;
		kolizjaYD = 2;

		kolizjaXL = 42;
		kolizjaXP = 43;
	}


	

	
	if(obraz != NULL)
		TobiektGry::obraz = obraz;
}

void Tplatforma::Aktualizuj(int xGracz, int yGracz) {
	if(odleglosc(x, y, xGracz, yGracz) < 2000)
		naEkranie = true;
	else
		naEkranie = false;
	if(klatkaObecna == 0) {
		if(x >= poczatkoweX + 85 * (jakDaleko -1))
			kierX = -1;
		else if(x <= poczatkoweX)
			kierX = 1;

		x += vX * kierX;
	}
}

int Tplatforma::ParametrKolizji() {
	return kierX;
}