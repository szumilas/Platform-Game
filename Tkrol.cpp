#include "Tkrol.h"

Tkrol::Tkrol(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, void (*StworzBonus)(int, int, int, int), ALLEGRO_FONT *czcionka) {
	TobiektGry::Tworz(x, y, vX, vY, kierX, kierY);

	Twrog::StworzBonus = StworzBonus;

	koniecGry = false;

	NadajID(KROL);

	niesmiertelny = false;

	Tkrol::czcionka = czcionka;

	mozeKolidowac = true;

	animacjaZatrzymana = false;

	ileZyc = 10;

	klatkaOstatnia = 1;
	klatkaObecna = 0;
	klatkaLicznik = 0;
	klatkaOpoznienie = 8;
	klatkaSzerokosc = 85;
	klatkaWysokosc = 85;

	kolizjaXL = 10;
	kolizjaXP = 10;
	kolizjaYG = 30;
	kolizjaYD = 43;
	
	sprite[0][0] = 100;		sprite[0][1] = 100;		sprite[0][2] = 4;	sprite[0][3] = 0;		//Bezczynny
	sprite[1][0] = 100;		sprite[1][1] = 100;		sprite[1][2] = 0;	sprite[1][3] = 0;		//Chodzenie
	sprite[2][0] = 125;		sprite[2][1] = 100;		sprite[2][2] = 4;	sprite[2][3] = 100;		//Ranny
	sprite[3][0] = 100;		sprite[3][1] = 100;		sprite[3][2] = 0;	sprite[3][3] = 0;		//Atak
	sprite[4][0] = 175;		sprite[4][1] = 125;		sprite[4][2] = 5;	sprite[4][3] = 200;		//Smierc
	sprite[5][0] = 100;		sprite[5][1] = 100;		sprite[5][2] = 5;	sprite[5][3] = 0;		//Bieg


	stanAI = AI_BEZCZYNNY;
	rodzajWroga = STRAZNIK_STOJACY;
	TobiektGry::kierX = -1;
	kierAnimacji = -1;
	poczatkoweX = x;

	vX = 0;
	poczatkoweY = y;

	bialy_tekst = al_map_rgb(250, 250, 250);
	czarny_tekst = al_map_rgb(0, 0, 0);

	
	if(obraz != NULL)
		TobiektGry::obraz = obraz;
}

void Tkrol::Usmierc() {
	if(stanAI != AI_RANNY && stanAI != AI_SMIERC) {
		if(ileZyc > 0) {
			zyje = true;
			//mozeKolidowac = true;
			stanAI = AI_RANNY;
			klatkaObecna = 0;
		}
		else {
			zyje = false;
			mozeKolidowac = false;
			stanAI = AI_SMIERC;
			klatkaObecna = 0;
		}

		ileZyc--;
		if(ileZyc <= -1) {
			StworzBonus(x, y - 50, NAPIS, 20000);
			koniecGry = true;
			aktywny = false;
		}
	}

}

void Tkrol::Aktualizuj(int xGracz, int yGracz) {
	Twrog::Aktualizuj(xGracz, yGracz);
	if(ileZyc >= 0 && stanAI == AI_SMIERC) {
		stanAI = AI_BEZCZYNNY;
		klatkaObecna = 0;
		animacjaZatrzymana = false;
		zyje = true;
	}
	if(odleglosc(x, y, xGracz, yGracz) < 1000)
		naEkranie = true;
	else
		naEkranie = false;

	if(stanAI == AI_BEZCZYNNY && klatkaObecna == 0 || niesmiertelny == false)
		niesmiertelny = false;
	else
		niesmiertelny = true;

	//std::cout<<stanAI << " " <<klatkaObecna << " " << niesmiertelny << "\n";
}

void Tkrol::Rysuj(int xGracz, int yGracz) {
	Twrog::Rysuj(xGracz, yGracz);

	int xTekstu = SZEROKOSC / 2;
	int yTekstu = 10;
	
	al_draw_textf(czcionka, bialy_tekst, xTekstu + 2, yTekstu, ALLEGRO_ALIGN_CENTRE, "King Hulog");
	al_draw_textf(czcionka, bialy_tekst, xTekstu - 2, yTekstu, ALLEGRO_ALIGN_CENTRE, "King Hulog");
	al_draw_textf(czcionka, bialy_tekst, xTekstu, yTekstu + 2, ALLEGRO_ALIGN_CENTRE, "King Hulog");
	al_draw_textf(czcionka, bialy_tekst, xTekstu, yTekstu - 2, ALLEGRO_ALIGN_CENTRE, "King Hulog");

	al_draw_textf(czcionka, czarny_tekst, xTekstu, yTekstu, ALLEGRO_ALIGN_CENTRE, "King Hulog");


	al_draw_scaled_bitmap(obraz, 1, 375, 1, 14, SZEROKOSC / 2 - 626 / 2 + 32, 60 + 16, 626 - 32 - 16, 17, 0);
	al_draw_scaled_bitmap(obraz, 0 ,375, 1, 14, SZEROKOSC / 2 - 626 / 2 + 32, 60 + 16, (626 - 32 - 16) * (ileZyc + 1) / 11, 17, 0);

	al_draw_bitmap_region(obraz, 0, 325, 626, 50, SZEROKOSC / 2 - 626 / 2, 60, NULL);

/*
	al_draw_filled_rectangle(SZEROKOSC / 2 - 200, 100, SZEROKOSC / 2 + 200, 130, al_map_rgb(200, 0, 0));
	al_draw_filled_rectangle(SZEROKOSC / 2 - 200, 100, SZEROKOSC / 2 - 200 + 400 * (ileZyc + 1) / 11, 130, al_map_rgb(0, 200, 0));*/
}