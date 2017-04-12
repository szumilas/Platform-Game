#pragma once

#include "Twrog.h"

class Tpudlo : public Twrog {

private:
	int ileBonusow;

public:
	Tpudlo();
	Tpudlo(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, void (*StworzBonus)(int, int, int, int));

	void Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, void (*StworzBonus)(int, int, int, int));
	
	void Usmierc();	
	void Aktualizuj(int xGracz, int yGracz);

};