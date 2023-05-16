/*Készítsen struktúrát munkák ütemezésének számontartására. A munka struktúra 2 stringet (munkát elvégzõ neve, munka azonosító) és két intet (munka kezdete, és munka hossza tartalmazzon). A kódból kiderül, de a tagok neve legyen: elvegzo; azonosito; kezdes és hossz.

Valósítsa meg a struktúradekalarációt és 2 rövid függvényt:

struct munka - a deklaráció
bool utkozes(struct munka m1, struct munka m2) - a munkák ütközésének figyelésére
void kiiratas(struct munka m) - kiíratás elvégzõ azonosító kezdés:befejezés formátumban, a munkát elvégzõ neve szerint rendezve


Segítség
A legegyszerûbb logika a munkák ütközésére: ha az egyik munka befejezése nagyobb a másik munka kezdeténél ÉS a a másik munka befejezése nagyobb az egyik munka kezdeténél, akkor ütközik. */

#include <iostream>
#include <string>
using namespace std;

#define DB 5

struct munka {
    string elvegzo;
    string azonosito;
    int kezdes;
    int hossz;
};

bool utkozes(struct munka m1, struct munka m2) {
    int m1_befejezes = m1.kezdes + m1.hossz;
    int m2_befejezes = m2.kezdes + m2.hossz;

    if (m1_befejezes > m2.kezdes && m2_befejezes > m1.kezdes)
        return true;

    return false;
}

void kiiratas(struct munka m) {
    cout << "Elvegzo: " << m.elvegzo << ", Azonosito: " << m.azonosito << ", Kezdes: " << m.kezdes << ", Befejezes: " << m.kezdes + m.hossz << endl;
}

void rendez(struct munka m[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (m[j].elvegzo > m[j + 1].elvegzo) {
                // Csere
                struct munka temp = m[j];
                m[j] = m[j + 1];
                m[j + 1] = temp;
            }
        }
    }
}

/*Írjon egy minoszlop nevû függvényt, ami paraméterként kap egy dinamikusan, soronként foglalt int mátrixot (a sorok kezdõcímeinek tömbjét), a sorok számát, és oszlopok számát; és visszaadja annak az oszlopnak az indexét, amelyikben az elemek összege a legkisebb. Ha több minimális összegû oszlop is van, ezek közül a legkisebb indexû oszlop indexét adja vissza.

*/

#include <climits>

int minoszlop(int** mtx, int s, int o) {
    int minIndex = 0;
    int minSum = INT_MAX;

    for (int j = 0; j < o; j++) {
        int sum = 0;
        for (int i = 0; i < s; i++) {
            sum += mtx[i][j];
        }
        if (sum < minSum) {
            minSum = sum;
            minIndex = j;
        }
    }

    return minIndex;
}


/*Adott az alábbi mátrixot leíró struktúra:


struct matrix {
  int sorok; // A matrix sorainak száma

  int oszlopok; // A matrix oszlopainak száma

  double** m; // Matrix mutatótömbös alakban megadva; 'sorok' darab 'double*' mutató, ami 'oszlop' elemû 'double' tömböt címez.

};


Készítse el a matrix* szorzas(const matrix& m, const double d) függvényt, melynek elsõ paramétere egy mátrix adatait megadó struktúra, második paraméter pedig egy konstans szám. 


A függvény térjen vissza egy dinamikusan foglalt területen lévõ mátrix címével, mely a mátrix konstans paraméterrel történõ szorzását tartalmazza!

Szintaktikai hiba esetén a fordító által jelzett sor számából vonjon ki 20-at, hogy megkapja a szerkesztõben olvasható sorszámot!

matrix *szorzas(const matrix x& m, const double d) {
    matrix* mtx = new matrix;
    mtx->sorok = m.sorok;
    mtx->oszlopok = m.oszlopok;

    mtx->m = new double* [m.sorok];
    for (int i = 0; i < m.sorok; i++) {
        mtx->m[i] = new double[m.oszlopok];
        for (int j = 0; j < m.oszlopok; j++) {
            mtx->m[i][j] = m.m[i][j] * d;
        }
    }

    return mtx;
}*/


/*Készítsen függvényeket, amelyekkel fájlból olvas be lebegõpontos számokat és azokat beszúrja egy láncolt listába úgy, hogy annak növekvõ rendezettsége mindvégig megmarad. Használja fel a függvény elõtt már elkészített következõ láncolt lista struktúradefiníciót:

struct Lista
{
    double szam;
    Lista *kov;
};
Valósítsa meg a 2 rövid függvényt:

Lista *listaRendezveBeszur(Lista *elso, double szam) - Beszúrja szam-ot abba a növekvõ sorrendbe rendezett láncolt listába, melynek elsõ elemét elso jelöli ki a tárban.
Lista *fajbolListaba(string fajlnev) - Feltételezheti, hogy a fajlnev-ben megadott szövegfájl sorai egy-egy racionális számot tartalmaznak (példát ld. alább). Olvassa be és konvertálja ezeket a számokat, majd a listaRendezveBeszur függvény hívásával helyezze el õket növekvõen rendezetten egy láncolt listában!
Például a tadat3.txt tartalma:
3.
1
5.5
4
2.0*/

/*#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Lista
{
    double szam;
    Lista *kov;
};

Lista *listaRendezveBeszur(Lista *elso, double szam)
{
    Lista *uj = new Lista;
    uj->szam = szam;
    uj->kov = nullptr;

    if (elso == nullptr || szam < elso->szam)
    {
        uj->kov = elso;
        return uj;
    }

    Lista *current = elso;
    while (current->kov != nullptr && szam >= current->kov->szam)
    {
        current = current->kov;
    }

    uj->kov = current->kov;
    current->kov = uj;

    return elso;
}

Lista *fajbolListaba(string fajlnev)
{
    Lista *elso = nullptr;

    ifstream file(fajlnev);
    if (!file)
    {
        cerr << "Hiba a fajl megnyitasa soran.\n";
        return elso;
    }

    double szam;
    while (file >> szam)
    {
        elso = listaRendezveBeszur(elso, szam);
    }

    file.close();
    return elso;
}

int main()
{
    string fajlnev = "tadat3.txt";
    Lista *lista = fajbolListaba(fajlnev);

    // Ellenõrzés - kiíratás
    Lista *current = lista;
    while (current != nullptr)
    {
        cout << current->szam << " ";
        current = current->kov;
    }
    cout << endl;

    // Felszabadítás
    while (lista != nullptr)
    {
        Lista *temp = lista;
        lista = lista->kov;
        delete temp;
    }

    return 0;
}
*/

/*Írjon egy string szokozkiszed(const string &s) és egy void betubolszam(string &s) függvényt. 

A szokozkiszed az átadott stringbõl szedje ki a szóközöket, majd ezt a stringet adja vissza.

A betubolszam a paraméter stringben található kisbetûkbõl állítson elõ számokat, mégpedig úgy, hogy 'a'-ból, '1', 'b'-bõl '2', stb. legyen. Ezt a standard kimentre írja ki.

#include <iostream>
#include <string>

std::string szokozkiszed(const std::string &s) {
    std::string result = "";
    for (char c : s) {
        if (c != ' ') {
            result += c;
        }
    }
    return result;
}

void betubolszam(std::string &s) {
    for (char &c : s) {
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + '1';
        }
    }
    std::cout << s << std::endl;
}

int main() {
    std::string input = "a b c d e";
    std::string result = szokozkiszed(input);
    std::cout << "Szokozok kiszedve: " << result << std::endl;

    std::string input2 = "abcd";
    std::cout << "Betubol szam: ";
    betubolszam(input2);

    return 0;
}
*/

int main() {
    struct munka munkak[DB] = {
      {"John", "M1", 0, 5},
      {"Alice", "M2", 2, 4},
      {"Bob", "M3", 1, 3},
      {"Alice", "M4", 6, 2},
      {"John", "M5", 4, 4}
    };

    cout << "Munkak utkozesenek ellenorzese:" << endl;
    for (int i = 0; i < DB - 1; i++) {
        for (int j = i + 1; j < DB; j++) {
            if (utkozes(munkak[i], munkak[j])) {
                cout << "Munka " << munkak[i].azonosito << " es " << munkak[j].azonosito << " utkozik." << endl;
            }
        }
    }

    cout << endl << "Munkak kiiratasa elvegzo szerint rendezve:" << endl;
    rendez(munkak, DB);
    for (int i = 0; i < DB; i++) {
        kiiratas(munkak[i]);
    }

    return 0;
}
