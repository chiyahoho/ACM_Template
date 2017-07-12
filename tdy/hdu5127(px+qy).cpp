#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
#define mp make_pair
#define pb push_back
#define st first
#define nd second
using namespace std;
typedef map<pair<int,int>,int>::iterator mit;
typedef long long ll;
typedef pair<int,int> pa;
const ll inf=~0ull>>1;
int n;
int tot;
ll ans[60001];
pair<int,int> a[60001];
map<pair<int,int>,int> b;
pair<pair<int,int>,pair<int,int> > q[60001];
int top;
vector<pair<int,int> > h[200001];
void build(int u,int l,int r) {
    int mid;
    mid=l+r>>1;
    h[u].clear();
    if (l==r) return;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
}
void add(int u,int l,int r,int lt,int rt,int x,int y) {
    int mid;
    if (l>rt||r<lt) return;
    if (l>=lt&&r<=rt) {
        h[u].pb(mp(x,y));
        return;
    }
    mid=l+r>>1;
    add(u<<1,l,mid,lt,rt,x,y);
    add(u<<1|1,mid+1,r,lt,rt,x,y);
}
bool cmp(const pa &a,const pa &b) {
    return a.nd<b.nd||a.nd==b.nd&&a.st<b.st;
}
pair<int,int> q1[60001];
pair<int,int> q2[60001];
int m1,m2;
pa operator+(const pa &a,const pa &b) {
    return mp(a.st+b.st,a.nd+b.nd);
}
pa operator-(const pa &a,const pa &b) {
    return mp(a.st-b.st,a.nd-b.nd);
}
ll operator*(const pa &a,const pa &b) {
    return (ll)a.st*b.st+(ll)a.nd*b.nd;
}
ll operator/(const pa &a,const pa &b) {
    return (ll)a.st*b.nd-(ll)a.nd*b.st;
}
ll area(pa p0,pa p1,pa p2) {
    return (p1-p0)/(p2-p0);
}
void scan(int u) {
    int i,l;
    m1=0;
    m2=0;
    l=h[u].size();
    for (i=0; i<l; i++) {
        while (m1>1&&area(q1[m1-1],q1[m1],h[u][i])<=0) m1--;
        q1[++m1]=h[u][i];
    }
    for (i=l-1; i>=0; i--) {
        while (m2>1&&area(q2[m2-1],q2[m2],h[u][i])<=0) m2--;
        q2[++m2]=h[u][i];
    }
}
ll binary(int x,int y,int px,int py) {
    int l,r,mid;
    ll ret;
    l=1;
    r=m1;
    while (l<r) {
        mid=l+r>>1;
        if ((q1[mid+1]-q1[mid])/mp(x,y)>0) l=mid+1;
        else r=mid;
    }
    ret=mp(px,py)*q1[l];
    x=-x;
    y=-y;
    l=1;
    r=m2;
    while (l<r) {
        mid=l+r>>1;
        if ((q2[mid+1]-q2[mid])/mp(x,y)>0) l=mid+1;
        else r=mid;
    }
    ret=max(ret,mp(px,py)*q2[l]);
    return ret;
}
void cal(int u,int l,int r) {
    int mid,i,x,y;
    sort(h[u].begin(),h[u].end(),cmp);
    if (!h[u].empty()) {
        scan(u);
        for (i=l; i<=r; i++) {
            x=-a[i].nd,y=a[i].st;
            if (y<0) x=-x,y=-y;
            ans[i]=max(ans[i],binary(x,y,a[i].st,a[i].nd));
        }
    }
    if (l==r) return;
    mid=l+r>>1;
    cal(u<<1,l,mid);
    cal(u<<1|1,mid+1,r);
}
int main() {
    int i,l,r,t,x,y;
    while (scanf("%d",&n),n) {
        tot=0;
        top=0;
        b.clear();
        for (i=1; i<=n; i++) {
            scanf("%d%d%d",&t,&x,&y);
            if (!t) a[++tot]=mp(x,y);
            else if (t==1) {
                b[mp(x,y)]=tot+1;
            }
            else {
                l=b[mp(x,y)];
                r=tot;
                if (l<=r) q[++top]=mp(mp(x,y),mp(l,r));
                b.erase(mp(x,y));
            }
        }
        for (mit it=b.begin(); it!=b.end(); it++) {
            x=it->st.st;
            y=it->st.nd;
            l=it->nd;
            r=tot;
            if (l<=r) q[++top]=mp(mp(x,y),mp(l,r));
        }
        if (!tot) continue;
        for (i=1; i<=tot; i++) ans[i]=-inf;
        build(1,1,tot);
        for (i=1; i<=top; i++) {
            x=q[i].st.st;
            y=q[i].st.nd;
            l=q[i].nd.st;
            r=q[i].nd.nd;
            add(1,1,tot,l,r,x,y);
        }
        cal(1,1,tot);
        for (i=1; i<=tot; i++)
            printf("%I64d\n",ans[i]);
    }
    return 0;
}
