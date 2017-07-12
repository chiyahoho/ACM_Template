//a:文本串；b:模式串;n=a的长度;m=b的长度;ab必须从1开始
void getnext(){
    int j=0;
    next[1]=0;
    rep(i,2,m){
        while (j && b[j+1]!=b[i]) j=next[j];
        if (b[j+1]==b[i]) j++;
        next[i]=j;
    }
}

void kmp(){
    int j=0; ans=0;
    rep(i,1,n){
        while (j && a[i]!=b[j+1]) j=next[j];
        if (a[i]==b[j+1]) j++;
        if (j==m){
            ans++;
            cout<<i-m+1<<endl;
            j=next[j];
        }
    }
}