#ifndef ADRESATMENEDZER.h
#define ADRESATMENEDZER.h

#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <sstream>

#include "Adresat.h"
#include "PlikZAdresatami.h"

using namespace std;

class AdresatMenedzer
{
    vector <Adresat> adresaci;
    PlikZAdresatami plikZAdresatami;
    int idZalogowanegoUzytkownika;

    void wyswietlDaneAdresata(Adresat adresat);
    Adresat podajDaneNowegoAdresata();

public:

    AdresatMenedzer(string nazwaPlikuZAdresatami) : plikZAdresatami(nazwaPlikuZAdresatami) {};

    void dodajAdresata();
    void wyswietlWszystkichAdresatow();
    void wczytajAdresatowZPliku(int idZalogowanegoUzytkownika);
};

#endif
