#include "PlikZAdresatami.h"

bool PlikZAdresatami::dopiszAdresataDoPliku(Adresat adresat)
{
    string liniaZDanymiAdresata = "";
    fstream plikTekstowy;
    plikTekstowy.open(NAZWA_PLIKU_Z_ADRESATAMI.c_str(), ios::out | ios::app);

    if (plikTekstowy.good() == true)
    {
        liniaZDanymiAdresata = zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(adresat);

        if (czyPlikJestPusty(plikTekstowy) == true)
        {
            plikTekstowy << liniaZDanymiAdresata;
        }
        else
        {
            plikTekstowy << endl << liniaZDanymiAdresata ;
        }
        idOstatniegoAdresata++;
        plikTekstowy.close();
        system("pause");
        return true;
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
    }
    return false;
}

string PlikZAdresatami::zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(Adresat adresat)
{
    string liniaZDanymiAdresata = "";

    liniaZDanymiAdresata += MetodyPomocnicze::konwersjaIntNaString(adresat.pobierzId()) + '|';
    liniaZDanymiAdresata += MetodyPomocnicze::konwersjaIntNaString(adresat.pobierzIdUzytkownika()) + '|';
    liniaZDanymiAdresata += adresat.wczytajImie() + '|';
    liniaZDanymiAdresata += adresat.wczytajNazwisko() + '|';
    liniaZDanymiAdresata += adresat.wczytajNumerTelefonu() + '|';
    liniaZDanymiAdresata += adresat.wczytajEmail() + '|';
    liniaZDanymiAdresata += adresat.wczytajAdres() + '|';

    return liniaZDanymiAdresata;
}

Adresat PlikZAdresatami::pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami)
{
    Adresat adresat;
    string pojedynczaDanaAdresata = "";
    int numerPojedynczejDanejAdresata = 1;

    for (size_t pozycjaZnaku = 0; pozycjaZnaku < daneAdresataOddzielonePionowymiKreskami.length(); pozycjaZnaku++)
    {
        if (daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku] != '|')
        {
            pojedynczaDanaAdresata += daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku];
        }
        else
        {
            switch(numerPojedynczejDanejAdresata)
            {
            case 1:
                adresat.ustawId(atoi(pojedynczaDanaAdresata.c_str()));
                break;
            case 2:
                adresat.ustawIdUzytkownika(atoi(pojedynczaDanaAdresata.c_str()));
                break;
            case 3:
                adresat.ustawImie(pojedynczaDanaAdresata);
                break;
            case 4:
                adresat.ustawNazwisko(pojedynczaDanaAdresata);
                break;
            case 5:
                adresat.ustawNumerTelefonu(pojedynczaDanaAdresata);
                break;
            case 6:
                adresat.ustawEmail(pojedynczaDanaAdresata);
                break;
            case 7:
                adresat.ustawAdres(pojedynczaDanaAdresata);
                break;
            }
            pojedynczaDanaAdresata = "";
            numerPojedynczejDanejAdresata++;
        }
    }
    return adresat;
}

int PlikZAdresatami::pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami)
{
    int pozycjaRozpoczeciaIdAdresata = 0;
    int idAdresata = MetodyPomocnicze::konwersjaStringNaInt(pobierzLiczbe(daneJednegoAdresataOddzielonePionowymiKreskami, pozycjaRozpoczeciaIdAdresata));
    return idAdresata;
}

int PlikZAdresatami::pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami)
{
    int pozycjaRozpoczeciaIdUzytkownika = daneJednegoAdresataOddzielonePionowymiKreskami.find_first_of('|') + 1;
    int idUzytkownika = MetodyPomocnicze::konwersjaStringNaInt(pobierzLiczbe(daneJednegoAdresataOddzielonePionowymiKreskami, pozycjaRozpoczeciaIdUzytkownika));

    return idUzytkownika;
}

vector <Adresat> PlikZAdresatami::wczytajAdresatowZalogowanegoUzytkownikaZPliku(int idZalogowanegoUzytkownika)
{
    vector <Adresat> adresaci;
    Adresat adresat;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    string daneOstaniegoAdresataWPliku = "";
    fstream plikTekstowy;
    plikTekstowy.open(NAZWA_PLIKU_Z_ADRESATAMI.c_str(), ios::in);

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            if (idZalogowanegoUzytkownika == pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(daneJednegoAdresataOddzielonePionowymiKreskami))
            {
                adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);
                adresaci.push_back(adresat);
            }
        }
        daneOstaniegoAdresataWPliku = daneJednegoAdresataOddzielonePionowymiKreskami;
        plikTekstowy.close();
    }
    else
        cout << "Nie udalo sie otworzyc pliku i wczytac danych." << endl;

    if (daneOstaniegoAdresataWPliku != "")
    {
        idOstatniegoAdresata = pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(daneOstaniegoAdresataWPliku);
        return adresaci;
    }
    else
        return adresaci;
}

string PlikZAdresatami::pobierzLiczbe(string tekst, int pozycjaZnaku)
{
    string liczba = "";
    while(isdigit(tekst[pozycjaZnaku]) == true)
    {
        liczba += tekst[pozycjaZnaku];
        pozycjaZnaku ++;
    }
    return liczba;
}

int PlikZAdresatami::pobierzIdOstatniegoAdresata()
{
    return idOstatniegoAdresata;
}

void PlikZAdresatami::wczytajIdOstatniegoAdresata(int Id)
{
    idOstatniegoAdresata = Id;
}

void PlikZAdresatami::usunAdresataZPliku(int idAdresata)
{
    int numerLiniiWPlikuTekstowym = 1;
    int numerUsuwanejLinii = 0;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    fstream plikTekstowy,tymczasowyPlikTekstowy;
    string nazwaTymczasowegoPlikuZAdresatami = "temp.txt";

    plikTekstowy.open(NAZWA_PLIKU_Z_ADRESATAMI.c_str(), ios::in);
    tymczasowyPlikTekstowy.open(nazwaTymczasowegoPlikuZAdresatami.c_str(), ios::out | ios::app);

    if (plikTekstowy.good() == true && idAdresata != 0)
    {
        while(getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            if(idAdresata == pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(daneJednegoAdresataOddzielonePionowymiKreskami))
            {
                tymczasowyPlikTekstowy << "";
                numerUsuwanejLinii = numerLiniiWPlikuTekstowym;
            }
            else if(numerLiniiWPlikuTekstowym == 1)
                tymczasowyPlikTekstowy << daneJednegoAdresataOddzielonePionowymiKreskami;
            else if (numerUsuwanejLinii == numerLiniiWPlikuTekstowym && numerLiniiWPlikuTekstowym == 2)
                tymczasowyPlikTekstowy << daneJednegoAdresataOddzielonePionowymiKreskami;
            else
                tymczasowyPlikTekstowy << endl << daneJednegoAdresataOddzielonePionowymiKreskami;

          numerLiniiWPlikuTekstowym++;
          numerUsuwanejLinii++;
        }

        plikTekstowy.close();
        tymczasowyPlikTekstowy.close();
        MetodyPomocnicze::usunOdczytywanyPlik(NAZWA_PLIKU_Z_ADRESATAMI);
        MetodyPomocnicze::zmienNazweTymczasowegoPlikuNaNazweOdczytywanegoPliku(nazwaTymczasowegoPlikuZAdresatami, NAZWA_PLIKU_Z_ADRESATAMI);

    }
}

void PlikZAdresatami::edytujAdresataWPliku(Adresat adresat)
{
    bool czyIstniejeAdresat = false;
    int numerLiniiWPlikuTekstowym = 1;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    fstream plikTekstowy,tymczasowyPlikTekstowy;
    string nazwaTymczasowegoPlikuZAdresatami="temp.txt";


    plikTekstowy.open(NAZWA_PLIKU_Z_ADRESATAMI.c_str(), ios::in);
    tymczasowyPlikTekstowy.open(nazwaTymczasowegoPlikuZAdresatami.c_str(), ios::out | ios::app);

    if (plikTekstowy.good() == true && adresat.pobierzId() != 0)
    {
        while(getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            if(adresat.pobierzId() == pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(daneJednegoAdresataOddzielonePionowymiKreskami)&&numerLiniiWPlikuTekstowym==1)
            {
                czyIstniejeAdresat = true;
                tymczasowyPlikTekstowy << zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(adresat);
            }
            else if(adresat.pobierzId() == pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(daneJednegoAdresataOddzielonePionowymiKreskami)&&numerLiniiWPlikuTekstowym>1)
            {
                czyIstniejeAdresat = true;
                tymczasowyPlikTekstowy << endl << zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(adresat);
            }
            else if(numerLiniiWPlikuTekstowym == 1)
                tymczasowyPlikTekstowy << daneJednegoAdresataOddzielonePionowymiKreskami;

            else if(numerLiniiWPlikuTekstowym > 1)
                tymczasowyPlikTekstowy << endl << daneJednegoAdresataOddzielonePionowymiKreskami;

         numerLiniiWPlikuTekstowym++;
        }

        if (!czyIstniejeAdresat)
        {
            plikTekstowy.close();
        }
        plikTekstowy.close();
        tymczasowyPlikTekstowy.close();

        MetodyPomocnicze::usunOdczytywanyPlik(NAZWA_PLIKU_Z_ADRESATAMI);
        MetodyPomocnicze::zmienNazweTymczasowegoPlikuNaNazweOdczytywanegoPliku(nazwaTymczasowegoPlikuZAdresatami, NAZWA_PLIKU_Z_ADRESATAMI);
    }
}
