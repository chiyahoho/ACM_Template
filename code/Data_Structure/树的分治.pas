//poj1741 楼教男人八题tree
var
  n,k,i,u,v,l,et,top,pt,ans:longint;
  vis:array[0..20000]of boolean;
  q,z,h,dis,size:array[0..20000]of longint;
  e:array[0..100000]of record v,n,l:longint; end;

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
  x:=q[(l+r)>>1];
  repeat
    while q[i]<x do inc(i);
    while x<q[j] do dec(j);
    if not(i>j) then begin
      swap(q[i],q[j]);
      inc(i); dec(j);
    end;
  until i>j;
  if l<j then sort(l,j);
  if i<r then sort(i,r);
end;

procedure add(u,v,l:longint);
begin
      inc(et);
      e[et].v:=v;
      e[et].l:=l;
      e[et].n:=h[u];
      h[u]:=et;
end;

procedure dfs(u:longint);               //get dist
var   y,v:longint;
begin
      vis[u]:=true;
      inc(top); q[top]:=dis[u];
      y:=h[u];
      while y>0 do begin
            v:=e[y].v;
            if not vis[v] then begin
                  dis[v]:=dis[u]+e[y].l;
                  dfs(v);
            end;
            y:=e[y].n;
      end;
      vis[u]:=false;
end;

function calc(l,r:longint):longint;
begin
      calc:=0;
      sort(l,r);
      while l<=r do begin
            while (q[r]+q[l]>k)and(r>l) do dec(r);
            if r>l then inc(calc,r-l);
            inc(l);
      end;
end;

procedure gs(u:longint);                    //get size
var   v,y:longint;
begin
      vis[u]:=true; size[u]:=1;
      y:=h[u];
      while y>0 do begin
            v:=e[y].v;
            if not vis[v] then begin
                  gs(v);
                  inc(size[u],size[v]);
            end;
            y:=e[y].n;
      end;
      vis[u]:=false;
end;

procedure gr(var p:longint);                      //get root
var   u,l,r,y,v,i:longint;
      flag:boolean;
begin
      l:=0; r:=1;
      z[1]:=p; vis[p]:=true;
      while l<r do begin
            inc(l); u:=z[l];
            flag:=size[u]*2>=size[p];
            y:=h[u];
            while y>0 do begin
                  v:=e[y].v;
                  if not vis[v] then begin
                        if size[v]*2>size[p] then flag:=false;
                        inc(r); vis[v]:=true; z[r]:=v;
                  end;
                  y:=e[y].n;
            end;
            if flag then begin p:=u; break; end;
      end;
      for i:=1 to r do vis[z[i]]:=false;
end;

procedure doit(u:longint);
var   y,v:longint;
begin
      gs(u); if size[u]=1 then begin vis[u]:=true; exit; end;
      gr(u); vis[u]:=true;
      pt:=1; top:=1; q[1]:=0;
      y:=h[u];
      while y>0 do begin
            v:=e[y].v;
            if not vis[v] then begin
                  dis[v]:=e[y].l;
                  dfs(v);
                  dec(ans,calc(pt+1,top));
                  pt:=top;
            end;
            y:=e[y].n;
      end;
      inc(ans,calc(1,top));
//--------------------------------------calc ans
      y:=h[u];
      while y>0 do begin
            if not vis[e[y].v] then doit(e[y].v);
            y:=e[y].n;
      end;
end;

begin
assign(input,'1741.in'); reset(input);
assign(output,'1741.out'); rewrite(output);
while true do begin
      readln(n,k);
      ans:=0; et:=0;
      fillchar(h,sizeof(h),0);
      fillchar(vis,sizeof(vis),0);

      if (n=0)and(k=0) then break;
      for i:=1 to n-1 do begin
            readln(u,v,l);
            add(u,v,l);
            add(v,u,l);
      end;
      doit(1);
      writeln(ans);
end;
close(output);
end.
