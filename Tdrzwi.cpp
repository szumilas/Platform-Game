#include "Tdrzwi.h"

Tdrzwi::Tdrzwi() {
	Tdrzwi(0, 0, 0, 0, 0, 0, NULL, 0);

}

Tdrzwi::Tdrzwi(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerDrzwi) {
	Tworz(x, y, vX, vY, kierX, kierY, obraz, numerDrzwi);
	
}

void Tdrzwi::Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerDrzwi) {
	TobiektGry::Tworz(x, y, vX, vY, kierX, kierY);

	NadajID(DRZWI);

	mozeKolidowac = true;

	otwarte = false;

	ktoreDrzwi = numerDrzwi;

	klatkaOstatnia = 9;
	klatkaObecna = 0;
	klatkaLicznik = 0;
	klatkaOpoznienie = 5;
	klatkaSzerokosc = 100;
	klatkaWysokosc = 192;


	kolizjaXL = 300;
	kolizjaXP = 300;
	kolizjaYG = 212;
	kolizjaYD = 43;
	
	kolizjaXLD = 25;
	kolizjaXPD = 25;
	kolizjaYGD = 42;
	kolizjaYDD = 43;

	
	if(obraz != NULL)
		TobiektGry::obraz = obraz;
}

void Tdrzwi::Aktualizuj(int xGracz, int yGracz) {
	if(odleglosc(x, y, xGracz, yGracz) < 400) {
		naEkranie = true;
		sprawdzajKolizje = true;
	}
	else {
		sprawdzajKolizje = false;
		if(odleglosc(x, y, xGracz, yGracz) < 800)
			naEkranie = true;
		else
			naEkranie = false;
	}

	if(otwarte) {
		if(++klatkaLicznik >= klatkaOpoznienie) {
			klatkaObecna ++;
			if(klatkaObecna >= klatkaOstatnia)
				klatkaObecna = klatkaOstatnia - 1;

			klatkaLicznik = 0;
		}
	}


}

void Tdrzwi::Rysuj(int xGracz, int yGracz) {
	int fx = klatkaObecna * klatkaSzerokosc;
	int fy = ktoreDrzwi * 160;

	//if(obraz!=NULL)
	al_draw_bitmap_region(obraz, fx, fy, klatkaSzerokosc, klatkaWysokosc,
		SZEROKOSC / 2 + x - klatkaSzerokosc / 2 - xGracz,  WYSOKOSC / 2 + y - klatkaWysokosc / 2 - yGracz - 20, 0);

	if(wypiszProstokatKolizji) {
		ALLEGRO_COLOR jaki = rozowy;
		if(CzyMozeKolidowac() == true)
			jaki = zielony;
		al_draw_filled_rectangle(SZEROKOSC / 2 + x - kolizjaXL - xGracz, WYSOKOSC / 2 + y - kolizjaYG - yGracz, SZEROKOSC / 2 + x + kolizjaXP - xGracz, WYSOKOSC / 2 + y + kolizjaYD - yGracz, jaki);
		al_draw_filled_circle(SZEROKOSC / 2 + x - xGracz, WYSOKOSC / 2 + y - yGracz, 5, czarny);

		al_draw_filled_rectangle(SZEROKOSC / 2 + x - kolizjaXLD - xGracz, WYSOKOSC / 2 + y - kolizjaYGD - yGracz, SZEROKOSC / 2 + x + kolizjaXPD - xGracz, WYSOKOSC / 2 + y + kolizjaYDD - yGracz, czarny);
		

	}

}

bool Tdrzwi::CzyWDrzwiach(TobiektGry *wsk) {
	if(wsk->PobierzX() - wsk->PobierzKolizjaXL() >= x - kolizjaXLD &&
		wsk->PobierzX() + wsk->PobierzKolizjaXP() <= x + kolizjaXLD &&
		wsk->PobierzY() - wsk->PobierzKolizjaYG() >= y - kolizjaYGD &&
		wsk->PobierzY() + wsk->PobierzKolizjaYD() >= y + kolizjaYDD)
		return true;
	else
		return false;
}