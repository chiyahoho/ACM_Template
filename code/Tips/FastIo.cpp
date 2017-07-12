inline int getint()
{
    char c;
    int sig=1,tp=0;
    while (c!='-'&&!isdigit(c)) c=getchar();
    if (c=='-')
    {
        sig=-1; c=getchar();
    }
    while (isdigit(c))
    {
        tp=tp*10+c-'0';
        c=getchar();
    }
    return sig*tp;
}

inline void putint(int x)
{
    if (x<0)
    {
        x=-x; putchar('-');
    }
	if(x>9) putint(x/10);
	putchar(x%10+'0');
}
