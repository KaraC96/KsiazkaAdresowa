#ifndef ADRESAT_H
#define ADRESAT_H

#include <iostream>

#include "UzytkownikMenedzer.h"

using namespace std;

class Adresat
{
    int id;
    int idUzytkownika;

public:
    string imie;
    string nazwisko;
    string numerTelefonu;
    string email;
    string adres;

    void ustawId(int noweId);
    int pobierzId();

    int pobierzIdUzytkownika();
    void ustawIdUzytkownika(int noweIdUzytkownika);
};

#endif
