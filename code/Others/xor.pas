//usaco 09 NOV lights
var
  ans,n,m,i,j,k,x,y:longint;
  flag:boolean;
  a:array[0..500,0..500]of longint;

procedure swap(var a,b:longint);
var c:longint; begin c:=a; a:=b; b:=c; end;

procedure dfs(k,t:longint);
var i:longint;
begin
  if t>=ans then exit;
  if k=0 then begin
        if t<ans then ans:=t;
        exit;
  end;
  if a[k,k]=0 then begin
      //for i:=1 to k-1 do if a[i,k]>0 then a[i,n+1]:=a[i,n+1]xor 0;
        dfs(k-1,t);
      //for i:=1 to k-1 do if a[i,k]>0 then a[i,n+1]:=a[i,n+1]xor 0;
        for i:=1 to k-1 do if a[i,k]>0 then a[i,n+1]:=a[i,n+1]xor 1;
        dfs(k-1,t+1);
        for i:=1 to k-1 do if a[i,k]>0 then a[i,n+1]:=a[i,n+1]xor 1;
  end
  else begin
        if a[k,n+1]=1 then inc(t);
        for i:=1 to k-1 do if a[i,k]>0 then a[i,n+1]:=a[i,n+1]xor a[k,n+1];
        dfs(k-1,t);
        if a[k,n+1]=1 then dec(t);
        for i:=1 to k-1 do if a[i,k]>0 then a[i,n+1]:=a[i,n+1]xor a[k,n+1];
  end;
end;

begin
assign(input,'xor.in'); reset(input);
assign(output,'xor.out'); rewrite(output);
  readln(n,m);
  for i:=1 to m do begin
        readln(x,y);
        a[x,y]:=1; a[y,x]:=1;
  end;
  for i:=1 to n do begin a[i,i]:=1; a[i,n+1]:=1; end;
  for i:=1 to n do begin
        flag:=false;
        for k:=i to n do if a[k,i]=1 then begin
                for j:=1 to n+1 do swap(a[i,j],a[k,j]);
                flag:=true; break;
        end;

        if not flag then continue;
        for k:=i+1 to n do if a[k,i]=1 then
                for j:=1 to n+1 do a[k,j]:=a[k,j] xor a[i,j];
  end;
  ans:=maxlongint;
  dfs(n,0);
  writeln(ans);
close(output);
end.
