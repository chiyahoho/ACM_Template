{hdu3065
题意：给n个模式串，一个母串，问每个模式串在母串中出现多少次。
1.模式串只包含大写字母，母串中包含各种奇葩字符。
2.空间被卡了。完全可以造出跟hdu2222一样的32M开不下的数据，还好数据比较人性化。
3.坑爹的！！！！多组数据木有声明啊有木有！！！！
}
const maxN=290000;
var
      ni,i,n,tot,len:longint;
      tr:array[0..maxN,'A'..'Z']of longint;     //trie树
      s:array[0..2000500]of char;               //模式串或母串
      qu,nt,vis:array[0..maxN]of longint;   //qu:bfs序，nt:next，vis:访问次数
      wd,lwd:array[0..2000]of longint;      //单词位置，单词长度
      wds:array[0..2000,0..100]of char;     //记录单词，此题输出要求，不必理会

procedure reads;                //读入，平常读入就好，这里是因为此题会发生某些奇葩字符也出现的情况
var   ch:char;
begin
      len:=0;
      while not eoln do begin
            read(ch); if (ch<'A')or(ch>'Z') then break;
            inc(len); s[len]:=ch;
      end;
end;

procedure insert;               //插入单词，建立trie树
var   p,i:longint;
begin
      p:=0;
      for i:=1 to len do begin
            if tr[p,s[i]]=0 then begin
                  inc(tot);
                  tr[p,s[i]]:=tot;
            end;
            p:=tr[p,s[i]];
      end;
      wd[ni]:=p;
end;

procedure build;                //bfs求next函数
var   l,r,u,v,q:longint;
      c:char;
begin
      l:=0; r:=1;
      qu[1]:=0;
      while l<r do begin
            inc(l);
            u:=qu[l];
            for c:='A' to 'Z' do if tr[u,c]>0 then begin
                  q:=nt[u]; v:=tr[u,c];
                  while (tr[q,c]=0)and(q<>0) do q:=nt[q];
                  if u=0 then nt[v]:=0 else nt[v]:=tr[q,c]; //注意要特判
                  inc(r); qu[r]:=v;
            end;
      end;
end;

procedure dos;                  //匹配
var   p,i:longint;
begin
      p:=0;
      for i:=1 to len do begin
            while (tr[p,s[i]]=0)and(p<>0) do p:=nt[p];
            p:=tr[p,s[i]]; inc(vis[p]);
      end;
end;

begin
assign(input,'3065.in'); reset(input);
assign(output,'3065.out'); rewrite(output);
while not eof do begin              //坑爹的多组数据
fillchar(nt,sizeof(nt),0);
fillchar(vis,sizeof(vis),0);
fillchar(tr,sizeof(tr),0);
tot:=0;

      readln(n);
      for ni:=1 to n do begin
            reads; readln;
            insert;
            lwd[ni]:=len;           //不必理会
            for i:=1 to len do wds[ni,i]:=s[i]; //不必理会
      end;
      build;
      while not eoln do begin
            reads;
            if len>0 then dos;
      end;
      for i:=tot+1 downto 2 do inc(vis[nt[qu[i]]],vis[qu[i]]);  //统计

      for ni:=1 to n do begin                   //奇葩的输出
            if vis[wd[ni]]=0 then continue;
            for i:=1 to lwd[ni] do write(wds[ni,i]);
            writeln(': ',vis[wd[ni]]);
      end;
end;
close(output);
end.