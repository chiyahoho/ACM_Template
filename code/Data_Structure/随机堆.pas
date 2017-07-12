//bzoj 1455: 罗马游戏
var
      i,n,m,a,b,t,f1,f2,f3:longint;
      fa,lson,rson,key:array[0..2000000]of longint;
      kd:array[0..2000000]of boolean;
      ch:char;

function gf(a:longint):longint;
begin
      if fa[a]=a then exit(a);
      fa[a]:=gf(fa[a]); exit(fa[a]);
end;
procedure swap(var a,b:longint);
var c:longint; begin c:=a; a:=b; b:=c; end;
function rand:boolean;
begin inc(t); exit(t and 1=1); end;

function merge(x,y:longint):longint;
begin
      if (x=0)or(y=0) then exit(x+y);
      if (key[x]>key[y]) then swap(x,y);
      if rand then lson[x]:=merge(lson[x],y)
              else rson[x]:=merge(rson[x],y);
      exit(x);
end;

begin
assign(input,'1455.in'); reset(input);
assign(output,'1455.out'); rewrite(output);
      readln(n);
      for i:=1 to n do begin
            fa[i]:=i;
            read(key[i]);
      end;
      readln;
      readln(m);
      for i:=1 to m do begin
            read(ch);
            if ch='M' then begin
                  readln(a,b);
                  f1:=gf(a); f2:=gf(b);
                  if kd[a] or kd[b] or (f1=f2) then continue;
                  f3:=merge(f1,f2);
                  fa[f1]:=f3; fa[f2]:=f3;
            end
            else if ch='K' then begin
                  readln(a);
                  if kd[a] then begin writeln(0); continue; end;
                  a:=gf(a);
                  kd[a]:=true;
                  writeln(key[a]);
                  fa[a]:=merge(lson[a],rson[a]);
                  fa[fa[a]]:=fa[a];
            end;
      end;
close(output);
end.
