#include <fstream>
using namespace std;
ifstream fin ("test01.in");
ofstream fout ("test01.out");

int main() {
    int a[100][100],s[100][100]={0};
    int i,j,m,n;
    fin>>n>>m;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++) {
            fin>>a[i][j];
            if(i==1 && j==1) s[i][j]=a[i][j];
            else if(i==1) s[i][j]=s[i][j-1]+a[i][j];
                 else if(j==1) s[i][j]=s[i-1][j]+a[i][j];
                      else if(s[i-1][j]<s[i][j-1]) s[i][j]=s[i-1][j]+a[i][j];
                           else s[i][j]=s[i][j-1]+a[i][j];
        }

    fout<<s[n][m]<<endl;
    fin.close();
    fout.close();
    return 0;
}