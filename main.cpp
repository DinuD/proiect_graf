#include <iostream>
#include <fstream>
#include <afxres.h>
#include <conio.h>
#include <string.h>

using namespace std;
ifstream fin("graf.in");
int n, a[30][30], viz_a[30], nrc=1, viz_l[30];

struct nod {
    int id;
    int varsta;
    char nume[31];
    char nr_telefon[11];
    char ocupatie[31];
    nod* st;
    nod* dr;
    nod* parinte = NULL;
} *rad;

nod* creare() {
    int x;
    nod* r;
    fin >> x;
    if(x) {
        r = new nod;
        r->id = x;
        fin >> r->varsta >> r->nume >> r->nr_telefon >> r->ocupatie;
        r->st = creare();
        r->dr = creare();
        // r->dr->parinte = r;
        // r->st->parinte = r;
        return r;
    } else return NULL;
}

void matrice() {
    fin >> n;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            fin >> a[i][j];
}

void afisare_pers(nod* x) {
    cout << "ID: " << x->id << endl;
    cout << "Nume: " << x->nume << endl;
    cout << "Varsta: " << x->varsta << endl;
    cout << "Nr de telefon: " << x->nr_telefon << endl;
    cout << "Ocupatie: " << x->ocupatie << endl;
}

void parcurgere(nod* r) {
    if(r) {
        afisare_pers(r);
        parcurgere(r->st);
        parcurgere(r->dr);
    }
}

void parcurgere_srd(nod* r) {
    if(r) {
        parcurgere_srd(r->st);
        afisare_pers(r);
        parcurgere_srd(r->dr);
    }
}

void parcurgere_sdr(nod* r) {
    if(r) {
        parcurgere_sdr(r->st);
        parcurgere_sdr(r->dr);
        afisare_pers(r);
    }
}

nod* cautare_nume(nod* r, char* nume) {
    if(r) {
        if(strcmp(r->nume, nume)==0)
            return r;
        else if(cautare_nume(r->st, nume))
            return cautare_nume(r->st, nume);
        else return cautare_nume(r->dr, nume);
    }
    return NULL;
}

nod* cautare_id(nod* r, int id) {
    if(r) {
        if(r->id == id)
            return r;
        else if(cautare_id(r->st, id))
            return cautare_id(r->st, id);
        else return cautare_id(r->dr, id);
    }
    return NULL;
}

nod* cautare_tel(nod* r, char* nr_tel) {
    if(r) {
        if(strcmp(r->nr_telefon, nr_tel)==0)
            return r;
        else if(cautare_tel(r->st, nr_tel))
            return cautare_tel(r->st, nr_tel);
        else return cautare_tel(r->dr, nr_tel);
    }
    return NULL;
}

void lista_pers(nod* x) {
    if(x == rad)
        cout << "ID: " << x->id << " " << x->nume << endl;
    if(x->st != NULL) {
        cout << "ID: " << x->st->id << " " << x->st->nume << endl;
        if(x->st->st!=NULL || x->st->dr!=NULL) {
            cout << "Copii:" << endl;
            lista_pers(x->st);
        }
    }
    if(x->dr != NULL) {
        cout << "ID: " << x->dr->id << " " << x->dr->nume << endl;
        if(x->dr->st!=NULL || x->dr->dr!=NULL) {
            cout << "Copii:" << endl;
            lista_pers(x->dr);
        }
    }
    if(x->st == NULL || x->dr == NULL)
        cout << endl;
}

void ocupatii(nod* r, char* oc) {
    if(r) {
        if(strcmp(r->ocupatie, oc)==0)
            afisare_pers(r);
        ocupatii(r->st, oc);
        ocupatii(r->dr, oc);
    }
}

void contact(nod* r) {
    nod* p;
    system("cls");
    cout << r->nume << " poate contacta direct urmatoarele persoane:\n";
    for(int i = 1; i <= n; i++)
        if(a[r->id][i] == 1) {
            p = cautare_id(rad, i);
            cout << p->nume << " " << p->nr_telefon << endl;
        }
}

void adancime(int vf, int afisare) {
    viz_a[vf] = nrc;
    if(afisare)
        cout << vf << " ";
    for(int i = 1; i <= n; i++)
        if(a[vf][i] == 1 && viz_a[i]==0)
            adancime(i, afisare);
}

void comp_conexe() {
    system("cls");
    nod* x;
    adancime(1, 0);
    for(int i = 1; i <= n; i++)
        if(viz_a[i] == 0) {
            nrc++;
            adancime(i, 0);
        }
    for(int i = 1; i <= nrc; i++) {
        cout << "Cercul/Componenta " << i << ":\n";
        for(int j = 1; j <= n; j++)
            if(viz_a[j] == i) {
                x = cautare_id(rad, j);
                cout << x->nume << " " << x->nr_telefon << endl;
            }
        cout << endl;
    }
}

void latime(int vf) {
    int c[30], ps, pi;
    viz_l[vf] = 1;
    cout << vf << " ";
    c[1] = vf;
    pi = 1;
    ps = 1;
    while(ps <= pi) {
        for(int i = 1; i <= n; i++)
            if(a[vf][i] == 1 && viz_l[i]==0) {
                pi++;
                c[pi] = i;
                viz_l[i] = 1;
                cout << i << " ";
            }
        ps++;
        vf = c[ps];
    }
}

int main() {
    rad = creare();
    matrice();
    fin.close();
    // parcurgere(rad);
    // cin.get();
    int t;
    do {
        system("cls");
        cout << "Selectati optiunea dorita: " << endl;
        cout << "1. Lista persoane" << endl;
        cout << "2. Detalii persoana" << endl;
        cout << "3. Cauta persoana dupa nr de telefon" << endl;
        cout << "4. Afiseaza persoanele cu o anumita ocupatie" << endl;
        cout << "5. Parcurgerea RSD" << endl;
        cout << "6. Parcurgerea SRD" << endl;
        cout << "7. Parcurgerea SDR" << endl;
        cout << "-------------------------------------------------------" << endl;
        cout << "8. Pe cine poate contacta direct persoana cautata" << endl;
        cout << "9. Afiseaza cercurile de prietenie (componentele conexe)" << endl;
        cout << "10. Parcurgerea grafului in adancime" << endl;
        cout << "11. Parcurgerea grafului in latime" << endl;
        cout << "Optiunea dorita: ";
        cin >> t;
        switch (t)
        {
            case 1: {
                system("cls");
                lista_pers(rad);
            } _getch();break;

            case 2: {
                system("cls");
                cout << "Introdu numele persoanei cautate:" << endl;
                char nume[31];
                cin >> nume;
                nod* x = cautare_nume(rad, nume);
                if(x != NULL) {
                    system("cls");
                    afisare_pers(x);
                } else
                    cout << "Nu am gasit persoana";
            } _getch(); break;

            case 3: {
                system("cls");
                cout << "Introdu numarul de telefon cautat:" << endl;
                char nr_tel[31];
                cin >> nr_tel;
                nod* x = cautare_tel(rad, nr_tel);
                if(x != NULL) {
                    system("cls");
                    afisare_pers(x);
                } else
                    cout << "Nu am gasit numarul";
            } _getch(); break;

            case 4: {
                system("cls");
                cout << "Introdu ocupatia cautata:" << endl;
                char oc[31];
                cin >> oc;
                ocupatii(rad, oc);
            } _getch(); break;

            case 5: {
                system("cls");
                parcurgere(rad);
            } _getch(); break;

            case 6: {
                system("cls");
                parcurgere_srd(rad);
            } _getch(); break;

            case 7: {
                system("cls");
                parcurgere_sdr(rad);
            } _getch(); break;

            case 8: {
                system("cls");
                cout << "Introdu numele persoanei cautate:" << endl;
                char nume[31];
                cin >> nume;
                nod* x = cautare_nume(rad, nume);
                if(x!=NULL)
                    contact(x);
                else
                    cout << "Nu am gasit persoana";
            } _getch(); break;

            case 9:
                comp_conexe();
                _getch(); break;

            case 10: {
                system("cls");
                cout << "Introdu numele persoanei de la care va porni parcurgerea" << endl;
                char nume[31];
                cin >> nume;
                nod* x = cautare_nume(rad, nume);
                adancime(x->id, 1);
                cout << endl;
            } _getch(); break;

            case 11: {
                system("cls");
                cout << "Introdu numele persoanei de la care va porni parcurgerea" << endl;
                char nume[31];
                cin >> nume;
                nod* x = cautare_nume(rad, nume);
                latime(x->id);
                cout << endl;
            } _getch(); break;

            case 0:
                return 0;

            default: {
                cout << "Optiune inexistenta. Incearca din nou\n";
                Sleep(1000);
            } break;
        }
    } while(t != 0);
    return 0;
}
