/*Egy hangszerbolt gitárjait egyirányú láncolt listában szeretnénk tárolni. Minden gitárról ismert a húrjainak száma, ami 6, 7, 8 vagy 12 lehet. Tudjuk az árát, ami legalább 200.000 forint, de 5.000.000 forintnál alacsonyabb. Illetve tároljuk a hangszedõje típusát, ami vagy "humbucker" vagy "single coil".

Készítsen general nevû függvényt, ami létrehoz egy gitárokból álló láncolt listát. A listán található gitárok száma legalább nulla és maximum 10. A maximális darabszámot, a minimális árat és a maximális árat a következõ szimbolikus állandókkal adja meg: MAX_DB, MIN_AR és MAX_AR. Véletlenszerûen döntse el, hogy hány darab gitár kerül a listára és a gitárok minden paramétere (húrok száma, ár, hangszedõ típusa) szintén véletlenszerûen kerüljön meghatározásra, a fenti szabályok figyelembe vételével. A véletlenszám generálás inicializálásáról nem kell gondoskodnia. A függvény visszatérési értéke a generált listában az elsõ gitár címe. A függvénynek bemeneti paraméterei nincsenek.

A lista egy elemének a szerkezetét a következõ struktúra adja meg (ennek létrehozásáról nem kell gondoskodnia):

struct gitar {
  int hurok_szama;
  int ar;
  string hangszedo;
  gitar* kov;
};*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_DB = 10;
const int MIN_AR = 200000;
const int MAX_AR = 5000000;

struct gitar {
    int hurok_szama;
    int ar;
    string hangszedo;
    gitar* kov;
};

gitar* general() {
    srand(time(0)); // Inicializáljuk a véletlenszám generátort

    int darabszam = rand() % (MAX_DB + 1); // Véletlenszerû darabszám generálása

    gitar* elso = nullptr; // Az elsõ gitár címe

    for (int i = 0; i < darabszam; i++) {
        gitar* uj = new gitar(); // Új gitár létrehozása

        // Véletlenszerûen generált gitár tulajdonságok
        uj->hurok_szama = (rand() % 3 + 2) * 2; // 6, 7, 8 vagy 12 húr
        uj->ar = (rand() % (MAX_AR - MIN_AR + 1)) + MIN_AR; // Ár MIN_AR és MAX_AR között
        uj->hangszedo = (rand() % 2 == 0) ? "humbucker" : "single coil"; // "humbucker" vagy "single coil" hangszedõ

        uj->kov = elso; // Az új gitár következõre mutat a jelenlegi elsõ gitár helyett
        elso = uj; // Az új gitár lesz az elsõ gitár
    }

    return elso; // Visszaadjuk az elsõ gitár címét
}

/*Készítsen hozzafuz nevû függvényt, ami a paraméterül kapott gitárokból álló egyirányú láncoltlista végére egy új gitárt fûz hozzá. A függvény bemenetként 4 paramétert vár: a gitárok listáját (a láncolt listában az elsõ gitár címe) és az új gitár paramétereit (húrok száma, ár, hangszedõ típusa). A függvény visszatérési értéke a láncolt lista legyen (a lista elsõ gitárjának a címe).

A lista egy elemének a szerkezetét a következõ struktúra adja meg (ennek létrehozásáról nem kell gondoskodnia):

struct gitar {
  int hurok_szama;
  int ar;
  string hangszedo;
  gitar* kov;
};*/

gitar* hozzafuz(gitar* lista, int hurok_szama, int ar, string hangszedo) {
    gitar* uj_gitar = new gitar;
    uj_gitar->hurok_szama = hurok_szama;
    uj_gitar->ar = ar;
    uj_gitar->hangszedo = hangszedo;
    uj_gitar->kov = nullptr;

    if (lista == nullptr) {
        // Ha a lista üres, az új gitár lesz az elsõ elem
        return uj_gitar;
    }
    else {
        // Különben végigiterálunk a listán, amíg el nem érjük a végét
        gitar* current = lista;
        while (current->kov != nullptr) {
            current = current->kov;
        }
        // Az új gitárt hozzáfüzzük a lista végéhez
        current->kov = uj_gitar;

        // Visszatérünk a lista elsõ elemének címével
        return lista;
    }
}

/*Készítsen szures nevû függvényt, ami gitárokat tartalmazó egyirányú láncolt listát vár paraméterül. A függvény készítsen egy új listát, amelyre a 6 húros, "single coil" típusú hangszedõvel, valamint a 8 húros, "humbucker" hangszedõvel rendelkezõ gitárok kerülnek fel. A szûrt listára a hangszerek olyan sorrendben kerüljenek, amilyen sorrendben egymás követik az eredeti listában. A függvény visszatérési értéke a szûrt lista legyen (a lista elsõ gitárjának a címe). Ha nincs ilyen gitár, akkor NULL értékkel térjen vissza.

A lista egy elemének a szerkezetét a következõ struktúra adja meg (ennek létrehozásáról nem kell gondoskodnia):

struct gitar {
  int hurok_szama;
  int ar;
  string hangszedo;
  gitar* kov;
};*/

gitar* szures(gitar* lista) {
    gitar* szurt_lista = nullptr;
    gitar* szurt_lista_vege = nullptr;

    gitar* current = lista;
    while (current != nullptr) {
        if ((current->hurok_szama == 6 && current->hangszedo == "single coil") ||
            (current->hurok_szama == 8 && current->hangszedo == "humbucker")) {
            gitar* uj_gitar = new gitar;
            uj_gitar->hurok_szama = current->hurok_szama;
            uj_gitar->ar = current->ar;
            uj_gitar->hangszedo = current->hangszedo;
            uj_gitar->kov = nullptr;

            if (szurt_lista == nullptr) {
                szurt_lista = uj_gitar;
                szurt_lista_vege = uj_gitar;
            }
            else {
                szurt_lista_vege->kov = uj_gitar;
                szurt_lista_vege = uj_gitar;
            }
        }

        current = current->kov;
    }

    return szurt_lista;
}


/*Készítsen szures nevû függvényt, ami paraméterül vár egy gitárokat tartalmazó egyirányú láncolt listát. A függvény készítsen egy új listát a drága gitárokról. Egy gitárt akkor nevezünk drágának, ha az ára magasabb, mint a listán szereplõ gitárok árának az átlaga. A szûrt lista legyen a függvény visszatérési értéke (a lista elsõ gitárjának a címe). Ha nincs ilyen gitár, akkor NULL értékkel térjen vissza.

A lista egy elemének a szerkezetét a következõ struktúra adja meg (ennek létrehozásáról nem kell gondoskodnia):

struct gitar {
  int hurok_szama;
  int ar;
  string hangszedo;
  gitar* kov;
};*/

gitar* szures(gitar* lista) {
    // Elsõ körben kiszámítjuk az átlagárat
    int osszeg = 0;
    int darab = 0;
    gitar* current = lista;
    while (current != nullptr) {
        osszeg += current->ar;
        darab++;
        current = current->kov;
    }
    if (darab == 0) {
        // Ha a lista üres, visszatérünk NULL értékkel
        return nullptr;
    }
    double atlag_ar = static_cast<double>(osszeg) / darab;

    // Létrehozzuk a szûrt listát és annak végét
    gitar* szurt_lista = nullptr;
    gitar* szurt_lista_vege = nullptr;

    // Második körben hozzáadjuk a drága gitárokat a szûrt listához
    current = lista;
    while (current != nullptr) {
        if (current->ar > atlag_ar) {
            gitar* uj_gitar = new gitar;
            uj_gitar->hurok_szama = current->hurok_szama;
            uj_gitar->ar = current->ar;
            uj_gitar->hangszedo = current->hangszedo;
            uj_gitar->kov = nullptr;

            if (szurt_lista == nullptr) {
                szurt_lista = uj_gitar;
                szurt_lista_vege = uj_gitar;
            }
            else {
                szurt_lista_vege->kov = uj_gitar;
                szurt_lista_vege = uj_gitar;
            }
        }

        current = current->kov;
    }

    return szurt_lista;
}

/*Készítsen szures nevû függvényt, ami paraméterül vár egy gitárokat tartalmazó egyirányú láncolt listát. A függvény visszatérési értéke egy 1 elemû lista, ami a legolcsóbb 12 húros gitárt tartalmazza. Ha több gitár is van a listán, ami a legolcsóbbnak minõsül, akkor a bemeneti lista sorrendjében az elsõ találatot kell figyelembe venni. Ha nincs ilyen gitár, akkor NULL értékkel térjen vissza.

A lista egy elemének a szerkezetét a következõ struktúra adja meg (ennek létrehozásáról nem kell gondoskodnia):

struct gitar {
  int hurok_szama;
  int ar;
  string hangszedo;
  gitar* kov;
};*/

gitar* szures(gitar* lista) {
    gitar* legolcsobb_gitar = nullptr;

    gitar* current = lista;
    while (current != nullptr) {
        if (current->hurok_szama == 12) {
            if (legolcsobb_gitar == nullptr || current->ar < legolcsobb_gitar->ar) {
                // Ha még nincs legolcsóbb gitár vagy az aktuális gitár olcsóbb, mint a jelenlegi legolcsóbb
                legolcsobb_gitar = current;
            }
        }
        current = current->kov;
    }

    if (legolcsobb_gitar == nullptr) {
        // Ha nincs 12 húros gitár, visszatérünk NULL értékkel
        return nullptr;
    }

    // Létrehozzuk az új listát a legolcsóbb gitárral
    gitar* szurt_lista = new gitar;
    szurt_lista->hurok_szama = legolcsobb_gitar->hurok_szama;
    szurt_lista->ar = legolcsobb_gitar->ar;
    szurt_lista->hangszedo = legolcsobb_gitar->hangszedo;
    szurt_lista->kov = nullptr;

    return szurt_lista;
}


int main() {
    gitar* elso = general();

    // Gitárok kiíratása
    gitar* akt = elso;
    while (akt != nullptr) {
        cout << "Hurok szama: " << akt->hurok_szama << endl;
        cout << "Ar: " << akt->ar << " Ft" << endl;
        cout << "Hangszedo: " << akt->hangszedo << endl << endl;

        akt = akt->kov;
    }

    // Gitárok felszabadítása
    akt = elso;
    while (akt != nullptr) {
        gitar* kov = akt->kov;
        delete akt;
        akt = kov;
    }

    return 0;
}
