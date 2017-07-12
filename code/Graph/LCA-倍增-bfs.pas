procedure bfs;
var     l,r,y,u,v,i,j:longint;
begin
        l:=0; r:=1;
        qq[1]:=1; dp[1]:=1;
        while l<r do begin
                inc(l); u:=qq[l];
                y:=h[u];
                while y>0 do begin
                        v:=e[y].v;
                        if f[u,0]<>v then begin
                                dp[v]:=dp[u]+1;
                                f[v,0]:=u;
                                inc(r); qq[r]:=v;
                        end;
                        y:=e[y].n;
                end;
        end;

        for i:=1 to n+1 do
        for j:=1 to lg do f[qq[i],j]:=f[f[qq[i],j-1],j-1];
end;

function lca(a,b:longint):longint;
var     i,tmp:longint;
begin
        if dp[a]<dp[b] then begin tmp:=a; a:=b; b:=tmp; end;
        for i:=lg downto 0 do if dp[f[a,i]]>=dp[b] then a:=f[a,i];
        for i:=lg downto 0 do if f[a,i]<>f[b,i] then begin a:=f[a,i]; b:=f[b,i]; end;
        if a<>b then exit(f[a,0]) else exit(a);
end;