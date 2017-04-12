#pragma once

#include "Tblok.h"

class Tplatforma : public Tblok {
private:

	int jakDaleko;	//Do ktorego momentu ma sie wysuwac winda
	int poczatkoweX;
	int poczatkoweY;

public:
	Tplatforma();
	Tplatforma(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki);
	
	void Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki);
	void Aktualizuj(int xGracz, int yGracz);

	int ParametrKolizji();

};