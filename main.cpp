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

// FUNCTII SPECIFICE
void info_pers() {
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
                } else cout << nume[i] << endl << "\nAlte rude:\n";
            else {
                cout << nume[i] << " ";
                if(a[id][i].frate == 0)
                    cout << "- copil\n";
                else
                    cout << "- frate\n";
            }

    }
}

int main() {
    matrice();
    int t;
    do {
        system("cls");
        cout << "Selectati optiunea dorita: " << endl;
        cout << "1. Informatii persoana" << endl;
        cout << "Optiunea dorita: ";
        cin >> t;
        switch (t)
        {
            case 1:
                info_pers();
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