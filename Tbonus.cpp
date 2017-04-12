#include "Tbonus.h"

Tbonus::Tbonus() {
	Tbonus(0, 0, 0, 0, 0, 0, NULL, 0);
}

Tbonus::Tbonus(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int jakiBonus) {
	TobiektGry::Tworz(x, y, vX, vY, kierX, kierY);

	NadajID(BONUS);

	TobiektGry::vX = 0;

	if(jakiBonus >= 100) {
		jakiBonus -= 100;
		zdobyty = true;
		naEkranie = true;
		skalowany = true;
		mozeKolidowac = false;
	}
	else {
		zdobyty = false;
		skalowany = false;
		mozeKolidowac = true;
	}


	Tbonus::jakiBonus = jakiBonus;

	
		klatkaObecna = 0;
		klatkaLicznik = 0;

	if(jakiBonus == PIENIAZEK) {
		poczatkowyPixelY = 0;


		klatkaOstatnia = 6;
		klatkaOpoznienie = 6;
		klatkaSzerokosc = 85;
		klatkaWysokosc = 85;
		
		kolizjaXL = 20;
		kolizjaXP = 20;
		kolizjaYG = 20;
		kolizjaYD = 20;
	} else if(jakiBonus == SERDUSZKO) {
		poczatkowyPixelY = 85;

		klatkaOstatnia = 1;
		klatkaOpoznienie = 1;
		klatkaSzerokosc = 50;
		klatkaWysokosc = 50;
		
		kolizjaXL = 15;
		kolizjaXP = 15;
		kolizjaYG = 15;
		kolizjaYD = 15;


	} else if(jakiBonus == MIESO) {
		poczatkowyPixelY = 135;

		klatkaOstatnia = 1;
		klatkaOpoznienie = 6;
		klatkaSzerokosc = 65;
		klatkaWysokosc = 65;
		
		kolizjaXL = 25;
		kolizjaXP = 25;
		kolizjaYG = 20;
		kolizjaYD = 30;


	} else if(jakiBonus == ZNIKANIE) {
		poczatkowyPixelY = 200;

		klatkaOstatnia = 4;
		klatkaOpoznienie = 5;
		klatkaSzerokosc = 45;
		klatkaWysokosc = 45;
		
		kolizjaXL = 20;
		kolizjaXP = 20;
		kolizjaYG = 20;
		kolizjaYD = 20;


	} else if(jakiBonus >= TRUSKAWKA) {
		poczatkowyPixelY = 245 + 80 * (jakiBonus - TRUSKAWKA);

		klatkaOstatnia = 1;
		klatkaOpoznienie = 5;
		klatkaSzerokosc = 80;
		klatkaWysokosc = 80;
		
		kolizjaXL = 22;
		kolizjaXP = 22;
		kolizjaYG = 22;
		kolizjaYD = 22;


	}else {
		kolizjaXL = 10;
		kolizjaXP = 10;
		kolizjaYG = 10;
		kolizjaYD = 10;
	}

	
	if(obraz != NULL)
		TobiektGry::obraz = obraz;
}

void Tbonus::Aktualizuj(int xGracz, int yGracz) {
	if(x < SZEROKOSC) {
		x += xGracz - SZEROKOSC / 2;
		y += yGracz - WYSOKOSC / 2;
	}

	if(zdobyty) {
		skalowany = true;

		if(jakiBonus == PIENIAZEK) {
			if(y < yGracz + WYSOKOSC / 2 && naEkranie) {
				vY ++;
				y += vY * 2 / 3;
			}
			else
				aktywny = false;
		}
		else if(jakiBonus == SERDUSZKO) {
			if(x - xGracz + SZEROKOSC / 2 > SZEROKOSC - 100 || y - yGracz + WYSOKOSC / 2 < 100)
				aktywny = false;
			
			
			vY --;
			y += vY;

			/*
			vX += 1;

			if(vX > 40)
				vX = 40;

			x += vX / 4;
			y -= 3;*/
		}
		else if(jakiBonus == MIESO || jakiBonus >= TRUSKAWKA) {
			jakiBonus = ZNIKANIE;
			poczatkowyPixelY = 200;

			klatkaOstatnia = 4;
			klatkaObecna = 0;
			klatkaLicznik = 0;
			klatkaOpoznienie = 5;
			klatkaSzerokosc = 45;
			klatkaWysokosc = 45;

		}
		
		else if(jakiBonus == ZNIKANIE) {
			
			skalowany = false;
			//aktywny = false;
		}
	}
	else {
		if(odleglosc(x, y, xGracz, yGracz) < 800)
			naEkranie = true;
		else
			naEkranie = false;
	}

	if(++klatkaLicznik >= klatkaOpoznienie) {
		klatkaObecna ++;
		if(klatkaObecna >= klatkaOstatnia) {
			if(jakiBonus == ZNIKANIE)
				aktywny = false;
			klatkaObecna = 0;

		}

		klatkaLicznik = 0;
	}
}

void Tbonus::Rysuj(int xGracz, int yGracz) {
	int fx = klatkaObecna * klatkaSzerokosc;
	int fy = poczatkowyPixelY;

	//if(obraz!=NULL)
	if(skalowany)
		al_draw_scaled_bitmap(obraz, fx, fy, klatkaSzerokosc, klatkaWysokosc, SZEROKOSC / 2 + x - klatkaSzerokosc / 4 - xGracz, WYSOKOSC / 2 + y - klatkaWysokosc / 4 - yGracz,
		klatkaSzerokosc / 2,  klatkaWysokosc / 2, 0);
	else
		al_draw_bitmap_region(obraz, fx, fy, klatkaSzerokosc, klatkaWysokosc,
		SZEROKOSC / 2 + x - klatkaSzerokosc / 2 - xGracz,  WYSOKOSC / 2 + y - klatkaWysokosc / 2 - yGracz, 0);

	if(wypiszProstokatKolizji) {
		ALLEGRO_COLOR jaki = rozowy;
		if(CzyMozeKolidowac() == true)
			jaki = zielony;
		al_draw_filled_rectangle(SZEROKOSC / 2 + x - kolizjaXL - xGracz, WYSOKOSC / 2 + y - kolizjaYG - yGracz, SZEROKOSC / 2 + x + kolizjaXP - xGracz, WYSOKOSC / 2 + y + kolizjaYD - yGracz, jaki);
		al_draw_filled_circle(SZEROKOSC / 2 + x - xGracz, WYSOKOSC / 2 + y - yGracz, 5, czarny);
		

	}

}