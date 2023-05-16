/*Egy bútoráruház termékeit(név, ár) egy irányban láncolt lista tárolja.Fejezze be az alábbi függvényt, melynek célja véletlenszerûen elõállítani egy legfeljebb 15 (MAX_DB szimbolikus állandóval adott) elembõl álló láncolt listát. (Tehát az elemek száma is véletlenszerû, lehet akár 0 is.)

Ezen kívül véletlenszerûen kell meghatározni a termékek nevét, mely csak Asztal, Szek, Kanape, Kisagy, Konyhapult, Allolampa, Fogas, Komod, Tukor, Vaza, Dohanyzoasztal és Hintaszek lehet.Azonos nevû termékbõl több is elõfordulhat, és nem kötelezõ mindegyiknek szerepelnie.

Hasonlóan véletlenszerûen kell meghatározni a termékek árát, ami legfeljebb 1000000 (MAX_AR szimbolikus állandóval adott), és nemnegatív egész érték.

A függvény visszatérési értéke a létrehozott lista legelsõ elemének címe(a horgony).

Feltételezheti, hogy a véletlenszám generátort a függvény hívása elõtt már inicializálták.

Szintaktikai hiba esetén a fordító által jelzett sor számából vonjon ki 20 - at, hogy megkapja a szerkesztõben olvasható sorszámot!

A lista egy elemének szerkezete a következõ :

struct termek {
    string nev;
    int ar;
    termek* kov;
};*/


#include <iostream>
#include <string>
#include <cstdlib>

#define MAX_DB 15
#define MAX_AR 1000000

using namespace std;

struct termek {
    string nev;
    int ar;
    termek* kov;
};

termek* termeketGeneral() {
    string nevek[] = { "Asztal", "Szek", "Kanape", "Kisagy", "Konyhapult", "Allolampa", "Fogas", "Komod", "Tukor", "Vaza", "Dohanyzoasztal", "Hintaszek" };
    int nevekMeret = sizeof(nevek) / sizeof(nevek[0]);

    termek* fej = nullptr;
    termek* akt = nullptr;

    int darab = rand() % (MAX_DB + 1);

    for (int i = 0; i < darab; i++) {
        termek* ujTermek = new termek;
        ujTermek->nev = nevek[rand() % nevekMeret];
        ujTermek->ar = rand() % (MAX_AR + 1);
        ujTermek->kov = nullptr;

        if (fej == nullptr) {
            fej = ujTermek;
            akt = ujTermek;
        }
        else {
            akt->kov = ujTermek;
            akt = ujTermek;
        }
    }

    return fej;
}


/*Egy bútoráruház termékeit (név, ár) egy irányban láncolt lista tárolja. Fejezze be az alábbi függvényt, melynek célja törölni a horgony paraméterrel adott láncolt listából minden olyan elemet, melyben a termék neve nev!

A függvény visszatérési értéke a módosított lista legelsõ elemének címe (a horgony). Ez változhat, ha a listának már a legelsõ elemét is törölni kell.

Szintaktikai hiba esetén a fordító által hibásnak jelzett sor számából vonjon ki 20-at, hogy megkapja a szerkesztõben olvasható valós sorszámot.

A lista egy elemének szerkezete a következõ:

struct termek {
  string nev;
  int ar;
  termek* kov;
};*/
termek* torol(termek* horgony, string nev) {
    // Kezdetben az elsõ elemre mutat a 'aktualis' pointer
    termek* aktualis = horgony;
    termek* elozo = nullptr;

    // Amíg van még elem a listában
    while (aktualis != nullptr) {
        // Ha a termék neve egyezik a keresett nevével
        if (aktualis->nev == nev) {
            // Ha az elsõ elemet kell törölni
            if (elozo == nullptr) {
                // Az 'aktualis' lesz az új horgony
                horgony = aktualis->kov;
            }
            else {
                // Különben az 'elozo' mutatóját állítjuk az 'aktualis' következõ elemére
                elozo->kov = aktualis->kov;
            }

            // Elmentjük az 'aktualis' mutatóját, majd felszabadítjuk a memóriaterületet
            termek* torlendo = aktualis;
            aktualis = aktualis->kov;
            delete torlendo;
        }
        else {
            // Ha nem kell törölni, lépünk a következõ elemre
            elozo = aktualis;
            aktualis = aktualis->kov;
        }
    }

    return horgony;
}


/*Egy bútoráruház termékeit (név, ár) egy irányban láncolt lista tárolja. Fejezze be az alábbi függvényt, melynek célja létrehozni a horgony paraméterrel azonosított lista alapján egy új, szûrt listát, melyben csak olyan termékek szerepelnek, melyek ára a megadott min és max értékek közé esik (ezeket is beleértve).

Ügyeljen rá, hogy az eredeti és szûrt listák semmiképpen se osztozzanak közös adatterületeken! Másképp fogalmazva, az eredeti listának sértetlennek kell maradnia.

A függvény visszatérési értéke a létrehozott új, szûrt lista legelsõ elemének címe (az új lista horgonya).

Szintaktikai hiba esetén a fordító által jelzett sor számából vonjon ki 20-at, hogy megkapja a szerkesztõben olvasható sorszámot!

A lista egy elemének szerkezete a következõ:

struct termek {
  string nev;
  int ar;
  termek* kov;
};*/

termek* szures(const termek* horgony, int min, int max) {
    termek* szurtHorgony = nullptr;
    termek* szurtElozo = nullptr;
    const termek* aktualis = horgony;

    // Végigmegyünk az eredeti listán
    while (aktualis != nullptr) {
        // Ellenõrizzük az árat
        if (aktualis->ar >= min && aktualis->ar <= max) {
            // Létrehozzuk az új szûrt elemet
            termek* ujTermek = new termek;
            ujTermek->nev = aktualis->nev;
            ujTermek->ar = aktualis->ar;
            ujTermek->kov = nullptr;

            // Ha ez az elsõ elem a szûrt listában
            if (szurtHorgony == nullptr) {
                szurtHorgony = ujTermek;
                szurtElozo = ujTermek;
            }
            else {
                // Különben beállítjuk az elõzõ elem következõ mutatóját
                szurtElozo->kov = ujTermek;
                szurtElozo = ujTermek;
            }
        }

        // Lépünk a következõ elemre az eredeti listában
        aktualis = aktualis->kov;
    }

    return szurtHorgony;
}

/*Egy bútoráruház termékeit (név, ár) egy irányban láncolt lista tárolja. Fejezze be az alábbi függvényt, melynek célja 50%-os kedvezményt adni a legdrágább termékbõl! Módosítsa a termék árát a felére (lefelé kerekítve)! Ha több azonos árú legdrágább termék létezik, csak a listában elsõként tárolt legdrágább termék árából adjon kedvezményt!

A függvény paramétere a lista elsõ elemének címe (a horgony).

Szintaktikai hiba esetén a fordító által jelzett sor számából vonjon ki 20-at, hogy megkapja a szerkesztõben olvasható sorszámot!

A lista egy elemének szerkezete a következõ:

struct termek {
  string nev;
  int ar;
  termek* kov;
};*/

void akcio(termek* elem) {
    if (elem == nullptr) {
        // Ha az elem nullpointer, nincs mit módosítani
        return;
    }

    termek* legdragabb = elem;
    termek* aktualis = elem->kov;

    // Keresés a legdrágább termékig
    while (aktualis != nullptr) {
        if (aktualis->ar > legdragabb->ar) {
            legdragabb = aktualis;
        }
        aktualis = aktualis->kov;
    }

    // 50%-os kedvezmény az árra
    legdragabb->ar = legdragabb->ar / 2;
}

/*Egy bútoráruház termékeit (név, ár) egy irányban láncolt lista tárolja. Fejezze be az alábbi függvényt, melynek célja hozzáfûzni egy új listaelemet a horgony-nyal azonosított lista végéhez! Ennek az új terméknek a nevét a nev, árát az ar paraméter adja meg.

A függvény visszatérési értéke a létrehozott lista legelsõ elemének címe (a horgony). A horgony megváltozhat, ha az eredeti lista üres volt a hozzáfûzés elõtt.

Szintaktikai hiba esetén a fordító által jelzett sor számából vonjon ki 20-at, hogy megkapja a szerkesztõben olvasható sorszámot!

A lista egy elemének szerkezete a következõ:

struct termek {
  string nev;
  int ar;
  termek* kov;
};*/

termek* hozzafuz(termek* horgony, string nev, int ar) {
    // Létrehozzuk az új listaelemet
    termek* ujElem = new termek;
    ujElem->nev = nev;
    ujElem->ar = ar;
    ujElem->kov = nullptr;

    // Ha a lista üres volt, az új elem lesz a horgony
    if (horgony == nullptr) {
        horgony = ujElem;
    }
    else {
        // Különben végigmegyünk a listán és hozzáfûzzük az új elemet a végére
        termek* aktualis = horgony;
        while (aktualis->kov != nullptr) {
            aktualis = aktualis->kov;
        }
        aktualis->kov = ujElem;
    }

    return horgony;
}

int main() {
    srand(time(0));  // Véletlenszám generátor inicializálása az aktuális idõ alapján

    termek* horgony = termeketGeneral();

    // Kiírás a teszteléshez
    termek* akt = horgony;
    while (akt != nullptr) {
        cout << "Termek: " << akt->nev << ", Ar: " << akt->ar << endl;
        akt = akt->kov;
    }

    // Memóriafelszabadítás
    akt = horgony;
    while (akt != nullptr) {
        termek* kov = akt->kov;
        delete akt;
        akt = kov;
    }

    return 0;
}