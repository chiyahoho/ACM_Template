int power(int a,int b,int mo){
    int k=a,ret=1;
    for(;b;b>>=1){
        if(b&1) ret=ret*k%mo;
        k=k*k%mo;
    }
    return ret;
}