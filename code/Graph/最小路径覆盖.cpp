void dfs(int u){
    int y,v;
    cout<<u<<' ';
    for(y=h[u];e[y].l!=0;y=e[y].n);
    v=e[y].v;
    if (v==0) return;
    dfs(v-n);
}

int main(){
    ss=0,tt=2*n+1;
    //建边，tot=1
    ans=n;
    g[ss]=1; vg[1]=1; vg[0]=oo;
    while(g[ss]<tt) ans-=sap(ss,oo);

    rep(u,n+1,2*n){
        for(y=h[u];e[y].v!=tt;y=e[y].n);
        if (e[y].l==1){
            dfs(u-n);
            cout<<endl;
        }
    }
    cout<<ans<<endl;
}