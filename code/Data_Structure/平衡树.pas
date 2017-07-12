//0:左儿子的标号   1：右儿子的标号     2：父亲标号    3..9：本节点的值
//0:lch;1:rch;2:fat;3:v;4:x;5:num;6:snum;7:sumv;8:sumx;9:sumv*x;
const
        maxn=30000;
var
        b:array[0..maxn,0..9] of int64;
        a:array[0..maxn,1..2] of int64;
        n,p,q,trs:int64;
        i:longint;
        ans:int64;

function sort(l,r:int64):int64;
var     x,i,j:int64;
        t:array[1..2] of int64;
begin
        i:=l;j:=r;x:=a[(l+r) shr 1,2];
        repeat
                while a[i,2]<x do inc(i);
                while a[j,2]>x do dec(j);
                if i<=j then begin
                        t:=a[i];
                        a[i]:=a[j];
                        a[j]:=t;
                        inc(i);
                        dec(j);
                end;
        until i>j;
        if l<j then sort(l,j);
        if i<r then sort(i,r);
end;

function tget(p:int64):int64;           //更新，维护题目中的需要的信息
var     l,r:int64;
begin
        l:=b[p,0];r:=b[p,1];
        b[p,6]:=b[l,6]+b[r,6]+b[p,5];
        b[p,7]:=b[l,7]+b[r,7]+b[p,3];
        b[p,8]:=b[l,8]+b[r,8]+b[p,4];
        b[p,9]:=b[l,9]+b[r,9]+b[p,3]*b[p,4];
end;

function build(p,v,x,d:int64):int64;        //p:父节点  v,x:节点信息  d:是父亲的左或右节点
begin
        inc(trs);
        b[trs,2]:=p;
        b[trs,3]:=v;
        b[trs,4]:=x;
        b[trs,5]:=1;
        tget(trs);
        b[p,d]:=trs;
        exit(trs);
end;

function ir(p:int64):int64;                   //p是其父亲的左节点则返回0，右节点返回1
begin
        //exit(ord(b[b[p,2],1]=p));         作用相同
        if b[b[p,2],0]=p then exit(0)
                else exit(1);
end;

function rtup(p:int64):int64;    //p：本节点  q：父节点
var     q,x,y:int64;
begin
        q:=b[p,2];x:=ir(p);y:=x xor 1;

        b[q,x]:=b[p,y];        //q的x方向孩子为p的y方向孩子
        if b[p,y]<>0 then b[b[p,y],2]:=q;     //十分重要，否则超级跟0节点会被转走

        b[p,2]:=b[q,2];        //将q脱离顶点，p顶替
        b[b[q,2],ir(q)]:=p;

        b[p,y]:=q;            //将p成为q的父亲
        b[q,2]:=p;

        tget(q);
end;

procedure sply(p:int64);             //将p转到根
begin
        if p=0 then exit;
        while b[p,2]<>0 do begin
                if b[b[p,2],2]<>0 then
                        if ir(p)=ir(b[p,2]) then rtup(b[p,2])
                                else rtup(p);
                rtup(p);
        end;
        tget(p);
end;

function kfnd(p,v:int64):int64;
var     q:int64;
begin
        if b[p,3]>v then
                if b[p,0]=0 then exit(-1)
                        else exit(kfnd(b[p,0],v))
        else begin
                q:=0;                      //重点。。必须要有q。。本过程应按需编写,但q必不可少，否则有可能输出无解的答案。。
                if b[p,1]<>0 then q:=kfnd(b[p,1],v);
                if q<=0 then exit(p)
                        else exit(q);
        end;
end;

function tins(p,v,x:int64):int64;    //插入一个点
begin
        if (v<b[p,3])or(b[p,3]=v)and(b[p,4]<=x) then
                if b[p,0]=0 then exit(build(p,v,x,0))
                        else exit(tins(b[p,0],v,x))
        else
                if b[p,1]=0 then exit(build(p,v,x,1))
                        else exit(tins(b[p,1],v,x));
        tget(p);
end;

begin
        read(n);
        for i:=1 to n do read(a[i,1],a[i,2]);
        sort(1,n);
        for i:=2 to n do begin
                if i=2 then build(0,a[i-1,1],a[i-1,2],1)
                else begin
                        p:=tins(b[0,1],a[i-1,1],a[i-1,2]);
                        sply(p);
                end;
                p:=kfnd(b[0,1],a[i,1]);
                if p=-1 then begin
                        p:=b[0,1];
                        ans:=b[p,7]*a[i,2]-b[p,9]+ans;
                        continue;
                end else if p=0 then begin
                        p:=b[0,1];
                        ans:=a[i,1]*a[i,2]*b[p,6]-a[i,1]*b[p,8]+ans;
                        continue;
                end;
                sply(p);
                q:=b[p,1];
                ans:=b[q,7]*a[i,2]-b[q,9]+ans;
                while b[q,0]<>0 do q:=b[q,0];
                sply(q);
                ans:=a[i,1]*a[i,2]*b[p,6]-a[i,1]*b[p,8]+ans;
        end;
        writeln(ans);
end.

poj1990