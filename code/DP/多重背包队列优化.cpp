void ins(int x,int y){
    while (l<=r && b[r]<=y) r--;
    a[++r]=x; b[r]=y;
}

int main(){
    cin>>n>>m; //n物品数，m背包空间
    rep(i,1,n){
        cin>>s>>v>>t; //s物品体积，v物品价值，t物品数量（0为无限制）
        if (!t || m/s<t) t=m/s;
        For(d,s){
            l=1; r=0;
            rep(j,0,(m-d)/s){
                ins(j,f[j*s+d]-j*v);
                if (a[l]<j-t) l++;
                f[j*s+d]=b[l]+j*v;
            }
        }
    }
    cout<<f[m]<<endl;
}