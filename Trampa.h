#pragma once

#include "Tblok.h"

class Trampa : public Tblok {

private:
	int spadek;

public:
	Trampa();
	Trampa(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki);

	int ParametrKolizji();

};