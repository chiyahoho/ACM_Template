void tarjan(int u){
    low[u]=dfn[u]=++cc;
    q[++top]=u;
    instack[u]=true;
    int v;
    For(i,e[u].size()){
        v=e[u][i];
        if (!dfn[v]){
            tarjan(v);
            upmin(low[u],low[v]);
        }
        else if (instack[v]) upmin(low[u],dfn[v]);
    }

    if (dfn[u]==low[u]) do{
        v=q[top--];
        instack[v]=false;
        //v被缩到u中，更新信息，如po[v]=u;
    } while (u!=v);
}

int main(){
    rep(i,1,n) if (!dfn[i]) tarjan(i);
}