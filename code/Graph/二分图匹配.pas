记link[i]表示右列i目前连着的点，没有时连0

对于左列的点x，去找可以与其相连的右列点i
若link[i]=0就找到，将link[i]改为x
若link[i]=p<>0，强制将link[i]改为x，再对p去做同样的操作，若能找到i2，则i给x，i2给p，否则i还给p（link[i]:=p），继续找能与x相连的下一个点i，同样操作。
注意，对于一次寻找，因为不能顶替在这次寻找中已经找过的右列点，所以要记cover数组。

代码：
function find(x:longint):boolean;
var
i,q:longint;
begin
  for i:=1 to m do if b[x,i] and not cover[i] then
  begin
    q:=link[i]; link[i]:=x; cover[i]:=true;
    if (q=0) or find(q) then exit(true);
    link[i]:=q;
  end;
  exit(false);
end;

调用时要：
  for i:=1 to n do 
  begin
    fillchar(cover,sizeof(cover),false);
    find(i);
  end;

答案：  for i:=1 to m do if link[i]>0 then inc(ans);