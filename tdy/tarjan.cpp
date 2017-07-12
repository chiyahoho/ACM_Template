struct node{
    int to,next;
    bool flag;
} w[300001];
int h[100001],cnt=1;
void add(int x,int y) {
    w[++cnt]=(node){y,h[x],0};
    h[x]=cnt;
    w[++cnt]=(node){x,h[y],0};
    h[y]=cnt;
}
int dfn[100001];
int low[100001];
int tot;
void tarjan(int u,int fa) {
    int j,v;
    dfn[u]=low[u]=++tot;
    for (v=h[u]; v; v=w[v].next) {
        j=w[v].to;;
        if (j==fa) continue;
        if (!dfn[j]) {
            tarjan(j,u);
            if (low[j]>dfn[u]) w[v].flag=1,w[v^1].flag=1;
            low[u]=min(low[u],low[j]);
        }
        else low[u]=min(low[u],dfn[j]);
    }
}
