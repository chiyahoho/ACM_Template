#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<set>
#include<vector>
using namespace std;
typedef long long ll;
const int mod=100007;
int P,B,N;
int m;
int pow(int a,int b) {
	int ret=1;
	while (b) {
		if (b&1) ret=(ll)ret*a%P;
		a=(ll)a*a%P;
		b>>=1;
	}
	return ret;
}
set<int> s;
vector<pair<int,int> > hs[100007];
set<int>::iterator it;
void add(int u,int id) {
	int i,j,l;
	j=u%mod;
	l=hs[j].size();
	for (i=0; i<l; i++)
		if (hs[j][i].first==u) {
			hs[j][i].second=id;
			return;
		}
	hs[j].push_back(make_pair(u,id));
	s.insert(j);
}
int ask(int u) {
	int i,j,l;
	j=u%mod;
	l=hs[j].size();
	for (i=0; i<l; i++)
		if (hs[j][i].first==u) {
			return hs[j][i].second;
		}
	return -1;
}
void BSGS() {
	int i,j,k,t;
	m=ceil(sqrt(P));
	for (i=0,j=1; i<m; i++,j=(ll)j*B%P) {
		if (j==N) {
			printf("%d\n",i);
			return;
		}
		add((ll)j*N%P,i);
	}
	for (i=1,k=j; i<=m; i++,k=(ll)k*j%P) {
		t=ask(k);
		if (t!=-1) {
			t=i*m-t;
			printf("%d\n",t);
			return;
		}
	}
	printf("no solution\n");
}
void init() {
	for (it=s.begin(); it!=s.end(); it++) {
		hs[*it].clear();
	}
	s.clear();
}
int main() {
	s.clear();
	while (scanf("%d%d%d",&P,&B,&N)!=EOF) {
		init();
		BSGS();
	}
	return 0;
}