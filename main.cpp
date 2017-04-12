#define ALLEGRO_STATICLINK

#include <Windows.h>

#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>

#include "TobiektGry.h"
#include "Tszumi.h"
#include "Tblok.h"
#include "Trampa.h"
#include "Twrog.h"
#include "Twinda.h"
#include "Tplatforma.h"
#include "TtloGry.h"
#include "Tpila.h"
#include "TzamekTlo.h"
#include "Tkolce.h"
#include "Tpudlo.h"
#include "Tbonus.h"
#include "Tnapis.h"
#include "TgrafikaGry.h"
#include "Tbeczka.h"
#include "Tdrzwi.h"
#include "Tekran.h"
#include "Tprzycisk.h"
#include "TmenuWyboru.h"
#include "Twyniki.h"
#include "Ttabliczka.h"
#include "Tkrol.h"
#include "TkamiennyPotwor.h"
#include "Togr.h"
#include "Tgoblin.h"

#include "ZmienneGlobalne.h"


int main() {

		//==============================
	//PARAMETRY NOWEGO OKNA
	//==============================

	srand(time(NULL));

	bool zmianaOkna = true;
	int losoweTlo = rand() % 3;

	std::fstream czyFullscreen;
	czyFullscreen.open("Data/Fullscreen.txt");
	std::string czyFullscreenTekst;
	getline(czyFullscreen, czyFullscreenTekst);

	if(czyFullscreenTekst == "Yes")
		FULLSCREEN = true;
	else
		FULLSCREEN = false;

	czyFullscreen.close();

	while(zmianaOkna) {

	zmianaOkna = false;
	
	//==============================
	//ZMIENNE GRY
	//==============================
	bool koniec = false;
	bool rysuj = false;

	float czasGry = 0;
	int FPS = 50;

	int x = 100;
	int y = 100;


	//==============================
	//URUCHAMIANIE ALLEGRO 5
	//==============================

	ALLEGRO_DISPLAY *display = NULL;
	if(!al_init()) {
		al_show_native_message_box(NULL, NULL, NULL, "Nie udalo sie uruchomic biblioteki Allegro5", NULL, NULL);                   
		return -1;
	}

	if(FULLSCREEN)
		al_set_new_display_flags( ALLEGRO_FULLSCREEN );
	else
		al_set_new_display_flags( ALLEGRO_WINDOWED );

	display = al_create_display(SZEROKOSC, WYSOKOSC);

	if(!display) {
		czyFullscreen.open("Data/Fullscreen.txt", std::ios::out);
		czyFullscreen << "No";
		czyFullscreen.close();

		al_show_native_message_box(NULL, NULL, NULL, "Wystapil blad podczas tworzenia okna", NULL, NULL);
		return -1;
	}

	al_hide_mouse_cursor(display);

	//==============================
	//INSTALACJA WTYCZEK
	//==============================

	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();


	//==============================
	//INICJOWANIE PROJEKTU
	//==============================
	ALLEGRO_FONT *czcionka24 = al_load_font("Data/Fonts/Aladin.ttf", 24, 0);
	czcionki.push_back(czcionka24);
	ALLEGRO_FONT *czcionka16 = al_load_font("Data/Fonts/Aladin.ttf", 16, 0);
	czcionki.push_back(czcionka16);
	ALLEGRO_FONT *czcionka40 = al_load_font("Data/Fonts/Aladin.ttf", 40, 0);
	czcionki.push_back(czcionka40);
	ALLEGRO_FONT *czcionka65 = al_load_font("Data/Fonts/Aladin.ttf", 65, 0);
	czcionki.push_back(czcionka65);
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_EVENT_QUEUE *kolejka = NULL;

	al_reserve_samples(10);

	//==============================
	//TIMER I ZDARZENIA
	//==============================
	kolejka = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(kolejka, al_get_timer_event_source(timer));
	al_register_event_source(kolejka, al_get_display_event_source(display));
	al_register_event_source(kolejka, al_get_keyboard_event_source());
	al_register_event_source(kolejka, al_get_mouse_event_source());

	al_start_timer(timer);
	czasGry = al_current_time();

	
	//==============================
	//WCZYTANIE GRAFIK
	//==============================

	
	if(!WczytajGrafiki(grafiki)) {
		al_show_native_message_box(NULL, "Error", "Blad", "Nie znaleziono wszystkich plikow graficznych", NULL, ALLEGRO_MESSAGEBOX_ERROR);  
		return 0;
	}
	if(!WczytajDzwieki(dzwieki)) {
		al_show_native_message_box(NULL, "Error", "Blad", "Nie znaleziono wszystkich plikow dzwiekowych", NULL, ALLEGRO_MESSAGEBOX_ERROR);  
		return 0;
	}

	//==============================
	//TWORZENIE BOHATERA
	//==============================

	Tszumi *szumi = new Tszumi(0, 0, 6, 2, 0, 1, grafiki[szumi->GRACZ], *GrajDzwiek);
	obiekty.push_back(szumi);

		
	//==============================
	//PARAMETRY ELEMENTOW MENU
	//==============================

	Twyniki wyniki(czcionki[0], czcionki[1]);
	wyniki.WczytajWyniki();


	//==============================
	//TWORZENIE MENU
	//==============================
	
	Tekran *ekran;
	ekran = new Tekran(0, 0, 0, 0, 0, 0, grafiki[ekran->EKRAN], losoweTlo);

	obiekty_menu.push_back(ekran);

	Tprzycisk *przycisk;
	przycisk = new Tprzycisk(300, 250, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 0, "Main Menu");
	obiekty_menu.push_back(przycisk);

	przycisk = new Tprzycisk(300, 300, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 1, "New Game");
	obiekty_menu.push_back(przycisk);

	przycisk = new Tprzycisk(300, 360, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 1, "High Scores");
	obiekty_menu.push_back(przycisk);

	przycisk = new Tprzycisk(300, 420, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 1, "About");
	obiekty_menu.push_back(przycisk);

	przycisk = new Tprzycisk(300, 480, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 1, "Options");
	obiekty_menu.push_back(przycisk);

	przycisk = new Tprzycisk(300, 540, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 1, "Exit Game");
	obiekty_menu.push_back(przycisk);
	
	przycisk = new Tprzycisk(300, 250, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 0, " New Game ");
	obiekty_menu.push_back(przycisk);

	przycisk = new Tprzycisk(300, 300, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 1, "Play Game");
	obiekty_menu.push_back(przycisk);

	przycisk = new Tprzycisk(300, 360, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 1, "Tutorial");
	obiekty_menu.push_back(przycisk);

	przycisk = new Tprzycisk(300, 420, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 1, "Back");
	obiekty_menu.push_back(przycisk);

	przycisk = new Tprzycisk(300, 250, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 0, " High Scores ");
	obiekty_menu.push_back(przycisk);

	przycisk = new Tprzycisk(300, 470, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 3, "#WYNIKI");
	obiekty_menu.push_back(przycisk);

	przycisk = new Tprzycisk(300, 680, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 1, "  Back  ");
	obiekty_menu.push_back(przycisk);

	przycisk = new Tprzycisk(300, 250, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 0, " About ");
	obiekty_menu.push_back(przycisk);

	przycisk = new Tprzycisk(300, 470, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 3, "#ABOUT");
	obiekty_menu.push_back(przycisk);

	przycisk = new Tprzycisk(300, 680, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 1, "     Back     ");
	obiekty_menu.push_back(przycisk);

	przycisk = new Tprzycisk(300, 250, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 0, " Options ");
	obiekty_menu.push_back(przycisk);

	przycisk = new Tprzycisk(300, 300, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 1, "Fullscreen");
	obiekty_menu.push_back(przycisk);

	przycisk = new Tprzycisk(300, 360, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 1, "Clear High Scores");
	obiekty_menu.push_back(przycisk);

	przycisk = new Tprzycisk(300, 420, 0, 0, 0, 0, czcionki[0], grafiki[przycisk->PRZYCISK], 1, "    Back    ");
	obiekty_menu.push_back(przycisk);
		
	WczytajMuzykeTla();


	//==============================
	//PETLA GRY
	//==============================

	while(!koniec) {


		ALLEGRO_EVENT zdarzenie;
		al_wait_for_event(kolejka, &zdarzenie);

		if(zdarzenie.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
		{
			if(OkienkoWyboru("Are you sure", "you want to exit the game?", "", "No", "Yes", kolejka) == true) {
				koniec = true;
				break;
			}
		}

		//==============================
		//==============================
		//==============================
		//GRA
		//==============================
		//==============================
		//==============================

		else if(stanGry == GRA) {

		//==============================
		//WCZYTYWANIE ZDARZENIA
		//==============================
			
		if(zdarzenie.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(zdarzenie.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				if(OkienkoWyboru("Are you sure", "you want to quit to main menu?", "", "No", "Yes", kolejka) == 1) {
					wybraneMenu = 0;
					wybranyPrzycisk = 0;
					SkonczMuzykeTla();
					stanGry = MENU;
					WczytajMuzykeTla();
					continue;
				}
				//koniec = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				break;
			case ALLEGRO_KEY_Z:
				keys[Z] = true;
				break;
			case ALLEGRO_KEY_X:
				keys[X] = true;
				break;
			}
		}
		else if(zdarzenie.type == ALLEGRO_EVENT_KEY_UP) {
			switch(zdarzenie.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			case ALLEGRO_KEY_Z:
				keys[Z] = false;
			case ALLEGRO_KEY_X:
				keys[X] = false;
				break;
			}
		}
		//==============================
		//AKTUALIZACJA
		//==============================
		else if(zdarzenie.type == ALLEGRO_EVENT_TIMER) {

			rysuj = true;


			szumi->PobierzRuch(keys);
			
			
			int xGracza = szumi->PobierzX();
			int yGracza = szumi->PobierzY();
			
			
			for(iter = obiekty.begin(); iter != obiekty.end(); iter++) {
				(*iter)->Aktualizuj(xGracza, yGracza);

					if((*iter)->aktywny == false) {
						if((*iter)->PobierzID() == szumi->NAPIS) {
							Tnapis rodzaj;
							if(dynamic_cast<Tnapis*>(*iter)->napisNaEkranie == false)
								szumi->liczbaPunktow += dynamic_cast<Tnapis*>(*iter)->liczba;

						} else if((*iter)->PobierzID() == szumi->BONUS) {
							Tbonus rodzaj;
							if(dynamic_cast<Tbonus*>(*iter)->jakiBonus == rodzaj.ZNIKANIE)
								StworzObiekt((*iter)->PobierzX(), (*iter)->PobierzY() - 50, szumi->NAPIS, 100);
							else if(dynamic_cast<Tbonus*>(*iter)->jakiBonus == rodzaj.PIENIAZEK)
								szumi->liczbaMonet++;
						} else if((*iter)->PobierzID() == szumi->KROL) {
							if(dynamic_cast <Tkrol*> (*iter)->koniecGry)
								szumi->szumiStanGry = 4;
							(*iter)->aktywny = true;
							continue;
						}
						(*iter)->Usun();
						delete (*iter);
						iter = obiekty.erase(iter);
						iter--;
				}


			}

			//Aktualizacja tla

			for(iter_tla = obiekty_tla.begin(); iter_tla != obiekty_tla.end(); iter_tla++)
				(*iter_tla)->Aktualizuj(xGracza, yGracza);

			if(szumi->szumiStanGry) {

				for(int q = 0 ; q < D; q++) {
					keys[q] = false;
				}
				if(szumi->szumiStanGry == 1) { //koniec etapu;
					stanGry = KONIEC_POZIOMU;
					SkonczMuzykeTla();
					WczytajMuzykeTla(12);
				}
				else if(szumi->szumiStanGry == 2) { //koniec gry
					stanGry = KONIEC_GRY;
					SkonczMuzykeTla();
					WczytajMuzykeTla(27);
					continue;
				}
				else if(szumi->szumiStanGry == 3) { //resetuj Poziom
					WczytajPoziom(aktualnyPoziom);
					continue;
				}
				else if(szumi->szumiStanGry == 4) { //Wygrana
					stanGry = ZWYCIESTWO;
					SkonczMuzykeTla();
					WczytajMuzykeTla(29);
					continue;
				}


				szumi->szumiStanGry = 0;
			}

			
		}
		
		//==============================
		//KOLIZJE
		//==============================
		iter = obiekty.begin();
		for(iter2 = iter; iter2 != obiekty.end(); ++iter2) {
			if( !(*iter2)->CzyMozeKolidowac() ) continue;

			if( (*iter)->CzyKolizja( (*iter2)))					
				(*iter)->KolidujeZ( (*iter2)->PobierzID(), *iter2);

			if((*iter2)->PobierzID() == (*iter2)->WROG || (*iter2)->PobierzID() == (*iter2)->PUDLO || (*iter2)->PobierzID() == (*iter2)->KROL) {
				if( szumi->CzyZaatakowal( dynamic_cast<Twrog*>(*iter2)))
					dynamic_cast<Twrog*>(*iter2)->Usmierc();
			}

		}

		//==============================
		//RYSOWANIE
		//==============================
		if(rysuj && al_is_event_queue_empty(kolejka)) {
			rysuj = false;
			
			int xGracz = szumi->PobierzX();
			int yGracz = szumi->PobierzY();
			
			(*obiekty_tla.begin())->Rysuj(xGracz, yGracz);

			int poczatekTablicy = max((szumi->PobierzX() + 1.1 * SZEROKOSC / 2 - (*wskazniki_tla[0])->PobierzX()) / (1.1 * SZEROKOSC) - 1, 0);
			

			for(iter_tla = wskazniki_tla[poczatekTablicy];
				iter_tla != obiekty_tla.end() && iter_tla != wskazniki_tla[min((szumi->PobierzX() + 1.1 * SZEROKOSC / 2 - (*wskazniki_tla[0])->PobierzX()) / (1.1 * SZEROKOSC) + 1, wskazniki_tla.size()-1)]; iter_tla++){
				if((*iter_tla)->naEkranie)
					(*iter_tla)->Rysuj(xGracz, yGracz);
			}

			//Rysowanie obiektow

			for(iter = obiekty.begin(); iter != obiekty.end(); iter++)
				if((*iter)->naEkranie)
					(*iter)->Rysuj(xGracz, yGracz);

			(*obiekty.begin())->Rysuj(xGracz, yGracz);

			al_flip_display();
		}

		}

		//==============================
		//==============================
		//==============================
		//KONIEC POZIOMU
		//==============================
		//==============================
		//==============================
		else if(stanGry == KONIEC_POZIOMU) {
			if(FULLSCREEN) {
				int xGracz = szumi->PobierzX();
				int yGracz = szumi->PobierzY();
				int qq=0;
				(*obiekty_tla.begin())->Rysuj(xGracz, yGracz);
				int poczatekTablicy = max((szumi->PobierzX() + 1.1 * SZEROKOSC / 2 - (*wskazniki_tla[0])->PobierzX()) / (1.1 * SZEROKOSC) - 1, 0);
				for(iter_tla = wskazniki_tla[poczatekTablicy];
					iter_tla != obiekty_tla.end() && iter_tla != wskazniki_tla[min((szumi->PobierzX() + 1.1 * SZEROKOSC / 2 - (*wskazniki_tla[0])->PobierzX()) / (1.1 * SZEROKOSC) + 1, wskazniki_tla.size()-1)]; iter_tla++){
					if((*iter_tla)->naEkranie)
						(*iter_tla)->Rysuj(xGracz, yGracz);
					qq++;
				}
				for(iter = obiekty.begin(); iter != obiekty.end(); iter++)
					if((*iter)->naEkranie)
						(*iter)->Rysuj(xGracz, yGracz);
				(*obiekty.begin())->Rysuj(xGracz, yGracz);
			}

			licznikAnimacji++;
			al_draw_filled_circle(SZEROKOSC / 2, WYSOKOSC / 2, licznikAnimacji * 5, al_map_rgb(0,0,0));
			szumi->Rysuj(0, 0);
			if(licznikAnimacji > 100) {
				if(aktualnyPoziom == 0) {
					al_draw_textf(czcionki[2], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 150, ALLEGRO_ALIGN_CENTRE, "Tutorial Complete!");
				}
				else {
					al_draw_textf(czcionki[2], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 150, ALLEGRO_ALIGN_CENTRE, "Level Complete!");
				}
			}

			if(licznikAnimacji > 200) {
				licznikAnimacji = 0;
				if(aktualnyPoziom == 0) {
					stanGry = MENU;
					wybraneMenu = 0;
					wybranyPrzycisk = 0;
					al_rest(3);
					dynamic_cast<Tszumi*>(*obiekty.begin())->ResetujDane();
					SkonczMuzykeTla();
					WczytajMuzykeTla();
				}
				else {
					stanGry = GRA;
					aktualnyPoziom++;
					al_rest(3);
					WczytajPoziom(aktualnyPoziom);
					continue;
				}
			}
			al_flip_display();
		}

		//==============================
		//==============================
		//==============================
		//KONIEC GRY
		//==============================
		//==============================
		//==============================
		else if(stanGry == KONIEC_GRY) {
			licznikAnimacji++;

			al_draw_filled_circle(SZEROKOSC / 2, WYSOKOSC / 2, licznikAnimacji * 5, al_map_rgb(0,0,0));
			szumi->Rysuj(0, 0);
			if(licznikAnimacji > 100) {
				al_draw_textf(czcionki[2], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 150, ALLEGRO_ALIGN_CENTRE, "You are dead!");
			}
			if(licznikAnimacji > 350) {
				if(aktualnyPoziom != 0)
					wyniki.DodajWynik(szumi->liczbaPunktow);

				licznikAnimacji = 0;
				stanGry = MENU;
				wybraneMenu = 0;
				wybranyPrzycisk = 0;

				std::ostringstream ss;
				ss << szumi->liczbaPunktow;

				al_draw_bitmap_region(grafiki[15], 0, 3600, SZEROKOSC, WYSOKOSC, 0, 0, 0);
				if(aktualnyPoziom == 0) {
					WypiszTekst(czcionki[2], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 150, ALLEGRO_ALIGN_CENTRE, "YOU FAILED", 1);
					WypiszTekst(czcionki[0], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 260, ALLEGRO_ALIGN_CENTRE, "Try again", 1);

				}
				else {
					WypiszTekst(czcionki[2], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 150, ALLEGRO_ALIGN_CENTRE, "GAME OVER", 1);
					WypiszTekst(czcionki[0], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 260, ALLEGRO_ALIGN_CENTRE, "Your score:", 1);
					WypiszTekst(czcionki[3], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 300, ALLEGRO_ALIGN_CENTRE, ss.str(), 1);
				}

				al_flip_display();
				al_rest(3);
				WypiszTekst(czcionki[0], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 550, ALLEGRO_ALIGN_CENTRE, "Press any key to continue", 1);
				al_flip_display();
				
				if(FULLSCREEN) {
					al_clear_to_color(al_map_rgb(0,0,0));
					al_draw_bitmap_region(grafiki[15], 0, 3600, SZEROKOSC, WYSOKOSC, 0, 0, 0);
					if(aktualnyPoziom == 0) {
						WypiszTekst(czcionki[2], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 150, ALLEGRO_ALIGN_CENTRE, "YOU FAILED", 1);
						WypiszTekst(czcionki[0], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 260, ALLEGRO_ALIGN_CENTRE, "Try again", 1);
					}
					else {
						WypiszTekst(czcionki[2], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 150, ALLEGRO_ALIGN_CENTRE, "GAME OVER", 1);
						WypiszTekst(czcionki[0], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 260, ALLEGRO_ALIGN_CENTRE, "Your score:", 1);
						WypiszTekst(czcionki[3], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 300, ALLEGRO_ALIGN_CENTRE, ss.str(), 1);
					}
					WypiszTekst(czcionki[0], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 550, ALLEGRO_ALIGN_CENTRE, "Press any key to continue", 1);
					al_flip_display();
				}


				PoczekajNaKlawisz(kolejka);
				dynamic_cast<Tszumi*>(*obiekty.begin())->ResetujDane();
				SkonczMuzykeTla();
				WczytajMuzykeTla();
			}
			al_flip_display();
		}
		//==============================
		//==============================
		//==============================
		//WYGRANA
		//==============================
		//==============================
		else if(stanGry == ZWYCIESTWO) {
			licznikAnimacji++;

			
			if(licznikAnimacji <= 2000) {

				szumi->PobierzRuch(keys);
				
				int xGracza = szumi->PobierzX();
				int yGracza = szumi->PobierzY();
				for(iter = obiekty.begin(); iter != obiekty.end(); iter++) {
					(*iter)->Aktualizuj(xGracza, yGracza);

						if((*iter)->aktywny == false) {
							if((*iter)->PobierzID() == szumi->NAPIS) {
								Tnapis rodzaj;
								if(dynamic_cast<Tnapis*>(*iter)->napisNaEkranie == false)
									szumi->liczbaPunktow += dynamic_cast<Tnapis*>(*iter)->liczba;

							} else if((*iter)->PobierzID() == szumi->BONUS) {
								Tbonus rodzaj;
								if(dynamic_cast<Tbonus*>(*iter)->jakiBonus == rodzaj.ZNIKANIE)
									StworzObiekt((*iter)->PobierzX(), (*iter)->PobierzY() - 50, szumi->NAPIS, 100);
								else if(dynamic_cast<Tbonus*>(*iter)->jakiBonus == rodzaj.PIENIAZEK)
									szumi->liczbaMonet++;
							}
							(*iter)->Usun();
							delete (*iter);
							iter = obiekty.erase(iter);
							iter--;
					}


				}

				//==============================
				//KOLIZJE
				//==============================
				int ileKolizji = 0;
				iter = obiekty.begin();
				for(iter2 = iter; iter2 != obiekty.end(); ++iter2) {
					if((*iter2)->PobierzID() == szumi->BLOK) {
						if( !(*iter2)->CzyMozeKolidowac() ) continue;
						ileKolizji ++;

						if( (*iter)->CzyKolizja( (*iter2)))
						{
							(*iter)->KolidujeZ( (*iter2)->PobierzID(), *iter2);
						}
					}

				}
				int xGracz = szumi->PobierzX();
				int yGracz = szumi->PobierzY();

				//Rysowanie tla
				int qq=0;

				(*obiekty_tla.begin())->Rysuj(xGracz, yGracz);

				int poczatekTablicy = max((szumi->PobierzX() + 1.1 * SZEROKOSC / 2 - (*wskazniki_tla[0])->PobierzX()) / (1.1 * SZEROKOSC) - 1, 0);
				for(iter_tla = wskazniki_tla[poczatekTablicy];
					iter_tla != obiekty_tla.end() && iter_tla != wskazniki_tla[min((szumi->PobierzX() + 1.1 * SZEROKOSC / 2 - (*wskazniki_tla[0])->PobierzX()) / (1.1 * SZEROKOSC) + 1, wskazniki_tla.size()-1)]; iter_tla++){
					if((*iter_tla)->naEkranie)
						(*iter_tla)->Rysuj(xGracz, yGracz);
					qq++;
				}

				//Rysowanie obiektow

				for(iter = obiekty.begin(); iter != obiekty.end(); iter++)
					if((*iter)->naEkranie)
						(*iter)->Rysuj(xGracz, yGracz);

				(*obiekty.begin())->Rysuj(xGracz, yGracz);

			}

			if(licznikAnimacji > 300) {
				al_draw_filled_circle(SZEROKOSC / 2, WYSOKOSC / 2, (licznikAnimacji - 300) * 5, al_map_rgb(0,0,0));
				szumi->Rysuj(0, 0);
			}
			if(licznikAnimacji > 400) {
				al_draw_textf(czcionki[2], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 150, ALLEGRO_ALIGN_CENTRE, "You are the winner!");
			}

			if(licznikAnimacji > 650) {
				wyniki.DodajWynik(szumi->liczbaPunktow);
				licznikAnimacji = 0;
				stanGry = MENU;
				wybraneMenu = 0;
				wybranyPrzycisk = 0;
				al_draw_bitmap_region(grafiki[15], 0, 4320, SZEROKOSC, WYSOKOSC, 0, 0, 0);
				WypiszTekst(czcionki[2], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 150, ALLEGRO_ALIGN_CENTRE, "YOU HAVE WON!", 1);
				WypiszTekst(czcionki[0], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 260, ALLEGRO_ALIGN_CENTRE, "Your score:", 1);
				std::ostringstream ss;
				ss << szumi->liczbaPunktow;
				WypiszTekst(czcionki[3], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 300, ALLEGRO_ALIGN_CENTRE, ss.str(), 1);
				al_flip_display();
				al_rest(3);
				WypiszTekst(czcionki[0], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 550, ALLEGRO_ALIGN_CENTRE, "Press any key to continue", 1);
				al_flip_display();
				if(FULLSCREEN) {
					al_clear_to_color(al_map_rgb(0,0,0));
					al_draw_bitmap_region(grafiki[15], 0, 4320, SZEROKOSC, WYSOKOSC, 0, 0, 0);
					WypiszTekst(czcionki[2], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 150, ALLEGRO_ALIGN_CENTRE, "YOU HAVE WON!", 1);
					WypiszTekst(czcionki[0], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 260, ALLEGRO_ALIGN_CENTRE, "Your score:", 1);
					WypiszTekst(czcionki[3], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 300, ALLEGRO_ALIGN_CENTRE, ss.str(), 1);
					WypiszTekst(czcionki[0], al_map_rgb(255, 255, 255), SZEROKOSC / 2, 550, ALLEGRO_ALIGN_CENTRE, "Press any key to continue", 1);
					al_flip_display();
				}
				PoczekajNaKlawisz(kolejka);
				dynamic_cast<Tszumi*>(*obiekty.begin())->ResetujDane();
				SkonczMuzykeTla();
				WczytajMuzykeTla();
				continue;
			}
			al_flip_display();
		}
		//==============================
		//==============================
		//==============================
		//MENU
		//==============================
		//==============================
		//==============================
		else if(stanGry == MENU) {
			
			if(zdarzenie.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(zdarzenie.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				GrajDzwiek(28);
				if(OkienkoWyboru("Are you sure", "you want to exit the game?", "", "No", "Yes", kolejka) == 1)
					koniec = true;
				break;
			case ALLEGRO_KEY_UP:
				GrajDzwiek(28);
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				GrajDzwiek(28);
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_ENTER:
				GrajDzwiek(28);
				keys[ENTER] = true;
				break;
			}
		}
		else if(zdarzenie.type == ALLEGRO_EVENT_KEY_UP) {
			switch(zdarzenie.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_ENTER:
				keys[ENTER] = false;
				break;
			}
		}
		//Aktualizacja
		else if(zdarzenie.type == ALLEGRO_EVENT_TIMER) {
			if(keys[DOWN]) {
				wybranyPrzycisk++;
				wybranyPrzycisk %= DaneMenu[wybraneMenu];
				keys[DOWN] = false;
			}
			else if(keys[UP]) {
				wybranyPrzycisk += DaneMenu[wybraneMenu];
				wybranyPrzycisk--;
				wybranyPrzycisk %= DaneMenu[wybraneMenu];
				keys[UP] = false;
			}
			else if(keys[ENTER]) {
				if(wybraneMenu == 0) { //Main menu
					if(wybranyPrzycisk == 4) {
						if(OkienkoWyboru("Are you sure", "you want to exit the game?", "", "No", "Yes", kolejka) == 1)
						koniec = true;
					}
					else {
						wybraneMenu = wybranyPrzycisk + 1;
						wybranyPrzycisk = 0;
					}
						
				}
				else if(wybraneMenu == 1) { //New Game
					if(wybranyPrzycisk == 0) {
						NowaGra(0);
					}
					else if(wybranyPrzycisk == 1) {
						NowaGra(1);
					}
					else if(wybranyPrzycisk == 2) {
						wybraneMenu = 0;
						wybranyPrzycisk = 0;
					}
				}
				else if(wybraneMenu == 2) { //High Scores
					if(wybranyPrzycisk == 0) {
						wybraneMenu = 0;
						wybranyPrzycisk = 0;
					}
				}
				else if(wybraneMenu == 3) { //About
					if(wybranyPrzycisk == 0) {
						wybraneMenu = 0;
						wybranyPrzycisk = 0;
					}
				}
				else if(wybraneMenu == 4) { //Options
					if(wybranyPrzycisk == 0) {
						if(OkienkoWyboru("", "Set fullscreen:", "", "On", "Off", kolejka) == 1) {
							if(FULLSCREEN == true) {
								koniec = true;
								zmianaOkna = true;
								FULLSCREEN = false;
								czyFullscreen.open("Data/Fullscreen.txt", std::ios::out);
								czyFullscreen << "No";
								czyFullscreen.close();
							}
						}
						else {
							if(FULLSCREEN == false) {
								koniec = true;
								zmianaOkna = true;
								FULLSCREEN = true;
								czyFullscreen.open("Data/Fullscreen.txt", std::ios::out);
								czyFullscreen << "Yes";
								czyFullscreen.close();
							}
						}
					}
					else if(wybranyPrzycisk == 1) {
						if(OkienkoWyboru("Are you sure", "you want to clear high scores?:", "", "No", "Yes", kolejka) == 1) {
							wyniki.CzyscWyniki();
							wyniki.ZapiszWyniki();
							wybraneMenu = 0;
							wybranyPrzycisk = 0;
						}
					}
					else if(wybranyPrzycisk == 2) {
						wybraneMenu = 0;
						wybranyPrzycisk = 0;
					}
				}


				keys[ENTER] = false;
				continue;
			}
		}


		for(iter_menu = obiekty_menu.begin(); iter_menu != obiekty_menu.end(); iter_menu++)
			(*iter_menu)->Aktualizuj(wybraneMenu, wybranyPrzycisk);


		for(iter_menu = obiekty_menu.begin(); iter_menu != obiekty_menu.end(); iter_menu++)
			if((*iter_menu)->naEkranie)
				(*iter_menu)->Rysuj(0, 0);


		if(wybraneMenu == 2) {
			int xP = 0;
			for(iter_menu = obiekty_menu.begin(); iter_menu != obiekty_menu.end(); iter_menu++) {

				if((*iter_menu)->PobierzID() == szumi->PRZYCISK) {
					if((*iter_menu)->naEkranie == true) {
						if(dynamic_cast <Tprzycisk*> (*iter_menu)->tekst == "#WYNIKI") {
							xP = (*iter_menu)->PobierzX();
							break;
						}
					}
				}

			}
			wyniki.Wypisz(xP);
		}
			

			al_flip_display();
		}

	}


	
	//==============================
	//PORZADKOWANIE
	//==============================

	szumi->Usun();
	
	for(iter = obiekty.begin(); iter != obiekty.end(); ) {
		(*iter)->Usun();
		delete (*iter);
		iter = obiekty.erase(iter);
	}

	
	for(iter_tla = obiekty_tla.begin(); iter_tla != obiekty_tla.end(); ) {
		(*iter_tla)->Usun();
		delete (*iter_tla);
		iter_tla = obiekty_tla.erase(iter_tla);
	}

	for(iter_menu = obiekty_menu.begin(); iter_menu != obiekty_menu.end(); ) {
		(*iter_menu)->Usun();
		delete (*iter_menu);
		iter_menu = obiekty_menu.erase(iter_menu);
	}

	for(int q = 0; q < czcionki.size(); q++) {
		al_destroy_font(czcionki[q]);
	}

	al_destroy_display(display);
	SkonczMuzykeTla();


	grafiki.clear();
	czcionki.clear();
	UsunGrafiki(grafiki);
	UsunDzwieki(dzwieki);

	}

	return 0;
}

void WczytajPoziom(int nrPoziomu) {
	
	for(int q = 0 ; q < D; q++) {
		keys[q] = false;
	}

	SkonczMuzykeTla();
	dynamic_cast<Tszumi*>(*obiekty.begin())->ResetujPozycje();

	al_draw_bitmap_region(grafiki[15], 0, 2880, SZEROKOSC, WYSOKOSC, 0, 0, 0);
	al_flip_display();
	al_rest(1);

	for(iter = ++obiekty.begin(); iter != obiekty.end(); ) {
		(*iter)->Usun();
		delete (*iter);
		iter = obiekty.erase(iter);
	}
	for(iter_tla = obiekty_tla.begin(); iter_tla != obiekty_tla.end(); ) {
		(*iter_tla)->Usun();
		delete (*iter_tla);
		iter_tla = obiekty_tla.erase(iter_tla);
	}
	int a;
	
	std::vector<TzamekTlo>tymczasowa;
	tymczasowa.clear();
	
	TobiektGry rodzaj;
	std::stringstream nazwa;
	std::fstream mapa;
	nazwa << "Data/Maps/Level_" << std::setw(2) << std::setfill('0') << nrPoziomu << ".txt";

	mapa.open(nazwa.str().c_str());

	while(mapa) {
		int r, a, b, c, d;
		mapa >> r>> a >> b >> c;
		if(r == rodzaj.BLOK) {
			Tblok *blok;
			blok = new Tblok(a, b, 0, 0, 0, 0, grafiki[rodzaj.BLOK], c);
			obiekty.push_back(blok);
		}
		else if(r == rodzaj.RAMPA) {
			Trampa *rampa;
			rampa = new Trampa(a, b, 0, 0, 0, 0, grafiki[rodzaj.RAMPA], c);
			obiekty.push_back(rampa);
		}
		else if(r == rodzaj.WROG) {
			Twrog *wrog;
			wrog = new Twrog(a, b, 1, 0, 0, 0, grafiki[rodzaj.WROG], c, *StworzObiekt);
			obiekty.push_back(wrog);
		}
		else if(r == rodzaj.WINDA) {
			Twinda *winda;
			mapa >> d;
			winda = new Twinda(a, b, 0, 1, 0, d, grafiki[rodzaj.WINDA], c);
			obiekty.push_back(winda);
		}
			
		else if(r == rodzaj.PLATFORMA) {
			Tplatforma *platforma;
			mapa >> d;
			platforma = new Tplatforma(a, b, 1, 0, d, 0, grafiki[rodzaj.PLATFORMA], c);
			obiekty.push_back(platforma);
		}
		else if(r == rodzaj.TLO_GRY) {
			TtloGry *tloGry;
			tloGry = new TtloGry(a, b, 0, 0, 0, 0, grafiki[rodzaj.TLO_GRY], c);
			obiekty_tla.push_back(tloGry);
		}
		else if(r == rodzaj.PILA) {
			Tpila *pila;
			mapa >> d;
			if(d < 100 && d > -100)
				pila = new Tpila(a, b, 1, 1, 0, d, grafiki[rodzaj.PILA], c);
			else
				pila = new Tpila(a, b, 1, 1, d, 0, grafiki[rodzaj.PILA], c);
			obiekty.push_back(pila);
		}
		else if(r == rodzaj.ZAMEK_TLO) {
			tymczasowa.push_back(TzamekTlo(a, b, 0, 0, 0, 0, grafiki[rodzaj.ZAMEK_TLO], c));
		}
		else if(r == rodzaj.KOLCE) {
			Tkolce *kolce;
			kolce = new Tkolce(a, b, 0, 0, 0, 0, grafiki[rodzaj.KOLCE], c);
			obiekty.push_back(kolce);
		}
		else if(r == rodzaj.PUDLO) {
			Tpudlo *pudlo;
			pudlo = new Tpudlo(a, b, 0, 0, 0, 0, grafiki[rodzaj.PUDLO], c, *StworzObiekt);
			obiekty.push_back(pudlo);
		}
		else if(r == rodzaj.BONUS) {
			Tbonus *bonus;
			bonus = new Tbonus(a, b, 0, 0, 0, 0, grafiki[rodzaj.BONUS], c);
			obiekty.push_back(bonus);
		}
		else if(r == rodzaj.BECZKA) {
			Tbeczka *beczka;
			beczka = new Tbeczka(a, b, 0, 0, 0, 0, grafiki[rodzaj.BECZKA], c, *StworzObiekt);
			obiekty.push_back(beczka);
		}
		else if(r == rodzaj.DRZWI) {
			Tdrzwi *drzwi;
			drzwi = new Tdrzwi(a, b, 0, 0, 0, 0, grafiki[rodzaj.DRZWI], c);
			obiekty.push_back(drzwi);
		}
		else if(r == rodzaj.TABLICZKA) {
			Ttabliczka *tabliczka;
			mapa >> d;
			tabliczka = new Ttabliczka(a, b, 0, 0, 0, 0, grafiki[rodzaj.TABLICZKA], c, d, czcionki[2]);
			obiekty.push_back(tabliczka);
		}
		else if(r == rodzaj.KROL) {
			Tkrol *krol;
			krol = new Tkrol(a, b, 1, 0, 0, 0, grafiki[rodzaj.KROL], c, *StworzObiekt, czcionki[2]);
			obiekty.push_back(krol);
		}
		else if(r == rodzaj.KAMIENNY_POTWOR) {
			TkamiennyPotwor *kamiennyPotwor;
			kamiennyPotwor = new TkamiennyPotwor(a, b, 1, 0, 0, 0, grafiki[rodzaj.KAMIENNY_POTWOR], c, *StworzObiekt);
			obiekty.push_back(kamiennyPotwor);
		}
		else if(r == rodzaj.OGR) {
			Togr *ogr;
			ogr = new Togr(a, b, 1, 0, 0, 0, grafiki[rodzaj.OGR], c, *StworzObiekt, *GrajDzwiek);
			obiekty.push_back(ogr);
		}
		else if(r == rodzaj.GOBLIN) {
			Tgoblin *goblin;
			goblin = new Tgoblin(a, b, 1, 0, 0, 0, grafiki[rodzaj.GOBLIN], c, *StworzObiekt);
			obiekty.push_back(goblin);
		}
	}

	mapa.close();

	Tnapis *napis;
	
	TgrafikaGry *grafikaGry;

	//PUNKTY
	napis = new Tnapis(100, 15, 0, 0, 0, 0, czcionki[0], PobierzParametrySzumiego(napis->PUNKTY), napis->PUNKTY, PobierzParametrySzumiego);
	obiekty.push_back(napis);

	//ZYCIA
	napis = new Tnapis(90, WYSOKOSC - 50, 0, 0, 0, 0, czcionki[0], 0, napis->TEKST, NULL, "x");
	obiekty.push_back(napis);
	napis = new Tnapis(110, WYSOKOSC - 50, 0, 0, 0, 0, czcionki[0], PobierzParametrySzumiego(napis->ZYCIA), napis->ZYCIA, PobierzParametrySzumiego);
	obiekty.push_back(napis);
	grafikaGry = new TgrafikaGry(25, WYSOKOSC - 60, 0, 0, 0, 0, grafiki[rodzaj.GRAFIKA_GRY], grafikaGry->GRAFIKA_SZUMI, PobierzParametrySzumiego);
	obiekty.push_back(grafikaGry);

	//SERDUSZKA
	grafikaGry = new TgrafikaGry(SZEROKOSC - 100, 15, 0, 0, 0, 0, grafiki[rodzaj.GRAFIKA_GRY], grafikaGry->GRAFIKA_SERDUSZKO, PobierzParametrySzumiego);
	obiekty.push_back(grafikaGry);
	
	grafikaGry = new TgrafikaGry(SZEROKOSC - 75, 15, 0, 0, 0, 0, grafiki[rodzaj.GRAFIKA_GRY], grafikaGry->GRAFIKA_SERDUSZKO, PobierzParametrySzumiego);
	obiekty.push_back(grafikaGry);
	
	grafikaGry = new TgrafikaGry(SZEROKOSC - 50, 15, 0, 0, 0, 0, grafiki[rodzaj.GRAFIKA_GRY], grafikaGry->GRAFIKA_SERDUSZKO, PobierzParametrySzumiego);
	obiekty.push_back(grafikaGry);

	//MONETY
	napis = new Tnapis(SZEROKOSC - 60, WYSOKOSC - 60, 0, 0, 0, 0, czcionki[0], 0, napis->TEKST, NULL, "x");
	obiekty.push_back(napis);
	napis = new Tnapis(SZEROKOSC - 80, WYSOKOSC - 60, 0, 0, 0, 0, czcionki[0], PobierzParametrySzumiego(napis->MONETY), napis->MONETY, PobierzParametrySzumiego);
	obiekty.push_back(napis);
	grafikaGry = new TgrafikaGry(SZEROKOSC - 50, WYSOKOSC - 60, 0, 0, 0, 0, grafiki[rodzaj.GRAFIKA_GRY], grafikaGry->GRAFIKA_MONETA, PobierzParametrySzumiego);
	obiekty.push_back(grafikaGry);

	
	struct wybierz_mniejszy {
		inline bool operator() (TobiektGry obiekt1, TobiektGry obiekt2)
		{
			if(obiekt1.PobierzX() == obiekt2.PobierzX()) {
				return (obiekt1.klatkaObecna < obiekt2.klatkaObecna);
			}
			return (obiekt1.PobierzX() < obiekt2.PobierzX());
		}

	};

	std::sort(tymczasowa.begin(), tymczasowa.end(), wybierz_mniejszy());

	wskazniki_tla.clear();
	
	for(int q = 0; q < tymczasowa.size(); q++) {
		TzamekTlo *zamekTlo;
		zamekTlo = new TzamekTlo;
		*zamekTlo = tymczasowa[q];

		obiekty_tla.push_back(zamekTlo);
	}
	iter_tla = ++obiekty_tla.begin();
	int aktualnyX = (*iter_tla)->PobierzX();

	for(; iter_tla != obiekty_tla.end(); ++iter_tla) {
		wskazniki_tla.push_back(iter_tla);
		aktualnyX += 1.1 * SZEROKOSC;
		while(iter_tla != obiekty_tla.end() && (*iter_tla)->PobierzX() < aktualnyX)	{
			iter_tla++;
		}
		iter_tla--;

	}
	iter_tla = obiekty_tla.end();
	iter_tla --;

	wskazniki_tla.push_back(iter_tla);

	
	WczytajMuzykeTla(aktualnyPoziom);

}

bool WczytajDzwieki(std::vector <ALLEGRO_SAMPLE*> &dzwieki) {
	
	ALLEGRO_SAMPLE *dzwiek = NULL;

	dzwiek = al_load_sample("Data/Sounds/Level_00.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/Level_01.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);
	
	dzwiek = al_load_sample("Data/Sounds/Level_02.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);
	
	dzwiek = al_load_sample("Data/Sounds/Level_03.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);
	
	dzwiek = al_load_sample("Data/Sounds/Level_04.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);
	
	dzwiek = al_load_sample("Data/Sounds/Level_05.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);
	
	dzwiek = al_load_sample("Data/Sounds/Level_06.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);
	
	dzwiek = al_load_sample("Data/Sounds/Level_07.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);
	
	dzwiek = al_load_sample("Data/Sounds/Level_08.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);
	
	dzwiek = al_load_sample("Data/Sounds/Level_09.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);
	
	dzwiek = al_load_sample("Data/Sounds/Level_10.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/Menu.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/NowyPoziom.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/MachanieMieczem.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/Skok.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/Slizg.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/MieczKolizja.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/WziecieJedzenia.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/Moneta.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/Serduszko.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/DodanieZycia.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/UtrataSerduszka.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/Smierc.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/SmiercBestii.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/SmiercWazonu.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/SmiercSkrzynii.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/Drzwi.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/MuzykaSmierc.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/Przycisk.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/MuzykaWygrana.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/KrolRanny.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/GoblinRanny.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/OgrRanny.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/KamiennyRanny.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/RycerzRanny.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	dzwiek = al_load_sample("Data/Sounds/AtakOgra.ogg");
	if(!dzwiek) return 0;
	dzwieki.push_back(dzwiek);

	return 1;
}

void UsunDzwieki(std::vector <ALLEGRO_SAMPLE*> &dzwieki) {

	for(int q = 0; q < dzwieki.size(); q++) {
		al_destroy_sample(dzwieki[q]);
	}
	dzwieki.clear();

}

bool WczytajGrafiki(std::vector <ALLEGRO_BITMAP*> &obrazki) {

	ALLEGRO_BITMAP *obrazek = NULL;

	obrazek = al_load_bitmap("Data/Images/Loading.png");
	if(!obrazek) return 0;
	al_draw_bitmap_region(obrazek, 0, 0, SZEROKOSC, WYSOKOSC, 0, 0, 0);
	al_flip_display();
	al_rest(1);
	al_destroy_bitmap(obrazek);

	obrazek = al_load_bitmap("Data/Images/Szumi.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/Zamek.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/ZamekRampy.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/CzarnyRycerz.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/Winda.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/Platforma.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/TloGry.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/Pila.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/ZamekTlo.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/Kolce.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/Wazon.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/Bonusy.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/GrafikiGry.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/Beczka.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/Drzwi.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	//Grafiki MENU

	obrazek = al_load_bitmap("Data/Images/TloMenu.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/Przyciski.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/MenuWyboru.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/Tabliczki.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/Krol.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/KamiennyPotwor.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/Ogr.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	obrazek = al_load_bitmap("Data/Images/Goblin.png");
	if(!obrazek) return 0;
	obrazki.push_back(obrazek);

	return 1;

}

void UsunGrafiki(std::vector <ALLEGRO_BITMAP*> &obrazki) {

	for(int q = 0; q < obrazki.size(); q++) {
		al_destroy_bitmap(obrazki[q]);
	}
	obrazki.clear();

}

void StworzObiekt(int x, int y, int jakiObiekt, int liczba) {
	TobiektGry rodzaj;
	if(jakiObiekt == rodzaj.BONUS) {
		Tbonus *bonus;
		bonus = new Tbonus(x, y, 0, 0, 0, 0, grafiki[bonus->BONUS], liczba);
		obiekty.push_back(bonus);
	}
	else if (jakiObiekt == rodzaj.NAPIS) {
		Tnapis *napis;
		napis = new Tnapis(x - (*obiekty.begin())->PobierzX() + SZEROKOSC / 2, y - (*obiekty.begin())->PobierzY() + WYSOKOSC / 2, 0, 0, 0, 0, czcionki[0], liczba);
		obiekty.push_back(napis);
	}

}

int PobierzParametrySzumiego(int jakiParametr) {
	Tnapis rodzaj;
	if(jakiParametr == rodzaj.PUNKTY) { //punkty
		return dynamic_cast <Tszumi*>(*obiekty.begin())->liczbaPunktow;
	} else if(jakiParametr == rodzaj.ZYCIA) { //zycia
		return dynamic_cast <Tszumi*>(*obiekty.begin())->liczbaZyc;
	} else if(jakiParametr == rodzaj.SERDUSZKA) { //serduszka
		return dynamic_cast <Tszumi*>(*obiekty.begin())->liczbaSerduszek;
	} else if(jakiParametr == rodzaj.MONETY) { //monety
		return dynamic_cast <Tszumi*>(*obiekty.begin())->liczbaMonet;
	}
}

bool OkienkoWyboru(std::string L1, std::string L2, std::string L3, std::string lewy, std::string prawy, ALLEGRO_EVENT_QUEUE *taKolejka) {
	bool aktywneOkno = true;
	int ileZaciemnienia = 0;
	
	TmenuWyboru *okienko;
	okienko = new TmenuWyboru(SZEROKOSC / 2, WYSOKOSC / 2, 0, 0, 0, 0,
		czcionki[0], grafiki[okienko->MENU_WYBORU], L1, L2, L3,
		lewy, prawy);

	while(aktywneOkno) {
		ALLEGRO_EVENT zdarzenie;
		al_wait_for_event(taKolejka, &zdarzenie);
		

		if(zdarzenie.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(zdarzenie.keyboard.keycode) {
			case ALLEGRO_KEY_ENTER:
				GrajDzwiek(28);
				aktywneOkno = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				GrajDzwiek(28);
				okienko->ZmienWybrany();
				break;
			case ALLEGRO_KEY_LEFT:
				GrajDzwiek(28);
				okienko->ZmienWybrany();
				break;
			}
		}
		if(ileZaciemnienia < 20) {
			al_draw_bitmap_region(grafiki[okienko->EKRAN], 0, 720 * 3, SZEROKOSC, WYSOKOSC, 0, 0, 0);
			ileZaciemnienia++;
		}
		okienko->Rysuj(0, 0);

		al_flip_display();
	}

	return okienko->Wybrany();
}

void PoczekajNaKlawisz(ALLEGRO_EVENT_QUEUE *taKolejka) {
	ALLEGRO_EVENT zdarzenie;
	do
		al_wait_for_event(taKolejka, &zdarzenie);
	while(zdarzenie.type != ALLEGRO_EVENT_KEY_DOWN);
}

void NowaGra(bool tutorial) {
	dynamic_cast<Tszumi*>(*obiekty.begin())->ResetujDane();
	if(tutorial)
		aktualnyPoziom = 0;
	else
		aktualnyPoziom = 1;
	stanGry = GRA;
	WczytajPoziom(aktualnyPoziom);
}

void WczytajMuzykeTla(int ktora) {
	
	if(ktora == -1)
		ktora = 11;

	songInstance = al_create_sample_instance(dzwieki[ktora]);
	if(ktora == 12) //Koniec poziomu
		al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_ONCE);
	else
		al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

	al_play_sample_instance(songInstance);

}

void SkonczMuzykeTla() {
	al_stop_sample_instance(songInstance);
	al_destroy_sample_instance(songInstance);

}

void GrajDzwiek(int ktory) {
	al_play_sample(dzwieki[ktory], 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
}


void WypiszTekst(ALLEGRO_FONT *czcionka, ALLEGRO_COLOR kolor, int x, int y, int wyrownanie, std::string jakiTekst, bool obramowanie) {
	if(obramowanie) {
		al_draw_textf(czcionka, al_map_rgb(0, 0, 0), x + 2, y, wyrownanie, jakiTekst.c_str());
		al_draw_textf(czcionka, al_map_rgb(0, 0, 0), x - 2, y, wyrownanie, jakiTekst.c_str());
		al_draw_textf(czcionka, al_map_rgb(0, 0, 0), x, y + 2, wyrownanie, jakiTekst.c_str());
		al_draw_textf(czcionka, al_map_rgb(0, 0, 0), x, y - 2, wyrownanie, jakiTekst.c_str());
	}
	al_draw_textf(czcionka, kolor, x, y, wyrownanie, jakiTekst.c_str());

}