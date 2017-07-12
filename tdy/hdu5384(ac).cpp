#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
int n,m;
char ch[20001];
string a[100001];
struct node{
    int ch[26];
    int fa;
    int v;
    int fail;
    void init() {
        fa=0;
        v=0;
        fail=0;
        memset(ch,0,sizeof ch);
    }
} T[200001];
int tot;
void add(int id) {
    int i,j,l,u=0,y;
    l=strlen(ch);
    for (i=0; i<l; i++) {
        y=ch[i]-'a';
        if (!T[u].ch[y]) {
            T[u].ch[y]=++tot;
            T[tot].init();
            T[tot].fa=u;
        }
        u=T[u].ch[y];
    }
    T[u].v++;
}
queue<int> q;
void ac() {
    int i,j,k,v,fail;
    while (!q.empty()) q.pop();
    T[0].fail=-1;
    q.push(0);
    while (!q.empty()) {
        i=q.front();
        q.pop();
        fail=T[i].fail;
        if (fail!=-1) T[i].v+=T[fail].v;
        for (j=0; j<26; j++)
            if (T[i].ch[j]) {
                v=T[i].ch[j];
                if (fail==-1) T[v].fail=0;
                else T[v].fail=T[fail].ch[j];
                q.push(v);
            }
            else if (fail!=-1) {
                T[i].ch[j]=T[fail].ch[j];
            }
    }
}
void cal(int id) {
    int i,j,k,l,u=0,v,ret=0;
    l=a[id].length();
    for (i=0; i<l; i++) {
        j=a[id][i]-'a';
        u=T[u].ch[j];
        v=T[u].v;
        ret+=v;
    }
    printf("%d\n",ret);
}
void print() {
    int i,j,l,v;
    for (i=0; i<=tot; i++) {
        cout<<i<<":"<<endl;
        for (j=0; j<26; j++)
            if (T[i].ch[j]) cout<<char(j+'a')<<":"<<T[i].ch[j]<<"  ";
        cout<<endl;
    }
}
int main() {
    int __,i;
    scanf("%d",&__);
    while (__--) {
        scanf("%d%d",&n,&m);
        for (i=1; i<=n; i++) {
            scanf("%s",ch);
            a[i]=ch;
        }
        tot=0;
        T[0].init();
        for (i=1; i<=m; i++) {
            scanf("%s",ch);
            add(i);
        }
        ac();
        for (i=1; i<=n; i++) {
            cal(i);
        }
    }
    return 0;
}
