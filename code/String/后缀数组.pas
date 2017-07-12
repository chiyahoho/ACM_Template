const maxl=100;
var height,sa,tmp,tax,rank:array[0..maxl*2]of longint;
t:array['@'..'z']of longint;
s:array[0..maxl]of char;
i,j,l,o,b:longint;
ch:char;

function max(a,b:longint):longint;
begin if a<b then exit(b); exit(a); end;

procedure sort(u:longint);
begin
  for j:=1 to l do tax[j]:=0;
  for j:=1 to l do inc(tax[rank[sa[j]+u]]);
  for j:=1 to l do inc(tax[j],tax[j-1]);
  for j:=l downto 1 do begin
    tmp[tax[rank[sa[j]+u]]]:=sa[j];
    dec(tax[rank[sa[j]+u]]);
  end;
  sa:=tmp;
end;

begin
assign(input,'1.in'); reset(input);
  while not eoln do begin inc(l); read(s[l]) end;
  for i:=1 to l do t[s[i]]:=1;
  for ch:='A'to 'z' do if t[ch]=1 then t[ch]:=t[pred(ch)]+1 else t[ch]:=t[pred(ch)];
  for i:=1 to l do rank[i]:=t[s[i]];
  for i:=1 to trunc(ln(2*l-1)/ln(2)) do begin
    o:=1 shl (i-1);
    for j:=1 to l do sa[j]:=j;
    sort(o);
    sort(0);
    for j:=1 to l do begin
      tmp[sa[j]]:=tmp[sa[j-1]];
      if(rank[sa[j]+o]<>rank[sa[j-1]+o]) or (rank[sa[j]]<>rank[sa[j-1]])
      then inc(tmp[sa[j]]);
    end;
    rank:=tmp;
  end;
  for i:=1 to l do if rank[i]<>l then begin
    b:=rank[i];
    o:=sa[b+1];
    while s[height[b]+i]=s[height[b]+o] do inc(height[b]);
    height[rank[i+1]]:=max(height[b]-1,0);
  end;
end.
