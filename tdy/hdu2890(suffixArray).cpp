#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<cstdlib>
#include<ctime>
#include<cstdlib>
#define pb push_back
#define mp make_pair
#define st first
#define nd second
using namespace std;
typedef vector<int>::iterator vit;
typedef map<int,int>::iterator mit;
const int inf=~0u>>2;
const int N=200000;
int n,m;
time_t temp;
struct SA{
    int a[N+1];
    int c[N+1];
    int len;
    int h[N+1];
    pair<int,int> b[N+1];
    int hs[N+1];
    int rk[N+1];
    int tab[N+1];
    int vw[N+1];
    void sa() {
        int i,j,k,x,y;
        memcpy(c,a,(len+1)*sizeof(int));
        b[0]=mp(inf,inf);
        for (i=1; i<=len; i++)
            b[i]=mp(a[i],i);
        sort(b+1,b+len+1);
        for (i=1,j=0; i<=len; i++) {
            if (b[i].st!=b[i-1].st) j++;
            a[b[i].nd]=j;
        }
        memset(hs,0,(len+1)*sizeof(int));
        for (i=1; i<=len; i++)
            hs[a[i]]++;
        for (i=1; i<=len; i++)
            hs[i]+=hs[i-1];
        for (i=len; i; i--)
            tab[hs[a[i]]--]=i;
        for (i=1; i<=len; i<<=1) {
            for (j=len-i+1,k=0; j<=len; j++)
                rk[++k]=j;
            for (j=1; j<=len; j++)
                if (tab[j]>i) rk[++k]=tab[j]-i;
            memset(hs,0,(len+1)*sizeof(int));
            for (j=1; j<=len; j++)
                hs[a[rk[j]]]++;
            for (j=1; j<=len; j++)
                hs[j]+=hs[j-1];
            for (j=len; j; j--)
                tab[hs[a[rk[j]]]--]=rk[j];
            for (j=1,k=0; j<=len; j++) {
                x=tab[j];
                y=tab[j-1];
                if (a[x]!=a[y]||a[x+i]!=a[y+i]) k++;
                vw[tab[j]]=k;
            }
            for (j=1; j<=len; j++) a[j]=vw[j];
        }
        for (i=1; i<=len; i++) {
            if (a[i]==1) h[i]=0;
            else {
                j=tab[a[i]-1];
                k=max(0,h[i-1]-1);
                while (i+k<=len && j+k<=len && c[i+k]==c[j+k]) k++;
                h[i]=k;
            }
        }
    }
} S;
int a[N+1];
int h[N+1];
int q[N+1],top;
int jud(int mid) {
    int i,j,k,t,ret=0;
    for (i=1; i<n; i++) {
        j=i;
        top=0;
        q[++top]=a[j];
        while (j<n&&h[a[j+1]]>=mid) {
            j++;
            q[++top]=a[j];
        }
        if (j-i+1>=m) {
            sort(q+1,q+top+1);
            ret=0;
            t=-inf;
            for (i=1; i<=top; i++) {
                if (q[i]-t>=mid) ret++,t=q[i];
                if (ret+top-i<m) break;
            }
            if (ret>=m) return q[1];
        }
        i=j;
        if (n-i<m) break;
    }
    return 0;
}
void binary() {
    int l=1,r=n,mid;
    while (l<r) {
        mid=l+r+1>>1;
        if (jud(mid)) l=mid;
        else r=mid-1;
    }
    int i,j;
    j=jud(l);
    if (j) {
        printf("%d\n",l);
        for (i=j; i<=j+l-1; i++)
            printf("%d\n",S.c[i]);
    }
    else printf("0\n");
}
int main() {
    int __,i,x;
    scanf("%d",&__);
    while (__--) {
        scanf("%d%d",&n,&m);

        memset(S.a,0,(2*n+1)*sizeof(int));
        S.len=n;
        for (i=1; i<=n; i++) {
            scanf("%d",&x);
            S.a[i]=x;
        }
        S.sa();
        memcpy(a,S.tab,(n+1)*sizeof(int));
        memcpy(h,S.h,(n+1)*sizeof(int));
        binary();
        if (__) printf("\n");
    }
    return 0;
}
