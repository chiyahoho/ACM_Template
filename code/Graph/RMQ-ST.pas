uses math;
var
  a:array[1..200000] of longint;
  f:array[1..200000,0..19] of longint;
  d:array[0..19] of longint;
  n,i,j,m,k,l,r:longint;

begin
  readln(n);
  for i:=1 to n do read(a[i]);

  d[0]:=1;
  for i:=1 to 19 do d[i]:=d[i-1]*2;            // d[i]=2^i
   //-----------------------
  for i:=1 to n do f[i,0]:=a[i];               // ready
  for j:=1 to trunc(ln(n)/ln(2)) do            // ln(n)/ln(2)=log2(n)
    for i:=1 to n-d[j]+1 do
      f[i,j]:=max(f[i,j-1],f[i+d[j-1],j-1]);
   //---------------------
  readln(m);
  for i:=1 to m do begin
        readln(l,r);
        k:=trunc(ln(r-l+1)/ln(2));             // 2^k<=r-l+1 but 2*2^k>r-l+1
        writeln(max(f[l,k],f[r-d[k]+1,k]));
  end;
end.