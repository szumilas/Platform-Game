#include "Tpudlo.h"

Tpudlo::Tpudlo() {
	Tpudlo(0, 0, 0, 0, 0, 0, NULL, 0, NULL);
}

Tpudlo::Tpudlo(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, void (*StworzBonus)(int, int, int, int)) {
	Tpudlo::Tworz(x, y, vX, vY, kierX, kierY, obraz, numerKlatki, StworzBonus);
}


void Tpudlo::Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, void (*StworzBonus)(int, int, int, int)) {
	TobiektGry::Tworz(x, y, vX, vY, kierX, kierY);

	Tpudlo::StworzBonus = StworzBonus;

	NadajID(PUDLO);
	idPudla = 0;

	niesmiertelny = false;

	mozeKolidowac = true;

	animacjaZatrzymana = false;

	ileBonusow = numerKlatki;

	klatkaOstatnia = 1;
	klatkaObecna = 0;
	klatkaLicznik = 0;
	klatkaOpoznienie = 4;
	klatkaSzerokosc = 85;
	klatkaWysokosc = 85;

	kolizjaXL = 13;
	kolizjaXP = 13;
	kolizjaYG = 30;
	kolizjaYD = 43;
	
	sprite[0][0] = 85;		sprite[0][1] = 85;		sprite[0][2] = 1;	sprite[0][3] = 0;		//Bezczynny
	sprite[1][0] = 85;		sprite[1][1] = 85;		sprite[1][2] = 1;	sprite[1][3] = 0;		//Chodzenie
	sprite[2][0] = 85;		sprite[2][1] = 85;		sprite[2][2] = 8;	sprite[2][3] = 85;		//Ranny
	sprite[3][0] = 85;		sprite[3][1] = 85;		sprite[3][2] = 1;	sprite[3][3] = 0;		//Atak
	sprite[4][0] = 85;		sprite[4][1] = 85;		sprite[4][2] = 6;	sprite[4][3] = 170;		//Smierc
	sprite[5][0] = 85;		sprite[5][1] = 85;		sprite[5][2] = 1;	sprite[5][3] = 0;		//Bieg

	stanAI = AI_BEZCZYNNY;
	
	if(obraz != NULL)
		TobiektGry::obraz = obraz;
}

void Tpudlo::Usmierc() {
	if(stanAI != AI_RANNY && stanAI != AI_SMIERC) {
		if(ileBonusow > 0) {
			zyje = true;
			mozeKolidowac = true;
			stanAI = AI_RANNY;
			klatkaObecna = 0;
		}
		else {
			zyje = false;
			mozeKolidowac = false;
			stanAI = AI_SMIERC;
			klatkaObecna = 0;
		}
		//StworzBonus(x, y, BONUS);
		ileBonusow--;
		if(ileBonusow >= 0)
			StworzBonus(x, y - 30, BONUS, 100);
		if(ileBonusow == -1)
			StworzBonus(x, y - 50, NAPIS, 100);
	}


}

void Tpudlo::Aktualizuj(int xGracz, int yGracz) {
	Twrog::Aktualizuj(xGracz, yGracz);
	if(ileBonusow >= 0 && stanAI == AI_SMIERC) {
		stanAI = AI_BEZCZYNNY;
		animacjaZatrzymana = false;
		zyje = true;
	}
	
}