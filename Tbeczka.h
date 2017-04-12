#pragma once

#include "Tpudlo.h"

class Tbeczka : public Tpudlo {
private:


public:
	Tbeczka();
	Tbeczka(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, void (*StworzBonus)(int, int, int, int));



};