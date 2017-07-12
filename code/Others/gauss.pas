var
  n,m,i,j,k,p:longint;
  max:extended;
  flag:boolean;
  a:array[0..400,0..400]of extended;
  x,xp:array[0..400]of longint;
begin
assign(input,'gauss.in'); reset(input);
assign(output,'gauss.out'); rewrite(output);
  readln(n); m:=n;
  for i:=1 to m do begin
        for j:=1 to n+1 do read(a[i,j]);
        readln;
  end;
  for i:=1 to m do begin
        max:=0;
        for j:=1 to n do if max<abs(a[i,j]) then begin max:=abs(a[i,j]); p:=j; end;
        if max=0 then if a[i,n+1]=0 then continue
                                    else begin flag:=true; break; end;
        xp[i]:=p;
        max:=a[i,p];      //for a[i,p]<0
        for j:=1 to n+1 do a[i,j]:=a[i,j]/max;
        for k:=1 to m do if i<>k then begin
                max:=a[k,p];
                for j:=1 to n+1 do a[k,j]:=a[k,j]-max*a[i,j];      //delete every line's p
        end;
  end;
  if flag then writeln('No Solution!')
  else begin
        for i:=1 to m do x[xp[i]]:=round(a[i,n+1]);//integer
        for i:=1 to n do write(x[i],' ');
  end;
close(output);
end.
