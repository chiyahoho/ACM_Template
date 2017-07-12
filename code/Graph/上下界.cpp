//bzoj2502: 清理雪道  2011福建集训

void add(int u,int v,int l){
    e[++tot].v=v;
    e[tot].l=l;
    e[tot].n=h[u];
    e[tot].b=tot+1;
    h[u]=tot;

    e[++tot].v=u;
    e[tot].l=0;
    e[tot].n=h[v];
    e[tot].b=tot-1;
    h[v]=tot;
}

int sap(int u,int flow){
    if (u==tt) return flow;
    int sapp=0;
    for (int y=h[u];y;y=e[y].n){
        int v=e[y].v;
        if (v<=up && g[u]==g[v]+1 && e[y].l){
            int ff=sap(v,min(flow-sapp,e[y].l));
            sapp+=ff;
            e[y].l-=ff;
            e[e[y].b].l+=ff;
            if (sap==flow) return sapp;
        }
    }
    if (g[ss]==up) return sapp;
    if (--vg[g[u]]==0) g[ss]=up;
    vg[++g[u]]++;
}

int main(){
freopen("2502.in","r",stdin);
freopen("2502.out","w",stdout);
    cin>>n;
    ss=0; tt=n+1; x=n+2; y=n+3;
    rep(u,1,n){
        add(ss,u,oo);
        add(u,tt,oo);
        cin>>m;
        rep(i,1,m){
            cin>>v;
            add(u,v,oo);
            add(u,x,1);
            add(y,v,1);
        }
    }
    add(tt,ss,oo);

    ss=y; tt=x; up=n+3;
    g[ss]=1; vg[1]=1; vg[0]=oo;
    while (g[ss]<up) sap(ss,oo);
    ans=e[tot].l;

    e[tot].l=e[tot-1].l=0;
    ss=n+1; tt=0; up=n+1;
    For(i,n+10) g[i]=vg[i]=0;
    g[ss]=1; vg[1]=1; vg[0]=oo;
    while (g[ss]<up) ans-=sap(ss,oo);

    cout<<ans<<endl;
}