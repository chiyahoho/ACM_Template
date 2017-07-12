int bit=10;
struct gao{
    int len,a[10000];
    void jinwei(){
        rep(i,1,len){
            a[i+1]+=a[i]/bit;
            a[i]%=bit;
        }
        while(a[len+1]){
            len++;
            a[len+1]=a[len]/bit;
            a[len]%=bit;
        }
    }
    gao operator *(const gao &u)const{
        gao c;
        c.len=len+u.len-1;
        rep(i,1,len) rep(j,1,u.len) c.a[i+j-1]+=a[i]*u.a[j];
        c.jinwei();
        return c;
    }
    gao operator +(const gao &u)const{
        gao c;
        c.len=max(len,u.len);
        rep(i,1,c.len) c.a[i]=a[i]+u.a[i];
        c.jinwei();
        return c;
    }
    gao operator *(const int &u)const{
        gao c;
        c.len=len;
        rep(i,1,len) c.a[i]=a[i]*u;
        c.jinwei();
        return c;
    }
    bool operator <(const gao &u)const{
        if (len<u.len) return 1;
        if (len==u.len) per(i,len,1){
            if (a[i]<u.a[i]) return 1;
            if (a[i]>u.a[i]) return 0;
        }
        return 0;
    }
    gao operator -(const gao &u)const{
        gao c;
        c.len=len;
        rep(i,1,len) c.a[i]=a[i]-u.a[i];
        rep(i,1,len) if (c.a[i]<0){
            c.a[i]+=bit;
            c.a[i+1]--;
        }
        while (c.len && !c.a[c.len]) c.len--;
        return c;
    }
}