#pragma once

#include "TobiektGry.h"

class Tdrzwi : public TobiektGry {
private:
	int ktoreDrzwi;
	int kolizjaXLD;
	int kolizjaXPD;
	int kolizjaYGD;
	int kolizjaYDD;

public:
	Tdrzwi();
	Tdrzwi(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerDrzwi);

	void Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerDrzwi);
	void Aktualizuj(int xGracz, int yGracz);
	void Rysuj(int xGracz, int yGracz);

	bool otwarte;

	bool CzyWDrzwiach(TobiektGry *wsk);
};