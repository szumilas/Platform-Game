#include "Ttabliczka.h"

Ttabliczka::Ttabliczka() {
	Ttabliczka(0, 0, 0, 0, 0, 0, NULL, 0, 0, NULL);

}

Ttabliczka::Ttabliczka(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, int id, ALLEGRO_FONT *czcionka) {
	Tworz(x, y, vX, vY, kierX, kierY, obraz, numerKlatki, id, czcionka);
	
}

void Ttabliczka::Tworz(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki, int id, ALLEGRO_FONT *czcionka) {
	TobiektGry::Tworz(x, y, vX, vY, kierX, kierY);

	NadajID(TABLICZKA);

	idTekstu = id;

	mozeKolidowac = true;

	klatkaOstatnia = 1;
	klatkaObecna = numerKlatki;
	klatkaLicznik = 0;
	klatkaOpoznienie = 1;

	klatkaSzerokosc = 90;

	klatkaWysokosc = 85;

	if(numerKlatki == 0) {
		kolizjaXL = 50;
		kolizjaXP = 50;
	}
	else {
		kolizjaXL = 40;
		kolizjaXP = 10;
	}
	kolizjaYG = 42;
	kolizjaYD = 43;

	Ttabliczka::czcionka = czcionka;
	
	bialy_tekst = al_map_rgb(250, 250, 250);
	czarny_tekst = al_map_rgb(0, 0, 0);

	
	if(obraz != NULL)
		TobiektGry::obraz = obraz;
}

void Ttabliczka::Aktualizuj(int xGracz, int yGracz) {
	if(odleglosc(x, y, xGracz, yGracz) < 50) {
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


}

void Ttabliczka::Rysuj(int xGracz, int yGracz) {
	TobiektGry::Rysuj(xGracz, yGracz);

	std::string napisNaTabliczce;
	if(idTekstu == 0)
		napisNaTabliczce = "Press LEFT or RIGHT to move";
	else if(idTekstu == 1)
		napisNaTabliczce = "Eat meat, because it's fresh and healthy";
	else if(idTekstu == 2)
		napisNaTabliczce = "Press UP to jump";
	else if(idTekstu == 3)
		napisNaTabliczce = "Watch out for spikes";
	else if(idTekstu == 4)
		napisNaTabliczce = "Run and press DOWN to slide";
	else if(idTekstu == 5)
		napisNaTabliczce = "Press SPACE to atack the enemy";
	else if(idTekstu == 6)
		napisNaTabliczce = "Go to the gate to finish level";
	else if(idTekstu == 7)
		napisNaTabliczce = "King Hulog - WANTED Dead or Alive - REWARD: 20 000";
	else if(idTekstu == 8)
		napisNaTabliczce = "Collect money. 100 coins give you extra life";
	else if(idTekstu == 9)
		napisNaTabliczce = "Use platform to move up";
	else if(idTekstu == 10)
		napisNaTabliczce = "Watch out for saw";
	else if(idTekstu == 11)
		napisNaTabliczce = "Wait for the platform";
	else if(idTekstu == 12)
		napisNaTabliczce = "Castle well - very dangerous";
	else if(idTekstu == 13)
		napisNaTabliczce = "Castle moat - a lot of spikes...";
	else if(idTekstu == 14)
		napisNaTabliczce = "Good luck...";
	else if(idTekstu == 15)
		napisNaTabliczce = "Upwards - Hulog's castle, Downwards - only spikes";
	else if(idTekstu == 16)
		napisNaTabliczce = "Hulog's castle";
	else if(idTekstu == 17)
		napisNaTabliczce = "Hulog's tower - entrance from the dungeon";
	else if(idTekstu == 18)
		napisNaTabliczce = "Castle dungeon";
	else if(idTekstu == 19)
		napisNaTabliczce = "Hulog's chamber";

	if(sprawdzajKolizje) {
		al_draw_textf(czcionka, czarny_tekst, SZEROKOSC / 2 - 2, 100, ALLEGRO_ALIGN_CENTRE, napisNaTabliczce.c_str());
		al_draw_textf(czcionka, czarny_tekst, SZEROKOSC / 2 + 2, 100, ALLEGRO_ALIGN_CENTRE, napisNaTabliczce.c_str());
		al_draw_textf(czcionka, czarny_tekst, SZEROKOSC / 2, 100 - 2, ALLEGRO_ALIGN_CENTRE, napisNaTabliczce.c_str());
		al_draw_textf(czcionka, czarny_tekst, SZEROKOSC / 2, 100 + 2, ALLEGRO_ALIGN_CENTRE, napisNaTabliczce.c_str());

		al_draw_textf(czcionka, bialy_tekst, SZEROKOSC / 2, 100, ALLEGRO_ALIGN_CENTRE, napisNaTabliczce.c_str());
	}


}