const oo=maxlongint;
var n,i,j,tot,p,pp,min,g:longint;
    a:array[0..200]of longint;
    v:array[0..200,0..200]of longint;
begin
assign(input,'agrinet.in'); reset(input);
assign(output,'agrinet.out'); rewrite(output);
while not eof do
begin
  tot:=0;
  readln(n);
  for i:=1 to n do
  begin
    a[i]:=oo;
    for j:=1 to n do read(v[i,j]);
  end;
  readln;
  a[1]:=0; tot:=0; p:=1;
  for g:=2 to n do
  begin
    min:=oo;
    for i:=1 to n do if a[i]<>0 then
    begin
      if v[p,i]<a[i] then a[i]:=v[p,i];
      if a[i]<min then
      begin
        min:=a[i];
        pp:=i;
      end;
    end;
    p:=pp; a[p]:=0; tot:=tot+min;
  end;
  writeln(tot);
end;
close(output);
end.


这程序是多组数据的。
具体见pku，题目1258。