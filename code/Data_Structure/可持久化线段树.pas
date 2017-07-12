//poj2104
var
      n,m,i,x,y,k,tot:longint;
      tr:array[0..3000000] of record n,l,r:longint; end;
      a,p,pp:array[0..200000]of longint;

procedure swap(var a,b:longint);
var c:longint;
begin
  c:=a; a:=b; b:=c;
end;

procedure sort(l,r:longint);
var
  i,j,x:longint;
begin
  i:=l; j:=r;
  x:=a[(l+r)>>1];
  repeat
    while a[i]<x do inc(i);
    while x<a[j] do dec(j);
    if not(i>j) then begin
      swap(a[i],a[j]);
      swap(p[i],p[j]);
      inc(i); dec(j);
    end;
  until i>j;
  if l<j then sort(l,j);
  if i<r then sort(i,r);
end;

procedure insert(x:longint);
var   p,q,l,r,m:longint;
begin
      l:=1; r:=n;
      p:=i; q:=i-1;
      while true do begin
            tr[p].n:=tr[q].n+1;
            if l=r then break;
            m:=(l+r)>>1;
            if x<=m then begin
                  tr[p].r:=tr[q].r;
                  inc(tot); tr[p].l:=tot;
                  p:=tot; q:=tr[q].l;
                  r:=m;
            end
            else begin
                  tr[p].l:=tr[q].l;
                  inc(tot); tr[p].r:=tot;
                  p:=tot; q:=tr[q].r;
                  l:=m+1;
            end;
      end;
end;

function kfnd(x,y,k,l,r:longint):longint;
var   t,m:longint;
begin
      t:=tr[tr[y].l].n-tr[tr[x].l].n; m:=(l+r)>>1;
      if l=r then begin writeln(a[l]); exit; end;
      if k<=t then kfnd(tr[x].l,tr[y].l,k,l,m)
      else kfnd(tr[x].r,tr[y].r,k-t,m+1,r);
end;

begin
assign(input,'chair.in'); reset(input);
assign(output,'chair.out'); rewrite(output);
      readln(n,m);
      tot:=n;
      for i:=1 to n do begin read(a[i]); p[i]:=i; end; readln;
      sort(1,n);
      for i:=1 to n do pp[p[i]]:=i;
      for i:=1 to n do insert(pp[i]);
      for i:=1 to m do begin readln(x,y,k); kfnd(x-1,y,k,1,n); end;
close(output);
end.
