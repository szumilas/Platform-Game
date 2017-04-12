#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include <allegro5\allegro_font.h>


class Twyniki {

private:
	ALLEGRO_FONT *czcionkaDuza;
	ALLEGRO_FONT *czcionkaMala;

	ALLEGRO_COLOR bialy_tekst;
	ALLEGRO_COLOR czarny_tekst;

	std::fstream plik;
	std::string daty[5];
	int wartosci[5];
	
public:
	Twyniki(ALLEGRO_FONT *czcionkaDuza, ALLEGRO_FONT *czcionkaMala);

	void WczytajWyniki();
	void WypiszWyniki();
	void DodajWynik(int ile, std::string jakaData);
	void DodajWynik(int ile);
	void Wypisz(int xP);
	void ZapiszWyniki();
	void CzyscWyniki();

};