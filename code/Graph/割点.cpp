int n,ans,u,v,low[N],dfn[N],cut[N],rt_son,sign;
vector<int> e[N];
void dfs(int u){
    low[u]=dfn[u]=++sign;
    For(i,e[u].size()){
        int v=e[u][i];
        if (!dfn[v]){
            dfs(v);
            if (u==1) rt_son++;
            upmin(low[u],low[v]);
            if (low[v]>=dfn[u]) cut[u]=1;
            if (low[v]>dfn[u]) uv是割边;
        }
        else upmin(low[u],dfn[v]);
    }
}

int main(){
    ans=sign=rt_son=0;
    rep(i,1,n) dfn[i]=cut[i]=0;
    dfs(1);
    if (rt_son<2) cut[1]=0;//有两个子树的根是割点
    rep(i,1,n) ans+=cut[i];
    cout<<ans<<endl;
}