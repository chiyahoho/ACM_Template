//A[i]=T与T(i,m)的最长公共前缀，2<=i<=m。
//B[i]=T与S(i,n)的最长公共前缀，1<=i<=n。
void getA(){
    int j,k,len;//len:能匹配到的最远距离;len=k+A[k]-1
    for(j=0;t[1+j]==t[2+j]&&2+j<=m;j++);
    a[2]=j; k=2;
    rep(i,3,m){
        len=k+a[k]-1; j=len-i+1;
        if (a[i-k+1]<j) a[i]=a[i-k+1];
        else{
            upmax(j,0);
            for(;t[1+j]==t[i+j]&&i+j<=m;j++);
            a[i]=j; k=i;
        }
    }
}

void getB(){
    int j,k,len;
    for(j=0;t[1+j]==s[1+j]&&1+j<=m&&1+j<=n;j++);
    b[1]=j; k=1;
    rep(i,2,n){
        len=k+b[k]-1; j=len-i+1;
        if (a[i-k+1]<j) b[i]=a[i-k+1];
        else{
            upmax(j,0);
            for(;t[1+j]==s[i+j]&&1+j<=m&&i+j<=n;j++);
            b[i]=j; k=i;
        }
    }
}