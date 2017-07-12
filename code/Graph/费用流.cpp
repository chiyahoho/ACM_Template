int d[],h[],q[],f[],ans,tot,ss,tt;
struct edge{int l,v,n,c;}e[];
struct PRE{int v,e;}pre[];
int spfa(){
    int l,r,u,v,y,k;
    rep(i,ss,tt){
        d[i]=oo;
        f[i]=pre[i].e=0;
        pre[i].v=-1;
    }
    l=0,r=1;
    q[1]=ss; d[ss]=0;
    while(l<r){
        u=q[++l]; f[u]=0;
        for(y=h[u];y;y=e[y].n){
            v=e[y].v;
            if (e[y].l>0 && relax(u,y,v) && !f[v]){
                f[v]=1;
                q[++r]=v;
            }
        }
    }
    if (d[tt]>=oo) return 0;
    for(k=oo,v=tt;pre[v].v!=-1;v=pre[v].v) upmin(k,e[pre[v].e].l);
    for(v=tt;pre[v].v!=-1;v=pre[v].v){
        y=pre[v].e;
        ans+=e[y].c*c;
        e[y].l-=k; e[y^1].l+=k;
    }
    return 1;
}

int main(){
    //建边，tot=1
    while (spfa()){}
    cout<<ans<<endl;
}