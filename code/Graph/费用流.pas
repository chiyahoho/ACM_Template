const oo=maxlongint>>3;
var
  e:array[0..1000000]of record l,v,b,n,c:longint; end;
  pre:array[0..10000]of record v,e:longint; end;
  d,h,q:array[0..100000]of longint;
  f:array[0..10000]of boolean;
  ans,tot,n,x,ss,tt,bu,qw,sw,qd,sd,i:longint;

procedure add(u,v,l,c:longint);
begin
  inc(tot);
  e[tot].v:=v;
  e[tot].l:=l;
  e[tot].c:=c;
  e[tot].b:=tot+1;
  e[tot].n:=h[u];
  h[u]:=tot;

  inc(tot);
  e[tot].v:=u;
  e[tot].l:=0;
  e[tot].c:=-c;
  e[tot].b:=tot-1;
  e[tot].n:=h[v];
  h[v]:=tot;
end;

function relax(u,y,v:longint):boolean;
begin
  if d[u]+e[y].c<d[v] then begin
      d[v]:=d[u]+e[y].c;
      pre[v].v:=u;            //pre[v].v:v的前一个点
      pre[v].e:=y;            //pre[v].e:v的前一个点→v的边
      exit(true);
  end;
  exit(false);
end;

function spfa:boolean;
var
  i,l,r,u,v,y,k:longint;
begin
  for i:=ss to tt do begin        //归零
      d[i]:=oo;
      f[i]:=false;
      pre[i].v:=-1;
      pre[i].e:=0;
  end;
  l:=0; r:=1;                    //spfa开始
  q[1]:=ss; d[ss]:=0;
  while l<r do begin
      inc(l);
      u:=q[l]; f[u]:=false;
      y:=h[u];
      while y>0 do begin
            v:=e[y].v;
            if (e[y].l>0)and relax(u,y,v) and not f[v] then begin
                  f[v]:=true;
                  inc(r);
                  q[r]:=v;
            end;
            y:=e[y].n;
      end;
  end;
  if d[tt]>=oo then exit(false);
  k:=oo; v:=tt;                    //这里不属于spfa了
  while pre[v].v<>-1 do begin      //找此增广路的流量k
      if e[pre[v].e].l<k then k:=e[pre[v].e].l;
      v:=pre[v].v;
  end;
  v:=tt;
  while pre[v].v<>-1 do begin     //修改图
      y:=pre[v].e;
      inc(ans,e[y].c*k);
      dec(e[y].l,k); inc(e[e[y].b].l,k);
      v:=pre[v].v;
  end;
  exit(true);
end;

begin
assign(input,'napk.in'); reset(input);
assign(output,'napk.out'); rewrite(output);
{  readln(n,bu,qd,qw,sd,sw);
  ss:=0; tt:=2*n+1;
  for i:=1 to n do begin
      readln(x);
      add(ss,i,x,0);
      add(i+n,tt,x,0);
      add(ss,i+n,oo,bu);
      if i<n then add(i,i+1,oo,0);
      if i+qd<=n then add(i,i+qd+n,oo,qw);
      if i+sd<=n then add(i,i+sd+n,oo,sw);
  end;               }建边的过程，忽略之

  while spfa do;     //其实这样写也是可以的，主程序就在这里了
  writeln(ans);

close(input); close(output);
end.