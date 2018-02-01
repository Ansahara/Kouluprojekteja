// arttu.ansaharju@student.tut.fi


#include "tietorakenne.hh"
#include <algorithm>

Tietorakenne::Tietorakenne():ensimmaisen_osoite_{nullptr}{
}


//Luo uuden struct rakenteen ja lisaa sinne tavaran ja sen taulukkoon
//vaatimuksen.
bool Tietorakenne::lisaa_pari(string &tavara, string &vaatimus){
    shared_ptr<tavarat> uuden_osoite{
        new tavarat{tavara, nullptr}};
    if ( ensimmaisen_osoite_ == nullptr ) {
        ensimmaisen_osoite_ = uuden_osoite;
        uuden_osoite->vaatimukset.push(vaatimus);
    }
    else {
        if (not onko_tavara(tavara)){
            uuden_osoite->seuraavan_osoite = ensimmaisen_osoite_;
            ensimmaisen_osoite_ = uuden_osoite;
            uuden_osoite->vaatimukset.push(vaatimus);
        }
        else{
            shared_ptr<tavarat> apu_osoite{ensimmaisen_osoite_};
            while (apu_osoite->tavara != tavara){
                apu_osoite = apu_osoite->seuraavan_osoite;
            }
            if (not apu_osoite->vaatimukset.onko_vaatimus(vaatimus)){
                apu_osoite->vaatimukset.push(vaatimus);
            }
            else{
                return false;
            }
        }
    }
    return true;
}


//tarkistaa onko parametrina annetulla tavaralla vaatimuksia
bool Tietorakenne::onko_tavara(string &tavara){
    shared_ptr<tavarat> apu_osoite{ensimmaisen_osoite_};
    while (apu_osoite != nullptr){
        if (apu_osoite->tavara == tavara){
            return true;
        }
        apu_osoite = apu_osoite->seuraavan_osoite;
    }
    return false;
}

//tulostaa parametrina annetun materiaalin suorat edeltajat
void Tietorakenne::tulosta_vaatimukset(string &materiaali){
    shared_ptr<tavarat> apu_osoite{ensimmaisen_osoite_};
    while(apu_osoite != nullptr){
        if (apu_osoite->tavara == materiaali){
            apu_osoite->vaatimukset.print_1();
        }
        apu_osoite = apu_osoite->seuraavan_osoite;
    }
}

//tutkii onko parametrina annettu materiaali mahdollista valmistaa
bool Tietorakenne::onko_askarreltavissa(string& materiaali, Pino& reppu){
    if (reppu.onko_vaatimus(materiaali)){
        return true;
    }
    if (this->onko_tavara(materiaali)){
        Pino tarvittavat_materiaalit;
        shared_ptr<tavarat> apu_osoite{ensimmaisen_osoite_};
        while(apu_osoite->tavara != materiaali){
            apu_osoite = apu_osoite->seuraavan_osoite;
        }
        tarvittavat_materiaalit = apu_osoite->vaatimukset;
        return tarvittavat_materiaalit.onko_askarreltavissa(reppu);
    }
    return false;
}
