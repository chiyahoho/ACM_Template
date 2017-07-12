//poj2187 USACO 2003 Fall Beauty Contest
//模板改int
void hull(point a,point b,int l,int r){
    int x=l;
    rep(k,l,r) if (s[x]<s[k] || (s[x]==s[k] && p[x]<p[k])) x=k;
    point y=p[x];
    int i=l-1,j=r+1;
    rep(k,l,r) if ((s[i+1]=(y-a)*(p[k]-a))>0) swap(p[++i],p[k]);
    per(k,r,l) if ((s[j-1]=(b-y)*(p[k]-y))>0) swap(p[--j],p[k]);
    if (l<=i) hull(a,y,l,i);
    bao[++m]=y;
    if (j<=r) hull(y,b,j,r);
}

int main(){
    cin>>n;
    rep(i,1,n) p[i].read();
    rep(i,2,n) if (p[i]<p[1]) swap(p[1],p[i]);
    bao[m=1]=p[1];
    hull(p[1],p[1],2,n);

    j=2; bao[m+1]=bao[1];
    rep(i,1,m){
        while ((bao[j]-bao[i])*(bao[i+1]-bao[i]) < (bao[j+1]-bao[i])*(bao[i+1]-bao[i])) j=(j%m)+1;
        upmax(ans,(bao[j]-bao[i]).len2());
    }
    cout<<ans<<endl;
}