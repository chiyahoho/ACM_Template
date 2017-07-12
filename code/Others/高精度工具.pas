type
wq=array[0..3000]of longint;
const
u:array[0..4]of longint=(1,10,100,1000,10000);

function max(a,b:longint):longint;
begin
    if a>b then exit(a);
    exit(b);
end;

procedure  cheng(a,b:wq; var t:wq);
var  tak:longint; sss:ansistring; i,j,k:longint;
begin
                fillchar(t,sizeof(t),0);
		t[0]:=a[0]+b[0]-1;
	        for i:=1 to b[0]do begin
	               for j:=1 to a[0] do t[j+i-1]:=t[j+i-1]+b[i]*a[j];
	               for j:=1 to t[0] do
		        if t[j+i-1]>=u[4] then begin
				t[j+i]:=t[j+i]+t[i+j-1] div 10000;
				t[j+i-1]:=t[j+i-1] mod 10000;
			        t[0]:=max(t[0],i+j);
			end;
                end;
end;
function plus(a,b:wq):wq;
var
i:longint;
t:wq;
begin
    t:=a;
    t[0]:=max(a[0],b[0]);
    for i:=1 to b[0] do inc(t[i],b[i]);
    for i:=1 to t[0] do begin
        if t[i]>=u[4] then begin
            inc(t[i+1]);
            dec(t[i],u[4]);
            t[0]:=max(t[0],i+1);
        end;
    end;
    exit(t);
end;
function minus(a,b:wq):wq;
var
i:longint;
t:wq;
begin
    t:=a;
    for i:=1 to b[0] do begin
        dec(t[i],b[i]);
        if t[i]<0 then begin
            inc(t[i],u[4]);
            dec(t[i+1]);
        end;
    end;
    while (t[t[0]]=0)and(t[0]>1) do dec(t[0]);
    exit(t);
end;
function compare(a,b:wq):longint;
var
i:longint;
begin
    if a[0]<b[0] then exit(0);
    if a[0]>b[0] then exit(2);
    for i:=a[0] downto 1 do begin
        if a[i]<b[i] then exit(0);
        if a[i]>b[i] then exit(2);
    end;
    exit(1);
end;
procedure print(a:wq);
var
i,j:longint;
begin
    write(a[a[0]]);
    for i:=a[0]-1 downto 1 do begin
        for j:=3 downto 0 do begin
            write((a[i]div u[j])mod 10);
        end;
    end;
    writeln;
end;
function reads:wq;
var
t:wq;
i,j:longint;
s:ansistring;
begin
    readln(s);
    fillchar(t,sizeof(t),0);
    for i:=length(s) downto 1 do begin
        j:= length(s)-i;
        inc(t[j div 4+1],u[j mod 4]*(ord(s[i])-ord('0')));
    end;
    t[0]:=(length(s)-1)div 4+1;
    exit(t);
end;
function change(a:longint):wq;
var
i,j:longint; t:wq;
begin
    fillchar(t,sizeof(t),0);
    i:=0;
    j:=3;
    while a<>0 do begin
        inc(j);
        if j=4 then begin
            j:=j-4;
            inc(i);
        end;
        inc(t[i],u[j]*(a mod 10));
        a:=a div 10;
    end;
    if i=0 then i:=1;
    t[0]:=i;
    exit(t);
end;
