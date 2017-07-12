#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N = 10005;
char ch[N];
struct SAM{
    struct node{
        int ch[26];
        int f, len, u;
        void init() {
            f = -1, len = 0;
            memset(ch,-1,sizeof ch);
        }
    };
    node a[N<<1];
    int tot, last;
    void init() {
        tot = 0, last = 0;
        a[tot++].init();
    }
    int newnode() {
        a[tot].init();
        return tot++;
    }
    void add(int c,int v) {
        int u, p, q, r;
        p = newnode();
        a[p].u = v;
        u = last;
        a[p].len = a[last].len + 1;
        for ( ; u != -1 && a[u].ch[c] == -1; u = a[u].f) a[u].ch[c] = p;
        if (u == -1) a[p].f = 0;
        else {
            q = a[u].ch[c];
            if (a[u].len + 1 == a[q].len) a[p].f = q;
            else {
                r = newnode();
                a[r] = a[q];
                a[r].len = a[u].len + 1;
                a[p].f = a[q].f = r;
                for ( ; u != -1 && a[u].ch[c] == q; u = a[u].f) a[u].ch[c] = r;
            }
        }
        last = p;
    }
} sam;
int a[11] = {0, 1, 0, 1, 2, 0, 1, 0};
int main() {
    int T, i, j, l, p;
    sam.init();
    for (i = 0; i < 8; i++) sam.add(a[i], i);
    l = sam.tot;
    cout<<l<<endl;
    for (i = 0; i < l; i++)
        for (j = 0; j < 26; j++)
            if (sam.a[i].ch[j] != -1) printf("%d %d %d\n",i, j, sam.a[i].ch[j]);
    for (i = 0; i < l; i++) printf("%d %d\n",sam.a[i].f,sam.a[i].u);
    /*scanf("%d",&T);
    while (T--) {
        sam.init();
        scanf("%s",ch);
        l = strlen(ch);
        for (i = 0; i < l; i++) sam.add(ch[i] - 'a');
        for (i = 0; i < l; i++) sam.add(ch[i] - 'a');
        p = 0;
        for (i = 0; i < l; i++)
            for (j = 0; j < 26; j++)
                if (sam.a[p].ch[j] != -1) {
                    p = sam.a[p].ch[j];
                    break;
                }
        printf("%d\n", sam.a[p].len - l + 1);
    }*/
    return 0;
}