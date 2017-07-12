int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}

//a和b的最小的正线性组合ax+by=gcd(a,b),求x,y.
int exgcd(int a,int b){
    if (!b){
        x=1,y=0;
        return a;
    }
    int gcd=exgcd(b,a%b);
    //int x1=x; x=y;
    //y=x1-a/b*y;
    swap(x,y);
    y-=a/b*x;
    return gcd;
}

//【解不定方程ax+by=c】
int bd(int a,int b,int c){
    int d=exgcd(a,b);
    if (c%d) return 0;
    x*=c/d; y*=c/d;
    return 1;
}
/*若ax+by=c有解，则d|c (d=gcd(a,b)) {这个性质很重要}。
所以若d不是c的约数，那么ax+by=c一定无解。
当d|c时，先用Euclid求出gcd(a,b)=d=ax'+by'的x'和y'，则x=x'*c/d，y=y'*c/d。

若ax+by=c有解，则有无数个解，即x+=b*c*k/d,y-=a*c*k/d, k取整数。
*/

//【计算同余方程ax≡b(mod n)】
int ty(int a,int b,int mo){return bd(a,mo,b);}//x即x

//【逆元】
int ny(int a,int mo){return bd(a,mo,1);}//x即a'
//还有费马法可做，待补

//【中国剩余定理】
x≡c1(mod b1)
x≡c2(mod b2)
……
x≡cn(mod bn)
求满足条件的x
int x,y,b1,b2,c1,c2,n,flag;
int exgcd();
int bd();
int main(){
    cin>>n;
    cin>>c1>>b1;
    rep(i,2,n){
        cin>>c2>>b2;
        if (!bd(b1,b2,c2-c1)) flag=1;
        x%=b2/d;
        c1+=x*b1;
        b1*=b2/d;
        c1=(c1+b1)%b1;
    }
    cout<<flag?-1:c1<<endl;
}

【费马小定理】：如果p是素数，a是小于p的正整数，那么a^(p-1) mod p =1。
应用：
于是随机几个a:=random(n-2)+2 来判断p是否满足。（最好是素数）（记得用快速幂）
或者用前7个素数(2, 3, 5, 7, 11, 13和17)可以搞定10e14以内的所有数。。
或者用【2,7,61】，可以搞定10e9以内的所有数。。

【欧拉函数】
n为正整数，φ(n)=不超过n且与n互质的正整数个数。

函数值：
φ(n)=n(1-1/p1)(1-1/p2)…(1-1/px),其中p1,p2…px为n的所有质因数,每种质因数只一个。
φ(1)=1。
例如12=2*2*3,φ(12)=12*(1-1/2)*(1-1/3)=4

常见性质：
φ(mn)=φ(m)φ(n)
当n为奇数时，φ(2n)=φ(n)