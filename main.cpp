#include <iostream>
#include <fstream>

using namespace std;

struct relatie {
    int leg;
    int frate;
} a[30][30];

int n, m;
char nume[30][31];

void matrice() {
    int x, y, z;
    ifstream fin("graf.in");
    fin >> n >> m;
    while(fin >> x >> y >> z) {
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

int main() {

    return 0;
}