def lukeminen():
    """Funktiossa luetaan tiedosto ja tallennetaan kulkukortit luokaksi.
    Lisäksi tallennetaan kulkukortit dict-rakenteeseen oikean kulkukortin
    kutsumisen helpottamiseksi."""
    try:
        tiedosto = open("kulkutiedot.txt", "r")
        oikeudet = {}

        for rivi in sorted(tiedosto):
            rivi = rivi.rstrip()
            osat = rivi.split(";")
            tunniste = osat[0]
            nimi = osat[1]
            alueet = osat[2].split(",")
            henkilö = Kulkukortti(tunniste, nimi, alueet)
            oikeudet[tunniste] = henkilö

        return oikeudet

    except IOError:
        print("Virhe: tiedostoa ei saa luettua.")


class Kulkukortti:

    def __init__(self, tunniste, nimi, alueet):
        """ Luokan rakentaja
        :param tunniste: henkilön tunniste (str)
        :param nimi: henkilön nimi (str)
        :param alueet: henkilön kulkuoikeudet(list)
        """
        pass  # TODO: Toteuta tähän luokan rakentaja
        self.__tunniste = tunniste
        self.__nimi = nimi
        self.__alueet = alueet

    def tulosta_tiedot(self):
        """ Funktiolla ei ole paluuarvoa. Se tulostaa kulkukortin
        tiedot näytölle täsmälleen seuraavassa muodossa:
        tunniste, nimi, kulkualueet: ka1,ka2,...,kaN
        eli esimerkiksi:
        567890, Siiri Siivooja, kulkualueet: F,K,P,R,S,T
        Huomaa, että pilkkujen ja kaksoispisteen perässä
        tulevien välilyöntien on oltava tulosteessa juuri
        saman logiikan mukaisesti kuin edellä ja kulkualueiden
        on tulostuttava tehtävänannon määräämässä järjestyksessä.
        TÄMÄN METODIN TOIMINTA TESTATAAN ERIKSEEN AUTOMAATTITESTISSÄ,
        JOTEN TULOSTUASUN MUUTTAMINEN JOHTAA TESTIEN EPÄONNISTUMISEEN.
        """
        pass  # TODO: Toteuta tämäkin metodi
        print(self.__tunniste, ", ", self.__nimi, ", kulkualueet: ", sep="",
              end="")
        for alue in range (len(self.__alueet)-1):
            print(self.__alueet[alue], sep="", end=",")
        print(self.__alueet[len(self.__alueet)-1])

    def anna_nimi(self):
        """ Palauttaa kulkukortille talletetun henkilön nimen."""
        pass # TODO: Toteuta tämäkin metodi
        return self.__nimi

    def anna_tunniste(self):
        """ Palauttaa kulkukortille tallennetun henkilön tunnisteen"""
        return self.__tunniste

    def anna_alueet(self):
        """ Palauttaa kulkukortilla annetun henkilön pääsyoikeudet"""
        return self.__alueet

    def tarkista_pääsy(self, ovi):
        """
        Tarkastaa pääseeko kulkukortilla ovesta.
        TÄMÄN METODIN TOIMINTA TESTATAAN ERIKSEEN AUTOMAATTITESTISSÄ,
        JOTEN PALUUARVOJEN MUUTTAMINEN JOHTAA TESTIEN EPÄONNISTUMISEEN.
        :param ovi: Ovi josta halutaan mennä läpi
        :return: True: ovi avautuu kulkukortille tallennetuilla oikeuksilla.
                 False: ovi ei avaudu kulkukortin oikeuksilla
        """
        pass  # TODO: Toteuta tämäkin metodi
        for alue in self.__alueet:
            if ovi[0:len(alue)] == alue and len(alue)<= len(ovi):
                return True
        return False

    def lisää_kulkualue(self, uusi_alue):
        """
        Funktio lisää uuden alueen kulkukortin oikeuksiin tehtävänannossa
        määritellyn säännön mukaisesti. Funktio ei saa tulostaa näytölle mitään.
        TÄMÄN METODIN TOIMINTA TESTATAAN ERIKSEEN AUTOMAATTITESTISSÄ.
        MIKÄLI SE EI TOIMI MÄÄRITTELYN MUKAISESTI, TESTIT EPÄONNISTUVAT.
        :param uusi_alue: Lisättävä kulkualue
        """
        pass  # TODO: Toteuta tämäkin metodi

        for alue in sorted(self.__alueet):
            if len(alue) < len(uusi_alue) and uusi_alue.startswith(alue):
                return

            elif alue == uusi_alue:
                return

            elif len(alue) > len(uusi_alue) and alue.startswith(uusi_alue):
                self.__alueet.remove(alue)

        self.__alueet.append(uusi_alue)


    def yhdistä_kulkukortti(self, toinen_kortti):
        """ Yhdistää toinen_kortti-parametrin sisältämät kulkuoikeudet
        käsiteltävänä olevalle kortille. Toimintalogiikka määritelty
        tehtävänannossa.
        :param toinen_kortti: Kulkukortti, jonka kanssa oikeudet yhdistetään
        """
        pass  # TODO: Toteuta tämäkin metodi
        for alue in sorted(toinen_kortti):
            i = 0
            for alue2 in sorted(self.__alueet):
                if len(alue2) < len(alue) and alue.startswith(alue2):
                    i += 1

                elif alue2 == alue:
                    i += 1

                elif len(alue2) > len(alue) and alue2.startswith(alue):
                    self.__alueet.remove(alue2)

            if i == 0:
                self.__alueet.append(alue)



def main():
    # TODO: Suorita tässä syötetiedoston lukeminen ja tietojen tallennus
    oikeudet = lukeminen()


    while True:
        rivi = input("komento> ")

        if rivi == "":
            break

        osat = rivi.split()
        käsky = osat[0]

        if käsky == "lista" and len(osat) == 1:
            pass # TODO: Suorita tässä käsky lista
            for henkilö in sorted(oikeudet):
                oikeudet[henkilö].tulosta_tiedot()

        elif käsky == "tiedot" and len(osat) == 2:
            tunniste = osat[1]
            # TODO: Suorita tässä käsky tiedot
            if tunniste in oikeudet:
                oikeudet[tunniste].tulosta_tiedot()
            else:
                print("Virhe: tuntematon tunniste.")

        elif käsky == "kulku" and len(osat) == 3:
            tunniste = osat[1]
            huone = osat[2]
            # TODO: Suorita tässä käsky kulku
            if tunniste in oikeudet:

                if oikeudet[tunniste].tarkista_pääsy(huone) is True:
                    print("Kortilla", tunniste, "(", oikeudet[tunniste].anna_nimi(), ") on kulkuoikeus huoneeseen", huone)
                else:
                    print("Kortilla", tunniste, "(", oikeudet[tunniste].anna_nimi(), ") ei kulkuoikeutta huoneeseen", huone)
            else:
                print("Virhe: tuntematon tunniste.")

        elif käsky == "lisää" and len(osat) == 3:
            tunniste = osat[1]
            alue = osat[2]
            # TODO: Suorita tässä käsky lisää
            if tunniste in oikeudet:
                oikeudet[tunniste].lisää_kulkualue(alue)
            else:
                print("Virhe: tuntematon tunniste.")

        elif käsky == "yhdistä" and len(osat) == 3:
            henkilö = osat[1]
            kortti = osat[2]
            # TODO: Suorita tässä käsky yhdistä
            if henkilö not in oikeudet:
                print("Virhe: tuntematon tunniste.")
            elif kortti not in oikeudet:
                print("Virhe: tuntematon tunniste.")
            else:
                alueet = oikeudet[kortti].anna_alueet()
                oikeudet[henkilö].yhdistä_kulkukortti(alueet)

        else:
            print("Virhe: Väärä syöte, yritä uudelleen")


main()
