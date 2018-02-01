//Arttu Ansaharju
//arttu.ansaharju@student.tut.fi


#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Tämän luokan julkista rajapintaa voisi parantaa huomattavasti,
// jos miettisi asiaa hiukankaan pidemmälle.  Yksinkertaisena
// esimerkkinä STL-säiliön käytöstä luokan private-osassa tämä
// kuitenkin on riittävä.
class Splitter {
  public:
    Splitter();

    // Asetetaan merkkijono, joka halutaan paloitella.
    void aseta_paloiteltavava_merkkijono(const string& mjono);

    // Paloitellaan merkkijono parametrina annetun erotinmerkin
    // kohdalta osiin. Paluuarvona tieto siitä, montako kenttää
    // rivillä oli.  Parametri ohita_tyhjat on lisäys
    // tehtävänantoon. Jos ohita_tyhjat- parametrin arvo on true,
    // paloittelun tuloksena mahdollisesti syntyvät tyhjät kentät
    // jätetään pois lopputuloksesta.  Tämä on hyödyllinen ominaisuus,
    // jos halutaan jakaa merkkijono sanoiksi, mutta ei olla täysin
    // varmoja siitä, onko sanojen välissä yksi vai useampia
    // välilyöntejä:  paloittelijaolio.paloittele(' ', true);
    int paloittele(char erotinmerkki, bool ohita_tyhjat = false);

    // Kun merkkijono on paloiteltu, tällä metodilla
    // voidaan pyytää Splitter-oliolta tietty kenttä.
    // Oletetaan että kentät on numeroitu vasemmalta
    // oikealle alkaen nollasta.
    string hae_kentta(int kentan_numero) const;

  private:
    // Lähtötieto: tätä merkkijonoa paloittele-metodi pätkiin osiin.
    string paloiteltava_;

    // onko_paloittelu_suoritettu_-muuttujan arvo on true, mikäli
    // paloittele-metodia on kutsuttu sen jälkeen, kun uusi
    // paloiteltava merkkijono viimeksi asetettiin
    // aseta_paloiteltavava_merkkijono-metodilla.
    bool onko_paloittelu_suoritettu_;

    // paloittele-metodi tallentaa tuloksen tähän vektoriin, niin
    // että kun merkkijono on kerran paloiteltu, sen kenttiin päästään
    // käsiksi nopeasti.
    vector<string> kentat_;
};

Splitter::Splitter():
    paloiteltava_(""), onko_paloittelu_suoritettu_(false), kentat_( {} ) {
}

void Splitter::aseta_paloiteltavava_merkkijono(const string& mjono) {
    paloiteltava_ = mjono;

    // onko_paloittelu_suoritettu_-jäsenmuuttuja pitää kirjaa siitä,
    // onko paloittele-metodia kutsuttu sen jälkeen, kun paloiteltava
    // merkkijono on viimeksi asetettu.  Käytännössä tämä tarkoittaa sitä,
    // onko kentat_-vektorin arvo ajan tasalla.
    onko_paloittelu_suoritettu_ = false;
}

int Splitter::paloittele(char erotinmerkki, bool ohita_tyhjat) {
    // Tyhjennetään kentat_-vektori siltä varalta, että samaa oliota
    // on jo aiemmin käytetty jokin toisen merkkijonon paloitteluun,
    // minkä seurauksena vektorissa on jotain vanhaa tietoa.
    kentat_.clear();

    // alkukohta pitää kirjaa siitä, missä kohdassa merkkijonoa
    // on seuraava kenttä, jota ei vielä ole siirretty kentat_-vektoriin.
    string::size_type alkukohta = 0;
    string kentan_teksti;

    while ( true ) {
        // loppukohtaan etsitään find-metodilla, missä kohdassa
        // on ensimmäinen alkukohdan jälkeen tuleva erotinmerkki.
        string::size_type loppukohta;

        loppukohta = paloiteltava_.find(erotinmerkki, alkukohta);

        // Jos alkukohdan perästä ei löydy erotinmerkkiä, merkkojonossa
        // on enää yksi kenttä jäljellä (viimeinen kenttä, jonka perässä
        // ei ole erotinmerkkiä).  Käsitellään se erikseen silmukän perässä.
        if ( loppukohta == string::npos ) {
            break;
        }

        // Otetaan talteen kentän sisältö indeksien
        // alkukohta ja loppukohta välistä.
        kentan_teksti = paloiteltava_.substr(alkukohta, loppukohta - alkukohta);

        // Tyhjiä kenttiä ei tallenneta, mikäli parametri
        // ohita_tyhjat on true.
        if ( not (ohita_tyhjat and kentan_teksti.empty()) ) {
            kentat_.push_back(kentan_teksti);
        }

        // Siirretään alkukohta seuraavan käsittelemättömän
        // kentän ensimmäiseen merkkiin.
        alkukohta = loppukohta + 1;
    }

    // Otetaan viimeisen erotinmerkin perässä oleva teksti talteen.
    // koska se on rivin viimeinen kenttä.
    kentan_teksti = paloiteltava_.substr(alkukohta);

    if ( not (ohita_tyhjat and kentan_teksti.empty()) ) {
        kentat_.push_back(kentan_teksti);
    }

    // Kirjataan ylös, että paloittelu on suoritettu.
    onko_paloittelu_suoritettu_ = true;

    return kentat_.size();
}

string Splitter::hae_kentta(int kentan_numero) const {
    // Mitä tämän funktion pitäisi tehdä virhetilanteessa?
    // Eli jos esimerkiksi yritetään hakea kenttä ennen kuin
    // paloiteltava_ on pistetty osiin ja talletettu
    // kentat_-vektoriin. Periaatteessa funktio voisi aiheuttaa
    // poikkeuksen throw-käskyllä. Mutta koska se ei vielä ole tuttu,
    // kikkaillaan ja asetetaan kentan_numero käsin niin suureksi,
    // että vektoria indeksoiva at-operaatio tuottaa poikkeuksen.
    // Häpeämätöntä kikkailua.
    if ( not onko_paloittelu_suoritettu_ ) {
        // Alkioiden lukumäärä on yhtä suurempi kuin suurin
        // sallittu indeksin arvo.
        kentan_numero = kentat_.size();
    }

    // Jos poikkeusten käyttö olisi hanskassa, oikeaoppisesti edellinen menisi:
    //
    //    #include <stdexcept>  // Ohjelmakoodin alkuun
    //    ···
    //    if ( not onko_paloittelu_suoritettu_ ) {
    //        throw out_of_range("paloittelua ei ole suoritettu")
    //    }

    // Jos yritetään hakea kenttää, jota ei ole olemassa: siis
    // kentan_numero on suurempi tai yhtäsuuri kuin kentat_-vektorin
    // alkioiden määrä, seuraava at-operaatio tuottaa poikkeuksen.
    // Luokan käyttäjän vastuulle siis jää huolehtia siitä, että hän
    // yrittää käsitellä vain olemassa olevia kenttiä.  Kenttien
    // lukumäärä saadaan paloittele-metodin paluuarvona.
    return kentat_.at(kentan_numero);
}

//-----------------------------------------------------------------------------


class pankkitili {
    public:
        pankkitili();
        pankkitili(string tilinro, double saldo, int asiakasnro);

        void tulosta() const;
        void pano(double summa);
        bool otto(double summa);
        void aseta(string tilinumero, double saldo, int asiakasnro);

    private:
        string tilinro_;
        double saldo_;
        int asiakasnro_;
};

pankkitili::pankkitili(){
    tilinro_="FI0000000000";
    saldo_=00.00;
    asiakasnro_=0000000;
}

pankkitili::pankkitili(string tilinro, double saldo, int asiakasnro){
    tilinro_=tilinro;
    saldo_=saldo;
    asiakasnro_=asiakasnro;
}

void pankkitili::pano(double summa){
        saldo_=saldo_+summa;
}

bool pankkitili::otto(double summa){
    if (summa <= saldo_){
        saldo_=saldo_-summa;
        return true;
    }
    else{
        return false;
    }
}

void pankkitili::tulosta() const{
    cout <<"Tilinumero: " <<tilinro_ <<endl
         << right << setprecision(2) << fixed
         <<"Saldo: " <<saldo_ <<endl
         <<"Asiakasnumero: " <<asiakasnro_ <<endl;
}

// Voitaisiin hoitaa rakentajalla, mutta en saanut siten ohjelmaa toimimaan
void pankkitili::aseta(string tilinumero, double saldo, int asiakasnro){
    tilinro_ = tilinumero;
    saldo_ = saldo;
    asiakasnro_ = asiakasnro;
}

//-----------------------------------------------------------------------------------
//Funktioita jotka lukevat tarvittavat syötteet luokan metodeita varten.
//Samat funktiot kutsuvat metodia.

void pano(pankkitili& tili, string& tilinro){
    cout <<"Syötä rahamäärä: ";
    double summa=0;
    cin >> summa;
    cin.ignore();
    if (summa >= 0){
        tili.pano(summa);
        cout <<"Pano suoritettu tilille " <<tilinro <<"." <<endl;
    }
    else{
        cout <<"Virhe: Syotettavan rahamaaran oltava posiitivinen." <<endl;
    }
}

void otto(pankkitili& tili, string& tilinro){
    cout <<"Syötä rahamäärä: ";
    double summa=0;
    cin >> summa;
    cin.ignore();
    if (summa >= 0){
        if (tili.otto(summa) == true){
            cout <<"Otto suoritettu tililtä " <<tilinro <<"." <<endl;
        }
        else{
            cout<<"Virhe: Tilin saldon oltava positiivinen" <<endl;
        }
    }
    else{
        cout <<"Virhe: Syotettavan rahamaaran oltava positiivinen." <<endl;
    }
}

void tilisiirto(pankkitili& tili, pankkitili& tili2){
    cout <<"Syötä siirtomäärä: ";
    double summa=0;
    cin >> summa;
    cin.ignore();
    if (summa >= 0){
        if (tili.otto(summa) == true){
            tili2.pano(summa);
        }
        else{
            cout<<"Virhe: Tilin saldon oltava positiivinen." <<endl;
        }
    }
    else{
        cout <<"Virhe: Syotettavan rahamaaran oltava positiivinen." <<endl;
    }
}

void aseta(pankkitili& tili, string tilino){
    cout <<"Syötä tilinumero: ";
    string tilinro;
    getline(cin,tilinro);
    cout <<"Syötä saldo: ";
    double saldo=0;
    cin >> saldo;
    if (saldo >0){
        cout <<"Syötä asiakasnumero: ";
        int asiakasnro=0;
        cin >> asiakasnro;
        cin.ignore();
        tili.aseta(tilinro, saldo, asiakasnro);
        cout <<"Tilin " <<tilino <<" tiedot asetettu." <<endl;
    }
    else{
        cout <<"Virhe: Syotettavan saldon oltava positiivinen." <<endl;
    }
}

//-----------------------------------------------------------------------

//Funktiolla haetaan komennon mukainen tili,
//jotta alemmissa funktioissa voidaan käsitellä oikeaa tiliä.
int hae_tili(string& tilinro){
    if (tilinro == "1"){
        return 0;
    }
    else if (tilinro == "2"){
        return 1;
    }
    else if (tilinro == "3"){
        return 2;
    }
    else{
        return 3;
    }
}

//funktiot tarkistavat että tapahtuma jota yritetään suorittaa on mahdollinen
//ja hakevat oikean tilin operoitavaksi
void tulosta(int& kenttia, Splitter& syote, vector<pankkitili>& tilit){
    if (kenttia != 2){
        cout << "Virhe: Virheellinen komento." <<endl;
    }
    else{
        string tilinro = syote.hae_kentta(1);
        if (hae_tili(tilinro) == 3){
            cout<<"Virhe: Tilia ei ole olemassa" <<endl;
        }
        else{
            pankkitili tili = tilit.at(hae_tili(tilinro));
            tili.tulosta();
        }
    }
}

void pano(int& kenttia, Splitter& syote, vector<pankkitili>& tilit){
    if (kenttia != 2){
        cout << "Virhe: Virheellinen komento." <<endl;
    }
    else{
        string tilinro = syote.hae_kentta(1);
        if (hae_tili(tilinro) == 3){
            cout<<"Virhe: Tilia ei ole olemassa" <<endl;
        }
        else{
            pano(tilit.at(hae_tili(tilinro)), tilinro);
        }
    }
}

void otto(int& kenttia, Splitter& syote, vector<pankkitili>& tilit){
    if (kenttia != 2){
        cout << "Virhe: Virheellinen komento." <<endl;
    }
    else{
        string tilinro = syote.hae_kentta(1);
        if (hae_tili(tilinro) == 3){
            cout<<"Virhe: Tilia ei ole olemassa" <<endl;
        }
        else{
            otto(tilit.at(hae_tili(tilinro)),tilinro);
        }
    }
}

void tilisiirto(int& kenttia, Splitter& syote, vector<pankkitili>& tilit){
    if (kenttia != 3){
        cout << "Virhe: Virheellinen komento." <<endl;
    }
    else{
        string tilinro = syote.hae_kentta(1);
        if (hae_tili(tilinro) == 3){
            cout<<"Virhe: Tilia ei ole olemassa" <<endl;
        }
        else{
            string tilinro_2 = syote.hae_kentta(2);
            if (hae_tili(tilinro) == 3){
                cout<<"Virhe: Tilia ei ole olemassa" <<endl;
            }
            else{
                tilisiirto(tilit.at(hae_tili(tilinro)),tilit.at(hae_tili(tilinro_2)));
            }
        }
    }
}

void aseta(int& kenttia, Splitter& syote, vector<pankkitili>& tilit){
    if (kenttia != 2){
        cout << "Virhe: Virheellinen komento." <<endl;
    }
    else{
        string tilinro = syote.hae_kentta(1);
        if (hae_tili(tilinro) == 3){
            cout<<"Virhe: Tilia ei ole olemassa" <<endl;
        }
        else{
            aseta(tilit.at(hae_tili(tilinro)), tilinro);
        }
    }
}


//funktio paloittelee komennon ja kutsuu oikeata funktiota komennon mukaan
void syota_komento(){
    pankkitili tili1;
    pankkitili tili2;
    pankkitili tili3;
    vector<pankkitili> tilit = {tili1,tili2,tili3};
    while (true){
        cout <<"pankkitilitesti> ";
        string komento;
        getline(cin,komento);
        Splitter syote;
        syote.aseta_paloiteltavava_merkkijono(komento);
        int kenttia = syote.paloittele(' ');
        komento = syote.hae_kentta(0);

        if (komento == "exit"){
            break;
        }
        else if (kenttia == 1){
            cout<<"Virhe: Virheellinen komento." <<endl;
        }
        else if (komento == "tulosta"){
            tulosta(kenttia, syote, tilit);
            }
        else if (komento == "aseta"){
            aseta(kenttia, syote, tilit);
        }
        else if (komento == "pano"){
            pano(kenttia, syote, tilit);
        }
        else if (komento == "otto"){
            otto(kenttia, syote, tilit);
        }
        else if (komento == "tilisiirto"){
            tilisiirto(kenttia, syote, tilit);
        }
        else{
            cout<<"Virhe: virheellinen komento" <<endl;
        }
    }
}


int main()
{
    syota_komento();
    cout <<endl <<"Näkemiin" <<endl <<endl;
}
