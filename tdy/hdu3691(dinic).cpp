#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int inf=~0u>>1;
int n,m;
int S,T;
int ans;
struct node{
    int to,f,v,next;
} w[100010];
int h[301],cnt=1;
void add(int x,int y,int z) {
    w[++cnt]=(node){y,z,z,h[x]};
    h[x]=cnt;
    w[++cnt]=(node){x,z,z,h[y]};
    h[y]=cnt;
}
queue<int> q;
int d[301];
bool bfs(int S) {
    int i,j,v;
    memset(d,0,sizeof d);
    d[S]=1;
    q.push(S);
    while (!q.empty()) {
        i=q.front();
        q.pop();
        for (v=h[i]; v; v=w[v].next) {
            j=w[v].to;
            if (w[v].f&&!d[j]) {
                d[j]=d[i]+1;
                q.push(j);
            }
        }
    }
    return d[T];
}
int dfs(int u,int f) {
    int j,v,t,ret=0;
    if (u==T) return f;
    for (v=h[u]; v; v=w[v].next) {
        j=w[v].to;
        if (w[v].f&&d[j]==d[u]+1) {
            t=dfs(j,min(f,w[v].f));
            w[v].f-=t,w[v^1].f+=t;
            f-=t,ret+=t;
            if (!f) return ret;
        }
    }
    return ret;
}
int cal() {
    int i,j,v,ret=0;
    for (v=h[T]; v; v=w[v].next) {
        j=w[v].to;
        ret+=w[v].f-w[v].v;
    }
    return ret;
}
int main() {
    int i,p,x,y,z;
    while (scanf("%d%d%d",&n,&m,&S)!=EOF) {
        if (n==0&&m==0&&S==0) break;
        memset(h,0,sizeof h);
        cnt=1;
        for (i=1; i<=m; i++) {
            scanf("%d%d%d",&x,&y,&z);
            add(x,y,z);
        }
        ans=inf;
        p=S;
        for (i=1; i<=n; i++)
            if (i!=S) {
                T=i;
                while (bfs(p)) dfs(p,inf);
                while (bfs(S)) dfs(S,inf);
                ans=min(ans,cal());
                p=i;
            }
        printf("%d\n",ans);
    }
    return 0;
}
