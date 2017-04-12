#pragma once

#include <string>
#include "Tprzycisk.h"
#include <allegro5\allegro_font.h>

class TmenuWyboru : public Tprzycisk {

private:
	int szerokoscTla;
	int szerokoscPrzycisku;

	int wysokoscTla;
	int wysokoscPrzycisku;

	std::string tekstL1;
	std::string tekstL2;
	std::string tekstL3;
	std::string lewy;
	std::string prawy;

	bool wybrany;

public:

	TmenuWyboru(float x = 0, float y = 0, float vX = 0, float vY = 0, int kierX = 0, int kierY = 0,
		ALLEGRO_FONT *czcionka = NULL, ALLEGRO_BITMAP *obraz = NULL, std::string tekstL1 = "NULL",  std::string tekstL2 = "NULL",  std::string tekstL3 = "NULL",
		 std::string lewy = "NULL",  std::string prawy = "NULL", bool obramowanie = true, int wyrownanie = DO_CENTRUM);

	void Rysuj(int xGracz, int yGracz);
	void Aktualizuj(int wybranyPrzycisk);
	
	inline void ZmienWybrany() {if(wybrany == 0) wybrany = 1; else wybrany = 0;}
	inline bool Wybrany() {return wybrany;}
};