#include<iostream>
#include<cstdio>
#include<algorithm>
#define mp make_pair
#define st first
#define nd second
using namespace std;
const int inf=~0u>>1;
int n,m;
int ans;
int a[100001];
pair<int,int> b[100001];
int f[100001];
struct ST{
    int ls,rs,v;
} T[2000001];
int tot;
int h[100001];
void build(int u,int l,int r) {
    int mid;
    if (l==r) return;
    mid=l+r>>1;
    T[u].ls=++tot;
    T[u].rs=++tot;
    T[u].v=0;
    build(T[u].ls,l,mid);
    build(T[u].rs,mid+1,r);
}
int add(int u,int l,int r,int k) {
    int mid;
    T[++tot]=T[u];
    u=tot;
    T[u].v++;
    if (l==r) return u;
    mid=l+r>>1;
    if (k<=mid)
        T[u].ls=add(T[u].ls,l,mid,k);
    else T[u].rs=add(T[u].rs,mid+1,r,k);
    return u;
}
int ask(int u,int v,int l,int r,int k) {
    int mid,t;
    if (l==r) return l;
    mid=l+r>>1;
    t=T[T[v].ls].v-T[T[u].ls].v;
    if (t>=k) return ask(T[u].ls,T[v].ls,l,mid,k);
    else return ask(T[u].rs,T[v].rs,mid+1,r,k-t);
}
int main() {
    int __,i,j,l,r,v;
    scanf("%d",&__);
    while (__--) {
        scanf("%d%d",&n,&m);
        for (i=1; i<=n; i++) {
            scanf("%d",&v);
            b[i]=mp(v,i);
        }
        sort(b+1,b+n+1);
        b[0]=mp(inf,inf);
        for (i=1,j=0; i<=n; i++) {
            if (b[i]!=b[i-1]) {
                j++;
                f[j]=b[i].st;
            }
            a[b[i].nd]=j;
        }
        tot=1;
        build(1,1,n);
        h[0]=1;
        for (i=1; i<=n; i++)
            h[i]=add(h[i-1],1,n,a[i]);
        for (i=1; i<=m; i++) {
            scanf("%d%d%d",&l,&r,&v);
            ans=ask(h[l-1],h[r],1,n,v);
            ans=f[ans];
            printf("%d\n",ans);
        }
    }
    return 0;
}
