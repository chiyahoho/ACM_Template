带权有向图，AOE网。
AOE网的性质：
一个顶点发生了，说明之前的活动都已完成，之后的活动可以开始。(不冲突的点可以同时发生)

★【要求的值】：
1.完成整个工程需要多少时间？
2.哪些活动是关键活动，会影响到工程进度？(因此只有优化关键活动才能缩短工程时间)

记：
ve[i]表示i点的最早发生时间。vl[i]表示i点的最迟发生时间。      //early，last
ee[i]表示i边的最早发生时间。el[i]表示i边的最迟发生时间。

因此得出：
ve[1]=0;
ve[v]=max{ve[u]+d[u,v]}(u为v的所有父亲)                   //d[u,v]表示边<u,v>的长，可用边表
vl[n]=ve[n]                                               //显然的
vl[u]=min{vl[v]-d[u,v]}(v为u的所有孩子)
对于y边连接着u和v
ee[y]=ve[u];  el[y]=vl[v]-d[u,v]

关键路径：
完成工程的最短时间是从开始点到完成点的最长路径长度，此路径就称之为关键路径。(回答问题一)(可能不止一条)

关键活动：
若ee[y]=el[y]则y为关键边。
若ve[i]=vl[i]则i为关键点。


算法总结：
1.输入e条弧，建立AOE网.
2.得出拓扑序，若无法拓扑说明有环，问题不可解，halt。
3.初始化ve[1]=0,按拓扑序更新ve
4.初始化vl[n]=ve[n]，按逆拓扑序更新vl                     //无需重求，逆序做即可(自己证)
5.求出ee[y]和el[y]
6.输出关键路径

算法简化：
两个关键点之间必为关键边，关键边的两头必然为2个关键点。                  //自己想
因此若无要求可以简化第5条。不必求ee[y]与el[y]。
直接这样：for i:=1 to n do if ve[a[i]]=vl[a[i]] then write(a[i],'->');   //a是拓扑序列

算法代码：
var
  i,j,n,m,u,v,l:longint;
  a,vl,ve,into:array[0..1000]of longint;
  d:array[0..1000,0..1000]of longint;
function toper:boolean;
var
  i,j,k:longint;
begin
  for i:=1 to n do for j:=1 to n do if d[i,j]>=0 then inc(into[j]);
  for i:=1 to n do begin
        for j:=1 to n+1 do if into[j]=0 then break;
        if j=n+1 then exit(false);
        a[i]:=j; into[j]:=-1;
        for k:=1 to n do if d[j,k]>=0 then dec(into[k]);
  end;
  exit(true);
end;

begin
assign(input,'guan.in'); reset(input);
assign(output,'guan.out'); rewrite(output);
  readln(n,m);
  fillchar(d,sizeof(d),200);
  for i:=1 to m do begin
        readln(u,v,l);
        d[u,v]:=l;
  end;
  if not toper then begin writeln('no solution!'); close(output); halt; end;
  ve[1]:=0;
  for i:=2 to n do
    for j:=1 to i-1 do if (d[a[j],a[i]]>=0)and(ve[a[i]]<ve[a[j]]+d[a[j],a[i]]) then
    ve[a[i]]:=ve[a[j]]+d[a[j],a[i]];
  fillchar(vl,sizeof(vl),100);
  vl[n]:=ve[n];
  for i:=n-1 downto 1 do
    for j:=i+1 to n do if (d[a[i],a[j]]>=0)and(vl[a[i]]>vl[a[j]]-d[a[i],a[j]]) then
    vl[a[i]]:=vl[a[j]]-d[a[i],a[j]];

  writeln(ve[n]);
  for i:=1 to n-1 do if ve[i]=vl[i] then write(a[i],'->');    //这里输出的不是关键路径。有肯能：1->2->4,1->3->4这个长度相等都是，而这里会输成1->2->3->4具体自己解决
  writeln(a[n]);
close(output);
end.