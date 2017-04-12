#include "Twrog.h"

Twrog::Twrog() {
	Twrog(0, 0, 0, 0, 0, 0, NULL, 0, NULL);
}

Twrog::Twrog(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, void (*StworzBonus)(int, int, int, int)) {
	Twrog::Tworz(x, y, vX, vY, kierX, kierY, obraz, numerKlatki, StworzBonus);

}

void Twrog::Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, void (*StworzBonus)(int, int, int, int)) {
	TobiektGry::Tworz(x, y, vX, vY, kierX, kierY);

	Twrog::StworzBonus = StworzBonus;

	NadajID(WROG);

	niesmiertelny = false;

	jakiWrog = 34;

	mozeKolidowac = true;

	animacjaZatrzymana = false;

	klatkaOstatnia = 1;
	klatkaObecna = 0;
	klatkaLicznik = 0;
	klatkaOpoznienie = 6;
	klatkaSzerokosc = 85;
	klatkaWysokosc = 85;

	kolizjaXL = 15;
	kolizjaXP = 15;
	kolizjaYG = 25;
	kolizjaYD = 43;
	
	sprite[0][0] = 100;		sprite[0][1] = 100;		sprite[0][2] = 6;	sprite[0][3] = 0;		//Bezczynny
	sprite[1][0] = 100;		sprite[1][1] = 100;		sprite[1][2] = 7;	sprite[1][3] = 100;		//Chodzenie
	sprite[2][0] = 125;		sprite[2][1] = 100;		sprite[2][2] = 7;	sprite[2][3] = 200;		//Ranny
	sprite[3][0] = 100;		sprite[3][1] = 100;		sprite[3][2] = 10;	sprite[3][3] = 300;		//Atak
	sprite[4][0] = 160;		sprite[4][1] = 100;		sprite[4][2] = 7;	sprite[4][3] = 400;		//Smierc
	sprite[5][0] = 100;		sprite[5][1] = 100;		sprite[5][2] = 10;	sprite[5][3] = 500;		//Bieg


	stanAI = AI_BEZCZYNNY;
	rodzajWroga = STRAZNIK_CHODZACY;
	if(numerKlatki > 0) {
		parametrRodzaju = numerKlatki;

		TobiektGry::kierX = 1;
		poczatkoweX = x;
	}
	else {
		parametrRodzaju = -numerKlatki;

		TobiektGry::kierX = -1;
		poczatkoweX = x - 85 * (parametrRodzaju - 1);

	}
	vX = 1;
	poczatkoweY = y;

	
	if(obraz != NULL)
		TobiektGry::obraz = obraz;
}

void Twrog::Aktualizuj(int xGracz, int yGracz) {
	if(odleglosc(x, y, xGracz, yGracz) < 800)
		naEkranie = true;
	else
		naEkranie = false;

	if(stanAI == AI_SMIERC && !naEkranie)
		aktywny = false;

	
	

	if(!animacjaZatrzymana) {
		if(rodzajWroga == STRAZNIK_STOJACY) {

		}
		else if (rodzajWroga == STRAZNIK_CHODZACY && zyje) {
			if(x >= poczatkoweX + 85 * (parametrRodzaju - 1)) {
				kierX = -1;
				kierAnimacji = -1;
			}
			if(x < poczatkoweX) {
				kierX = 1;
				kierAnimacji = 1;
			}
			x += kierX * vX;
			if(stanAI != AI_ATAK && stanAI != AI_BIEG)
				stanAI = AI_CHODZENIE;
		}
		

		if(++klatkaLicznik >= klatkaOpoznienie) {
			
			if(PobierzID() == WROG && stanAI == AI_RANNY && klatkaObecna == 0)
				StworzBonus(x, y - 50, NAPIS, 150);
			/*else if(PobierzID() == KROL && stanAI == AI_RANNY && klatkaObecna == 0)
				StworzBonus(x, y - 50, NAPIS, 20000);*/
			klatkaObecna ++;
			if(klatkaObecna >= sprite[stanAI][2]) {
				if(stanAI == AI_SMIERC) {
					animacjaZatrzymana = true;
					klatkaObecna--;
				}
				else if(stanAI == AI_RANNY) {
					stanAI = AI_SMIERC;
					klatkaObecna = 0;
				}
				else
					klatkaObecna = 0;
			}

			klatkaLicznik = 0;
		}

	}
}

void Twrog::Usmierc() {
	zyje = false;
	mozeKolidowac = false;
	stanAI = AI_RANNY;
	klatkaObecna = 0;

}

void Twrog::Rysuj(int xGracz, int yGracz) {

	int fx = klatkaObecna * sprite[stanAI][0];
	int fy = sprite[stanAI][3];
	
	al_draw_bitmap_region(obraz, fx, fy, sprite[stanAI][0], sprite[stanAI][1],
		SZEROKOSC / 2 + x - sprite[stanAI][0] / 2 - xGracz,  WYSOKOSC / 2 + y - sprite[stanAI][1] / 2 - yGracz, (kierAnimacji == -1) ? ALLEGRO_FLIP_HORIZONTAL : 0);

	if(wypiszProstokatKolizji && mozeKolidowac) {
		ALLEGRO_COLOR jaki = rozowy;
		if(naEkranie == true)
			jaki = zielony;
		al_draw_filled_rectangle(SZEROKOSC / 2 + x - kolizjaXL - xGracz, WYSOKOSC / 2 + y - kolizjaYG - yGracz, SZEROKOSC / 2 + x + kolizjaXP - xGracz, WYSOKOSC / 2 + y + kolizjaYD - yGracz, jaki);
		al_draw_filled_circle(SZEROKOSC / 2 + x - xGracz, WYSOKOSC / 2 + y - yGracz, 5, czarny);
	}
}