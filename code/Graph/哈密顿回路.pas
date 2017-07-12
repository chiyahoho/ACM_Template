//sgu122
var
      u,uu,v,y,n,m,et,g,i:integer;
      q,qq:array[0..10000]of integer;
      f,h:array[0..10000]of boolean;
      e:array[0..1010,0..1010]of boolean;
      flag:boolean;

begin
assign(input,'122.in'); reset(input);
assign(output,'122.out'); rewrite(output);
      readln(n);
      for u:=1 to n do begin
            while not eoln do begin
                  read(v);
                  e[u,v]:=true; e[v,u]:=true;
            end;
            readln;
            h[u]:=true;
      end;

      f[1]:=true; q[1]:=1; m:=1;
      for g:=1 to n-1 do begin
            flag:=false;
            u:=q[m];
            for v:=1 to n do if h[u] and e[u,v] and not f[v] then begin
                  inc(m); q[m]:=v; f[v]:=true;
                  flag:=true; break;
            end;
            if flag then continue;
            u:=q[1];
            for v:=1 to n do if h[u] and e[u,v] and not f[v] then begin
                  inc(m); for i:=m downto 2 do q[i]:=q[i-1];
                  q[1]:=v; f[v]:=true;
                  flag:=true; break;
            end;
            if flag then continue;

            for uu:=2 to m-1 do if not e[q[1],q[m]] and e[q[m],q[uu]] and e[q[1],q[uu+1]] then begin
                  for i:=1 to uu do qq[i]:=q[i];
                  for i:=uu+1 to m do qq[m-i+uu+1]:=q[i];
                  for i:=1 to m do q[i]:=qq[i];
                  break;
            end;

            for uu:=2 to m-1 do if not flag then begin
                  u:=q[uu]; if not h[u] then continue;
                  for v:=1 to n do if e[u,v] and not f[v] then begin
                        for i:=uu to m do qq[i-uu+2]:=q[i];
                        for i:=1 to uu-1 do qq[m-uu+2+i]:=q[i];
                        inc(m);
                        for i:=2 to m do q[i]:=qq[i];
                        q[1]:=v; f[v]:=true;
                        flag:=true; break;
                  end;
                  if not flag then h[u]:=false;
            end;
      end;

      for uu:=2 to m-1 do if not e[q[1],q[m]] and e[q[m],q[uu]] and e[q[1],q[uu+1]] then begin
                  for i:=1 to uu do qq[i]:=q[i];
                  for i:=uu+1 to m do qq[m-i+uu+1]:=q[i];
                  for i:=1 to m do q[i]:=qq[i];
                  break;
            end;
      for u:=1 to m do if q[u]=1 then begin
            for i:=u to m do write(q[i],' ');
            for i:=1 to u-1 do write(q[i],' ');
            //for i:=u downto 1 do write(q[i],' ');
            //for i:=m downto u+1 do write(q[i],' ');
            writeln(1);
      end;
close(output);
end.
