#ifndef PLIKTEKSTOWY_H
#define PLIKTEKSTOWY_H

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class PlikTekstowy
{
    const string NAZWA_PLIKU;

protected:
    fstream plikTekstowy;
    bool czyPlikJestPusty(fstream &plikTekstowy);
    string pobierzNazwePliku();

public:
    PlikTekstowy(string nazwaPliku) : NAZWA_PLIKU(nazwaPliku) {};
};
#endif
