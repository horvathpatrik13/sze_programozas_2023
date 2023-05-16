/*Egy hangszerbolt git�rjait egyir�ny� l�ncolt list�ban szeretn�nk t�rolni. Minden git�rr�l ismert a h�rjainak sz�ma, ami 6, 7, 8 vagy 12 lehet. Tudjuk az �r�t, ami legal�bb 200.000 forint, de 5.000.000 forintn�l alacsonyabb. Illetve t�roljuk a hangszed�je t�pus�t, ami vagy "humbucker" vagy "single coil".

K�sz�tsen general nev� f�ggv�nyt, ami l�trehoz egy git�rokb�l �ll� l�ncolt list�t. A list�n tal�lhat� git�rok sz�ma legal�bb nulla �s maximum 10. A maxim�lis darabsz�mot, a minim�lis �rat �s a maxim�lis �rat a k�vetkez� szimbolikus �lland�kkal adja meg: MAX_DB, MIN_AR �s MAX_AR. V�letlenszer�en d�ntse el, hogy h�ny darab git�r ker�l a list�ra �s a git�rok minden param�tere (h�rok sz�ma, �r, hangszed� t�pusa) szint�n v�letlenszer�en ker�lj�n meghat�roz�sra, a fenti szab�lyok figyelembe v�tel�vel. A v�letlensz�m gener�l�s inicializ�l�s�r�l nem kell gondoskodnia. A f�ggv�ny visszat�r�si �rt�ke a gener�lt list�ban az els� git�r c�me. A f�ggv�nynek bemeneti param�terei nincsenek.

A lista egy elem�nek a szerkezet�t a k�vetkez� strukt�ra adja meg (ennek l�trehoz�s�r�l nem kell gondoskodnia):

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
    srand(time(0)); // Inicializ�ljuk a v�letlensz�m gener�tort

    int darabszam = rand() % (MAX_DB + 1); // V�letlenszer� darabsz�m gener�l�sa

    gitar* elso = nullptr; // Az els� git�r c�me

    for (int i = 0; i < darabszam; i++) {
        gitar* uj = new gitar(); // �j git�r l�trehoz�sa

        // V�letlenszer�en gener�lt git�r tulajdons�gok
        uj->hurok_szama = (rand() % 3 + 2) * 2; // 6, 7, 8 vagy 12 h�r
        uj->ar = (rand() % (MAX_AR - MIN_AR + 1)) + MIN_AR; // �r MIN_AR �s MAX_AR k�z�tt
        uj->hangszedo = (rand() % 2 == 0) ? "humbucker" : "single coil"; // "humbucker" vagy "single coil" hangszed�

        uj->kov = elso; // Az �j git�r k�vetkez�re mutat a jelenlegi els� git�r helyett
        elso = uj; // Az �j git�r lesz az els� git�r
    }

    return elso; // Visszaadjuk az els� git�r c�m�t
}

/*K�sz�tsen hozzafuz nev� f�ggv�nyt, ami a param�ter�l kapott git�rokb�l �ll� egyir�ny� l�ncoltlista v�g�re egy �j git�rt f�z hozz�. A f�ggv�ny bemenetk�nt 4 param�tert v�r: a git�rok list�j�t (a l�ncolt list�ban az els� git�r c�me) �s az �j git�r param�tereit (h�rok sz�ma, �r, hangszed� t�pusa). A f�ggv�ny visszat�r�si �rt�ke a l�ncolt lista legyen (a lista els� git�rj�nak a c�me).

A lista egy elem�nek a szerkezet�t a k�vetkez� strukt�ra adja meg (ennek l�trehoz�s�r�l nem kell gondoskodnia):

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
        // Ha a lista �res, az �j git�r lesz az els� elem
        return uj_gitar;
    }
    else {
        // K�l�nben v�gigiter�lunk a list�n, am�g el nem �rj�k a v�g�t
        gitar* current = lista;
        while (current->kov != nullptr) {
            current = current->kov;
        }
        // Az �j git�rt hozz�f�zz�k a lista v�g�hez
        current->kov = uj_gitar;

        // Visszat�r�nk a lista els� elem�nek c�m�vel
        return lista;
    }
}

/*K�sz�tsen szures nev� f�ggv�nyt, ami git�rokat tartalmaz� egyir�ny� l�ncolt list�t v�r param�ter�l. A f�ggv�ny k�sz�tsen egy �j list�t, amelyre a 6 h�ros, "single coil" t�pus� hangszed�vel, valamint a 8 h�ros, "humbucker" hangszed�vel rendelkez� git�rok ker�lnek fel. A sz�rt list�ra a hangszerek olyan sorrendben ker�ljenek, amilyen sorrendben egym�s k�vetik az eredeti list�ban. A f�ggv�ny visszat�r�si �rt�ke a sz�rt lista legyen (a lista els� git�rj�nak a c�me). Ha nincs ilyen git�r, akkor NULL �rt�kkel t�rjen vissza.

A lista egy elem�nek a szerkezet�t a k�vetkez� strukt�ra adja meg (ennek l�trehoz�s�r�l nem kell gondoskodnia):

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


/*K�sz�tsen szures nev� f�ggv�nyt, ami param�ter�l v�r egy git�rokat tartalmaz� egyir�ny� l�ncolt list�t. A f�ggv�ny k�sz�tsen egy �j list�t a dr�ga git�rokr�l. Egy git�rt akkor nevez�nk dr�g�nak, ha az �ra magasabb, mint a list�n szerepl� git�rok �r�nak az �tlaga. A sz�rt lista legyen a f�ggv�ny visszat�r�si �rt�ke (a lista els� git�rj�nak a c�me). Ha nincs ilyen git�r, akkor NULL �rt�kkel t�rjen vissza.

A lista egy elem�nek a szerkezet�t a k�vetkez� strukt�ra adja meg (ennek l�trehoz�s�r�l nem kell gondoskodnia):

struct gitar {
  int hurok_szama;
  int ar;
  string hangszedo;
  gitar* kov;
};*/

gitar* szures(gitar* lista) {
    // Els� k�rben kisz�m�tjuk az �tlag�rat
    int osszeg = 0;
    int darab = 0;
    gitar* current = lista;
    while (current != nullptr) {
        osszeg += current->ar;
        darab++;
        current = current->kov;
    }
    if (darab == 0) {
        // Ha a lista �res, visszat�r�nk NULL �rt�kkel
        return nullptr;
    }
    double atlag_ar = static_cast<double>(osszeg) / darab;

    // L�trehozzuk a sz�rt list�t �s annak v�g�t
    gitar* szurt_lista = nullptr;
    gitar* szurt_lista_vege = nullptr;

    // M�sodik k�rben hozz�adjuk a dr�ga git�rokat a sz�rt list�hoz
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

/*K�sz�tsen szures nev� f�ggv�nyt, ami param�ter�l v�r egy git�rokat tartalmaz� egyir�ny� l�ncolt list�t. A f�ggv�ny visszat�r�si �rt�ke egy 1 elem� lista, ami a legolcs�bb 12 h�ros git�rt tartalmazza. Ha t�bb git�r is van a list�n, ami a legolcs�bbnak min�s�l, akkor a bemeneti lista sorrendj�ben az els� tal�latot kell figyelembe venni. Ha nincs ilyen git�r, akkor NULL �rt�kkel t�rjen vissza.

A lista egy elem�nek a szerkezet�t a k�vetkez� strukt�ra adja meg (ennek l�trehoz�s�r�l nem kell gondoskodnia):

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
                // Ha m�g nincs legolcs�bb git�r vagy az aktu�lis git�r olcs�bb, mint a jelenlegi legolcs�bb
                legolcsobb_gitar = current;
            }
        }
        current = current->kov;
    }

    if (legolcsobb_gitar == nullptr) {
        // Ha nincs 12 h�ros git�r, visszat�r�nk NULL �rt�kkel
        return nullptr;
    }

    // L�trehozzuk az �j list�t a legolcs�bb git�rral
    gitar* szurt_lista = new gitar;
    szurt_lista->hurok_szama = legolcsobb_gitar->hurok_szama;
    szurt_lista->ar = legolcsobb_gitar->ar;
    szurt_lista->hangszedo = legolcsobb_gitar->hangszedo;
    szurt_lista->kov = nullptr;

    return szurt_lista;
}


int main() {
    gitar* elso = general();

    // Git�rok ki�rat�sa
    gitar* akt = elso;
    while (akt != nullptr) {
        cout << "Hurok szama: " << akt->hurok_szama << endl;
        cout << "Ar: " << akt->ar << " Ft" << endl;
        cout << "Hangszedo: " << akt->hangszedo << endl << endl;

        akt = akt->kov;
    }

    // Git�rok felszabad�t�sa
    akt = elso;
    while (akt != nullptr) {
        gitar* kov = akt->kov;
        delete akt;
        akt = kov;
    }

    return 0;
}
