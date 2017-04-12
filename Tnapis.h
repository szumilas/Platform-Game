#pragma once

#include <string>
#include "TobiektGry.h"
#include <allegro5\allegro_font.h>

class Tnapis : public TobiektGry {

private:
	ALLEGRO_FONT *czcionka;
	int (*PobierzParametry)(int ile);
	int jakiNapis;
	ALLEGRO_COLOR bialy_tekst;
	ALLEGRO_COLOR czarny_tekst;

	bool obramowanie;
	int wyrownanie;
	std::string tekst;

public:
	enum {PUNKTY = 1, ZYCIA, SERDUSZKA, MONETY, TEKST};
	enum {DO_LEWEJ = ALLEGRO_ALIGN_LEFT, DO_CENTRUM = ALLEGRO_ALIGN_CENTRE, DO_PRAWEJ = ALLEGRO_ALIGN_RIGHT};

	Tnapis(float x = 0, float y = 0, float vX = 0, float vY = 0, int kierX = 0, int kierY = 0, ALLEGRO_FONT *czcionka = NULL, int numerKlatki = 0, int typNapisu = 0,
		int (*PobierzParametrySzumiego)(int) = NULL, std::string tekst = "NULL", bool obramowanie = true, int wyrownanie = DO_CENTRUM);

	void Rysuj(int xGracz, int yGracz);
	void Aktualizuj(int xGracz, int yGracz);

	bool napisNaEkranie;
	int liczba;
	int typNapisu;

};