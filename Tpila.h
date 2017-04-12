#pragma once

#include "Twinda.h"

class Tpila : public Twinda {

private:

public:
	Tpila();
	Tpila(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki);
	
	void Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki);
	void Aktualizuj(int xGracz, int yGracz);

};