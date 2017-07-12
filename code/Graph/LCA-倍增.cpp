void dfs(int u,int d){
    if (d) rep(i,1,20) fa[u][i]=fa[fa[u][i-1]][i-1];
    deep[u]=d;
    For(i,e[u].size()){
        fa[e[u][i]][0]=u;
        dfs(e[u][i],d+1);
    }
}

int main(){
    cin>>n;
    rep(i,1,n-1){
        cin>>u>>v;
        e[u].PB(v);
    }
    dfs(1,0);
    cin>>a>>b;
    if (deep[a]<deep[b]) swap(a,b);
    d=deep[a]-deep[b];
    per(i,20,0) if (d>=g[i]){
        d-=g[i];
        a=fa[a][i];
    }
    per(i,20,0) if (fa[a][i]!=fa[b][i]){
        a=fa[a][i];
        b=fa[b][i];
    }
    if (a!=b) a=fa[a][0];
    cout<<a<<endl;
}