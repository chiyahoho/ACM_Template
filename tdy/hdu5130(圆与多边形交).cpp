#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const double PI=acos(-1.0);
const double eps=1e-8;
int n;
double k;
double R;
double ans;
int dcmp(double x) {
    if (x<-eps) return -1;
    if (x>eps) return 1;
    return 0;
}
struct point{
    double x,y;
    point() {}
    point(double x,double y):x(x),y(y) {}
    point operator+(const point &a) const{
        return point(x+a.x,y+a.y);
    }
    point operator-(const point &a) const{
        return point(x-a.x,y-a.y);
    }
    double operator*(const point &a) const{
        return x*a.x+y*a.y;
    }
    point operator*(const double &a) const{
        return point(x*a,y*a);
    }
    double operator/(const point &a) const{
        return x*a.y-y*a.x;
    }
    point operator/(const double &a) const{
        return point(x/a,y/a);
    }
    bool operator==(const point &a) const{
        return dcmp(x-a.x)==0&&dcmp(y-a.y)==0;
    }
    double abs() {
        return sqrt(x*x+y*y);
    }
} p[1001];
point O=point(0,0);
point crosspt(point &a,point &b,point &c,point &d) {
    double s1,s2;
    s1=(c-a)/(b-a);
    s2=(b-a)/(d-a);
    return (c*s2+d*s1)/(s1+s2);
}
double sector_area(point a,point b,double r) {
    double theta;
    theta=atan2(a.y,a.x)-atan2(b.y,b.x);
    while (theta <= 0) theta+=2*PI;
    while (theta > 2*PI) theta-=2*PI;
    theta=min(theta,2*PI-theta);
    return r*r*theta/2;
}
void circle_cross_line(point o,double r,point a,point b,point ret[2],int &num) {
    double ax=a.x-o.x;
    double ay=a.y-o.y;
    double bx=b.x-o.x;
    double by=b.y-o.y;
    double dx=bx-ax;
    double dy=by-ay;
    double A=dx*dx+dy*dy;
    double B=2*(ax*dx+ay*dy);
    double C=ax*ax+ay*ay-r*r;
    double delta=B*B-4*A*C;
    num=0;
    if (dcmp(delta)>=0) {
        double t1=(-B-sqrt(delta))/(2*A);
        double t2=(-B+sqrt(delta))/(2*A);
        if (dcmp(t1-1)<=0&&dcmp(t1)>=0)
            ret[num++]=point(a.x+t1*dx,a.y+t1*dy);
        if (dcmp(t2-1)<=0&&dcmp(t2)>=0)
            ret[num++]=point(a.x+t2*dx,a.y+t2*dy);
    }
}
double calc(point &a,point &b) {
    bool ina,inb;
    point ret[2];
    int num;
    if (O==a||O==b) return 0;
    if (a==b) return 0;
    ina=dcmp((a).abs()-R)<=0;
    inb=dcmp((b).abs()-R)<=0;
    if (ina) {
        if (inb) {
            return abs(a/b)/2.0;
        }
        else {
            circle_cross_line(O,R,a,b,ret,num);
            return abs(a/ret[num-1])/2.0+sector_area(ret[num-1],b,R);
        }
    }
    else{
        if (inb) {
            circle_cross_line(O,R,b,a,ret,num);
            return abs(b/ret[num-1])/2.0+sector_area(ret[num-1],a,R);
        }
        else {
            circle_cross_line(O,R,a,b,ret,num);
            if (num==2) {
                return sector_area(a,ret[0],R)+abs(ret[0]/ret[1])/2.0+sector_area(ret[1],b,R);
            }
            else {
                return sector_area(a,b,R);
            }
        }
    }
}
int main() {
    int i,x,y,T=0;
    point u,v;
    point p1,p2;
    point mid;
    while (scanf("%d%lf",&n,&k)!=EOF) {
        for (i=1; i<=n; i++) {
            scanf("%d%d",&x,&y);
            p[i]=point(x,y);
        }
        scanf("%d%d",&x,&y);
        u=point(x,y);
        scanf("%d%d",&x,&y);
        v=point(x,y);
        p1=v+(u-v)*k/(1+k);
        p2=v+(u-v)*k/(k-1);
        mid=(p1+p2)/2;
        R=(p1-p2).abs()/2;
        for (i=1; i<=n; i++) {
            p[i]=p[i]-mid;
        }
        p[n+1]=p[1];
        ans=0;
        for (i=1; i<=n; i++) {
            int sig;
            sig=dcmp(p[i]/p[i+1]);
            double temp;
            temp=calc(p[i],p[i+1]);
            if (sig>=0) ans+=temp;
            else ans-=temp;
        }
        ans=abs(ans);
        printf("Case %d: %.12f\n",++T,ans);
    }
    return 0;
}
