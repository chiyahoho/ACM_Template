void shai(int n){
    rep(i,1,n) f[i]=i;//f[i]表示i的最小质因数
    rep(i,2,n){
        if (f[i]==i) a.push_back(i);//a是素数表
        for(int j=0;j<a.size() && a[j]*i<=n;j++){
            f[a[j]*i]=a[j];
            if (i%a[j]==0) break;
        }
    }
}