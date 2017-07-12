uses math;
const oo=maxlongint;
var
  ans,ss,tt,n,m,i,j,u,v,tot,y:longint;
  g,vg,h:array[0..4000]of longint;
  e:array[0..100000]of record l,v,b,n:longint; end;

procedure add(u,v:longint);
begin
  inc(tot);
  e[tot].v:=v;
  e[tot].l:=1;
  e[tot].b:=tot+1;
  e[tot].n:=h[u];
  h[u]:=tot;

  inc(tot);
  e[tot].v:=u;
  e[tot].l:=0;
  e[tot].b:=tot-1;
  e[tot].n:=h[v];
  h[v]:=tot;
end;

function sap(u,flow:longint):longint;
var
  v,ff,y:longint;
begin
  if u=tt then exit(flow);
  sap:=0;
  y:=h[u];
  while y>0 do begin
        v:=e[y].v;
        if g[u]=g[v]+1 then begin
                ff:=sap(v,min(e[y].l,flow-sap));
                inc(sap,ff);
                dec(e[y].l,ff);
                inc(e[e[y].b].l,ff);
                if flow=sap then exit;
        end;
        y:=e[y].n;
  end;

  if g[ss]=tt then exit;
  dec(vg[g[u]]); if vg[g[u]]=0 then g[ss]:=tt;
  inc(g[u]); inc(vg[g[u]]);
end;

procedure dfs(u:longint);
var
  y,v:longint;
begin
  write(u,' ');
  y:=h[u];
  while e[y].l<>0 do y:=e[y].n;
  v:=e[y].v;
  if v=0 then exit;
  dfs(v-n);
end;

begin
assign(input,'path.in'); reset(input);
assign(output,'path.out'); rewrite(output);
  readln(n,m);
  ss:=0; tt:=2*n+1;
  ans:=n;
  for i:=1 to m do begin
      readln(u,v);
      add(u,v+n);
  end;
  for i:=1 to n do begin add(0,i); add(i+n,tt); end;
  g[ss]:=1; vg[1]:=1; vg[0]:=oo;
  while g[ss]<tt do dec(ans,sap(ss,oo));

  for u:=n+1 to 2*n do begin
        y:=h[u];
        while e[y].v<>tt do y:=e[y].n;
        if e[y].l=1 then begin
                dfs(u-n);
                writeln;
        end;
  end;
  writeln(ans);
close(input); close(output);
end.