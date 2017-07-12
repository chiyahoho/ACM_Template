//bzoj1001: [BeiJing2006]狼抓兔子
var
  u,v,l,n,m,i,d,g,y,tot,ss,tt,j,x,oo:longint;
  heap,num,link,dist,h:array[0..4000000]of longint;
  done:array[0..4000000]of boolean;
  e:array[0..5500000]of record v,n,l:longint; end;

procedure add(u,v,l:longint);
begin
  inc(tot);
  e[tot].v:=v;
  e[tot].l:=l;
  e[tot].n:=h[u];
  h[u]:=tot;
end;

procedure swap(var a,b:longint);
var c:longint; begin c:=a; a:=b; b:=c; end;
function max(a,b:longint):longint;
begin if a>b then exit(a); exit(b); end;

procedure up(p:longint);
begin
  while (p>1)and(heap[p]<heap[p>>1]) do begin
        swap(heap[p],heap[p>>1]);
        swap(link[num[p]],link[num[p>>1]]);
        swap(num[p],num[p>>1]);
        p:=p>>1;
  end;
end;

procedure down(p:longint);
var k:longint;
begin
  while p<=tot>>1 do begin
        k:=p<<1;
        if (k<tot)and(heap[k]>heap[k+1]) then inc(k);
        if heap[p]<=heap[k] then break;

        swap(heap[p],heap[k]);
        swap(link[num[p]],link[num[k]]);
        swap(num[p],num[k]);
        p:=k;
  end;
end;
begin
assign(input,'1001.in'); reset(input);
assign(output,'1001.out'); rewrite(output);
  readln(n,m);
  if (n=1)or(m=1) then begin
      v:=maxlongint;
      for i:=1 to n-1 do begin read(x); if x<v then v:=x; end;
      for i:=1 to m-1 do begin read(x); if x<v then v:=x; end;
      writeln(v);
      close(output); halt;
  end;
//-------------------------------------qunimei de wa
  ss:=0; tt:=(n-1)*(m-1)*2+1;
  for i:=1 to n-1 do
      for j:=1 to m-1 do begin
            read(x);
            v:=((i-1)*(m-1)+j)*2;
            add(max(v-m*2+1,ss),v,x);
      end;
  for j:=1 to m-1 do begin
      read(x);
      add(((n-2)*(m-1)+j)*2-1,tt,x);
  end;

  for i:=1 to n-1 do begin
      read(x);
      add((i-1)*(m-1)*2+1,tt,x);
      for j:=2 to m-1 do begin
            read(x);
            v:=((i-1)*(m-1)+j-1)*2;
            add(v+1,v,x);
      end;
      read(x);
      add(ss,i*(m-1)*2,x);
  end;

  for i:=1 to n-1 do
      for j:=1 to m-1 do begin
            read(x);
            v:=((i-1)*(m-1)+j)*2-1;
            add(v+1,v,x);
      end;
//---------------------------caodan de jianbian
  fillchar(dist,sizeof(dist),100); dist[0]:=0; oo:=dist[1];
  fillchar(heap,sizeof(heap),100); heap[1]:=0;
  tot:=tt+1;
  for i:=1 to tot do begin
        num[i]:=i-1;
        link[i-1]:=i;
  end;

  for g:=1 to tt+1 do begin
        d:=heap[1]; u:=num[1]; done[u]:=true;
        dist[u]:=d;
        heap[1]:=heap[tot]; num[1]:=num[tot]; link[num[tot]]:=1;
        dec(tot); down(1);

        y:=h[u];
        while y>0 do begin
                v:=e[y].v;
                if not done[v] and (heap[link[v]]>d+e[y].l) then begin
                        heap[link[v]]:=d+e[y].l;
                        up(link[v]);
                end;
                y:=e[y].n;
        end;
  end;
  writeln(dist[tt]);
close(output);
end.