int n,m,ans,fa[N];
struct edge{int u,v,l;}e[M];
int main(){
    cin>>n>>m;
    ans=0;
    rep(i,1,m) cin>>e[i].u>>e[i].v>>e[i].l;
    sort(e+1,e+m+1);
    rep(i,1,n) fa[i]=i;
    rep(i,1,m) if (gf(e[i].u)!=gf(e[i].v)){
        fa[gf(e[i].v)]=gf(e[i].u);
        ans+=e[i].l;
    }
    cout<<ans<<endl;
}