#pragma once

#include <string>
#include "TobiektGry.h"
#include <allegro5\allegro_font.h>

class Tprzycisk : public TobiektGry {

protected:
	ALLEGRO_FONT *czcionka;
	ALLEGRO_COLOR bialy_tekst;
	ALLEGRO_COLOR czarny_tekst;
	ALLEGRO_COLOR zolty_tekst;

	bool obramowanie;
	int wyrownanie;
	int numerPrzycisku;

public:
	enum {DO_LEWEJ = ALLEGRO_ALIGN_LEFT, DO_CENTRUM = ALLEGRO_ALIGN_CENTRE, DO_PRAWEJ = ALLEGRO_ALIGN_RIGHT};

	Tprzycisk(float x = 0, float y = 0, float vX = 0, float vY = 0, int kierX = 0, int kierY = 0,
		ALLEGRO_FONT *czcionka = NULL, ALLEGRO_BITMAP *obraz = NULL, int numerPrzycisku = 1, std::string tekst = "NULL", bool obramowanie = true, int wyrownanie = DO_CENTRUM);

	void Rysuj(int xGracz, int yGracz);
	void Aktualizuj(int wybraneMenu, int wybranyPrzycisk);

	std::string tekst;
	bool animuj;

};