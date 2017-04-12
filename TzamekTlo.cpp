#include "TzamekTlo.h"

TzamekTlo::TzamekTlo() {
	TzamekTlo(0, 0, 0, 0, 0, 0, NULL, 0);

}

TzamekTlo::TzamekTlo(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki) {
	Tworz(x, y, vX, vY, kierX, kierY, obraz, numerKlatki);
	
}

TzamekTlo::TzamekTlo(const TzamekTlo & wzor) {
	*this = wzor;
}

void TzamekTlo::Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki) {
	TobiektGry::Tworz(x, y, vX, vY, kierX, kierY);

	NadajID(ZAMEK_TLO);

	mozeKolidowac = false;
	//naEkranie = true;

	klatkaOstatnia = 1;
	klatkaObecna = numerKlatki;
	klatkaLicznik = 0;
	klatkaOpoznienie = 1;
	klatkaSzerokosc = 85;
	klatkaWysokosc = 85;

	kolizjaXL = 10;
	kolizjaXP = -1;
	kolizjaYG = 10;
	kolizjaYD = -1;

	
	if(obraz != NULL)
		TobiektGry::obraz = obraz;
}

void TzamekTlo::Aktualizuj(int xGracz, int yGracz) {
	if(odleglosc(x, y, xGracz, yGracz) < 800)
		naEkranie = true;
	else
		naEkranie = false;
}