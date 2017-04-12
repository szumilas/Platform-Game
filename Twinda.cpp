#include "Twinda.h"

Twinda::Twinda() {
	Twinda(0, 0, 0, 0, 0, 0, NULL, 0);

}

Twinda::Twinda(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki) {
	Tworz(x, y, vX, vY, kierX, kierY, obraz, numerKlatki);
	
}

void Twinda::Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki) {
	TobiektGry::Tworz(x, y, vX, vY, kierX, 1);

	NadajID(WINDA);

	
	poczatkoweX = x;

	if(kierY < 0) {
		jakDaleko = -kierY;
		poczatkoweY = y - 85 * (-1 - kierY);
	}
	else {
		jakDaleko = kierY;
		poczatkoweY = y;
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
		kolizjaYD = 0;

		kolizjaXL = 42;
		kolizjaXP = 43;
	}


	

	
	if(obraz != NULL)
		TobiektGry::obraz = obraz;
}

void Twinda::Aktualizuj(int xGracz, int yGracz) {
	if(odleglosc(x, y, xGracz, yGracz) < 2000)
		naEkranie = true;
	else
		naEkranie = false;
	if(klatkaObecna == 0) {
		if(y >= poczatkoweY + 85 * (jakDaleko - 1))
			kierY = -1;
		else if(y <= poczatkoweY)
			kierY = 1;

		y += vY * kierY;
	}
}