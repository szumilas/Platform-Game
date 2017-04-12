#include "Tnapis.h"

/*Tnapis::Tnapis() {
	Tnapis(0, 0, 0, 0, 0, 0, NULL, 0);
}*/

Tnapis::Tnapis(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_FONT *czcionka, int numerKlatki, int typNapisu,
	int (*PobierzParametrySzumiego)(int), std::string tekst, bool obramowanie, int wyrownanie) {


	TobiektGry::Tworz(x, y, vX, vY, kierX, kierY);

	NadajID(NAPIS);

	PobierzParametry = PobierzParametrySzumiego;

	if(typNapisu == 0)
		napisNaEkranie = false;
	else
		napisNaEkranie = true;

	jakiNapis = typNapisu;

	mozeKolidowac = false;
	naEkranie = true;

	Tnapis::obramowanie = obramowanie;
	Tnapis::wyrownanie = wyrownanie;
	Tnapis::typNapisu = typNapisu;
	Tnapis::tekst = tekst;

	liczba = numerKlatki;

	Tnapis::czcionka = czcionka;
	
	bialy_tekst = al_map_rgb(250, 250, 250);
	czarny_tekst = al_map_rgb(0, 0, 0);

}


void Tnapis::Rysuj(int xGracz, int yGracz) {
	if(typNapisu != TEKST) {
		if(obramowanie) {
			al_draw_textf(czcionka, czarny_tekst, x+2, y, wyrownanie, "%i", liczba);
			al_draw_textf(czcionka, czarny_tekst, x-2, y, wyrownanie, "%i", liczba);
			al_draw_textf(czcionka, czarny_tekst, x, y+2, wyrownanie, "%i", liczba);
			al_draw_textf(czcionka, czarny_tekst, x, y-2, wyrownanie, "%i", liczba);
		}
		al_draw_textf(czcionka, bialy_tekst, x, y, wyrownanie, "%i", liczba);
	}
	else {
		if(obramowanie) {
			al_draw_textf(czcionka, czarny_tekst, x+2, y, wyrownanie, tekst.c_str());
			al_draw_textf(czcionka, czarny_tekst, x-2, y, wyrownanie, tekst.c_str());
			al_draw_textf(czcionka, czarny_tekst, x, y+2, wyrownanie, tekst.c_str());
			al_draw_textf(czcionka, czarny_tekst, x, y-2, wyrownanie, tekst.c_str());
		}
		al_draw_textf(czcionka, bialy_tekst, x, y, wyrownanie, tekst.c_str());
	}
}

void Tnapis::Aktualizuj(int xGracz, int yGracz) {
	//wyrownanie = DO_CENTRUM;

//	PobierzParametry(jakiNapis);
	if(x > SZEROKOSC)
		x = x - xGracz + SZEROKOSC / 2;
	if(y > WYSOKOSC)
		y = y - yGracz + WYSOKOSC / 2;

	if(typNapisu != TEKST) {
		if(napisNaEkranie == true) {
			liczba = PobierzParametry(jakiNapis);
		}
		else {

			if(x < 100 || y < 100)
				aktywny = false;
		
			vY --;
			y += vY;
		}
	} else if(typNapisu == TEKST) {

	}
}