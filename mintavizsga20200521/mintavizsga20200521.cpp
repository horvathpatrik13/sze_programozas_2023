/*K�sz�tsen strukt�r�t munk�k �temez�s�nek sz�montart�s�ra. A munka strukt�ra 2 stringet (munk�t elv�gz� neve, munka azonos�t�) �s k�t intet (munka kezdete, �s munka hossza tartalmazzon). A k�db�l kider�l, de a tagok neve legyen: elvegzo; azonosito; kezdes �s hossz.

Val�s�tsa meg a strukt�radekalar�ci�t �s 2 r�vid f�ggv�nyt:

struct munka - a deklar�ci�
bool utkozes(struct munka m1, struct munka m2) - a munk�k �tk�z�s�nek figyel�s�re
void kiiratas(struct munka m) - ki�rat�s elv�gz� azonos�t� kezd�s:befejez�s form�tumban, a munk�t elv�gz� neve szerint rendezve


Seg�ts�g
A legegyszer�bb logika a munk�k �tk�z�s�re: ha az egyik munka befejez�se nagyobb a m�sik munka kezdet�n�l �S a a m�sik munka befejez�se nagyobb az egyik munka kezdet�n�l, akkor �tk�zik. */

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

/*�rjon egy minoszlop nev� f�ggv�nyt, ami param�terk�nt kap egy dinamikusan, soronk�nt foglalt int m�trixot (a sorok kezd�c�meinek t�mbj�t), a sorok sz�m�t, �s oszlopok sz�m�t; �s visszaadja annak az oszlopnak az index�t, amelyikben az elemek �sszege a legkisebb. Ha t�bb minim�lis �sszeg� oszlop is van, ezek k�z�l a legkisebb index� oszlop index�t adja vissza.

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


/*Adott az al�bbi m�trixot le�r� strukt�ra:


struct matrix {
  int sorok; // A matrix sorainak sz�ma

  int oszlopok; // A matrix oszlopainak sz�ma

  double** m; // Matrix mutat�t�mb�s alakban megadva; 'sorok' darab 'double*' mutat�, ami 'oszlop' elem� 'double' t�mb�t c�mez.

};


K�sz�tse el a matrix* szorzas(const matrix& m, const double d) f�ggv�nyt, melynek els� param�tere egy m�trix adatait megad� strukt�ra, m�sodik param�ter pedig egy konstans sz�m. 


A f�ggv�ny t�rjen vissza egy dinamikusan foglalt ter�leten l�v� m�trix c�m�vel, mely a m�trix konstans param�terrel t�rt�n� szorz�s�t tartalmazza!

Szintaktikai hiba eset�n a ford�t� �ltal jelzett sor sz�m�b�l vonjon ki 20-at, hogy megkapja a szerkeszt�ben olvashat� sorsz�mot!

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


/*K�sz�tsen f�ggv�nyeket, amelyekkel f�jlb�l olvas be lebeg�pontos sz�mokat �s azokat besz�rja egy l�ncolt list�ba �gy, hogy annak n�vekv� rendezetts�ge mindv�gig megmarad. Haszn�lja fel a f�ggv�ny el�tt m�r elk�sz�tett k�vetkez� l�ncolt lista strukt�radefin�ci�t:

struct Lista
{
    double szam;
    Lista *kov;
};
Val�s�tsa meg a 2 r�vid f�ggv�nyt:

Lista *listaRendezveBeszur(Lista *elso, double szam) - Besz�rja szam-ot abba a n�vekv� sorrendbe rendezett l�ncolt list�ba, melynek els� elem�t elso jel�li ki a t�rban.
Lista *fajbolListaba(string fajlnev) - Felt�telezheti, hogy a fajlnev-ben megadott sz�vegf�jl sorai egy-egy racion�lis sz�mot tartalmaznak (p�ld�t ld. al�bb). Olvassa be �s konvert�lja ezeket a sz�mokat, majd a listaRendezveBeszur f�ggv�ny h�v�s�val helyezze el �ket n�vekv�en rendezetten egy l�ncolt list�ban!
P�ld�ul a tadat3.txt tartalma:
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

    // Ellen�rz�s - ki�rat�s
    Lista *current = lista;
    while (current != nullptr)
    {
        cout << current->szam << " ";
        current = current->kov;
    }
    cout << endl;

    // Felszabad�t�s
    while (lista != nullptr)
    {
        Lista *temp = lista;
        lista = lista->kov;
        delete temp;
    }

    return 0;
}
*/

/*�rjon egy string szokozkiszed(const string &s) �s egy void betubolszam(string &s) f�ggv�nyt. 

A szokozkiszed az �tadott stringb�l szedje ki a sz�k�z�ket, majd ezt a stringet adja vissza.

A betubolszam a param�ter stringben tal�lhat� kisbet�kb�l �ll�tson el� sz�mokat, m�gpedig �gy, hogy 'a'-b�l, '1', 'b'-b�l '2', stb. legyen. Ezt a standard kimentre �rja ki.

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
