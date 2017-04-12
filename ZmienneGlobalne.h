#pragma once

const int SZEROKOSC = 1280;
const int WYSOKOSC = 720;

bool edytorMap = false;
bool siatka = false;
bool wypiszProstokatKolizji = false;
bool keys[] = {false, false, false, false, false, false, false, false, false, false, false, false};

enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE, ENTER, Z, X, W, S, A, D};
enum STAN{MENU, GRA, KONIEC_POZIOMU, KONIEC_GRY, ZWYCIESTWO};

int aktualnyPoziom = -1;
int stanGry = MENU;

bool FULLSCREEN = false;

int wybraneMenu = 0;
int wybranyPrzycisk = 0;

int DaneMenu[5] = {5, 3, 1, 1, 3};

int licznikAnimacji = 0;


std::list <TobiektGry *> obiekty;
std::list <TobiektGry *>::iterator iter;
std::list <TobiektGry *>::iterator iter2;

std::list <TobiektGry *> obiekty_tla;
std::list <TobiektGry *>::iterator iter_tla;
std::vector <std::list <TobiektGry *>::iterator> wskazniki_tla;

std::list <TobiektGry *> obiekty_menu;
std::list <TobiektGry *>::iterator iter_menu;

std::vector <ALLEGRO_BITMAP*> grafiki;
std::vector <ALLEGRO_SAMPLE*> dzwieki;
std::vector <ALLEGRO_FONT*> czcionki;

ALLEGRO_SAMPLE_INSTANCE *songInstance;

void WczytajPoziom(int nrPoziomu);

bool WczytajGrafiki(std::vector <ALLEGRO_BITMAP*> &obrazki);
void UsunGrafiki(std::vector <ALLEGRO_BITMAP*> &obrazki);

bool WczytajDzwieki(std::vector <ALLEGRO_SAMPLE*> &dzwieki);
void UsunDzwieki(std::vector <ALLEGRO_SAMPLE*> &dzwieki);

void WczytajMuzykeTla(int ktora = -1);
void SkonczMuzykeTla();
void GrajDzwiek(int ktory);

void StworzObiekt(int x, int y, int jakiObiekt, int liczba);
int PobierzParametrySzumiego(int jakiParametr);

bool OkienkoWyboru(std::string L1, std::string L2, std::string L3, std::string lewy, std::string prawy, ALLEGRO_EVENT_QUEUE *taKolejka);
void PoczekajNaKlawisz(ALLEGRO_EVENT_QUEUE *taKolejka);
void NowaGra(bool tutorial);

void WypiszTekst(ALLEGRO_FONT *czcionka, ALLEGRO_COLOR kolor, int x, int y, int wyrownanie, std::string jakiTekst, bool obramowanie);