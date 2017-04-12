#include "Tekran.h"

Tekran::Tekran() {
	Tekran(0, 0, 0, 0, 0, 0, NULL, 0);
}

Tekran::Tekran(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerBitmapy) {
	TobiektGry::Tworz(x, y, vX, vY, kierX, kierY);

	NadajID(EKRAN);

	Tekran::numerBitmapy = numerBitmapy;

	klatkaOstatnia = 1;
	klatkaObecna = 0;
	klatkaLicznik = 0;
	klatkaOpoznienie = 1;
	klatkaSzerokosc = 1280;
	klatkaWysokosc = 720;

	if(obraz != NULL)
		TobiektGry::obraz = obraz;
}

void Tekran::Rysuj(int xGracz, int yGracz) {
	int fx = klatkaObecna * klatkaSzerokosc;
	int fy = numerBitmapy * WYSOKOSC;

	al_draw_bitmap_region(obraz, fx, fy, klatkaSzerokosc, klatkaWysokosc, 0, 0, 0);

}