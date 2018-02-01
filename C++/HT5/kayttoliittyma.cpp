// arttu.ansaharju@student.tut.fi


#include <iostream>
#include <kayttoliittyma.hh>
#include <tietorakenne.hh>
#include <pino.hh>
using namespace std;

//parametreina tietorakenne johon tallennettu materiaalien
//vuorovaikututssuhteet ja luokan pino muotoinen taulukko
//johon tallennettu tunnetut materiaalit.

//Funktio kysyy kaytaajalta syotetta ja suorittaa komennon mukaiset
//toimenpiteet

void kayttoliittyma(Tietorakenne& polut, Pino& sallitut){
    regex rivi_reg(RIVI_REGEX_1);
    regex sana_reg(SANA_REGEX_1);
    string syoterivi;
    Pino reppu;
    cout << "testikayttoliittyma> ";
    while (getline(cin,syoterivi)){
        if (regex_match(syoterivi, rivi_reg)){
            sregex_iterator iter(syoterivi.begin(), syoterivi.end(), sana_reg);
            sregex_iterator end;
            string komento = iter->str();
            if (komento == "reppu"){
                reppu.tyhjenna();
                ++iter;
                if (iter == end){
                    cout <<"Reppu tyhjennetty." <<endl;
                }
                else {
                    while ( iter != end ) {
                        string esine = iter->str();
                        if (sallitut.onko_vaatimus(esine)){
                            if (not reppu.onko_vaatimus(esine)){
                                reppu.push(esine);
                            }
                            else{
                                reppu.tyhjenna();
                                cout <<"Virhe: sama esine useasti" <<endl;

                                break;
                            }
                        }
                        else{
                            reppu.tyhjenna();
                            cout <<"Virhe: tuntematon materiaali" <<endl;

                            break;
                        }
                        ++iter;
                    }
                    if (not reppu.empty()){
                        cout <<"Repun sisältö asetettu." <<endl;
                    }
                }

            }
            else if (komento == "tulostareppu"){
                ++iter;
                if (iter != end){
                    cout <<"Virhe: tuntematon komento." <<endl;
                }
                else{
                    reppu.print();
                }
            }
            else if (komento == "askarreltavissa"){
                ++iter;
                if (iter == end){
                    cout <<"Virhe: tuntematon komento." <<endl;
                }
                else{
                    string materiaali = iter->str();
                    ++iter;
                    if (iter != end){
                        cout <<"Virhe: tuntematon komento." <<endl;
                    }
                    else if (not sallitut.onko_vaatimus(materiaali)){
                        cout <<"Virhe :tuntematon materiaali." <<endl;
                    }
                    else if (not polut.onko_askarreltavissa(materiaali, reppu)){
                        cout <<"Ei ole askarreltavissa." <<endl;
                    }
                    else{
                        cout <<"On askarreltavissa." <<endl;
                    }
                }

            }
            else if (komento == "materiaalit"){
                ++iter;
                if (iter != end){
                    string materiaali = iter->str();
                    ++iter;
                    if (iter != end){
                        cout <<"Virhe: Tuntematon komento." <<endl;
                    }
                    else{
                        if (sallitut.onko_vaatimus(materiaali)){
                            polut.tulosta_vaatimukset(materiaali);
                        }
                        else{
                            cout <<"Virhe: tuntematon materiaali." <<endl;
                        }
                    }
                }
                else{
                    cout << "Virhe: ei materiaalia." <<endl;
                }

            }
            else if (komento == "loppu"){
                ++iter;
                if (iter != end){
                    cout << "Virhe: tuntematon komento." <<endl;
                }
                return;
            }
            else{
                cout << "Virhe: tuntematon komento"  <<endl;
            }
        }
        else{
            cout <<"Virhe: tuntematon komento" <<endl;
        }
        cout << "testikayttoliittyma> ";
    }
    return;
}
