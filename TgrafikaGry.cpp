#include "TgrafikaGry.h"

TgrafikaGry::TgrafikaGry() {
	TgrafikaGry(0, 0, 0, 0, 0, 0, NULL, 0, NULL);
}

TgrafikaGry::TgrafikaGry(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int jakaGrafika, int (*PobierzParametrySzumiego)(int)) {
	TobiektGry::Tworz(x, y, vX, vY, kierX, kierY);

	NadajID(GRAFIKA_GRY);

	TgrafikaGry::jakaGrafika = jakaGrafika;

	PobierzParametry = PobierzParametrySzumiego;

	naEkranie = true;

	if(jakaGrafika == GRAFIKA_SZUMI) {
		poczatkowyPixelY = 0;

		klatkaOstatnia = 1;
		klatkaObecna = 0;
		klatkaLicznik = 0;
		klatkaOpoznienie = 1;
		klatkaSzerokosc = 50;
		klatkaWysokosc = 50;
	}
	else if(jakaGrafika == GRAFIKA_SERDUSZKO) {
		poczatkowyPixelY = 50;

		klatkaOstatnia = 1;
		klatkaObecna = 0;
		klatkaLicznik = 0;
		klatkaOpoznienie = 1;
		klatkaSzerokosc = 25;
		klatkaWysokosc = 25;
	}
	else if(jakaGrafika == GRAFIKA_MONETA) {
		poczatkowyPixelY = 75;

		klatkaOstatnia = 1;
		klatkaObecna = 0;
		klatkaLicznik = 0;
		klatkaOpoznienie = 1;
		klatkaSzerokosc = 25;
		klatkaWysokosc = 25;
	}
	
	
	if(obraz != NULL)
		TobiektGry::obraz = obraz;

}

void TgrafikaGry::Rysuj(int xGracz, int yGracz) {
	int fx = klatkaObecna * klatkaSzerokosc;
	int fy = poczatkowyPixelY;

	//if(obraz!=NULL)
	al_draw_bitmap_region(obraz, fx, fy, klatkaSzerokosc, klatkaWysokosc, x,  y, 0);

}

void TgrafikaGry::Aktualizuj(int xGracz, int yGracz) {
	if(jakaGrafika == GRAFIKA_SERDUSZKO) {
		int ileSerc = PobierzParametry(3);

		if(x >= SZEROKOSC - 100 + ileSerc * 25)
			naEkranie = false;
		else
			naEkranie = true;

	}
}