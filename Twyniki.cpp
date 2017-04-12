#include "Twyniki.h"

Twyniki::Twyniki(ALLEGRO_FONT *czcionkaDuza, ALLEGRO_FONT *czcionkaMala) {
	Twyniki::czcionkaDuza = czcionkaDuza;
	Twyniki::czcionkaMala = czcionkaMala;

	bialy_tekst = al_map_rgb(250, 250, 250);
	czarny_tekst = al_map_rgb(0, 0, 0);
}

void Twyniki::WczytajWyniki() {
	plik.open("Data/High Scores.txt");
	std::string data;
	int wartosc;
	
	CzyscWyniki();

	int licznik = 0;

	while(getline(plik, data)) {
		std::stringstream linia(data);
		linia >> wartosc;
		linia >> data;
		wartosci[licznik] = wartosc;
		daty[licznik] = data;

		licznik++;
	}

	ZapiszWyniki();

	plik.close();

	
}

void Twyniki::DodajWynik(int ile, std::string jakaData) {
	for(int q = 0; q < 5; q++) {
		if(ile > wartosci[q]) {
			for(int w = 3; w >= q; w--) {
				wartosci[w+1] = wartosci[w];
				daty[w+1] = daty[w];

			}
			wartosci[q] = ile;
			daty[q] = jakaData;
			ile = -1;
		}
	}
	ZapiszWyniki();
}

void Twyniki::DodajWynik(int ile) {
	time_t czas;
    struct tm * data;
    char jakaData[80];
    
    time( & czas );
    data = localtime( & czas );
    
    strftime( jakaData, 80, "%d.%m.%Y_%H:%M", data );
    DodajWynik(ile, jakaData);

}

void Twyniki::ZapiszWyniki() {
	plik.open("Data/High Scores.txt", std::ios::out);
	for(int licznik = 0; licznik < 5; licznik++) {
		plik << wartosci[licznik] << " ";
		plik << daty[licznik];
		plik << std::endl;
	}
	plik.close();
}

void Twyniki::CzyscWyniki() {
	for(int licznik = 0; licznik < 5; licznik++) {
		daty[licznik] = "--.--.----_--:--";
		wartosci[licznik] = 0;
	}
}

void Twyniki::Wypisz(int xP) {
	int x = xP - 50;
	int y = 335;

	
	/*al_draw_textf(czcionkaMala, bialy_tekst, x - 50 + 2, y - 20, ALLEGRO_ALIGN_CENTRE, "RANK");
	al_draw_textf(czcionkaMala, bialy_tekst, x - 50 - 2, y - 20, ALLEGRO_ALIGN_CENTRE, "RANK");
	al_draw_textf(czcionkaMala, bialy_tekst, x - 50, y - 20 + 2, ALLEGRO_ALIGN_CENTRE, "RANK");
	al_draw_textf(czcionkaMala, bialy_tekst, x - 50, y - 20 - 2, ALLEGRO_ALIGN_CENTRE, "RANK");*/

	al_draw_textf(czcionkaMala, czarny_tekst, x - 50, y - 20, ALLEGRO_ALIGN_CENTRE, "RANK");
	
	/*al_draw_textf(czcionkaMala, bialy_tekst, x + 2, y - 20, ALLEGRO_ALIGN_LEFT, "SCORE");
	al_draw_textf(czcionkaMala, bialy_tekst, x - 2, y - 20, ALLEGRO_ALIGN_LEFT, "SCORE");
	al_draw_textf(czcionkaMala, bialy_tekst, x, y - 20 + 2, ALLEGRO_ALIGN_LEFT, "SCORE");
	al_draw_textf(czcionkaMala, bialy_tekst, x, y - 20 - 2, ALLEGRO_ALIGN_LEFT, "SCORE");*/
	
	al_draw_textf(czcionkaMala, czarny_tekst, x, y - 20, ALLEGRO_ALIGN_LEFT, "SCORE");
	//std::cout<<x<<"\n";
	for(int q = 0; q < 5; q++) {
		/*al_draw_textf(czcionkaDuza, bialy_tekst, x - 50 + 2, y + q * 60, ALLEGRO_ALIGN_CENTRE, "%i.", q+1);
		al_draw_textf(czcionkaDuza, bialy_tekst, x - 50 - 2, y + q * 60, ALLEGRO_ALIGN_CENTRE, "%i.", q+1);
		al_draw_textf(czcionkaDuza, bialy_tekst, x - 50, y + q * 60 + 2, ALLEGRO_ALIGN_CENTRE, "%i.", q+1);
		al_draw_textf(czcionkaDuza, bialy_tekst, x - 50, y + q * 60 - 2, ALLEGRO_ALIGN_CENTRE, "%i.", q+1);*/

		al_draw_textf(czcionkaDuza, czarny_tekst, x - 50, y + q * 60, ALLEGRO_ALIGN_CENTRE, "%i.", q+1);
		
		/*al_draw_textf(czcionkaDuza, bialy_tekst, x + 2, y + q * 60, ALLEGRO_ALIGN_LEFT, "%i", wartosci[q]);
		al_draw_textf(czcionkaDuza, bialy_tekst, x - 2, y + q * 60, ALLEGRO_ALIGN_LEFT, "%i", wartosci[q]);
		al_draw_textf(czcionkaDuza, bialy_tekst, x, y + q * 60 + 2, ALLEGRO_ALIGN_LEFT, "%i", wartosci[q]);
		al_draw_textf(czcionkaDuza, bialy_tekst, x, y + q * 60 - 2, ALLEGRO_ALIGN_LEFT, "%i", wartosci[q]);*/
		
		al_draw_textf(czcionkaDuza, czarny_tekst, x, y + q * 60, ALLEGRO_ALIGN_LEFT, "%i", wartosci[q]);
		
		/*al_draw_textf(czcionkaMala, bialy_tekst, x + 2, y + 30 + q * 60, ALLEGRO_ALIGN_LEFT, "(%s)", (daty[q].replace(10, 1, " ")).c_str());
		al_draw_textf(czcionkaMala, bialy_tekst, x - 2, y + 30 + q * 60, ALLEGRO_ALIGN_LEFT, "(%s)", (daty[q].replace(10, 1, " ")).c_str());
		al_draw_textf(czcionkaMala, bialy_tekst, x, y + 30 + q * 60 + 2, ALLEGRO_ALIGN_LEFT, "(%s)", (daty[q].replace(10, 1, " ")).c_str());
		al_draw_textf(czcionkaMala, bialy_tekst, x, y + 30 + q * 60 - 2, ALLEGRO_ALIGN_LEFT, "(%s)", (daty[q].replace(10, 1, " ")).c_str());*/

		
		al_draw_textf(czcionkaMala, czarny_tekst, x, y + 30 + q * 60, ALLEGRO_ALIGN_LEFT, "(%s)", (daty[q].substr(0, 10) + " " + daty[q].substr(11, 5)).c_str());
		//al_draw_textf(czcionkaMala, czarny_tekst, x, y + 30 + q * 60, ALLEGRO_ALIGN_LEFT, "(%s)", (daty[q].replace(10, 1, " ")).c_str());

	}
	
}