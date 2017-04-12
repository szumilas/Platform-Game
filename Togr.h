#pragma once

#include "Twrog.h"

class Togr : public Twrog {

private:
	void (*GrajDzwiek)(int);

public:
	Togr(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, void (*StworzBonus)(int, int, int, int), void (*GrajDzwiek)(int));

	void Aktualizuj(int xGracz, int yGracz);

};