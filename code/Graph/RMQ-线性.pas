var
  i,n,top,tot,l,r,y,m:longint;
  fa,a,q,ans,h:array[0..100000]of longint;
  e:array[0..250000]of record v,n,xu:longint; end;

function gf(u:longint):longint;
begin
  if fa[u]=u then exit(u);
  fa[u]:=gf(fa[u]);
  exit(fa[u]);
end;

procedure add(u,v,xu:longint);
begin
  inc(tot);
  e[tot].v:=v;
  e[tot].xu:=xu;
  e[tot].n:=h[u];
  h[u]:=tot;
end;

begin
  readln(n,m);
  for i:=1 to n do readln(a[i]);
  for i:=1 to m do begin
        readln(l,r);
        add(r,l,i);
  end;
  for i:=1 to n do fa[i]:=i;

  for i:=1 to n do begin
        while (top>0)and(a[q[top]]<=a[i]) do begin   //以最大值为例，若要求最小值，只需将此处<=改成>=，程序的其他地方无需变动
                fa[q[top]]:=i;
                dec(top);
        end;
        inc(top);
        q[top]:=i;
  //--------------------------
        y:=h[i];
        while y>0 do begin
                ans[e[y].xu]:=a[gf(e[y].v)];
                y:=e[y].n;
        end;
  end;
  for i:=1 to tot do writeln(ans[i]);
end.
