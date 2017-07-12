#include<stdio.h>

struct node{
    long long s,p;
};

node tr[1000000];

void pass(long p,long l,long r){
    tr[p].s+=tr[p].p*(r-l+1);
    if (l!=r){
        tr[p*2].p+=tr[p].p;
        tr[p*2+1].p+=tr[p].p;
    }
    tr[p].p=0;
}

void insert(long p,long l,long r,long a,long b,long long c){
    if (l==a&&r==b){
        tr[p].p+=c;
        return;
    }
    pass(p,l,r);
    tr[p].s+=(b-a+1)*c;
    int m=(l+r)/2;
    if (b<=m) insert(p*2,l,m,a,b,c);
    else if (a>m) insert(p*2+1,m+1,r,a,b,c);
    else {
        insert(p*2,l,m,a,m,c);
        insert(p*2+1,m+1,r,m+1,b,c);
    }
}

long long get(long p,long l,long r,long a,long b){
    pass(p,l,r);
    if (l==a&&r==b) return tr[p].s;
    long m=(l+r)/2;
    if (b<=m) return get(p*2,l,m,a,b);
    else if (a>m) return get(p*2+1,m+1,r,a,b);
    else {
        long long x1=get(p*2,l,m,a,m);
        long long x2=get(p*2+1,m+1,r,m+1,b);
        return x1+x2;
    }
}

int main(){
    freopen("3468.in","r",stdin);
    freopen("3468.out","w",stdout);
    long n,m,a,b,i;
    long long c;
    char ch;
    scanf("%ld%ld",&n,&m);
    for (i=1;i<=n;i++){
        scanf("%lld",&c);
        insert(1,1,n,i,i,c);
    }
    for (i=1;i<=m;i++){
        scanf("\n%c",&ch);
        if (ch=='Q') {
            scanf("%ld%ld",&a,&b);
            printf("%lld\n",get(1,1,n,a,b));
        }else {
            scanf("%ld%ld%lld",&a,&b,&c);
            insert(1,1,n,a,b,c);
        }
    }
    return 0;
}
//poj 3468
