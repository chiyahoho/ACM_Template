const int inf=~0u>>1;
int n,m;
int S,T;
int ans;
struct node{
    int to,f,v,next;
} w[1000001];
int h[1001],cnt=1;
void add(int x,int y,int f,int v) {
    w[++cnt]=(node){y,f,v,h[x]};
    h[x]=cnt;
    w[++cnt]=(node){x,0,-v,h[y]};
    h[y]=cnt;
}
queue<int> q;
int d[1001];
bool vst[1001];
int fa[1001];
bool Spfa() {
    int i,j,v;
    while (!q.empty()) q.pop();
    memset(vst,0,sizeof vst);
    for (i=1; i<=T; i++) d[i]=-inf;
    memset(fa,0,sizeof fa);
    d[S]=0;
    vst[S]=1;
    q.push(S);
    while (!q.empty()) {
        i=q.front();
        q.pop();
        vst[i]=0;
        for (v=h[i]; v; v=w[v].next) {
            j=w[v].to;
            if (w[v].f&&d[i]+w[v].v>d[j]) {
                d[j]=d[i]+w[v].v;
                fa[j]=v;
                if (!vst[j]) {
                    vst[j]=1;
                    q.push(j);
                }
            }
        }
    }
    return d[T]!=-inf;
}
void Adjust() {
    int i,v,f=inf;
    i=T;
    while (i!=S) {
        v=fa[i];
        f=min(f,w[v].f);
        i=w[v^1].to;
    }
    ans+=f*d[T];
    i=T;
    while (i!=S) {
        v=fa[i];
        w[v].f-=f;
        w[v^1].f+=f;
        i=w[v^1].to;
    }
}
int main() {
	while (Spfa()) Adjust();
}