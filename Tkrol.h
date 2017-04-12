#pragma once

#include <string>
#include <allegro5\allegro_font.h>
#include "Twrog.h"

class Tkrol : public Twrog {
private:
	ALLEGRO_FONT *czcionka;
	ALLEGRO_COLOR bialy_tekst;
	ALLEGRO_COLOR czarny_tekst;

public:
	Tkrol(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, void (*StworzBonus)(int, int, int, int), ALLEGRO_FONT *czcionka);

	void Usmierc();
	void Aktualizuj(int xGracz, int yGracz);
	void Rysuj(int xGracz, int yGracz);

	int ileZyc;

	bool koniecGry;
};