//hdu49666
struct node{
    int u,v,l;
}e[10000];
const int oo=10000000;
int nn,m,mm,x,c1,c2,l1,l2,cost,sum[1000],minl[1000],pre[1000],id[1000],vis[1000];

inline void add(int u,int v,int l){
    e[++m].u=u;
    e[m].v=v;
    e[m].l=l;
}

int zhuliu(int root,int n,int m) {
    int u,v,cost=0;
    while(1){ 
        pre[root]=0;
        rep(i,1,n) minl[i]=oo;
        rep(i,1,m){
            u=e[i].u; v=e[i].v;
            if (e[i].l<minl[v] && u!=v){
                pre[v]=u;
                minl[v]=e[i].l;
            }
        }
        rep(i,1,n) if (i!=root && minl[i]==oo) return -1;
        int nn=minl[root]=0;
        rep(i,0,n) id[i]=vis[i]=-1;

        rep(i,1,n){
            cost+=minl[i];
            for(v=i;v && vis[v]==-1;v=pre[v]) vis[v]=i;
            if (v && vis[v]==i){
                id[v]=++nn;
                for(u=pre[v];u!=v;u=pre[u]) id[u]=nn;
            }
        }
        if (!nn) break;
        rep(i,1,n) if(id[i]==-1) id[i]=++nn;
        int j=1;
        rep(i,1,m){
            v=e[i].v;
            e[j].u=id[e[i].u];
            e[j].v=id[e[i].v];
            if (e[j].u!=e[j].v){
                e[j].l=e[i].l-minl[v];
                j++;
            }
        }
        m=j-1; n=nn;
        root=id[root];
    }
    return cost;
} 

int main(){
    while (1){
        scanf("%d%d",&nn,&mm);
        if (nn==0 && mm==0) break;
        sum[0]=1; m=0;
        rep(i,1,nn){
            scanf("%d",&x); x++;
            sum[i]=sum[i-1]+x;
            rep(j,1,x-1) add(sum[i-1]+j+1,sum[i-1]+j,0);
            add(1,sum[i-1]+1,0);
        }
        rep(i,1,mm){
            scanf("%d%d%d%d%d",&c1,&l1,&c2,&l2,&cost);
            add(sum[c1-1]+l1+1,sum[c2-1]+l2+1,cost);
        }
         printf("%d\n",zhuliu(1,sum[nn],m));
    }
}