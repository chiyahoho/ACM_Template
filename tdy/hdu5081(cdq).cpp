#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<map>
#define pb push_back
#define mp make_pair
#define st first
#define nd second
using namespace std;
typedef long long ll;
typedef vector<int>::iterator vit;
typedef vector<pair<int,int> >::iterator pit;
int n,m;
struct Trie{
    int ch[26];
    int fail;
    void init() {
        memset(ch,0,sizeof ch);
        fail=0;
    }
} T[100001];
vector<int> adj[100001];
queue<int> q;
void ac() {
    int i,j,k,fail;
    while (!q.empty()) q.pop();
    T[1].fail=0;
    q.push(1);
    while (!q.empty()) {
        i=q.front();
        q.pop();
        fail=T[i].fail;
        for(j=0; j<26; j++) {
            if (T[i].ch[j]) {
                k=T[i].ch[j];
                T[k].fail=T[fail].ch[j];
                if (!T[k].fail) T[k].fail=1;
                q.push(k);
            }
            else {
                T[i].ch[j]=T[fail].ch[j];
            }
        }
    }
}
int tot;
int f[100001];
int fr[100001];
vector<int> g[100001];
int d[100001];
int fa[100001][21];
void dfs(int u,int v) {
    int j;
    f[u]=v;
    for (int i=0; i<16; i++)
        if (fa[v][i])
            fa[v][i+1]=fa[fa[v][i]][i];
        else break;
    for (vit it=adj[u].begin(); it!=adj[u].end(); it++) {
        j=*it;
        tot++;
        g[v].pb(tot);
        d[tot]=d[v]+1;
        fa[tot][0]=v;
        dfs(j,tot);
    }
    fr[v]=tot;
}
int lca(int u,int v) {
    int i;
    if (u==v) return u;
    if (d[u]>d[v]) swap(u,v);
    for (i=16; i>=0; i--)
        if (d[fa[v][i]]>=d[u]) v=fa[v][i];
    if (u==v) return u;
    for (i=16; i>=0; i--)
        if (fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
    return fa[u][0];
}
int a[100001];
vector<int> b[100001];
int c[100001];
void ready(int u,int l) {
    int i,j,k;
    sort(c+1,c+l+1);
    if (a[u]==1) {
        j=0;
        for (i=1; i<=l; i++)
        if (c[i]>fr[j]) {
            b[u].pb(c[i]);
            j=c[i];
        }
    }
    else {
        j=c[1];
        b[u].pb(j);
        for (i=2; i<=l; i++) {
            k=lca(j,c[i]);
            b[u].pb(k);
            b[u].pb(c[i]);
            j=c[i];
        }
    }
}
vector<pair<int,int> > vs[400001];
vector<int> vt[400001];
int qs[200001];
void build(int u,int l,int r) {
    int mid;
    if (l==r) {
        vs[u].clear();
        vt[u].clear();
        if (a[l]==1) {
            for (vit it=b[l].begin(); it!=b[l].end(); it++) {
                vs[u].pb(mp(*it,1));
            }
        }
        else {
            int i,j;
            j=0;
            for (vit it=b[l].begin(); it!=b[l].end(); it++) {
                qs[++j]=*it;
            }
            sort(qs+1,qs+j+1);
            for (i=1; i<=j; i++)
                if (qs[i]!=qs[i-1]) vt[u].pb(qs[i]);
        }
        return;
    }
    mid=l+r>>1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    int i,j,l1,l2,lt,rt;

    lt=u<<1;
    rt=u<<1|1;

    vs[u].clear();
    l1=vs[lt].size();
    l2=vs[rt].size();
    i=0,j=0;
    while (i<l1&&j<l2) {
        int t;
        t=vs[lt][i].st-vs[rt][j].st;
        if (t<0) vs[u].pb(vs[lt][i++]);
        if (t>0) vs[u].pb(vs[rt][j++]);
        if (t==0) {
            vs[u].pb(mp(vs[lt][i].st,vs[lt][i].nd+vs[rt][j].nd));
            i++;
            j++;
        }
    }
    while (i<l1) vs[u].pb(vs[lt][i++]);
    while (j<l2) vs[u].pb(vs[rt][j++]);

    vt[u].clear();
    l1=vt[lt].size();
    l2=vt[rt].size();
    i=0,j=0;
    while (i<l1&&j<l2) {
        int t;
        t=vt[lt][i]-vt[rt][j];
        if (t<0) vt[u].pb(vt[lt][i++]);
        if (t>0) vt[u].pb(vt[rt][j++]);
        if (t==0) {
            vt[u].pb(vt[lt][i]);
            i++;
            j++;
        }
    }
    while (i<l1) vt[u].pb(vt[lt][i++]);
    while (j<l2) vt[u].pb(vt[rt][j++]);

}
struct sta{
    int u,v;
    ll z;
    sta() {}
    sta(int u,int v,ll z):u(u),v(v),z(z) {}
} stk[100001];
int top;
ll sum[100001];
ll ans[100001];
pair<int,int> s[100001];
void cdq(int u,int l,int r) {
    int mid;
    if (l==r) return;
    mid=l+r>>1;
    cdq(u<<1,l,mid);

    if (!vs[u<<1].empty()&&!vt[u<<1|1].empty()) {

        int i,j,k,l1,l2,lt,rt;
        lt=u<<1;
        rt=u<<1|1;
        l1=vs[lt].size();
        l2=vt[rt].size();
        i=0,j=0,k=0;
        while (i<l1&&j<l2) {
            int t;
            t=vs[lt][i].st-vt[rt][j];
            if (t<0) s[++k]=vs[lt][i++];
            if (t>0) s[++k]=mp(vt[rt][j++],0);
            if (t==0) {
                s[++k]=vs[lt][i];
                i++;
                j++;
            }
        }
        while (i<l1) s[++k]=vs[lt][i++];
        while (j<l2) s[++k]=mp(vt[rt][j++],0);

        top=0;
        for (i=1; i<=k; i++) {
            while (top&&s[i].st>fr[stk[top].u]) top--;
            ll t;
            t=(ll)(d[s[i].st]-d[stk[top].u])*stk[top].v+s[i].nd+stk[top].z;
            top++;
            stk[top]=sta(s[i].st,stk[top-1].v+s[i].nd,t);
            sum[s[i].st]=t;
        }

        for (i=mid+1; i<=r; i++)
        if (a[i]==2) {
            int k;
            k=0;
            for (vit it=b[i].begin(); it!=b[i].end(); it++) {
                k^=1;
                if (k) ans[i]+=sum[*it];
                else ans[i]-=sum[*it];
            }
        }

    }

    cdq(u<<1|1,mid+1,r);
}
int main() {
    int __,i,j,k,x;
    char ch;
    scanf("%d",&__);
    while (__--) {
        scanf("%d",&n);
        for (i=1; i<=n; i++)
            T[i].init();
        for (i=2; i<=n; i++) {
            scanf("%d %c",&x,&ch);
            T[x].ch[ch-'a']=i;
        }
        ac();
        for (i=1; i<=n; i++)
            adj[i].clear();
        for (i=2; i<=n; i++) {
            adj[T[i].fail].pb(i);
        }
        for (i=1; i<=n; i++) g[i].clear();
        tot=1;
        d[1]=1;
        memset(fa,0,sizeof fa);
        dfs(1,1);

        scanf("%d",&m);
        for (i=1; i<=m; i++) b[i].clear();
        memset(ans,0,sizeof ans);
        for (i=1; i<=m; i++) {
            scanf("%d",&a[i]);
            scanf("%d",&k);
            for (j=1; j<=k; j++) {
                scanf("%d",&x);
                c[j]=f[x];
            }
            ready(i,k);
        }
        build(1,1,m);
        cdq(1,1,m);
        for (i=1; i<=m; i++)
            if (a[i]==2)
                printf("%I64d\n",ans[i]);
    }
    return 0;
}