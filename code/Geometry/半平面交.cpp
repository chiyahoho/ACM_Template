//[ZJOI2008]掺望塔  BZOJ1038

int jiao(point a,point b,point p,point q){ //l1=a→b,l2=p→q
    double k=(b-a)*(q-p);
    if (dcmp(k)==0) return 0; //平行
    double t=(p-a)*(q-p)/k;
    dd=a+((b-a)*t); //dd为交点
    return eps<t && t<1-eps;
    //交点在端点看不看只用判t=0和t=1算不算。这里判断的是l2所在直线与l1线段是否相交，若二者皆为线段可以反交。
}

int main(){
    cin>>n;
    ans=oo;
    rep(i,1,n) cin>>z[i].x;
    rep(i,1,n) cin>>z[i].y;
    m=4;
    ba[1].x=z[1].x; ba[1].y=-oo; //先搞个大包
    ba[2].x=z[1].x; ba[2].y=oo;
    ba[3].x=z[n].x; ba[3].y=oo;
    ba[4].x=z[n].x; ba[4].y=-oo;
    rep(i,1,n-1){
        mm=0; ba[m+1]=ba[1];
        rep(j,1,m){
            if ((z[i+1]-z[i])*(ba[j]-z[i])>-eps) bb[++mm]=ba[j];
            if (jiao(ba[j],ba[j+1],z[i],z[i+1])) bb[++mm]=dd;
        }
        m=mm; rep(j,1,m) ba[j]=bb[j];
    }
    //半平面交结束，以下是此题蛋疼输出
    
}