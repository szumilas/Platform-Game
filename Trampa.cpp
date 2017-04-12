#include "Trampa.h"

Trampa::Trampa() {
	Trampa(0, 0, 0, 0, 0, 0, NULL, 0);
}

Trampa::Trampa(float x, float y, float vX, float vY, int kierX, int kierY, ALLEGRO_BITMAP *obraz, int numerKlatki) {
	Tblok::Tworz(x, y, vX, vY, kierX, kierY, obraz, numerKlatki);

	NadajID(RAMPA);

	if(numerKlatki == 0)
		spadek = -243;
	else if(numerKlatki == 1)
		spadek = -200;
	else if(numerKlatki == 2)
		spadek = -143;
	else if(numerKlatki == 3)
		spadek = 143;
	else if(numerKlatki == 4)
		spadek = 243;
	else if(numerKlatki == 5)
		spadek = 200;

}

int Trampa::ParametrKolizji() {
	return spadek;
}
