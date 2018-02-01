

#ifndef TIEDOSTON_LUKU_HH
#define TIEDOSTON_LUKU_HH

#include <tietorakenne.hh>
#include <iostream>
#include <regex>
#include <string>
#include <fstream>

using namespace std;

const string NOLLA_TAI_USEAMPIA_VALEJA_REGEX = "[[:space:]]*";
const string SANA_REGEX                      = "[[:alpha:]_]+";
const string KAKSOISPISTE_REGEX              = "\\:";

const string RIVI_REGEX = NOLLA_TAI_USEAMPIA_VALEJA_REGEX +
        SANA_REGEX +
        NOLLA_TAI_USEAMPIA_VALEJA_REGEX +
        KAKSOISPISTE_REGEX +
        NOLLA_TAI_USEAMPIA_VALEJA_REGEX +
        SANA_REGEX +
        NOLLA_TAI_USEAMPIA_VALEJA_REGEX;

bool lue_tiedosto(ifstream& tiedosto, Tietorakenne& polut, Pino& sallitut);


#endif
