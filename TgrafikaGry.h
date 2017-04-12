#pragma once

#include "TobiektGry.h"

class TgrafikaGry : public TobiektGry {
private:
	int jakaGrafika;
	int poczatkowyPixelY;
	int (*PobierzParametry)(int);

public:
	enum {GRAFIKA_SZUMI, GRAFIKA_SERDUSZKO, GRAFIKA_MONETA};

	TgrafikaGry();
	TgrafikaGry(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int jakaGrafika, int (*PobierzParametrySzumiego)(int));

	void Rysuj(int xGracz, int yGracz);
	void Aktualizuj(int xGracz, int yGracz);
};