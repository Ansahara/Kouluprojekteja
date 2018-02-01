// arttu.ansaharju@student.tut.fi
// 246341

#ifndef KAYTTOLIITTYMA_HH
#define KAYTTOLIITTYMA_HH

#include <regex>
#include <tietorakenne.hh>
#include <pino.hh>
using namespace std;

const string USEAMPIA_VALEJA_REGEX = "[[:space:]]*";
const string VALI_REGEX = "[[:space:]]+";
const string SANA_REGEX_1    = "[[:alpha:]_]+";

const string RIVI_REGEX_1 = USEAMPIA_VALEJA_REGEX +
        SANA_REGEX_1 +
        "(" +
        VALI_REGEX +
        SANA_REGEX_1 +
        ")*" +
        USEAMPIA_VALEJA_REGEX;

void kayttoliittyma(Tietorakenne& polut, Pino& sallitut);



#endif // KAYTTOLIITTYMA_HH
