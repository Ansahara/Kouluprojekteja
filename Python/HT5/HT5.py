# TIE-02100 Johdatus ohjelmointiin
# Valmiina annettu koodirunko harjoitustyö T5

import math



def lue_biometriikkarekisteri(tiedoston_nimi):
    """ Funktio lukee biometrisen informaation tehtävänannon määrämässä muodossa
    olevasta tiedostosta. Luettu informaatio jäsennellään ja talletetaan
    tietorakenteeseen, jonka harjoitustyön tekijä saa valita itse
    (ohjelmakoodissa tämä rakenne on nimetty muuttujaksi «tulos»).

    :param tiedoston_nimi: tiedoston nimi, josta biometrinen informaatio luetaan.
    :return: Palauttaa tietorakenteen, johon koko tiedosto on luettu ja tallennettu.
             Virhetilanteessa palauttaa arvon None.
    """

    # HUOMIOTAVAA:
    # (a) Kohtiin, joissa lukee TODO, ohjelmoijan on täytettävä jotain
    #     valitun tietorakenteen käsittelyyn liittyvää (kommenteissa vihjeitä).
    # (b) Tietorakenteen, jonka funktio palauttaa, on oltava jonkinlainen
    #     yhdistelmä sisäkkäisiä list- ja/tai dict-rakenteita. Se on koko
    #     harjoitustyön tavoite: sisäkkäisten tietorakenteiden käsittely.

    # TODO: Alustus: minkälaiseen rakenteeseen tiedoston sisältämä informaatio
    # olisi järkevää tallentaa?
    tulos = []

    aiemmin_käsitellyt_passit = []

    try:
        with open(tiedoston_nimi, mode="r") as tiedosto_olio:
            for rivi in tiedosto_olio:
                lista = []
                rivi = rivi.rstrip()

                kentät = rivi.split(';')

                if len(kentät) != 8:
                    print("Virhe: syötetiedoston rivillä väärä määrä kenttiä:")
                    print("'", rivi, "'", sep="")
                    return None

                # Muutetaan listan lopussa viisi biometrista
                # arvoa merkkijonosta desimaaliluvuiksi.
                for indeksi in range(3, 8):
                    kentät[indeksi] = float(kentät[indeksi])
                    if not (0 <= kentät[indeksi] <= 3.0):
                        print("Virhe: tiedostossa virheellinen arvo rivillä:")
                        print("'", rivi, "'", sep="")
                        return None

                nimi = kentät[0] + ", " + kentät[1]
                passi = kentät[2]
                biometriikka = kentät[3:]

                if passi in aiemmin_käsitellyt_passit:
                    print("Virhe: passi nro.", passi, "toistuu.")
                    return None
                else:
                    aiemmin_käsitellyt_passit.append(passi)

                # TODO: Miten edellä luettu henkilön informaatio talletetaan
                # funktion alussa valittuun rakenteeseen?

                lista.append(nimi)
                lista.append(passi)
                lista.append(biometriikka)

                tulos.append(lista)
        return tulos

    except FileNotFoundError:
        print("Virhe: tiedostoa", tiedoston_nimi, "ei saa avattua.")

    except ValueError:
        print("Virhe: tiedostossa ei-numeerinen biomeriikka-arvo rivillä:")
        print("'", rivi, "'", sep="")

    return None


def suorita_samat(biorekisteri):
    # TODO: Toteuta metodin toiminnallisuus tehtävänannon mukaisesti.
    pass
    i = 1
    nimet = []
    kirjoitettu = 0

    for vertailtava in biorekisteri:
        nimet.append(vertailtava[0])
        eka = 0
        for verrattava in biorekisteri:
            if verrattava[0] not in nimet:
                tulos = 0
                for i in range(5):
                    rivi = (vertailtava[2][i]-verrattava[2][i])**2
                    tulos += rivi
                if math.sqrt(tulos) <= 0.1:
                    kirjoitettu = 1
                    nimet.append(verrattava[0])
                    if eka == 0:
                        print("Mahdollisesti samat henkilöt:")
                        for i in range(2):
                            print(vertailtava[i], end=";")
                        määrä = 0
                        for rivi in vertailtava[2]:
                            if määrä <4:
                                print("{:.2f}".format(rivi), end=";")
                                määrä += 1
                            else:
                                print("{:.2f}".format(rivi), end="")
                        print()
                    for i in range(2):
                        print(verrattava[i], end=";")
                    määrä = 0
                    for rivi in verrattava[2]:
                        if määrä <4:
                            print("{:.2f}".format(rivi), end=";")
                            määrä += 1
                        else:
                            print("{:.2f}".format(rivi), end="")
                    print()
                    eka += 1
        if eka !=0:
            print()
    if kirjoitettu !=1:
        print("Ei samoja henkilöitä.")






def suorita_haku(biorekisteri):
    # TODO: Toteuta metodin toiminnallisuus tehtävänannon mukaisesti.
    pass
    eka = 0
    i=0
    while i != 1:
        biot = input("Syötä 5 mittausarvoa puolipisteellä eroteltuna: ")
        biot = biot.split(";")
        if len(biot) != 5:
            print("Virhe: väärä määrä syötteitä: yritä uudelleen.")
        else:
            try:
                for rivi in biot:
                    rivi = float(rivi)
                i = 1
            except ValueError:
                print("Virhe: syötä vain desimaalilukuja: yritä uudelleen.")

    for i in range(5):
        biot[i] = float(biot[i])

    pituus = len(biorekisteri)

    for j in range(pituus):
        tulos = 0
        for i in range(5):
            rivi = (float(biorekisteri[j][2][i]) - biot[i])**2
            tulos += rivi
        if math.sqrt(tulos) <= 0.1:
            if eka == 0:
                print("Löytyi epäiltyjä:")
            for i in range(2):
                print(biorekisteri[j][i], end=";")
            määrä = 0
            for rivi in biorekisteri[j][2]:
                if määrä <4:
                    print("{:.2f}".format(rivi), end=";")
                    määrä += 1
                else:
                    print("{:.2f}".format(rivi), end="")
            print()
            eka += 1

    if eka == 0:
        print("Ei löytynyt epäiltyjä.")

    print()


def main():

    # Ohjelmoijan tehtävänänä on toteuttaa funktiot «suorita_samat» ja
    # ja «suorita_haku», joita valmiissa koodissa on kutsuttu.
    # Saattaa olla järkevää toteuttaa myös muita apufunktioita niiden avuksi.

    # HUOMIOTAVAA:
    # Tätä funktiota ei ole tarkoitus muokata.

    rekisteritiedosto = input("Syötä rekisteritiedoston nimi: ")

    biometriikkarekisteri = lue_biometriikkarekisteri(rekisteritiedosto)
    if biometriikkarekisteri is not None:

        while True:
            komento = input("komento [haku/samat/<enter>] ")
            if komento == "":
                return
            elif komento == "samat":
                suorita_samat(biometriikkarekisteri)
            elif komento == "haku":
                suorita_haku(biometriikkarekisteri)
            else:
                print("Virhe: tuntematon komento '", komento,
                      "': yritä uudelleen.", sep="")

main()
