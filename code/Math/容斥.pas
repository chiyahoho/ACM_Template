//给出N个整数A1，A2，⋯⋯，AN，统计满足i<j且Ai和Aj互质的二元组(i，j)的数量。

【【题解】】：
把每个数分解质因数，比如分解后有2,3,5，那么给记录有2的+1，有3的+1，有5的+1，有2又有3的+1⋯⋯
一个处理就是w就是记录这个的数组。那么很显然2记在w[2]里，3记在w[3]里，又有2又有3的就可以记在w[2*3]，就是w[6]里。这样一一对应了。
现在假如加入a[i]=3*5*7(省略了多次幂，比如(3^2)*(5^4)*(7^3)也当做3*5*7处理)，那么i之前的数中不与a[i]互质的数就有w[3]+w[5]+w[7]-w[15]-w[21]-w[35]+w[105]个，就是上面的容斥了。
做法是枚举长度为3的二进制，100表示3,010表示5,001表示7,101表示21⋯⋯然后再计算这个二进制中有多少1，odd一下判断是+还是-就好了。

【【程序】】：
var
  num,x,opt,t,y,n,i,j,max:longint;
  f,w,a,now:array[0..2000000]of longint;
  ans:int64;
begin
assign(input,'coprime.in'); reset(input);
assign(output,'coprime.out'); rewrite(output);
  max:=1000000;
  for i:=1 to max do f[i]:=i;
  for i:=2 to max do begin
        if f[i]=i then begin inc(a[0]); a[a[0]]:=i; end;
        for j:=1 to a[0] do if a[j]*i<=max then begin
                f[a[j]*i]:=a[j];
                if f[i]=a[j] then break;
        end
        else break;
  end;

  readln(n);
  for i:=1 to n do begin
        read(x);
        inc(ans,i-1);
        now[0]:=0;
        while x>1 do begin
                if now[now[0]]<>f[x] then begin
                        inc(now[0]);
                        now[now[0]]:=f[x];
                end;
                x:=x div f[x];
        end;

        for opt:=1 to 1<<now[0]-1 do begin
                num:=1;
                x:=opt; t:=0; y:=0;
                while x>0 do begin
                        inc(y);
                        if odd(x) then begin
                                num:=num*now[y];
                                inc(t);
                        end;
                        x:=x>>1;
                end;
                if odd(t) then dec(ans,w[num])
                else inc(ans,w[num]);
                inc(w[num]);
        end;
  end;

  writeln(ans);
close(output);
end.
