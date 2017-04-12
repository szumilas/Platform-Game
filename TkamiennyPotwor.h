#pragma once

#include "Twrog.h"

class TkamiennyPotwor : public Twrog {

private:

public:
	TkamiennyPotwor(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, void (*StworzBonus)(int, int, int, int));

};