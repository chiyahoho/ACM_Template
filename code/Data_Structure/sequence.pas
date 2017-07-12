//1:left 2:right 3:father 4:num 5:change 6:sum 7:maxl 8:maxr 9:maxm 10:size 11:turn
const oo=maxlongint>>2; mo=510000;
var
  c:string[7];
  ch:char;
  p,i,j,n,m,x,y,k,ll,rr:longint;
  qq,a:array[0..1000000]of longint;
  b:array[0..1000000,1..11]of longint;

procedure swap(var a,b:longint);
var c:longint;
begin c:=a; a:=b; b:=c; end;

function max(a,b:longint):longint;
begin if a>b then exit(a); exit(b); end;

function ir(p:longint):longint;
begin
  if b[b[p,3],1]=p then exit(1); exit(2);
end;

procedure pass(p:longint);
var k:longint;
begin
  if p=0 then exit;
  if b[p,11]=1 then begin
      swap(b[p,1],b[p,2]);
      swap(b[p,7],b[p,8]);
      if b[p,1]<>0 then b[b[p,1],11]:=1-b[b[p,1],11];
      if b[p,2]<>0 then b[b[p,2],11]:=1-b[b[p,2],11];
      b[p,11]:=0;
  end;
  if b[p,5]<>-oo then begin
      k:=b[p,5]; b[p,5]:=-oo;
      b[p,4]:=k;
      b[p,6]:=k*b[p,10];
      if b[p,1]<>0 then b[b[p,1],5]:=k;
      if b[p,2]<>0 then b[b[p,2],5]:=k;
      b[p,9]:=max(k,b[p,6]);
      if k>0 then k:=b[p,6] else k:=0;     //b[p,9]=k?
      b[p,7]:=k; b[p,8]:=k;
  end;
end;

procedure tget(p:longint);
var l,r:longint;
begin
  if p=0 then exit;
  l:=b[p,1]; r:=b[p,2];
  pass(l); pass(r);
  b[p,6]:=b[l,6]+b[r,6]+b[p,4];
  b[p,7]:=max(b[l,7],b[l,6]+b[p,4]+b[r,7]);
  b[p,8]:=max(b[r,8],b[r,6]+b[p,4]+b[l,8]);
  b[p,9]:=max(max(b[l,9],b[r,9]), b[l,8]+b[p,4]+b[r,7]);
  b[p,10]:=b[l,10]+b[r,10]+1;
end;

procedure tup(p:longint);
var q,x,y:longint;
begin
  q:=b[p,3]; x:=ir(p); y:=3-x;
  b[q,x]:=b[p,y];
  if b[p,y]<>0 then b[b[p,y],3]:=q;

  b[p,3]:=b[q,3];
  b[b[q,3],ir(q)]:=p;

  b[q,3]:=p;
  b[p,y]:=q;
  tget(q);
end;

procedure splay(p,v:longint);
begin
  if p=v then exit;
  while b[p,3]<>v do begin
      if b[b[p,3],3]<>v then
            if ir(p)=ir(b[p,3]) then tup(b[p,3]) else tup(p);
      tup(p);
  end;
  tget(p);
end;

function kfnd(p,k:longint):longint;
begin
  pass(p);
  if k=b[b[p,1],10]+1 then exit(p);
  if k<b[b[p,1],10]+1 then exit(kfnd(b[p,1],k))
                      else exit(kfnd(b[p,2],k-b[b[p,1],10]-1));
end;

procedure build(p,l,r,d:longint);
var q,mi,i:longint;
begin
  if l>r then exit;
  mi:=(l+r)>>1;
  q:=qq[ll]; ll:=(ll mod mo)+1;
  for i:=1 to 11 do b[q,i]:=0;
  b[q,5]:=-oo;
  b[q,3]:=p; b[p,d]:=q;
  b[q,4]:=a[mi];
  build(q,l,mi-1,1);
  build(q,mi+1,r,2);
  tget(q);
end;

function getxy(x,y:longint):longint;
var u,v:longint;
begin
  u:=kfnd(b[0,2],x-1);
  v:=kfnd(b[0,2],y+1);
  splay(u,0); splay(v,b[0,2]);
  exit(b[b[b[0,2],2],1]);
end;

procedure kong(p:longint);
begin
  rr:=(rr mod mo)+1;
  qq[rr]:=p;
  if b[p,1]<>0 then kong(b[p,1]);
  if b[p,2]<>0 then kong(b[p,2]);
end;

begin
assign(input,'sequence.in'); reset(input);
assign(output,'sequence.out'); rewrite(output);
  readln(n,m);
  for i:=2 to n+1 do read(a[i]); readln;
  a[1]:=-oo; a[n+2]:=-oo;
  for i:=1 to mo do qq[i]:=i;
  ll:=1; rr:=mo; b[0,9]:=-oo;
  build(0,1,n+2,2);

  for j:=1 to m do begin
      read(c);
      if c='INSERT ' then begin
                  read(x,y); inc(x);
                  getxy(x+1,x);
                  for i:=1 to y do read(a[i]); readln;
                  build(b[b[0,2],2],1,y,1);
                  tget(b[b[0,2],2]); tget(b[0,2]);
      end;
      if c='DELETE ' then begin
                  readln(x,y); inc(x); y:=x+y-1;
                  p:=getxy(x,y);
                  b[b[p,3],ir(p)]:=0;
                  tget(b[b[0,2],2]); tget(b[0,2]);
                  kong(p);
      end;
      if c='MAKE-SA' then begin
                  read(ch); read(ch);
                  readln(x,y,k); inc(x); y:=x+y-1;
                  p:=getxy(x,y);
                  b[p,5]:=k;
                  pass(p);
                  tget(b[b[0,2],2]); tget(b[0,2]);
      end;
      if c='REVERSE' then begin
                  readln(x,y); inc(x); y:=x+y-1;
                  p:=getxy(x,y);
                  b[p,11]:=1-b[p,11];
                  pass(p);
                  tget(b[b[0,2],2]); tget(b[0,2]);
      end;
      if c='GET-SUM' then begin
                  readln(x,y); inc(x); y:=x+y-1;
                  p:=getxy(x,y);
                  writeln(b[p,6]);
      end;
      if c='MAX-SUM' then begin
                  readln;
                  writeln(b[b[0,2],9]);
      end;
  end;
close(output);
end.
