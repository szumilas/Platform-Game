#include "Tprzycisk.h"

Tprzycisk::Tprzycisk(float x, float y, float vX, float vY, int kierX, int kierY,
		ALLEGRO_FONT *czcionka, ALLEGRO_BITMAP *obraz, int numerPrzycisku, std::string tekst, bool obramowanie, int wyrownanie) {

	TobiektGry::Tworz(x, y, vX, vY, kierX, kierY);

	NadajID(PRZYCISK);

	Tprzycisk::numerPrzycisku = numerPrzycisku;

	klatkaOstatnia = 1;
	klatkaObecna = 0;
	klatkaLicznik = 0;
	klatkaOpoznienie = 1;

	naEkranie = false;
	animuj = false;

	if(numerPrzycisku == 0 || numerPrzycisku == 3)
		klatkaSzerokosc = 395;
	else
		klatkaSzerokosc = 275;

	if(numerPrzycisku == 3)
		klatkaWysokosc = 380;
	else
		klatkaWysokosc = 60;

	
	if(obraz != NULL)
		TobiektGry::obraz = obraz;

	Tprzycisk::czcionka = czcionka;
	Tprzycisk::obramowanie = obramowanie;
	Tprzycisk::wyrownanie = wyrownanie;
	Tprzycisk::tekst = tekst;
	
	bialy_tekst = al_map_rgb(250, 250, 250);
	czarny_tekst = al_map_rgb(0, 0, 0);
	zolty_tekst = al_map_rgb(180, 140, 30);
}

void Tprzycisk::Rysuj(int xGracz, int yGracz) {
	
	int fx = klatkaObecna * klatkaSzerokosc;
	int fy = numerPrzycisku * 60;

	al_draw_bitmap_region(obraz, fx, fy, klatkaSzerokosc, klatkaWysokosc, x - klatkaSzerokosc / 2, y - klatkaWysokosc / 2, 0);

	if(tekst == "#ABOUT") {
		al_draw_textf(czcionka, czarny_tekst, x+2, 320, wyrownanie, "(C) 2017 Piotr Szumilas");

		
		al_draw_textf(czcionka, czarny_tekst, x+2, 380, wyrownanie, "C++ platform game");
		al_draw_textf(czcionka, czarny_tekst, x+2, 420, wyrownanie, "made for fun");
		al_draw_textf(czcionka, czarny_tekst, x+2, 460, wyrownanie, "enjoy :)");
		al_draw_textf(czcionka, czarny_tekst, x+2, 540, wyrownanie, "Freeware License");
		al_draw_textf(czcionka, czarny_tekst, x+2, 580, wyrownanie, "Lord Szumi v.1.0");

	}
	else if(tekst != "#WYNIKI") {
		int yTekst = y - czcionka->height / 2;
		if(obramowanie) {
			al_draw_textf(czcionka, czarny_tekst, x+2, yTekst, wyrownanie, tekst.c_str());
			al_draw_textf(czcionka, czarny_tekst, x-2, yTekst, wyrownanie, tekst.c_str());
			al_draw_textf(czcionka, czarny_tekst, x, yTekst+2, wyrownanie, tekst.c_str());
			al_draw_textf(czcionka, czarny_tekst, x, yTekst-2, wyrownanie, tekst.c_str());
		}

		al_draw_textf(czcionka, (numerPrzycisku == 0) ? zolty_tekst : bialy_tekst, x, yTekst, wyrownanie, tekst.c_str());
	}
}

void Tprzycisk::Aktualizuj(int wybraneMenu, int wybranyPrzycisk) {
	if(animuj) {
		vX ++;
		x += vX;
		if(x >= 300) {
			x = 300;
			animuj = false;
		}
	}


	int przedNaEkranie = naEkranie;

	if(wybraneMenu == 0) { //Main Menu
		if(tekst == "Main Menu" || tekst == "New Game" || tekst == "High Scores" || tekst == "About" || tekst == "Options" || tekst == "Exit Game")
			naEkranie = true;
		else
			naEkranie = false;

		if(wybranyPrzycisk == 0 && tekst == "New Game" || 
			wybranyPrzycisk == 1 && tekst == "High Scores" || wybranyPrzycisk == 2 && tekst == "About" || 
			wybranyPrzycisk == 3 && tekst == "Options" || wybranyPrzycisk == 4 && tekst == "Exit Game")
			numerPrzycisku = 2;
		else if(numerPrzycisku != 3)
			numerPrzycisku = 1;
	} else if(wybraneMenu == 1) { //New Game
		if(tekst == " New Game " || tekst == "Play Game" || tekst == "Tutorial" || tekst == "Back")
			naEkranie = true;
		else
			naEkranie = false;

		if(wybranyPrzycisk == 0 && tekst == "Play Game" || wybranyPrzycisk == 1 && tekst == "Tutorial" || 
			wybranyPrzycisk == 2 && tekst == "Back")
			numerPrzycisku = 2;
		else if(numerPrzycisku != 3)
			numerPrzycisku = 1;
	} /*else if(wybraneMenu == 2) { //Load Game
		if(tekst == " Load Game " || tekst.find("Empty") != tekst.npos || tekst == " Back ")
			naEkranie = true;
		else
			naEkranie = false;

		if(wybranyPrzycisk == 0 && tekst == "Empty" || wybranyPrzycisk == 1 && tekst == " Empty " || 
			wybranyPrzycisk == 2 && tekst == "  Empty  " || wybranyPrzycisk == 3 && tekst == "   Empty   " || 
			wybranyPrzycisk == 4 && tekst == "    Empty    " || wybranyPrzycisk == 5 && tekst == " Back ")
			numerPrzycisku = 2;
		else if(numerPrzycisku != 3)
			numerPrzycisku = 1;
	}*/ else if(wybraneMenu == 2) { //High Scores
		if(tekst == " High Scores " || tekst == "  Back  " || tekst == "#WYNIKI")
			naEkranie = true;
		else
			naEkranie = false;

		if(wybranyPrzycisk == 0 && tekst == "  Back  ")
			numerPrzycisku = 2;
		else if(numerPrzycisku != 3)
			numerPrzycisku = 1;
	} else if(wybraneMenu == 3) { //About
		if(tekst == " About " || tekst == "     Back     " || tekst == "#ABOUT")
			naEkranie = true;
		else
			naEkranie = false;

		if(wybranyPrzycisk == 0 && tekst == "     Back     ")
			numerPrzycisku = 2;
		else if(numerPrzycisku != 3)
			numerPrzycisku = 1;
	} else if(wybraneMenu == 4) { //Options
		if(tekst == " Options " || tekst == "Fullscreen" || tekst == "Clear High Scores" || tekst == "Clear Saved Games" || tekst == "    Back    ")
			naEkranie = true;
		else
			naEkranie = false;

		if(wybranyPrzycisk == 0 && tekst == "Fullscreen" || wybranyPrzycisk == 1 && tekst == "Clear High Scores" || 
			wybranyPrzycisk == 2 && tekst == "    Back    ")
			numerPrzycisku = 2;
		else if(numerPrzycisku != 3)
			numerPrzycisku = 1;
	}

	
	if(tekst == "Main Menu" || tekst == " New Game " || tekst == " Load Game " || tekst == " High Scores " || tekst == " About " || tekst == " Options ")
		numerPrzycisku = 0;

	if(przedNaEkranie != naEkranie) {
		animuj = true;
		x = -y;
		vX = 30;
	}

}