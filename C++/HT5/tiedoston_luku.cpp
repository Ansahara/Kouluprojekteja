// arttu.ansaharju@student.tut.fi


#include "tiedoston_luku.hh"
#include "tietorakenne.hh"

//Kay tiedoston lapi rivi kerrallaan ja lisaa tietoparit tietorakenteeseen
//lisaksi lisaa jokaisen tiedostossa esiintyvan materiaalin Pinoon sallitut

bool lue_tiedosto(ifstream& tiedosto, Tietorakenne& polut, Pino& sallitut){
    regex rivi_reg(RIVI_REGEX);
    regex sana_reg(SANA_REGEX);
    regex tyhja_reg(NOLLA_TAI_USEAMPIA_VALEJA_REGEX);
    string rivi;

    while (getline(tiedosto, rivi) ) {
        if ( regex_match(rivi, rivi_reg) ) {
            // cout << "Syoterivi on oikean muotoinen." << endl;

            // sregex_iterator:in avulla merkkijonosta voidaan käydä
            // läpi kaikki osamerkkijonot, jotka sopivat rakentajan parametrina
            // annetun regular expressionin määräämään "muottiin".
            sregex_iterator iter(rivi.begin(), rivi.end(), sana_reg);

            // Oletusarvo sregex_iterator:illa on end-iteraattori, mikäli
            // rakentajalle ei anneta parametreja, jotka määräävät toisin.
            string tavara = iter->str();
            if (tavara != "#"){
                sallitut.push(tavara);
                ++iter;
                string vaatimus = iter->str();
                sallitut.push(vaatimus);
                if (not polut.lisaa_pari(tavara, vaatimus)){
                    return false;
                }
            }

        }
        else if (regex_match(rivi,tyhja_reg)){

        }
        else if (rivi.at(0) == '#'){

        }
        else{
            size_t merkki = rivi.find_first_not_of(' ');
            if (rivi[merkki] == '#'){

            }
            else{
                return false;
            }
        }
    }
    return true;
}
