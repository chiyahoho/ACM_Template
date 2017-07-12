#include<stdio.h>

    long fa[100000];

int gf(int u){
    if (u==fa[u]) return u;
    return fa[u]=gf(fa[u]);
}
void main(){
    long i,n,m,u,v,flag=0;
    scanf("%ld%ld",&n,&m);
    for (i=1;i<=n;i++) fa[i]=i;
    for (i=1;i<=m;i++){
        scanf("%ld%ld",&u,&v);
        if (gf(u)!=gf(v))
            fa[gf(u)]=gf(v);
        else {
            flag=1;
            break;
        }
    }
    printf("%ld\n",flag);
    (flag==1)?printf("false"):printf("true");
}
