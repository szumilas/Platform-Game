#pragma once

#include <string>
#include "TobiektGry.h"
#include <allegro5\allegro_font.h>

class Ttabliczka : public TobiektGry {

private:
	int idTekstu;
	
	ALLEGRO_FONT *czcionka;
	ALLEGRO_COLOR bialy_tekst;
	ALLEGRO_COLOR czarny_tekst;

public:
	Ttabliczka();
	Ttabliczka(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, int id, ALLEGRO_FONT *czcionka);

	void Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, int id, ALLEGRO_FONT *czcionka);

	void Aktualizuj(int xGracz, int yGracz);
	void Rysuj(int xGracz, int yGracz);

};