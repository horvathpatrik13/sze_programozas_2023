/*Egy b�tor�ruh�z term�keit(n�v, �r) egy ir�nyban l�ncolt lista t�rolja.Fejezze be az al�bbi f�ggv�nyt, melynek c�lja v�letlenszer�en el��ll�tani egy legfeljebb 15 (MAX_DB szimbolikus �lland�val adott) elemb�l �ll� l�ncolt list�t. (Teh�t az elemek sz�ma is v�letlenszer�, lehet ak�r 0 is.)

Ezen k�v�l v�letlenszer�en kell meghat�rozni a term�kek nev�t, mely csak Asztal, Szek, Kanape, Kisagy, Konyhapult, Allolampa, Fogas, Komod, Tukor, Vaza, Dohanyzoasztal �s Hintaszek lehet.Azonos nev� term�kb�l t�bb is el�fordulhat, �s nem k�telez� mindegyiknek szerepelnie.

Hasonl�an v�letlenszer�en kell meghat�rozni a term�kek �r�t, ami legfeljebb 1000000 (MAX_AR szimbolikus �lland�val adott), �s nemnegat�v eg�sz �rt�k.

A f�ggv�ny visszat�r�si �rt�ke a l�trehozott lista legels� elem�nek c�me(a horgony).

Felt�telezheti, hogy a v�letlensz�m gener�tort a f�ggv�ny h�v�sa el�tt m�r inicializ�lt�k.

Szintaktikai hiba eset�n a ford�t� �ltal jelzett sor sz�m�b�l vonjon ki 20 - at, hogy megkapja a szerkeszt�ben olvashat� sorsz�mot!

A lista egy elem�nek szerkezete a k�vetkez� :

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


/*Egy b�tor�ruh�z term�keit (n�v, �r) egy ir�nyban l�ncolt lista t�rolja. Fejezze be az al�bbi f�ggv�nyt, melynek c�lja t�r�lni a horgony param�terrel adott l�ncolt list�b�l minden olyan elemet, melyben a term�k neve nev!

A f�ggv�ny visszat�r�si �rt�ke a m�dos�tott lista legels� elem�nek c�me (a horgony). Ez v�ltozhat, ha a list�nak m�r a legels� elem�t is t�r�lni kell.

Szintaktikai hiba eset�n a ford�t� �ltal hib�snak jelzett sor sz�m�b�l vonjon ki 20-at, hogy megkapja a szerkeszt�ben olvashat� val�s sorsz�mot.

A lista egy elem�nek szerkezete a k�vetkez�:

struct termek {
  string nev;
  int ar;
  termek* kov;
};*/
termek* torol(termek* horgony, string nev) {
    // Kezdetben az els� elemre mutat a 'aktualis' pointer
    termek* aktualis = horgony;
    termek* elozo = nullptr;

    // Am�g van m�g elem a list�ban
    while (aktualis != nullptr) {
        // Ha a term�k neve egyezik a keresett nev�vel
        if (aktualis->nev == nev) {
            // Ha az els� elemet kell t�r�lni
            if (elozo == nullptr) {
                // Az 'aktualis' lesz az �j horgony
                horgony = aktualis->kov;
            }
            else {
                // K�l�nben az 'elozo' mutat�j�t �ll�tjuk az 'aktualis' k�vetkez� elem�re
                elozo->kov = aktualis->kov;
            }

            // Elmentj�k az 'aktualis' mutat�j�t, majd felszabad�tjuk a mem�riater�letet
            termek* torlendo = aktualis;
            aktualis = aktualis->kov;
            delete torlendo;
        }
        else {
            // Ha nem kell t�r�lni, l�p�nk a k�vetkez� elemre
            elozo = aktualis;
            aktualis = aktualis->kov;
        }
    }

    return horgony;
}


/*Egy b�tor�ruh�z term�keit (n�v, �r) egy ir�nyban l�ncolt lista t�rolja. Fejezze be az al�bbi f�ggv�nyt, melynek c�lja l�trehozni a horgony param�terrel azonos�tott lista alapj�n egy �j, sz�rt list�t, melyben csak olyan term�kek szerepelnek, melyek �ra a megadott min �s max �rt�kek k�z� esik (ezeket is bele�rtve).

�gyeljen r�, hogy az eredeti �s sz�rt list�k semmik�ppen se osztozzanak k�z�s adatter�leteken! M�sk�pp fogalmazva, az eredeti list�nak s�rtetlennek kell maradnia.

A f�ggv�ny visszat�r�si �rt�ke a l�trehozott �j, sz�rt lista legels� elem�nek c�me (az �j lista horgonya).

Szintaktikai hiba eset�n a ford�t� �ltal jelzett sor sz�m�b�l vonjon ki 20-at, hogy megkapja a szerkeszt�ben olvashat� sorsz�mot!

A lista egy elem�nek szerkezete a k�vetkez�:

struct termek {
  string nev;
  int ar;
  termek* kov;
};*/

termek* szures(const termek* horgony, int min, int max) {
    termek* szurtHorgony = nullptr;
    termek* szurtElozo = nullptr;
    const termek* aktualis = horgony;

    // V�gigmegy�nk az eredeti list�n
    while (aktualis != nullptr) {
        // Ellen�rizz�k az �rat
        if (aktualis->ar >= min && aktualis->ar <= max) {
            // L�trehozzuk az �j sz�rt elemet
            termek* ujTermek = new termek;
            ujTermek->nev = aktualis->nev;
            ujTermek->ar = aktualis->ar;
            ujTermek->kov = nullptr;

            // Ha ez az els� elem a sz�rt list�ban
            if (szurtHorgony == nullptr) {
                szurtHorgony = ujTermek;
                szurtElozo = ujTermek;
            }
            else {
                // K�l�nben be�ll�tjuk az el�z� elem k�vetkez� mutat�j�t
                szurtElozo->kov = ujTermek;
                szurtElozo = ujTermek;
            }
        }

        // L�p�nk a k�vetkez� elemre az eredeti list�ban
        aktualis = aktualis->kov;
    }

    return szurtHorgony;
}

/*Egy b�tor�ruh�z term�keit (n�v, �r) egy ir�nyban l�ncolt lista t�rolja. Fejezze be az al�bbi f�ggv�nyt, melynek c�lja 50%-os kedvezm�nyt adni a legdr�g�bb term�kb�l! M�dos�tsa a term�k �r�t a fel�re (lefel� kerek�tve)! Ha t�bb azonos �r� legdr�g�bb term�k l�tezik, csak a list�ban els�k�nt t�rolt legdr�g�bb term�k �r�b�l adjon kedvezm�nyt!

A f�ggv�ny param�tere a lista els� elem�nek c�me (a horgony).

Szintaktikai hiba eset�n a ford�t� �ltal jelzett sor sz�m�b�l vonjon ki 20-at, hogy megkapja a szerkeszt�ben olvashat� sorsz�mot!

A lista egy elem�nek szerkezete a k�vetkez�:

struct termek {
  string nev;
  int ar;
  termek* kov;
};*/

void akcio(termek* elem) {
    if (elem == nullptr) {
        // Ha az elem nullpointer, nincs mit m�dos�tani
        return;
    }

    termek* legdragabb = elem;
    termek* aktualis = elem->kov;

    // Keres�s a legdr�g�bb term�kig
    while (aktualis != nullptr) {
        if (aktualis->ar > legdragabb->ar) {
            legdragabb = aktualis;
        }
        aktualis = aktualis->kov;
    }

    // 50%-os kedvezm�ny az �rra
    legdragabb->ar = legdragabb->ar / 2;
}

/*Egy b�tor�ruh�z term�keit (n�v, �r) egy ir�nyban l�ncolt lista t�rolja. Fejezze be az al�bbi f�ggv�nyt, melynek c�lja hozz�f�zni egy �j listaelemet a horgony-nyal azonos�tott lista v�g�hez! Ennek az �j term�knek a nev�t a nev, �r�t az ar param�ter adja meg.

A f�ggv�ny visszat�r�si �rt�ke a l�trehozott lista legels� elem�nek c�me (a horgony). A horgony megv�ltozhat, ha az eredeti lista �res volt a hozz�f�z�s el�tt.

Szintaktikai hiba eset�n a ford�t� �ltal jelzett sor sz�m�b�l vonjon ki 20-at, hogy megkapja a szerkeszt�ben olvashat� sorsz�mot!

A lista egy elem�nek szerkezete a k�vetkez�:

struct termek {
  string nev;
  int ar;
  termek* kov;
};*/

termek* hozzafuz(termek* horgony, string nev, int ar) {
    // L�trehozzuk az �j listaelemet
    termek* ujElem = new termek;
    ujElem->nev = nev;
    ujElem->ar = ar;
    ujElem->kov = nullptr;

    // Ha a lista �res volt, az �j elem lesz a horgony
    if (horgony == nullptr) {
        horgony = ujElem;
    }
    else {
        // K�l�nben v�gigmegy�nk a list�n �s hozz�f�zz�k az �j elemet a v�g�re
        termek* aktualis = horgony;
        while (aktualis->kov != nullptr) {
            aktualis = aktualis->kov;
        }
        aktualis->kov = ujElem;
    }

    return horgony;
}

int main() {
    srand(time(0));  // V�letlensz�m gener�tor inicializ�l�sa az aktu�lis id� alapj�n

    termek* horgony = termeketGeneral();

    // Ki�r�s a tesztel�shez
    termek* akt = horgony;
    while (akt != nullptr) {
        cout << "Termek: " << akt->nev << ", Ar: " << akt->ar << endl;
        akt = akt->kov;
    }

    // Mem�riafelszabad�t�s
    akt = horgony;
    while (akt != nullptr) {
        termek* kov = akt->kov;
        delete akt;
        akt = kov;
    }

    return 0;
}