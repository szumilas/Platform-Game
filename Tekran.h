#pragma once

#include "TobiektGry.h"

class Tekran : public TobiektGry {

private:
	int numerBitmapy;

public:
	Tekran();
	Tekran(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerBitmapy);

	void Rysuj(int xGracz, int yGracz);
};