#include "TkamiennyPotwor.h"

TkamiennyPotwor::TkamiennyPotwor(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, void (*StworzBonus)(int, int, int, int)) {
	Twrog::Tworz(x, y - 14, 1.7, vY, kierX, kierY, obraz, numerKlatki, StworzBonus);

	jakiWrog = 33;

	niesmiertelny = false;

	klatkaOpoznienie = 5;
	klatkaSzerokosc = 85;
	klatkaWysokosc = 85;

	kolizjaXL = 28;
	kolizjaXP = 28;
	kolizjaYG = 60;
	kolizjaYD = 57;
	
	sprite[0][0] = 100;		sprite[0][1] = 100;		sprite[0][2] = 0;	sprite[0][3] = 0;		//Bezczynny
	sprite[1][0] = 130;		sprite[1][1] = 125;		sprite[1][2] = 10;	sprite[1][3] = 0;		//Chodzenie
	sprite[2][0] = 150;		sprite[2][1] = 150;		sprite[2][2] = 5;	sprite[2][3] = 125;		//Ranny
	sprite[3][0] = 100;		sprite[3][1] = 100;		sprite[3][2] = 0;	sprite[3][3] = 0;		//Atak
	sprite[4][0] = 150;		sprite[4][1] = 140;		sprite[4][2] = 5;	sprite[4][3] = 275;		//Smierc
	sprite[5][0] = 100;		sprite[5][1] = 100;		sprite[5][2] = 0;	sprite[5][3] = 0;		//Bieg
}