// arttu.ansaharju@student.tut.fi


#include <iostream>
#include <tiedoston_luku.hh>
#include <tietorakenne.hh>
#include <pino.hh>
#include <kayttoliittyma.hh>
#include <string>

using namespace std;

//main-funktio kutsuu funktiota, joka lukee tiedoston.
//Jos edellisessa ei virheita, funktio kutsuu kayttöliittymaa

int main()
{

    Tietorakenne polut;
    Pino sallitut;
    string tiedoston_nimi;
    cout << "Syotetiedosto: ";
    getline(cin,tiedoston_nimi);
    ifstream tiedosto(tiedoston_nimi);
    if (not tiedosto){
        cout <<"Virhe: Tiedostoa ei saatu luettua" <<endl;
        return 1;
    }
    else if (not lue_tiedosto(tiedosto, polut, sallitut)){
        cout <<"Virhe: Tiedosto vaaran muotoinen:" <<endl;
        return 1;
    }
    else{
        cout << "Tuotantoketjut luettu onnistuneesti." <<endl;
        kayttoliittyma(polut, sallitut);
    }
}
