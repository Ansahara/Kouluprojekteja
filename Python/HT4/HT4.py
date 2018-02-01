def avaus(tiedosto, kilpailijat, numerot):
    if kilpailijat == None:
        yritys = 1
    else:
        yritys = 2
    try:
        nimet = {}
        numero= []
        tiedosto = open(tiedosto, "r")
        for rivi in tiedosto:
            rivi = rivi.rstrip()
            rivi = rivi.split(":")
            if len(rivi) != 2:
                if yritys ==1:
                    print("Virhe: nimitiedoston rivien oltava muotoa nimi:kilpailunumero.")
                if yritys == 2:
                    print("Virhe: pistetiedoston rivien pitää olla muotoa kilpailunumero:pisteet.")
                return None, None
                break
            if yritys == 1:
                if rivi[1] in numero:
                    print("Virhe: tiedostossa samoja kilpailunumeroita.")
                    return None, None
                    break
                numero.append(rivi[1])
                nimet[rivi[0]] = rivi[1]
            elif yritys == 2:
                if rivi[1] == "" or rivi[0] == "":
                    print("Virhe: pistetiedoston rivien pitää olla muotoa kilpailunumero:pisteet.")
                    return None, None
                    break
                elif rivi[0] not in numerot:
                    print("Virhe: tiedostossa tuntematon kilpailunumero.")
                    return None, None
                    break
                elif rivi[1].isdigit() ==False:
                    print("Virhe: pisteiden on oltava kokonaislukuja.")
                    return None, None
                    break
                elif rivi[0] in nimet:
                    nimet[rivi[0]] = int(nimet[rivi[0]]) + int(rivi[1])
                else:
                    nimet[rivi[0]] = rivi[1]
        return nimet, numero

    except IOError:
        print("Virhe: tiedostoa", tiedosto, "ei voida lukea.")
        return None, None
    except ValueError:
        print("Virhe: nimitiedoston rivien oltava muotoa nimi:kilpailunumero.")
        return None, None

def järjestys(kilpailijat, pisteet):
    pistetulokset = {}
    for kilpailija in kilpailijat:
        for piste in pisteet:
            if kilpailijat[kilpailija] == piste:
                pistetulokset[pisteet[piste]] = kilpailija
    return pistetulokset

def main():
    nimi_tiedosto = input("Anna nimitiedoston nimi: ")
    kilpailijat, numero = avaus(nimi_tiedosto, None, None)
    if kilpailijat != None:
        piste_tiedosto = input("Anna pistetiedoston nimi: ")
        pisteet, pekka = avaus(piste_tiedosto, kilpailijat, numero)
        if pisteet != None:
            print("Seitsenottelun tulokset ovat:")
            pistetulokset = järjestys(kilpailijat, pisteet)
            i=1
            for tulos in sorted(pistetulokset, reverse=True):
                print(i, ". ", pistetulokset[tulos], " ", tulos, sep="")
                i+=1


main()