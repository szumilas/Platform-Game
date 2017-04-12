#include "TmenuWyboru.h"

TmenuWyboru::TmenuWyboru(float x, float y, float vX, float vY, int kierX, int kierY,
		ALLEGRO_FONT *czcionka, ALLEGRO_BITMAP *obraz, std::string tekstL1,  std::string tekstL2, std::string tekstL3,
		std::string lewy, std::string prawy, bool obramowanie, int wyrownanie) {

	TobiektGry::Tworz(x, y, vX, vY, kierX, kierY);

	NadajID(MENU_WYBORU);

	klatkaOstatnia = 1;
	klatkaObecna = 0;
	klatkaLicznik = 0;
	klatkaOpoznienie = 1;


	TmenuWyboru::tekstL1 = tekstL1;
	TmenuWyboru::tekstL2 = tekstL2;
	TmenuWyboru::tekstL3 = tekstL3;
	TmenuWyboru::lewy = lewy;
	TmenuWyboru::prawy = prawy;

	szerokoscTla = 395;
	szerokoscPrzycisku = 123;

	wysokoscTla = 230;
	wysokoscPrzycisku = 60;

	wybrany = 0;

	naEkranie = false;
	animuj = false;

	
	if(obraz != NULL)
		TobiektGry::obraz = obraz;

	Tprzycisk::czcionka = czcionka;
	Tprzycisk::obramowanie = obramowanie;
	Tprzycisk::wyrownanie = wyrownanie;
	Tprzycisk::tekst = tekst;

}

void TmenuWyboru::Rysuj(int xGracz, int yGracz) {
	al_draw_bitmap_region(obraz, 0, wysokoscPrzycisku * 2, szerokoscTla, wysokoscTla, x - szerokoscTla / 2, y - wysokoscTla / 2, 0);

	if(wybrany == 1) {
		
		al_draw_bitmap_region(obraz, 0, 0, szerokoscPrzycisku, wysokoscPrzycisku, x - 100 - szerokoscPrzycisku / 2, y + 50 - wysokoscPrzycisku / 2, 0);
		al_draw_bitmap_region(obraz, 0, wysokoscPrzycisku, szerokoscPrzycisku, wysokoscPrzycisku, x + 100 - szerokoscPrzycisku / 2, y + 50 - wysokoscPrzycisku / 2, 0);
	}
	else {
		al_draw_bitmap_region(obraz, 0, wysokoscPrzycisku, szerokoscPrzycisku, wysokoscPrzycisku, x - 100 - szerokoscPrzycisku / 2, y + 50 - wysokoscPrzycisku / 2, 0);
		al_draw_bitmap_region(obraz, 0, 0, szerokoscPrzycisku, wysokoscPrzycisku, x + 100 - szerokoscPrzycisku / 2, y + 50 - wysokoscPrzycisku / 2, 0);

	}
	
	int yTekst = y - czcionka->height / 2 - 60;
	if(obramowanie) {
		al_draw_textf(czcionka, bialy_tekst, x+2, yTekst, wyrownanie, tekstL1.c_str());
		al_draw_textf(czcionka, bialy_tekst, x-2, yTekst, wyrownanie, tekstL1.c_str());
		al_draw_textf(czcionka, bialy_tekst, x, yTekst+2, wyrownanie, tekstL1.c_str());
		al_draw_textf(czcionka, bialy_tekst, x, yTekst-2, wyrownanie, tekstL1.c_str());

		al_draw_textf(czcionka, bialy_tekst, x+2, yTekst + 25, wyrownanie, tekstL2.c_str());
		al_draw_textf(czcionka, bialy_tekst, x-2, yTekst + 25, wyrownanie, tekstL2.c_str());
		al_draw_textf(czcionka, bialy_tekst, x, yTekst+2 + 25, wyrownanie, tekstL2.c_str());
		al_draw_textf(czcionka, bialy_tekst, x, yTekst-2 + 25, wyrownanie, tekstL2.c_str());

		al_draw_textf(czcionka, bialy_tekst, x+2, yTekst + 50, wyrownanie, tekstL3.c_str());
		al_draw_textf(czcionka, bialy_tekst, x-2, yTekst + 50, wyrownanie, tekstL3.c_str());
		al_draw_textf(czcionka, bialy_tekst, x, yTekst+2 + 50, wyrownanie, tekstL3.c_str());
		al_draw_textf(czcionka, bialy_tekst, x, yTekst-2 + 50, wyrownanie, tekstL3.c_str());
		
		al_draw_textf(czcionka, czarny_tekst, x+2 - 100, yTekst + 110, wyrownanie, lewy.c_str());
		al_draw_textf(czcionka, czarny_tekst, x-2 - 100, yTekst + 110, wyrownanie, lewy.c_str());
		al_draw_textf(czcionka, czarny_tekst, x - 100, yTekst+2 + 110, wyrownanie, lewy.c_str());
		al_draw_textf(czcionka, czarny_tekst, x - 100, yTekst-2 + 110, wyrownanie, lewy.c_str());
		
		al_draw_textf(czcionka, czarny_tekst, x+2 + 100, yTekst + 110, wyrownanie, prawy.c_str());
		al_draw_textf(czcionka, czarny_tekst, x-2 + 100, yTekst + 110, wyrownanie, prawy.c_str());
		al_draw_textf(czcionka, czarny_tekst, x + 100, yTekst+2 + 110, wyrownanie, prawy.c_str());
		al_draw_textf(czcionka, czarny_tekst, x + 100, yTekst-2 + 110, wyrownanie, prawy.c_str());
	}
	
	al_draw_textf(czcionka, czarny_tekst, x, yTekst, wyrownanie, tekstL1.c_str());
	al_draw_textf(czcionka, czarny_tekst, x, yTekst + 25, wyrownanie, tekstL2.c_str());
	al_draw_textf(czcionka, czarny_tekst, x, yTekst + 50, wyrownanie, tekstL3.c_str());
	
	al_draw_textf(czcionka, bialy_tekst, x - 100, yTekst + 110, wyrownanie, lewy.c_str());
	al_draw_textf(czcionka, bialy_tekst, x + 100, yTekst + 110, wyrownanie, prawy.c_str());
}