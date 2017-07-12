procedure tarjan(uu:longint);
var
  v,top,i,tt:longint;
  flag:boolean;
begin
  top:=1; d[top]:=uu;
  while top>0 do begin
        u:=d[top];
        flag:=true;
        if dfn[u]=0 then begin
                inc(cc); dfn[u]:=cc; low[u]:=cc;
                inc(tot); q[tot]:=u;
                f[u]:=true; ff[u]:=true;
                y[top]:=h[u];
        end
        else begin low[u]:=min(low[u],low[e[y[top]].v]); y[top]:=e[y[top]].n; end;
        while y[top]>0 do begin
                v:=e[y[top]].v;
                if not f[v] then begin
                        inc(top);
                        d[top]:=v;
                        flag:=false;
                        break;
                end
                else if ff[v] then low[u]:=min(low[u],dfn[v]);
                y[top]:=e[y[top]].n;
        end;
        if flag then begin
              if dfn[u]=low[u] then begin
                      tt:=0;
                      repeat
                              v:=q[tot];
                              dec(tot);
                              ff[v]:=false;
                              {here you can give the information to u}
                      until u=v;
              end;
              dec(top);
        end;
  end;
end;

begin
  for i:=1 to n do if dfn[i]=0 then tarjan(i);
end.