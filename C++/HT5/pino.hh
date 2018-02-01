// arttu.ansaharju@student.tut.fi


#ifndef PINO_HH
#define PINO_HH
#include <string>
#include <array>
#include <memory>




using namespace std;

class Pino {
  public:
    Pino();
    ~Pino();

    // Julkinen rajapinta käytännössä sama kuin luentomonisteen
    // esimerkissä.  Muutamia esteettisiä säätöjä tehty
    // ja size- ja print-metodit lisätty.
    bool empty() const;
    int  size() const;
    void push(string lisattava_arvo);
    bool pop(string& poistettu_arvo);
    void print() const;
    void print_1() const;
    bool onko_vaatimus(string vaatimus);
    void tyhjenna();
    bool onko_askarreltavissa(Pino& reppu);

  private:
    string* taulukko_;      // Osoitin dynaamisesti varatun taulukon alkuun.
    int  kokonaistila_ ; // Minkä kokoinen dynaamisesti varattu taulukko on.
    int  kaytetty_tila_; // Montako alkiota taulukosta on käytetty.
};

#endif // PINO_H
