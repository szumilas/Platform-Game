#pragma once

#include "TobiektGry.h"

class TtloGry : public TobiektGry {

private:
	int poczatkoweX;
	int poczatkoweY;
	int pomocniczeX;

public:
	TtloGry();
	TtloGry(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki);

	void Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki);
	void Aktualizuj(int xGracz, int yGracz);
	void Rysuj(int xGracz, int yGracz);

};