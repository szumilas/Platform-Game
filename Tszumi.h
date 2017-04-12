#pragma once

#include "TobiektGry.h"
#include "Twrog.h"
#include "Tbonus.h"
#include "Tdrzwi.h"
#include "Tkrol.h"

extern bool wypiszProstokatKolizji;
extern const int SZEROKOSC;
extern const int WYSOKOSC;

class Tszumi : public TobiektGry {

private:
	void (*GrajDzwiek)(int);

	int sprite[12][4];			//tablica z danymi spritea	
	int stan;					//jaki stan ma gracz: BEZCZYNNY, BIEG, SKOK...
	bool animacjaZatrzymywalna;	//czy gracz moze sterowac z klawiatury postacia

	int poprzednieY;			//y przed obliczona pozycja w tej klatce
	int poprzednieX;			//x przed obliczona pozycja w tej klatce
	int poprzednieVY;			//vY przed obliczona pozycja w tej klatce
	int poprzedniKierX;			//vX przed obliczona pozycja w tej klatce

	int aktualneY;				//y po obliczonej pozycji w tej klatce
	int aktualneX;				//x  po obliczonej pozycji w tej klatce
	int aktualneVY;				//vY  po obliczonej pozycji w tej klatce

	//Prostokat ataku
	bool atakuje;
	int atakXL;
	int atakXP;
	int atakYG;
	int atakYD;

	int g;						//grawitacja g = 60 px/s^2

	int ileBezczynny;
	bool ranny;
	int ileNiesmiertelny;
	
	void WyrownajDoY(int y, bool pozwolSkoczyc = false, bool ostatecznie = true);
	void WyrownajDoX(TobiektGry *zKim, bool ostatecznie = true);

	void KolizjaZBlokiem(TobiektGry *zKim);

public:
	enum ktoryStan{ BEZCZYNNY, BIEG, RANNY, ATAK, SMIERC, SLIZG, ATAK_DOLEM, RANNY_DOLEM, DOL, SKOK, BEZCZYNNY2, SUPER_ATAK};
	enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE, ENTER, Z, X, W, S, A, D};
	enum {DZWIEK_MACHANIE_MIECZEM = 13, DZWIEK_SKOK, DZWIEK_SLIZG, DZWIEK_MIECZ_KOLIZJA, DZWIEK_WZIECIE_JEDZENIA, DZWIEK_MONETA,
	DZWIEK_SERDUSZKO, DZWIEK_DODANIE_ZYCIA, DZWIEK_UTRATA_SERDUSZKA, DZWIEK_SMIERC, DZWIEK_SMIERC_BESTII, DZWIEK_SMIERC_WAZONU,
	DZWIEK_SMIERC_SKRZYNII, DZWIEK_DRZWI, DZWIEK_KROL_RANNY = 30, DZWIEK_GOBLIN_RANNY, DZWIEK_OGR_RANNY, DZWIEK_KAMIENNY_RANNY,
	DZWIEK_RYCERZ_RANNY};

	Tszumi(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, void (*GrajDzwiek)(int));
	void Rysuj(int xGracz, int yGracz);
	void Usun();
	void Aktualizuj(int xGracz, int yGracz);
	void ZmienAnimacje(int animacja = 0);
	void ZmienStan(int stan = 0);
	void ZmienKierunek(int kierunek);
	void KolidujeZ(int ID, TobiektGry *zKim = NULL);
	void PobierzRuch(bool *keys);
	bool CzyZaatakowal(Twrog *innyObiekt);

	int startoweX;
	int startoweY;

	int kierAnimacji;
	bool maPodloge;
	bool naWindzie;
	bool naRampie;
	int naPlatformie;
	bool mozeSkoczyc;

	int liczbaPunktow;
	int liczbaZyc;
	int liczbaSerduszek;
	int liczbaSerduszekMax;
	int liczbaMonet;

	int przerwa;

	int szumiStanGry;

	//Zwracanie zmiennych prywatnych
	
	int PobierzStan() {return stan;}
	int PobierzVX() {return vX;}
	int PobierzVY() {return vY;}
	bool PobierzRodzajAnimacji() {return animacjaZatrzymywalna;}

	void WylaczGrawitacje(){g = 0;}
	void WlaczGrawitacje(){g = 1;}

	
	void ResetujPozycje();
	void ResetujDane();
	
};