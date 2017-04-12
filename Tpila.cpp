#include "Tpila.h"

Tpila::Tpila() {
	Tpila(0, 0, 0, 0, 0, 0, NULL, 0);

}

Tpila::Tpila(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki) {
	Tworz(x, y, vX, vY, kierX, kierY, obraz, numerKlatki);
	
}

void Tpila::Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki) {
	TobiektGry::Tworz(x, y, vX, vY, kierX, kierY);

	NadajID(PILA);

	if(kierY) {
		poczatkoweX = x;

		if(kierY < 0) {
			jakDaleko = -kierY;
			poczatkoweY = y - 85 * (-1 - kierY);
		}
		else {
			jakDaleko = kierY;
			poczatkoweY = y;
		}
	}
	else {
		poczatkoweY = y;

		if(kierX < 0) {
			kierX += 100;
			jakDaleko = - kierX;
			poczatkoweX = x - 85 * (-1 - kierX);
		}
		else {
			kierX -= 100;
			jakDaleko = kierX;
			poczatkoweX = x;
		}

	}


	klatkaOstatnia = 12;
	klatkaObecna = numerKlatki;
	klatkaLicznik = 0;
	klatkaOpoznienie = 3;
	klatkaSzerokosc = 85;
	klatkaWysokosc = 85;

	if(numerKlatki >= 12) {
		mozeKolidowac = false;
		
		kolizjaYG = 0;
		kolizjaYD = 0;

		kolizjaXL = 0;
		kolizjaXP = 0;
	}
	else {
		mozeKolidowac = true;
		kolizjaYG = 32;
		kolizjaYD = 32;

		kolizjaXL = 32;
		kolizjaXP = 32;
	}


	

	
	if(obraz != NULL)
		TobiektGry::obraz = obraz;
}

void Tpila::Aktualizuj(int xGracz, int yGracz) {
	if(odleglosc(x, y, xGracz, yGracz) < 2000)
		naEkranie = true;
	else
		naEkranie = false;
	if(klatkaObecna < 12) {
		if(kierY) {
			if(y >= poczatkoweY + 85 * (jakDaleko - 1))
				kierY = -1;
			else if(y <= poczatkoweY)
				kierY = 1;
			y += vY * kierY;
		}
		else {
			if(x >= poczatkoweX + 85 * (jakDaleko - 1))
				kierX = -1;
			else if(x <= poczatkoweX)
				kierX = 1;
			x += vX * kierX;
		}
		
		if(++klatkaLicznik >= klatkaOpoznienie) {
				klatkaObecna ++;
				if(klatkaObecna >= klatkaOstatnia)
					klatkaObecna = 0;

				klatkaLicznik = 0;
		}
	}
	
}