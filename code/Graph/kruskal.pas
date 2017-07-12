var
  tot,t,k,i,j,n:longint;
  v:array[0..100000]of record
                         a,b,len:longint;
                       end;
  fa:array[0..100000]of longint;

procedure swap(i,j:longint);
var g:longint;
begin
  g:=v[i].len; v[i].len:=v[j].len; v[j].len:=g;
  g:=v[i].a; v[i].a:=v[j].a; v[j].a:=g;
  g:=v[i].b; v[i].b:=v[j].b; v[j].b:=g;
end;

procedure sort(l,r: longint);
var
  i,j,x,y: longint;
begin
  i:=l;
  j:=r;
  x:=v[(l+r) div 2].len;
  repeat
    while v[i].len<x do
     inc(i);
    while x<v[j].len do
     dec(j);
    if not(i>j) then
    begin
      swap(i,j);
      inc(i);
      dec(j);
    end;
  until i>j;
  if l<j then
    sort(l,j);
  if i<r then
    sort(i,r);
end;

function gf(a:longint):longint;
begin
  if fa[a]=a then exit(a);
  fa[a]:=gf(fa[a]);
  exit(fa[a]);
end;

begin
assign(input,'kruskal.in'); reset(input);
assign(output,'kruskal.out'); rewrite(output);
while not eof do
begin
  readln(n); k:=0;
  for i:=1 to n do
    for j:=1 to n do
    begin
      inc(k);
      v[k].a:=i; v[k].b:=j;
      read(v[k].len);
    end;
    readln;

  sort(1,n*n);

  for i:=1 to n*n do fa[i]:=i;

  tot:=0; t:=0; k:=0;
  while t<n-1 do
  begin
    inc(k);
    if gf(v[k].a)<>gf(v[k].b) then
    begin
      fa[gf(v[k].a)]:=gf(v[k].b);
      inc(tot,v[k].len);
      inc(t);
    end;
  end;
  writeln(tot);
end;
close(output);
end.


这程序是多组数据的。
具体见pku，题目1258。