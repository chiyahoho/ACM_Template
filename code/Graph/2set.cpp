int n,x[N],y[N],flag,q[N],top,low[N],dfn[N],cc,f[N],ff[N],po[N];
vector<int> e[N];
void add(int u,int v){e[u].PB(v);}

void tarjan(int u){
    low[u]=dfn[u]=++cc;
    q[++top]=u;
    f[u]=ff[u]=true;
    int v;
    For(i,e[u].size()){
        v=e[u][i];
        if (!f[v]){
            tarjan(v);
            upmin(low[u],low[v]);
        }
        else if (ff[v]) upmin(low[u],dfn[v]);
    }

    if (dfn[u]==low[u]) do{
        v=q[top--];
        ff[v]=false;
        po[v]=u;
    } while (u!=v);
}

void main(){
    freopen("3207.in","r",stdin);
    freopen("3207.out","w",stdout);
    flag=true;
    cin>>n>>n;
    rep(i,1,n){
        cin>>x[i]>>y[i];
        if (x[i]>y[i]) swap(x[i],y[i]);
    }
    rep(i,1,n-1) rep(j,i+1,n)
        if (!( (y[i]<=x[j]) || (y[j]<=x[i]) || ((x[i]<=x[j])&&(y[j]<=y[i])) || ((x[i]>=x[j])&&(y[j]>=y[i])) )){
            add(i,j+n); add(j,i+n);
            add(i+n,j); add(j+n,i);
        }
    rep(i,1,2*n) if (!f[i]) tarjan(i);
    rep(i,1,n) if (po[i]==po[i+n]) flag=false;
    flag?cout<<"panda is telling the truth..."<<endl:cout<<"the evil panda is lying again"<<endl;
}