#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
int maxx=1000000;
int n,m;
int p[100001];
bool vst[1000001];
int fst[1000001];
int e[1000001];
void Eular() {
    int i,j,k;
    for (i=2; i<=maxx; i++) {
        if (!vst[i]) {
            p[++p[0]] = i;
            fst[i]=p[0];
            e[i] = i-1;
        }
        for (j=1; j<=p[0] && i*p[j]<=maxx; j++) {
            k=i*p[j];
            vst[k]=1;
            fst[k]=j;
            if (i%p[j]==0) {
                e[k] = e[i] * p[j];
                break;
            }
            else {
                e[k] = e[i] * (p[j] - 1);
            }
        }
    }
    //for (i=1; i<=100; i++) cout<<p[i]<<" ";
    //cout<<endl;
}
int b[101];
void devide(int u) {
    int i,j;
    b[0]=0;
    while (u>1) {
        i=fst[u];
        j=p[i];
        b[++b[0]]=j;
        while (u%j==0) u/=j;
    }
    //for (i=1; i<=b[0]; i++) cout<<b[i]<<" ";
    //cout<<endl;
}
int pow(int a,int b) {
    int ret=1;
    while (b) {
        if (b&1) ret=(ll)ret*a%n;
        a=(ll)a*a%n;
        b>>=1;
    }
    return ret;
}
bool jud(int u) {
    int i;
    if (pow(u,m)==0) return 0;
    for (i=1; i<=b[0]; i++)
        if (pow(u,m/b[i])==1) return 0;
    return 1;
}
int main() {
    int i;
    Eular();
    while (scanf("%d",&n)!=EOF) {
        m = e[n];
        //cout<<m<<endl;
        //continue;
        devide(m);
        for (i=2; i<n; i++)
            if (jud(i)) printf("%d ",i);
        printf("%d\n");
    }
    return 0;
}
