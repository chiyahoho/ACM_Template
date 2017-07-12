int n,m,u,v,c,tot,d,dd,dist[N],num[N],lnk[N],heap[N],done[N];
struct edge{int v,l;};
vector<edge> e[N];

void up(int p){
    while(p>1 && heap[p]<heap[p>>1]){
        swap(heap[p],heap[p>>1]);
        swap(lnk[num[p]],lnk[num[p>>1]]);
        swap(num[p],num[p>>1]);
        p>>=1;
    }
}
void down(int p){
    while(p<=(tot>>1)){
        int k=p<<1;
        if (k<tot && heap[k]>heap[k+1]) k++;
        if (heap[p]<=heap[k]) return;
        swap(heap[p],heap[k]);
        swap(lnk[num[p]],lnk[num[k]]);
        swap(num[p],num[k]);
        p=k;
    }
}

int main(){
//freopen("test.in","r",stdin);
while(cin>>n>>m,n&&m){
    rep(i,1,n) e[i].clear();
    rep(i,1,m){
        cin>>u>>v>>c;
        e[u].push_back(edge(v,c));
        e[v].push_back(edge(u,c));
    }
    rep(i,1,n) dist[i]=heap[i]=oo;
    rep(i,1,n) done[i]=0;
    dist[1]=heap[1]=0;
    tot=n;
    rep(i,1,n) num[i]=lnk[i]=i;//num[i]:堆中标号为i的点在图中是哪个点 lnk[i]:图中标号为i的点在堆中的标号是多少
    rep(i,1,n){
        done[u=num[1]]=1;
        dist[u]=d=heap[1];
        heap[1]=heap[tot]; num[1]=num[tot]; lnk[num[tot--]]=1;
        down(1);
        For(j,e[u].size()){
            v=e[u][j].v; dd=d+e[u][j].l;
            if (!done[v] && heap[lnk[v]]>dd){
                heap[lnk[v]]=dd;
                up(lnk[v]);
            }
        }
    }
    cout<<dist[n]<<endl;
}
}