//m行n+1列，m条方程n个未知数
void gauss(){
    rep(i,1,m){
        int p=1;
        rep(j,1,n) if (abs(a[i][p])<abs(a[i][j])) p=j;
        if (dcmp(a[i][p])==0){
            if (dcmp(a[i][n+1])==0) continue;
            else return 1;
        }
        xp[i]=p;
        double tmp=a[i][p];
        rep(j,1,n+1) a[i][j]/=tmp;
        rep(k,1,m) if (i!=k){
            tmp=a[k][p];
            rep(j,1,n+1) a[k][j]-=tmp*a[i][j];
        }
    }
    rep(i,1,m) x[xp[i]]=a[i][n+1];
    return 0;
}

int main(){
    cin>>n; m=n;
    rep(i,1,m) rep(j,1,n+1) cin>>a[i][j];
    if (gauss()) cout<<"No Solution!"<<endl;
    else rep(i,1,n) cout<<x[i]<<' ';cout<<endl;
}