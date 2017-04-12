#include "Tszumi.h"


Tszumi::Tszumi(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, void (*GrajDzwiek)(int)) {
	TobiektGry::Tworz(x, y, vX, vY, kierX, kierY);

	NadajID(GRACZ);

	Tszumi::GrajDzwiek = GrajDzwiek;


	startoweX = 85730;
	startoweY = 85950;

	if(x == 0 && y == 0) {
		TobiektGry::x = startoweX;
		TobiektGry::y = startoweY;
	}

	g = 1;

	przerwa = 0;

	szumiStanGry = 0; // 1 - koniec etapu, 2 - koniec gry, 3 - resetuj poziom, 4 - wygrana

	liczbaPunktow = 0;
	liczbaZyc = 3;
	liczbaSerduszek = 3;
	liczbaSerduszekMax = 3;
	liczbaMonet = 0;

	mozeKolidowac = true;
	wyrownalDoY = false;

	naEkranie = true;

	animacjaZatrzymywalna = true;
	kierAnimacji = 1;
	stan = 0;
	ileBezczynny = 0;
	ranny = false;
	ileNiesmiertelny = 0;
	poprzedniKierX = 0;

	naWindzie = false;
	naPlatformie = 0;

	kolizjaXL = 10;
	kolizjaXP = 13;
	kolizjaYG = 30;
	kolizjaYD = 38;
	
	sprite[0][0] = 100;		sprite[0][1] = 100;		sprite[0][2] = 9;	sprite[0][3] = 0;		//Bezczynny
	sprite[1][0] = 100;		sprite[1][1] = 100;		sprite[1][2] = 10;	sprite[1][3] = 100;		//Bieg
	sprite[2][0] = 125;		sprite[2][1] = 100;		sprite[2][2] = 7;	sprite[2][3] = 200;		//Ranny
	sprite[3][0] = 150;		sprite[3][1] = 100;		sprite[3][2] = 8;	sprite[3][3] = 300;		//Atak
	sprite[4][0] = 160;		sprite[4][1] = 100;		sprite[4][2] = 6;	sprite[4][3] = 400;		//Smierc
	sprite[5][0] = 100;		sprite[5][1] = 100;		sprite[5][2] = 12;	sprite[5][3] = 500;		//Slizg
	sprite[6][0] = 150;		sprite[6][1] = 100;		sprite[6][2] = 7;	sprite[6][3] = 600;		//Atak dolem
	sprite[7][0] = 100;		sprite[7][1] = 100;		sprite[7][2] = 9;	sprite[7][3] = 700;		//Ranny dolem
	sprite[8][0] = 100;		sprite[8][1] = 100;		sprite[8][2] = 9;	sprite[8][3] = 800;		//Dol
	sprite[9][0] = 100;		sprite[9][1] = 100;		sprite[9][2] = 13;	sprite[9][3] = 900;		//Skok
	sprite[10][0] = 100;	sprite[10][1] = 100;	sprite[10][2] = 9;	sprite[10][3] = 1000;	//Bezczynny 2
	sprite[11][0] = 150;	sprite[11][1] = 150;	sprite[11][2] = 9;	sprite[11][3] = 1100;	//Super atak

	atakuje = false;

	atakXL = 10;
	atakXP = 10;
	atakYG = 10;
	atakYD = 10;

	if(obraz != NULL)
		TobiektGry::obraz = obraz;
}

void Tszumi::Rysuj(int xGracz, int yGracz) {
	int fx = klatkaObecna * sprite[stan][0];
	int fy = sprite[stan][3];
	
	if(!ranny || ileNiesmiertelny % 5 != 0 || ileNiesmiertelny < 30)
	al_draw_bitmap_region(obraz, fx, fy, sprite[stan][0], sprite[stan][1],
		SZEROKOSC / 2 - sprite[stan][0] / 2,  WYSOKOSC / 2 - sprite[stan][1] / 2, (kierAnimacji == -1) ? ALLEGRO_FLIP_HORIZONTAL : 0);

	if(wypiszProstokatKolizji) {
		al_draw_filled_rectangle(SZEROKOSC / 2 - kolizjaXL, WYSOKOSC / 2 - kolizjaYG, SZEROKOSC / 2 + kolizjaXP, WYSOKOSC / 2 + kolizjaYD, zielony);
		al_draw_filled_circle(SZEROKOSC / 2, WYSOKOSC / 2, 5, czarny);

		if(atakuje)
			al_draw_filled_rectangle(SZEROKOSC / 2 - atakXL, WYSOKOSC / 2 - atakYG, SZEROKOSC / 2 + atakXP, WYSOKOSC / 2 + atakYD, rozowy);
	}



}

void Tszumi::Usun() {
	
}

void Tszumi::Aktualizuj(int xGracz, int yGracz) {


	//liczbaSerduszek = 3;











	if(stan == SMIERC && klatkaObecna + 1 == sprite[SMIERC][2]) {
		przerwa++;
		vY += g;

		if(vY > 20)
			vY = 20;


		x += vX * kierX + naPlatformie;
		y += vY * kierY;
	}

	if(liczbaMonet >= 100) {
		liczbaMonet -= 100;
		liczbaZyc ++;
		GrajDzwiek(DZWIEK_DODANIE_ZYCIA);
	}

	if(przerwa >= 100) {
		liczbaSerduszek = liczbaSerduszekMax;
		liczbaZyc--;
		if(liczbaZyc <= 0) {
			szumiStanGry = 2;
			return;
		}
		przerwa = 0;/*
		x = 85730;
		y = 85950;
		stan = BEZCZYNNY;
		kierX = 0;
		kierAnimacji = 1;*/
		szumiStanGry = 3;
	}
		
	if(przerwa == 0) {

		poprzednieX = x;
		poprzednieY = y;
		poprzednieVY = vY;
		vY += g;

		if(vY > 20)
			vY = 20;

		x += vX * kierX + naPlatformie;
		y += vY * kierY;

		aktualneX = x;
		aktualneY = y;
		aktualneVY = vY;



		if(++klatkaLicznik >= klatkaOpoznienie) {
			klatkaObecna ++;
			if(klatkaObecna >= sprite[stan][2]) {
				animacjaZatrzymywalna = true;
				klatkaObecna = 0;
			}

			klatkaLicznik = 0;
		}

		wyrownalDoY = false;
		wyrownalDoX = false;

		if(poprzednieVY == 0 && maPodloge)
			mozeSkoczyc = true;
		else
			mozeSkoczyc = false;
		maPodloge = false;

	

		if(ranny)
			ileNiesmiertelny++;
		if(ileNiesmiertelny >= 100) {
			ranny = false;
			ileNiesmiertelny = 0;
		}

		if(naWindzie && vY != 1)
			naWindzie = false;

		naPlatformie = 0;

		if(vY > 5)
			naRampie = false;


		ZmienStan(-1);
	}
}

void Tszumi::ZmienStan(int stan) {
	if(stan == ATAK || stan == ATAK_DOLEM || stan == SUPER_ATAK)
		GrajDzwiek(DZWIEK_MACHANIE_MIECZEM);
	else if(stan == SKOK)
		GrajDzwiek(DZWIEK_SKOK);
	else if(stan == SLIZG)
		GrajDzwiek(DZWIEK_SLIZG);

	if(stan >= BEZCZYNNY) {
		if(stan == RANNY || stan == RANNY_DOLEM) {
			kierX = 0;
			ranny = true;
		}
		else if(animacjaZatrzymywalna == true) {
			if(ileBezczynny >= 100 && stan == BEZCZYNNY)
				stan = BEZCZYNNY2;

			if(stan == SKOK && mozeSkoczyc) {
					vY = -22;
					animacjaZatrzymywalna = false;
					mozeSkoczyc = false;
			}
		}
	

		if(stan == BEZCZYNNY || stan == BIEG || stan == DOL || stan == BEZCZYNNY2)
				animacjaZatrzymywalna = true;
		else
			animacjaZatrzymywalna = false;

		if(stan == BEZCZYNNY && stan == RANNY || stan == ATAK || stan == SMIERC || stan == ATAK_DOLEM
			|| stan == RANNY_DOLEM || stan == DOL || stan == BEZCZYNNY2 || stan == SUPER_ATAK)
			kierX = 0;

		ZmienAnimacje(stan);
		Tszumi::stan = stan;

	
		if(stan == DOL || stan == ATAK_DOLEM || stan == RANNY_DOLEM) {
			kolizjaXL = (kierAnimacji == -1) ? 13 : 10;	kolizjaXP = (kierAnimacji == 1) ? 13 : 10;	kolizjaYG = 20;	kolizjaYD = 38; }
		else if(stan == SLIZG) {
			kolizjaXL = (kierAnimacji == -1) ? 35 : 10;	kolizjaXP = (kierAnimacji == 1) ? 35 : 10;	kolizjaYG = 5;	kolizjaYD = 38; }
		else {
			kolizjaXL = (kierAnimacji == -1) ? 13 : 10;	kolizjaXP = (kierAnimacji == 1) ? 13 : 10;	kolizjaYG = 30;	kolizjaYD = 38; }

	}

	if(Tszumi::stan == ATAK || Tszumi::stan == ATAK_DOLEM || Tszumi::stan == SUPER_ATAK) {
		if(klatkaObecna >= 3) {
			if(Tszumi::stan == ATAK) {
				atakXL = (kierAnimacji == -1) ? 65 : 0;	atakXP = (kierAnimacji == 1) ? 65 : 0;	atakYG = 20;	atakYD = 38; }
			else if (Tszumi::stan == SUPER_ATAK) {
				atakXL = (kierAnimacji == -1) ? 60 : 0;	atakXP = (kierAnimacji == 1) ? 60 : 0;	atakYG = 38;	atakYD = 38; }
			else {
				atakXL = (kierAnimacji == -1) ? 60 : 0;	atakXP = (kierAnimacji == 1) ? 60 : 0;	atakYG = 20;	atakYD = 38; }
		}
		else {
			atakXL = -1;	atakXP = -1;	atakYG = -1;	atakYD = -1;}
		atakuje = true;
	}
	else
		atakuje = false;
}

void Tszumi::ZmienAnimacje(int animacja) {
	if(stan == 0 && animacja == 0)
		ileBezczynny ++;
	else
		ileBezczynny = 0;

	int jakaAnimacja = stan;
	stan = animacja;

	if(jakaAnimacja != animacja) {
		klatkaObecna = 0;
	}
}

void Tszumi::ZmienKierunek(int kierunek) {
	poprzedniKierX = kierX;
	if(kierunek == 1) {
		kierX = 1;
		kierAnimacji = 1;
	}
	else if(kierunek == -1) {
		kierX = -1;
		kierAnimacji = -1;
	}
	else
		kierX = 0;

}

void Tszumi::KolidujeZ(int ID, TobiektGry *zKim) {

	if(ID == BLOK) {
		KolizjaZBlokiem(zKim);
	}
	else if (ID == RAMPA) {
		if(poprzednieX <= zKim->PobierzX() + zKim->PobierzKolizjaXP() && poprzednieX >= zKim->PobierzX() - zKim->PobierzKolizjaXL()){
			int ynowe = zKim->PobierzY() - (zKim->PobierzKolizjaXP() - (poprzednieX - zKim->PobierzX() )) / (zKim->ParametrKolizji() / 100) - kolizjaYD + zKim->ParametrKolizji() % 100;
			if(y >= ynowe) {
				WyrownajDoY(ynowe, true);
				naRampie = true;
			}
		}
	}
	else if(ID == WROG || ID == PILA || ID == KOLCE || ID == KROL) {
		if(ranny == false) {
			if(stan == DOL || stan == RANNY_DOLEM || stan == ATAK_DOLEM)
				ZmienStan(RANNY_DOLEM);
			else
				ZmienStan(RANNY);
			liczbaSerduszek--;
			if(liczbaSerduszek == 0) {
				stan = SMIERC;
				GrajDzwiek(DZWIEK_SMIERC);
			}
			else
				GrajDzwiek(DZWIEK_UTRATA_SERDUSZKA);

		}

	}
	else if(ID == WINDA) {
		if(zKim->CzyMozeKolidowac()) {
			KolizjaZBlokiem(zKim);
			naWindzie = true;
		}
	}
	else if(ID == PLATFORMA) {
		if(zKim->CzyMozeKolidowac()) {
			KolizjaZBlokiem(zKim);
			//naWindzie = true;
		}
		if(zKim->PobierzY() - zKim->PobierzKolizjaYG() > aktualneY)
			naPlatformie = zKim->ParametrKolizji();
	}
	else if(ID == BONUS) {
		Tbonus rodzaj;
		
		if(!dynamic_cast<Tbonus*> (zKim)->zdobyty) {
			if(dynamic_cast<Tbonus*> (zKim)->jakiBonus == rodzaj.SERDUSZKO) {
				GrajDzwiek(DZWIEK_SERDUSZKO);
				liczbaSerduszek = liczbaSerduszekMax;
			}
			else if(dynamic_cast<Tbonus*> (zKim)->jakiBonus == rodzaj.PIENIAZEK)
				GrajDzwiek(DZWIEK_MONETA);
			else
				GrajDzwiek(DZWIEK_WZIECIE_JEDZENIA);
		}
		dynamic_cast<Tbonus*> (zKim)->zdobyty = true;

	}
	else if(ID == DRZWI) {
		Tbonus rodzaj;
		if(!dynamic_cast<Tdrzwi*> (zKim)->otwarte)
			GrajDzwiek(DZWIEK_DRZWI);
		dynamic_cast<Tdrzwi*> (zKim)->otwarte = true;
		if(dynamic_cast<Tdrzwi*> (zKim)->CzyWDrzwiach(this) == true) {
			ZmienStan();
			kierX = 0;
			vY = 0;
			szumiStanGry = 1;
		}

	}
}

void Tszumi::WyrownajDoY(int y, bool pozwolSkoczyc, bool ostatecznie) {
	Tszumi::y = y;


	if(pozwolSkoczyc) {
		maPodloge = true;
		if(stan == SKOK) {
			animacjaZatrzymywalna = true;
			ZmienStan(BEZCZYNNY);
		}
		
	}
	vY = 0;
	if(ostatecznie) {
		wyrownalDoY = true;
		if(!wyrownalDoX)
			x = aktualneX;
	}
}

void Tszumi::WyrownajDoX(TobiektGry *zKim, bool ostatecznie) {
	if(stan == SLIZG) {
		animacjaZatrzymywalna = true;
		ZmienStan();
	}
	if(zKim->PobierzX() > x)
		x = zKim->PobierzX() - zKim->PobierzKolizjaXL() - kolizjaXP;
	else
		x = zKim->PobierzX() + zKim->PobierzKolizjaXP() + kolizjaXL;
	if(ostatecznie) {
		wyrownalDoX = true;
		if(!wyrownalDoY) {
				vY = aktualneVY;
				y = aktualneY;
				maPodloge = false;
		}
	}
}

void Tszumi::KolizjaZBlokiem(TobiektGry *zKim) {
	
	if(aktualneX <= zKim->PobierzX() + zKim->PobierzKolizjaXP() && aktualneX >= zKim->PobierzX() - zKim->PobierzKolizjaXL()) {
			if(zKim->PobierzY() > y)	// Kolizja gracza z gruntem
				WyrownajDoY(zKim->PobierzY() - zKim->PobierzKolizjaYG() - kolizjaYD, true);
			else						// Kolizja gracza z sufitem
				WyrownajDoY(zKim->PobierzY() + zKim->PobierzKolizjaYD() + kolizjaYG, false);
		}
		else if(aktualneY <= zKim->PobierzY() + zKim->PobierzKolizjaYD() && aktualneY >= zKim->PobierzY() - zKim->PobierzKolizjaYG()) {
			WyrownajDoX(zKim);
		}
		else if((poprzednieX + kolizjaXP <= zKim->PobierzX() - zKim->PobierzKolizjaXL() || poprzednieX - kolizjaXL >= zKim->PobierzX() + zKim->PobierzKolizjaXP()) &&
			poprzednieY + kolizjaYD != zKim->PobierzY() - zKim->PobierzKolizjaYG()) {
			if(!wyrownalDoY)
				WyrownajDoX(zKim, false);
		}
		else {
			if(zKim->PobierzY() > y)	// Kolizja gracza z gruntem
				WyrownajDoY(zKim->PobierzY() - zKim->PobierzKolizjaYG() - kolizjaYD, true, false);
			else						// Kolizja gracza z sufitem
				WyrownajDoY(zKim->PobierzY() + zKim->PobierzKolizjaYD() + kolizjaYG, false, false);
		}
}

void Tszumi::PobierzRuch(bool *keys) {

	if(animacjaZatrzymywalna == true) {
		if(keys[SPACE] && maPodloge) {
			if(stan == DOL || stan == ATAK_DOLEM || stan == RANNY_DOLEM)
				ZmienStan(ATAK_DOLEM);
			else
				ZmienStan(ATAK);
		}
		else if(keys[Z] && maPodloge) {
			ZmienStan(SUPER_ATAK);
		}
		else if(keys[UP] && mozeSkoczyc) {
			ZmienStan(SKOK);
		}
		else if(keys[DOWN]) {
			if((keys[RIGHT] || keys[LEFT]) && stan == BIEG) {
				if(kierX == 1 && keys[RIGHT] || kierX == -1 && keys[LEFT])
					ZmienStan(SLIZG);
				else
					ZmienKierunek(BEZCZYNNY);
			}
			else
				ZmienStan(DOL);
		}
		else if(keys[RIGHT]) {
			ZmienKierunek(1);
			if(maPodloge || naWindzie || naRampie)
				ZmienStan(BIEG);
			else
				ZmienStan();
		}
		else if(keys[LEFT]) {
			ZmienKierunek(-1);
			if(maPodloge || naWindzie || naRampie)
				ZmienStan(BIEG);
			else
				ZmienStan();
		}
		else {
			ZmienKierunek(0);
			if(stan == DOL || stan == ATAK_DOLEM || stan == RANNY_DOLEM) {
				ZmienStan(DOL);
			}
			else
				if(stan != BEZCZYNNY2)
					ZmienStan(BEZCZYNNY);
		}
	}
	else {
		if(stan == SKOK) {
			if(keys[RIGHT]) {
				ZmienKierunek(1);
			}
			else if(keys[LEFT]) {
				ZmienKierunek(-1);
			}
			else
				ZmienKierunek(BEZCZYNNY);
		}
	}
}

bool Tszumi::CzyZaatakowal(Twrog *innyObiekt) {
	if(innyObiekt->niesmiertelny)
		return false;
	if(stan == ATAK || stan == ATAK_DOLEM || stan == SUPER_ATAK) {
		Twrog rodzaj;
		if(innyObiekt->stanAI != rodzaj.AI_RANNY && innyObiekt->stanAI != rodzaj.AI_SMIERC) {
			int x2 = innyObiekt->PobierzX();
			int y2 = innyObiekt->PobierzY();

			int kolizjaXL2 = innyObiekt->PobierzKolizjaXL();
			int kolizjaXP2 = innyObiekt->PobierzKolizjaXP();
			int kolizjaYG2 = innyObiekt->PobierzKolizjaYG();
			int kolizjaYD2 = innyObiekt->PobierzKolizjaYD();

			if( x + atakXP > x2 - kolizjaXL2 &&
				x - atakXL < x2 + kolizjaXP2 &&
				y + atakYD > y2 - kolizjaYG2 &&
				y - atakYG < y2 + kolizjaYD2) {
				GrajDzwiek(DZWIEK_MIECZ_KOLIZJA);
				if(innyObiekt->PobierzID() == WROG)
					GrajDzwiek(innyObiekt->jakiWrog);
				else if(innyObiekt->idPudla == 0)
					GrajDzwiek(DZWIEK_SMIERC_WAZONU);
				else if(innyObiekt->idPudla == 1)
					GrajDzwiek(DZWIEK_SMIERC_SKRZYNII);
				else if(innyObiekt->PobierzID() == KROL) {
					GrajDzwiek(DZWIEK_KROL_RANNY);
				}
				return true;
			}
		}
	}
	return false;
}

void Tszumi::ResetujPozycje() {
	x = 85730;
	y = 85950;
	szumiStanGry = 0;
	stan = BEZCZYNNY;

	przerwa = 0;

	szumiStanGry = 0;

	mozeKolidowac = true;
	wyrownalDoY = false;

	naEkranie = true;

	animacjaZatrzymywalna = true;
	kierAnimacji = 1;
	stan = 0;
	ileBezczynny = 0;
	ranny = false;
	ileNiesmiertelny = 0;
	poprzedniKierX = 0;

	naWindzie = false;
	naPlatformie = 0;

	atakuje = false;
}

void Tszumi::ResetujDane() {
	ResetujPozycje();
	liczbaZyc = 3;
	liczbaSerduszek = 3;
	liczbaMonet = 0;
	liczbaPunktow = 0;
}