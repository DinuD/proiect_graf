#include <iostream>
#include <fstream>
#include <afxres.h>
#include <conio.h>

using namespace std;

struct relatie {
    int leg;
    int frate;
} a[31][31];

int n, m, d[31];
char nume[31][31];

// FUNCTII PRINCIPALE

void matrice() {
    int x, y, z;
    ifstream fin("graf.in");
    fin >> n >> m;
    for(int i = 1; i <= m; i++) {
        fin >> x >> y >> z;
        a[x][y].leg = 1;
        a[x][y].frate = z;
        a[y][x] = a[x][y];
    }
    for(int i = 1; i <= m; i++)
        fin >> nume[i];
    fin.close();
}

int grad(int vf) {
    int gr = 0;
    for(int i = 1; i <= n; i++)
        if(a[vf][i].leg == 1)
            gr++;
    return gr;
}

void vdg(int d[30]) {
    for(int i = 1; i <= n; i++)
        d[i] = grad(i);
}

int lant(int z[15], int p) {
    for(int i = 1; i < p; i++)
        if(a[z[i]][z[i+1]].leg == 0)
            return 0;
    return 1;
}

// HELPER FUNCTIONS

int cautare_pers(char* pers) {
    for(int i = 1; i <= n; i++)
        if(strcmp(pers, nume[i])==0)
            return i;
    return 0;
}

int cautare_id_in_vect(int id, int v[5]) {
    for(int i = 0; i < 5; i++)
        if(v[i] == id)
            return 1;
    return 0;
}

// FUNCTII SPECIFICE
void parinti_pers() {
    char p[31];
    system("cls");
    cout << "Introdu numele persoanei pe care o cauti" << endl;
    cin >> p;
    int id = cautare_pers(p);
    int x = 1;
    system("cls");
    cout << "Parinti: ";
    for(int i = 1; i <= n; i++) {
        if(a[id][i].leg == 1)
            if(i < id)
                if(x < 2) {
                    cout << nume[i] << ", ";
                    x++;
                } else cout << nume[i] << endl;
    }
    if(x!=3)
        cout << "Persoana este din prima generatie a familiei";
}

void copii_pers() {
    char p[31];
    system("cls");
    cout << "Introdu numele persoanei pe care o cauti" << endl;
    cin >> p;
    int id = cautare_pers(p);
    int x = 0;
    system("cls");
    cout << "Copii:\n";
    for(int i = 1; i <= n; i++) {
        if(a[id][i].leg == 1 && i > id)
            if(a[id][i].frate == 0) {
                x++;
                cout << nume[i] << endl;
            }
    }
    if(!x)
        cout << "Nu are" << endl;
}

void frati_pers() {
    char p[31];
    system("cls");
    cout << "Introdu numele persoanei pe care o cauti" << endl;
    cin >> p;
    int id = cautare_pers(p);
    int x = 0;
    system("cls");
    cout << "Frati:\n";
    for(int i = 1; i <= n; i++) {
        if(a[id][i].leg == 1)
            if(a[id][i].frate == 1) {
                x++;
                cout << nume[i] << endl;
            }
    }
    if(!x)
        cout << "Nu are" << endl;
}

void parteneri_pers() {
    char p[31];
    system("cls");
    cout << "Introdu numele persoanei pe care o cauti" << endl;
    cin >> p;
    int id = cautare_pers(p);
    int x = 0, z[5];
    system("cls");
    cout << "Parteneri:\n";
    for(int i = id+1; i <= n; i++) {
        if(a[id][i].leg == 1)
            if(a[id][i].frate == 0) {
                for(int j = 1; j < i; j++)
                    if(a[i][j].leg == 1 && i>j && id!=j) {
                        if(a[i][j].frate == 0)
                            if(i == id+1 || i == j+1)
                                if(cautare_id_in_vect(j, z)==0) {
                                    z[x] = j;
                                    x++;
                                    cout << nume[j] << endl;
                                }
                    }
            }
    }
    if(!x)
        cout << "Nu are" << endl;
}

void max_frati() {
    system("cls");
    int m = 0, x = 0;
    char *p;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++) {
            x = 0;
            if(i!=j)
                if(a[i][j].leg == 1 && a[i][j].frate == 1)
                    x++;
            if(x > m) {
                m = x;
                p = nume[i];
            }
        }
    if(!m)
        cout << "Nimeni nu are frati";
    else
        cout << p << " are cei mai multi frati";
}

void max_copii() {
    system("cls");
    int m = 0, x = 0;
    char *p;
    for(int i = 1; i <= n; i++) {
        x = 0;
        for (int j = i+1; j <= n; j++) {
            if (a[i][j].leg == 1)
                x++;
            if (x > m) {
                m = x;
                p = nume[i];
            }
        }
    }
    cout << p << " are cei mai multi copii";
}

int main() {
    matrice();
    vdg(d);
    int t;
    do {
        system("cls");
        cout << "Selectati optiunea dorita: " << endl;
        cout << "1. Vezi parintii unei persoane" << endl;
        cout << "2. Vezi copiii unei persoane" << endl;
        cout << "3. Vezi fratii unei persoane" << endl;
        cout << "4. Vezi partenerii unei persoane" << endl;
        cout << "5. Cine are cei mai multi frati" << endl;
        cout << "6. Cine are cei mai multi copii" << endl;
        cout << "Optiunea dorita: ";
        cin >> t;
        switch (t)
        {
            case 1:
                parinti_pers();
                _getch();break;

            case 2:
                copii_pers();
                _getch();break;

            case 3:
                frati_pers();
                _getch();break;

            case 4:
                parteneri_pers();
                _getch();break;

            case 5:
                max_frati();
                _getch();break;

            case 6:
                max_copii();
                _getch();break;

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
