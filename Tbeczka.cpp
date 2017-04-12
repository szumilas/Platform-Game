#include "Tbeczka.h"

Tbeczka::Tbeczka() {
	Tbeczka(0, 0, 0, 0, 0, 0, NULL, 0, NULL);
}

Tbeczka::Tbeczka(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, void (*StworzBonus)(int, int, int, int)) {
	Tpudlo::Tworz(x, y, vX, vY, kierX, kierY, obraz, numerKlatki, StworzBonus);

	idPudla = 1;

	
	klatkaOpoznienie = 6;

	niesmiertelny = false;

	kolizjaXL = 30;
	kolizjaXP = 30;
	kolizjaYG = 30;
	kolizjaYD = 43;
	
	sprite[0][0] = 85;		sprite[0][1] = 85;		sprite[0][2] = 1;	sprite[0][3] = 0;		//Bezczynny
	sprite[1][0] = 85;		sprite[1][1] = 85;		sprite[1][2] = 1;	sprite[1][3] = 0;		//Chodzenie
	sprite[2][0] = 85;		sprite[2][1] = 85;		sprite[2][2] = 5;	sprite[2][3] = 85;		//Ranny
	sprite[3][0] = 85;		sprite[3][1] = 85;		sprite[3][2] = 1;	sprite[3][3] = 0;		//Atak
	sprite[4][0] = 85;		sprite[4][1] = 85;		sprite[4][2] = 7;	sprite[4][3] = 170;		//Smierc
	sprite[5][0] = 85;		sprite[5][1] = 85;		sprite[5][2] = 1;	sprite[5][3] = 0;		//Bieg
}