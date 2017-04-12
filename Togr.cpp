#include "Togr.h"

Togr::Togr(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, void (*StworzBonus)(int, int, int, int), void (*GrajDzwiek)(int)) {
	Twrog::Tworz(x, y - 13, 0.5, vY, kierX, kierY, obraz, numerKlatki, StworzBonus);

	jakiWrog = 32;

	niesmiertelny = false;

	Togr::GrajDzwiek = GrajDzwiek;

	klatkaOpoznienie = 5;
	klatkaSzerokosc = 85;
	klatkaWysokosc = 85;

	kolizjaXL = 23;
	kolizjaXP = 23;
	kolizjaYG = 52;
	kolizjaYD = 56;
	
	sprite[0][0] = 100;		sprite[0][1] = 100;		sprite[0][2] = 0;	sprite[0][3] = 0;		//Bezczynny
	sprite[1][0] = 200;		sprite[1][1] = 200;		sprite[1][2] = 13;	sprite[1][3] = 0;		//Chodzenie
	sprite[2][0] = 200;		sprite[2][1] = 200;		sprite[2][2] = 8;	sprite[2][3] = 200;		//Ranny
	sprite[3][0] = 200;		sprite[3][1] = 200;		sprite[3][2] = 8;	sprite[3][3] = 400;		//Atak
	sprite[4][0] = 275;		sprite[4][1] = 175;		sprite[4][2] = 7;	sprite[4][3] = 600;		//Smierc
	sprite[5][0] = 100;		sprite[5][1] = 100;		sprite[5][2] = 0;	sprite[5][3] = 0;		//Bieg
}

void Togr::Aktualizuj(int xGracz, int yGracz) {
	Twrog::Aktualizuj(xGracz, yGracz);

	if(zyje && odleglosc(x, y, xGracz, yGracz) < 95 && (xGracz < x && kierX == -1 || xGracz > x && kierX == 1) || stanAI == AI_ATAK && klatkaObecna > 0) {
		if(stanAI != AI_ATAK) {
			klatkaObecna = 0;
			klatkaLicznik = 0;
		}
		stanAI = AI_ATAK;
		vX = 0;
		if(klatkaObecna == 4) {
			if(kierX == 1)
				kolizjaXP = 90;
			else
				kolizjaXL = 90;
			niesmiertelny = true;
		}
		else {
			kolizjaXL = 23;
			kolizjaXP = 23;
			niesmiertelny = false;
		}

	}
	else {
		vX = 0.5;
		if(zyje)
			stanAI = AI_CHODZENIE;
		kolizjaXL = 23;
		kolizjaXP = 23;
	}
	if(stanAI == AI_ATAK && klatkaObecna == 0 && klatkaLicznik == 0)
		GrajDzwiek(35);
}