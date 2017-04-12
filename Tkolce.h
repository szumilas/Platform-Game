#pragma once

#include "Tblok.h"

class Tkolce : public Tblok {
private:

public:
	Tkolce();
	Tkolce(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki);

	void Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki);

	void Aktualizuj(int xGracz, int yGracz);

};