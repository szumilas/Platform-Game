#include "Tgoblin.h"

Tgoblin::Tgoblin(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, void (*StworzBonus)(int, int, int, int)) {
	Twrog::Tworz(x, y + 13, 0.75, vY, kierX, kierY, obraz, numerKlatki, StworzBonus);

	jakiWrog = 31;

	niesmiertelny = false;

	klatkaOpoznienie = 5;
	klatkaSzerokosc = 85;
	klatkaWysokosc = 85;

	kolizjaXL = 10;
	kolizjaXP = 10;
	kolizjaYG = 26;
	kolizjaYD = 30;
	
	sprite[0][0] = 100;		sprite[0][1] = 100;		sprite[0][2] = 0;	sprite[0][3] = 0;		//Bezczynny
	sprite[1][0] = 100;		sprite[1][1] = 100;		sprite[1][2] = 6;	sprite[1][3] = 0;		//Chodzenie
	sprite[2][0] = 100;		sprite[2][1] = 100;		sprite[2][2] = 6;	sprite[2][3] = 100;		//Ranny
	sprite[3][0] = 100;		sprite[3][1] = 100;		sprite[3][2] = 0;	sprite[3][3] = 0;		//Atak
	sprite[4][0] = 125;		sprite[4][1] = 90;		sprite[4][2] = 6;	sprite[4][3] = 200;		//Smierc
	sprite[5][0] = 100;		sprite[5][1] = 100;		sprite[5][2] = 8;	sprite[5][3] = 290;		//Bieg
}


void Tgoblin::Aktualizuj(int xGracz, int yGracz) {
	Twrog::Aktualizuj(xGracz, yGracz);


	if(zyje && odleglosc(x, y, xGracz, yGracz) < 200 && (xGracz < x && kierX == -1 || xGracz > x && kierX == 1) || stanAI == AI_BIEG && klatkaObecna > 0) {
		/*if(stanAI != AI_BIEG)
			klatkaObecna = 0;*/
		stanAI = AI_BIEG;
		vX = 2.2;
		klatkaOpoznienie = 4;
	}
	else {
		vX = 0.8;
		klatkaOpoznienie = 5;
		if(zyje)
			stanAI = AI_CHODZENIE;
	}
	
}