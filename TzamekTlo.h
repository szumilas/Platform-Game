#pragma once

#include "Tblok.h"

class TzamekTlo : public Tblok {

private:

public:
	TzamekTlo();
	TzamekTlo(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki);
	TzamekTlo(const TzamekTlo & wzor);

	void Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki);
	void Aktualizuj(int xGracz, int yGracz);

};