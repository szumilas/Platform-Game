#pragma once

#include "Twrog.h"

class Tgoblin : public Twrog {

private:

public:
	Tgoblin(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, void (*StworzBonus)(int, int, int, int));
	void Aktualizuj(int xGracz, int yGracz);

};