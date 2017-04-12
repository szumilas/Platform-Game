#include "TtloGry.h"

TtloGry::TtloGry() {
	TtloGry(0, 0, 0, 0, 0, 0, NULL, 0);

}

TtloGry::TtloGry(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki) {
	Tworz(x, y, vX, vY, kierX, kierY, obraz, numerKlatki);
	
}

void TtloGry::Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki) {

	TobiektGry::Tworz(x, y, vX, vY, kierX, kierY);

	NadajID(TLO_GRY);

	mozeKolidowac = false;
	naEkranie = true;

	poczatkoweX = x;
	poczatkoweY = y;

	pomocniczeX = x + 3000;

	klatkaOstatnia = 1;
	klatkaObecna = numerKlatki;
	klatkaLicznik = 0;
	klatkaOpoznienie = 1;
	klatkaSzerokosc = 3000;
	klatkaWysokosc = 1600;

	kolizjaXL = -1;
	kolizjaXP = -1;
	kolizjaYG = -1;
	kolizjaYD = -1;

	
	if(obraz != NULL)
		TobiektGry::obraz = obraz;

}

void TtloGry::Aktualizuj(int xGracz, int yGracz) {

}
void TtloGry::Rysuj(int xGracz, int yGracz) {
	if(yGracz > poczatkoweY + 1500 || yGracz < poczatkoweY -1500) {
		if(yGracz > y)
			al_clear_to_color(al_get_pixel(obraz, 1, 1600));
		else
			al_clear_to_color(al_get_pixel(obraz, 1, 1));
	}
	
	y = (yGracz * 4 + poczatkoweY) / 5;
	x = (xGracz * 2 + poczatkoweX) / 3;

	if(xGracz < x) {
		x -= 3000;
	} else if(xGracz > x + 3000) {
		x += 3000;
	}
	pomocniczeX = x + 3000;

	int fx = klatkaObecna * klatkaSzerokosc;
	int fy = 0;

	//if(obraz!=NULL)
	al_draw_bitmap_region(obraz, fx, fy, klatkaSzerokosc, klatkaWysokosc,
		SZEROKOSC / 2 + x - klatkaSzerokosc / 2 - xGracz,  WYSOKOSC / 2 + y - klatkaWysokosc / 2 - yGracz, 0);

	al_draw_bitmap_region(obraz, fx, fy, klatkaSzerokosc, klatkaWysokosc,
		SZEROKOSC / 2 + x + 3000 - klatkaSzerokosc / 2 - xGracz,  WYSOKOSC / 2 + y - klatkaWysokosc / 2 - yGracz, 0);

}