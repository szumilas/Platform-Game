#pragma once

#include <iostream>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>
#include <cmath>

extern bool wypiszProstokatKolizji;
extern const int SZEROKOSC;
extern const int WYSOKOSC;



class TobiektGry {

private:
	int ID;

protected:
	float x;
	float y;
	float vX;
	float vY;

	ALLEGRO_COLOR rozowy;
	ALLEGRO_COLOR zielony;
	ALLEGRO_COLOR niebieski;
	ALLEGRO_COLOR czarny;
	
	int klatkaOstatnia;
	int klatkaOpoznienie;
	int klatkaSzerokosc;
	int klatkaWysokosc;

	//Prostokat kolizji
	int kolizjaXL;
	int kolizjaXP;
	int kolizjaYG;
	int kolizjaYD;

	bool wyrownalDoX;
	bool wyrownalDoY;

	bool mozeKolidowac;
	bool sprawdzajKolizje;
	bool zyje;

	ALLEGRO_BITMAP *obraz;

public:
	enum Rodzaj {GRACZ, BLOK, RAMPA, WROG, WINDA, PLATFORMA, TLO_GRY, PILA, ZAMEK_TLO, KOLCE, PUDLO, BONUS, GRAFIKA_GRY, BECZKA, DRZWI, EKRAN, PRZYCISK,
		MENU_WYBORU, TABLICZKA, KROL, KAMIENNY_POTWOR, OGR, GOBLIN, NAPIS = 100};

	TobiektGry();

	bool aktywny;
	void virtual Usun();
	void Tworz(float x, float y, float vX, float vY, int kierX, int kierY);
	void virtual Aktualizuj(int xGracz, int yGracz);
	void virtual Rysuj(int xGracz, int yGracz);
	void virtual KolidujeZ(int ID, TobiektGry *zKim = NULL);

	int klatkaObecna;
	int klatkaLicznik;
	int idPudla;
	bool naEkranie;
	int kierX;
	int kierY;

	void NadajID(int ID){TobiektGry::ID = ID;}

	int PobierzID(){return ID;}
	int PobierzKolizjaXL(){return kolizjaXL;};
	int PobierzKolizjaXP(){return kolizjaXP;};
	int PobierzKolizjaYG(){return kolizjaYG;};
	int PobierzKolizjaYD(){return kolizjaYD;};

	int PobierzX(){return x;}
	int PobierzY(){return y;}
	int PobierzVY(){return vY;}

	bool CzyMozeKolidowac(){return naEkranie &&sprawdzajKolizje && mozeKolidowac;}
	bool CzyKolizja(TobiektGry *innyObiekt);
	virtual int ParametrKolizji();

	int modul(int a){ if(a < 0) return -a; return a;}
	int odleglosc(int x1, int y1, int x2, int y2){return sqrt((double)(pow((float)x1 - x2, 2) + pow((float)y1 - y2, 2)));}

	void Przesun(int dx, int dy) {x += dx; y += dy;}

};