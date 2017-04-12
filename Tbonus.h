#pragma once

#include "TobiektGry.h"

class Tbonus : public TobiektGry {
private:
	int poczatkowyPixelY;

public:
	enum {PIENIAZEK, SERDUSZKO, MIESO, ZNIKANIE, TRUSKAWKA, BANAN, JABLKO, CEBULA, BROKUL, MARCHEWKA, CHILI, WISNIA, WINOGRON, PAPRYKA, PIECZARKI};

	Tbonus();
	Tbonus(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int jakiBonus);

	void Aktualizuj(int xGracz, int yGracz);
	void Rysuj(int xGracz, int yGracz);
	bool zdobyty;

	int jakiBonus;
	bool skalowany;

};