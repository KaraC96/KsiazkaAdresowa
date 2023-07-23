#include "Adresat.h"

void Adresat::ustawId(int noweId)
{
    if (noweId >= 0)
    id = noweId;
}

int Adresat::pobierzId()
{
    return id;
}

int Adresat::pobierzIdUzytkownika()
{
    return idUzytkownika;
}

void Adresat::ustawIdUzytkownika(int noweIdUzytkownika)
{
    idUzytkownika = noweIdUzytkownika;
}
