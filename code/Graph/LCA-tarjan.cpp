void tarjan(int u){
    For(i,e[u].size()){
        int v=e[u][i];
        tarjan(v);
        fa[v]=u;
    }
    done[u]=1;
    For(i,qe[u].size()){
        int v=qe[u][i];
        if (done[v]) lca[u][v]=gf(v);
        else qe[v].push_back(u);
    }
}

int main(){
    cin>>n>>m;
    rep(i,1,n-1){
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    rep(i,1,n) fa[i]=i,done[i]=0;
    rep(i,1,m){
        cin>>u>>v;
        qe[u].push_back(v);
    }
    tarjan(1);
}