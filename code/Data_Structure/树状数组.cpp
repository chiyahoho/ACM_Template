#define lowbit(x) ((x)&(-(x)))
int sum(int *a,int x){
  int s=0;
  for(;x;x-=lowbit(x))s+=a[x];
  return s;
}
void update(int *a,int x,int w){
  for(;x<=n;x+=lowbit(x))a[x]+=w;
}
