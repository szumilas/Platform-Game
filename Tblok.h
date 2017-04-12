#pragma once

#include "TobiektGry.h"

class Tblok : public TobiektGry {
private:

public:
	Tblok();
	Tblok(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki);

	void Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki);

	void Aktualizuj(int xGracz, int yGracz);
	void Usun();

};