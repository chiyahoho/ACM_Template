//BZOJ2659 bjwc2012
var
      p,q,ans:int64;

function calc(n,a,b:int64):int64;
var
      r,k:int64;
begin
      if a=0 then exit(0);
      if a>=b then begin
            r:=a mod b;
            k:=a div b;
            exit(k*(n+1)*n div 2+calc(n,r,b));
      end
      else begin
            r:=n*a div b;
            exit(r*n-calc(r,b,a){+r div a});    //r div a是直线上的点，因此题p,q互质，无此点
      end;
end;

begin
assign(input,'2659.in'); reset(input);
assign(output,'2659.out'); rewrite(output);
      readln(p,q);
      inc(ans,calc(p div 2,q,p));
      inc(ans,calc(q div 2,p,q));
      writeln(ans);
close(output);
end.
