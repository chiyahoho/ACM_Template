//记link[i]表示右列i目前连着的点，没有时连0
int find(int x){
    rep(i,1,m) if (b[x][i] && !cover[i]){
        int v=link[i];
        link[i]=x; cover[i]=1;
        if (!v || find(v)) return 1;
        link[i]=v;
    }
    return 0;
}
//调用时：
rep(i,1,n){
    memset(cover,0,sizeof(cover));
    find(i);
}
//ans:
rep(i,1,m) if (link[i]) ans++;