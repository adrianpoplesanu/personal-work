#include <iostream>
#include <fstream>
using namespace std;

int a[100][100], vizitat[100][100], n;

void walk(int i, int j, float &media, float &insule) {
    vizitat[i][j] = 1;
    if (a[i][j] == 0) return;
    media += (float)(a[i][j]);
    insule++;
    if (i - 1 > 0 && vizitat[i - 1][j] == 0 && a[i - 1][j] > 0) walk(i - 1, j, media, insule);
    if (i + 1 < n && vizitat[i + 1][j] == 0 && a[i + 1][j] > 0) walk(i + 1, j, media, insule);
    if (j - 1 > 0 && vizitat[i][j - 1] == 0 && a[i][j - 1] > 0) walk(i, j - 1, media, insule);
    if (j + 1 < n && vizitat[i][j + 1] == 0 && a[i][j + 1] > 0) walk(i, j + 1, media, insule);
}

int main(int argc, char * argv[]) {
    ifstream in("insule.in");
    ofstream out("insule.out");

    //int n, a[100][100], vizitat[100][100], numar = 0;
    in >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
             in >> a[i][j];
             vizitat[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(vizitat[i][j] == 0) {
                float total = 0, insule = 0;
                //numar++;
                walk(i, j, total, insule);
                //cout << a[i][j] << endl;
                //if (insule > 0)
                //cout << total/insule << " ";
                //cout << total << " " << insule << endl;
                if (a[i][j] > 0) cout << (float)(total / insule) << " ";
            }
        }
    }

    cout << endl;
    in.close();
    out.close();
    return 0;
}
