int n,q[N],dist[N],f[N];
struct edge{int v,l;};
vector<edge> e[N];

void spfa(int uu){
    For(i,n+2) dist[i]=oo,f[i]=0;
    int l=0,r=1,u,v;
    q[1]=uu; dist[uu]=0;
    while (l!=r){
        l=(l%n)+1;
        f[u=q[l]]=false;
        For(i,e[u].size()){
            v=e[u][i].v;
            if (dist[v]>dist[u]+e[u][i].l){
                dist[v]=dist[u]+e[u][i].l;
                if (!f[v]){
                    r=(r%n)+1;
                    f[q[r]=v]=true;
                }
            }
        }
    }
}