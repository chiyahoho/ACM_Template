原题：ZJOI2008 树的统计 Count bzoj题号1036
{$M 50000000}
uses math;
const oo=maxlongint>>2;
var
  s:string[5];
  ch:char;
  e:array[0..500000]of record v,n:longint; end;
  sz,bel,fa,po,hd,deep,ma,sum,h,lh,a:array[-1..500000]of longint;
  tr:array[0..500000,0..1]of longint;
  tot,path,n,m,i,j,u,v,x,y,ans,su:longint;

procedure add(u,v:longint);
begin
  inc(tot);
  e[tot].v:=v;
  e[tot].n:=h[u];
  h[u]:=tot;
end;

procedure dfs1(u:longint);
var y,v:longint;
begin
  sz[u]:=1;
  y:=h[u];
  while y>0 do begin
        v:=e[y].v;
        if v<>fa[u] then begin
                deep[v]:=deep[u]+1;
                fa[v]:=u;
                dfs1(v);
                inc(sz[u],sz[v]);
        end;
        y:=e[y].n;
  end;
end;

procedure dfs2(u,head,len:longint);
var y,v,ma:longint;
begin
  bel[u]:=path;
  lh[head]:=len;
  po[u]:=len;
  hd[u]:=head;
  ma:=-1; y:=h[u];
  while y>0 do begin
        v:=e[y].v;
        if (fa[u]<>v)and(sz[v]>sz[ma])then ma:=v;    //so sz:array[-1..]
        y:=e[y].n;
  end;
  if ma>0 then dfs2(ma,head,len+1);

  y:=h[u];
  while y>0 do begin
        v:=e[y].v;
        if (fa[u]<>v)and(v<>ma) then begin
                inc(path);
                dfs2(v,v,1);
        end;
        y:=e[y].n;
  end;
end;

procedure insert(nod,l,r,p,c:longint);
var mi:longint;
begin
  if l=r then begin
        ma[nod]:=c; sum[nod]:=c;
        exit;
  end;
  mi:=(l+r)>>1;
  if tr[nod,0]=0 then begin inc(path); tr[nod,0]:=path; end;
  if tr[nod,1]=0 then begin inc(path); tr[nod,1]:=path; end;
  if p<=mi then insert(tr[nod,0],l,mi,p,c) else insert(tr[nod,1],mi+1,r,p,c);
  sum[nod]:=sum[tr[nod,0]]+sum[tr[nod,1]];
  ma[nod]:=max(ma[tr[nod,0]] , ma[tr[nod,1]]);
end;

procedure ask(nod,l,r,a,b,k:longint);
var mi:longint;
begin
  if (l=a)and(r=b) then begin
        if k=1 then ans:=max(ans,ma[nod]) else inc(su,sum[nod]);
        exit;
  end;
  mi:=(l+r)>>1;
  if b<=mi then ask(tr[nod,0],l,mi,a,b,k)
  else if a>mi then ask(tr[nod,1],mi+1,r,a,b,k)
  else begin
        ask(tr[nod,0],l,mi,a,mi,k);
        ask(tr[nod,1],mi+1,r,mi+1,b,k);
  end;
end;

procedure get(x,y,k:longint);
begin
  ans:=-oo; su:=0;
  while hd[x]<>hd[y] do begin
        if deep[hd[x]]>deep[hd[y]] then begin
                ask(bel[x],1,lh[hd[x]],1,po[x],k);
                x:=fa[hd[x]];
        end
        else begin
                ask(bel[y],1,lh[hd[y]],1,po[y],k);
                y:=fa[hd[y]];
        end;
  end;
  ask(bel[x],1,lh[hd[x]],min(po[x],po[y]),max(po[x],po[y]),k);
  if k=1 then writeln(ans) else writeln(su);
end;


begin
assign(input,'count.in'); reset(input);
assign(output,'count.out'); rewrite(output);
  readln(n);
  for i:=1 to n-1 do begin
        readln(u,v);
        add(u,v); add(v,u);
  end;
  for i:=1 to n do read(a[i]); readln;
  dfs1(1); dfs2(1,1,1);
  for i:=1 to n do insert(bel[i],1,lh[hd[i]],po[i],a[i]);

  readln(m);
  for i:=1 to m do begin
        read(s);
        if s='QMAX ' then begin
                readln(x,y);
                get(x,y,1);
        end;
        if s='QSUM ' then begin
                readln(x,y);
                get(x,y,2);
        end;
        if s='CHANG' then begin
                readln(ch,x,y);
                insert(bel[x],1,lh[hd[x]],po[x],y);
        end;
  end;
close(output);
end.
