#pragma once

#include "TobiektGry.h"

class Twrog : public TobiektGry {

protected:
	void (*StworzBonus)(int, int, int, int);

	int sprite[6][4];
	int poczatkoweX;
	int poczatkoweY;
	int kierAnimacji;
	bool animacjaZatrzymana;
	int rodzajWroga;
	int parametrRodzaju;

public:
	enum StanAI {AI_BEZCZYNNY, AI_CHODZENIE, AI_RANNY, AI_ATAK, AI_SMIERC, AI_BIEG};
	enum RodzajWroga {STRAZNIK_STOJACY, STRAZNIK_CHODZACY, AGRESOR};

	Twrog();
	Twrog(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, void (*StworzBonus)(int, int, int, int));
	
	void Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, void (*StworzBonus)(int, int, int, int));
	virtual void Usmierc();
	void Aktualizuj(int xGracz, int yGracz);
	void Rysuj(int xGracz, int yGracz);
	void ZmienStanAI(int stan) {if(stanAI != stan) {stanAI = stan; }}

	int stanAI;
	int jakiWrog;
	bool niesmiertelny;

};