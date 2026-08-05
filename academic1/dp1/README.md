822. Se citeste un numar natural n (2<=n<=20) si apoi o matrice cu n linii si n coloane av�nd elementele numere �ntregi cu cel mult 4 cifre fiecare. Parcurgerea matricii se face din coltul (n,1) spre coltul (1,n) si se poate face pe directiile: nord, nord-est si est.
a) Afisati numarul de moduri �n care se poate ajunge din coltul (n,1) �n coltul (1,n).
b) Afisati suma maxima care se poate obtine parcurg�nd matricea din coltul (n,1) �n coltul (1,n).
Pentru citire se va folosi fisierul 2.in, iar pentru afisare fisierul 2.out.
Exemplu:
2.in
3
1 2 3
-1 3 4
2 -1 -1
2.out
13
12

their solution:
```
#include <fstream>
using namespace std;
ifstream fin("2.in");
ofstream fout("2.out");

int A[21][21],n,m,D[21][21],S[21][21];

int main()
{
     fin>>n;
     for(int i=1;i<=n;i++)
          for(int j=1;j<=n;j++)
               fin>>A[i][j];
     //numarul de drumuri
     for(int i=n;i>=1;i--)
          for(int j=1;j<=n;j++)
               if(i==n || j==1) D[i][j]=1;
               else D[i][j]=D[i][j-1]+D[i+1][j-1]+D[i+1][j];
     fout<<D[1][n]<<endl;
     //sumele maxime
     for(int i=n;i>=1;i--)
          for(int j=1;j<=n;j++)
               S[i][j]=A[i][j]+max(max(S[i][j-1],S[i+1][j-1]),S[i+1][j]);
     fout<<S[1][n]<<endl;
     return 0;
}
```
solutia lor nu imi place pentru ca se bazeaza pe iterare de la 1..n si pe faptul ca un int a[10] are by default valoarea 0 in elementele sale.

821. Se citesc doua numere naturale n si m (1<=m,n<=100) si apoi o matrice cu n linii si m coloane av�nd elementele numere �ntregi cu cel mult 4 cifre fiecare. Afisati pentru fiecare coloana a matricii numarul de elemente al celui mai lung subsir strict crescator care se poate forma parcurg�nd elementele coloanei de sus �n jos. Pentru citire se va folosi fisierul 1.in, iar pentru afisare fi?ierul 1.out.
     Exemplu:
     1.in
     4 4
     1 4 2 3
     2 9 8 7
     3 6 3 8
     1 2 3 3
     1.out
     3 2 2 3

their solution:
```
#include <fstream>
using namespace std;
ifstream fin("1.in");
ofstream fout("1.out");

int A[101][101],n,m,L[101];

int main()
{
    fin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            fin>>A[i][j];
    for(int c=1;c<=m;c++)
    {//pentru fiecare coloana
        int lmax=0;
        for(int i=1;i<=n;i++)
        {
            int l=0;
            for(int j=1;j<i;j++)
                if(A[j][c]<A[i][c] && L[j]>l)
                    l=L[j];
                L[i]=l+1;
                if(L[i]>lmax) lmax=L[i];
        }
        fout<<lmax<<" ";
    }
    return 0;
}
```

750. O livada este impartita in nXm zone. In fiecare zona creste cate un pom. Din fiecare pom cade pe jos o cantitate de fructe.
     In zona stanga sus se afla un arici care vrea sa ajunga in zona dreapta jos. Ariciul se poate deplasa doar pe doua directii: in jos sau spre dreapta.
     Determinati cantitatea maxima de fructe pe care le poate aduna ariciul prin deplasarea din pozitia initiala in cea dorita.
     Citirea se face din fisierul arici.in care contine pe prima linie dimensiunile livezii, adica n si m, si apoi cantitatea de fructe din fiecare dintre cele nXm zone.
     Afisarea cantitatii maxime de fructe se va face in fisierul arici.out.
     Exemplu:
     arici.in
     3 3
     0 4 1
     0 1 1
     1 0 1
     arici.out
     7

```
#include<fstream>
using namespace std;
ifstream f("arici.in");
ofstream g("arici.out");

int a[101][101],max,n,m,i,j;

int main()
{
	f>>n>>m;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
		{
			f>>a[i][j];
			if(a[i-1][j]>a[i][j-1])
				a[i][j]=a[i][j]+a[i-1][j];
			else a[i][j]=a[i][j]+a[i][j-1];
		}
	g<<a[n][m];
	f.close();
	g.close();
	return 0;
}
```