int tp(){
    int l=0,r=0;
    rep(i,1,n) if (!ru[i]) q[++r]=i;
    while(l<r){
        int u=q[++l];
        For(i,e[u].size()){
            int v=e[u][i];
            if ((--ru[v])==0) q[++r]=v;
        }
    }
    return r==n;
}
判断图中是否有环，如果有环那么途中会剩余一些点和边的。
(判断图中是否有负权环的是Bellman-ford)
有唯一拓扑序当且仅当任何时刻入度=0，出度>0的点只有一个。