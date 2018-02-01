// arttu.ansaharju@student.tut.fi


#ifndef TIETORAKENNE_HH
#define TIETORAKENNE_HH

#include <pino.hh>
#include <memory>
#include <string>
using namespace std;

class Tietorakenne
{
public:
    Tietorakenne();
    bool onko_tavara(string& tavara);
    bool lisaa_pari(string& tavara, string& vaatimus);
    void tulosta_vaatimukset(string& materiaali);
    bool onko_askarreltavissa(string& materiaali, Pino& reppu);

private:


    struct tavarat{
        string tavara;
        shared_ptr<tavarat> seuraavan_osoite;
        Pino vaatimukset;
    };
    shared_ptr<tavarat> ensimmaisen_osoite_;

};

#endif // TIETORAKENNE_HH
