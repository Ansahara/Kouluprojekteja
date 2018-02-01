// arttu.ansaharju@student.tut.fi


#include <iostream>
#include "pino.hh"
#include "algorithm"

using namespace std;

const int ALKUKOKO = 8;


Pino::Pino():
    taulukko_(new string[ALKUKOKO]),
    kokonaistila_(ALKUKOKO),
    kaytetty_tila_(0) {
}

Pino::~Pino() {
    delete [] taulukko_;
}

bool Pino::empty() const {
    return size() == 0;
}

int Pino::size() const {
    return kaytetty_tila_;
}

void Pino::print() const {
    for ( int i =0; i < size(); ++i ){
        if (taulukko_[i] != ""){
            cout <<taulukko_[i] <<endl;
        }
    }
}

void Pino::print_1() const {
    string* uusi_taulukko = new string[kokonaistila_];


    for ( int i = 0; i < size(); ++i ) {
        if (taulukko_[i] != ""){
            uusi_taulukko[i] = taulukko_[i];
        }
    }


    sort(uusi_taulukko, uusi_taulukko + kaytetty_tila_);
    for ( int i = 0; i < size(); ++i ) {
        if (uusi_taulukko[i] != ""){
            cout << uusi_taulukko[i] <<endl;
        }
    }

    delete [] uusi_taulukko;
}

void Pino::push(string lisattava_arvo) {
    if (not onko_vaatimus(lisattava_arvo)){
        // Jos pinosta loppuu tila (dynaamisesti varattu taulukko on täynnä),
        // varataan kaksi kertaa isompi taulukko ja siirretään vanhan taulukon
        // alkiot sinne, minkä jälkeen vanha taulukko voidaan vapauttaa.
        if ( size() == kokonaistila_ ) {
            string* uusi_taulukko = new string[2 * kokonaistila_];

            for ( int i = 0; i < size(); ++i ) {
                uusi_taulukko[i] = taulukko_[i];
            }

            delete [] taulukko_;

            taulukko_ = uusi_taulukko;
            kokonaistila_ = 2 * kokonaistila_;
        }

        // Tässä kohdassa dynaamisessa taulukossa on tilaa.  Joko sitä
        // oli alunperin tai taulukon kokoa on kasvatattu edellisessä
        // if-rakenteessa.

        taulukko_[kaytetty_tila_] = lisattava_arvo;
        ++kaytetty_tila_;
    }
}

bool Pino::pop(string& poistettu_arvo) {
    if ( empty() ) {
        return false;
    }

    --kaytetty_tila_;
    poistettu_arvo = taulukko_[kaytetty_tila_];

    return true;
}

//Funktio kay osoittimen avulla lapi koko taulukon ja tarkistaa
//onko parametrina annettu string tallennettuna taulukkoon.

bool Pino::onko_vaatimus(string vaatimus){
    string *taulukko_osoitin{nullptr};
    taulukko_osoitin = taulukko_;
    while ( taulukko_osoitin < taulukko_+kokonaistila_) {
        if (*taulukko_osoitin==vaatimus){
            return true;
        }
        ++taulukko_osoitin;
    }
    return false;
}


// Funktio luo uuden tyhjam taulukon joka on samnkokoinen kuin alkuperainen
//alkuperainen postetaan ja uusi merkitaan pino-olion taulukoksi
void Pino::tyhjenna(){
    string* uusi_taulukko = new string[kokonaistila_];
    delete [] taulukko_;
    taulukko_ = uusi_taulukko;
    kaytetty_tila_ = 0;
}


//tarkistaaloytyyko parametrina annetusta Pinosta kaikki
//materiaalit jotka on Pinossa joka kutsuu funktiota.
bool Pino::onko_askarreltavissa(Pino& reppu){
    string *taulukko_osoitin{nullptr};
    taulukko_osoitin = taulukko_;
    int i = 0;
    while ( taulukko_osoitin < taulukko_+kaytetty_tila_) {
        string *reppu_osoitin{nullptr};
        reppu_osoitin = reppu.taulukko_;
        while (reppu_osoitin < reppu.taulukko_+reppu.kaytetty_tila_){
            string tavara = *taulukko_osoitin;
            string tavara_1 = *reppu_osoitin;
            if (tavara == tavara_1){
                ++i;
            }
            /*else if (polku.onko_askarreltavissa(tavara, reppu)){
                ++i;
            }*/
            ++reppu_osoitin;

        }
        ++taulukko_osoitin;
    }
    if (i < kaytetty_tila_){
        return false;
    }
    else{
        return true;
    }
}
