#include <bits/stdc++.h>
#include <chrono>
#include <thread>
using namespace std;
#include <stdio.h>
#include <ctype.h>

class InParser {
private:
	FILE *fin;
	char *buff;
	int sp;

	char read_ch() {
		++sp;
		if (sp == 4096) {
			sp = 0;
			fread(buff, 1, 4096, fin);
		}
		return buff[sp];
	}

public:
	InParser(const char* nume) {
		fin = fopen(nume, "r");
		buff = new char[4096]();
		sp = 4095;
	}
	
	InParser& operator >> (int &n) {
		char c;
		while (!isdigit(c = read_ch()) && c != '-');
		int sgn = 1;
		if (c == '-') {
			n = 0;
			sgn = -1;
		} else {
			n = c - '0';
		}
		while (isdigit(c = read_ch())) {
			n = 10 * n + c - '0';
		}
		n *= sgn;
		return *this;
	}
	
	InParser& operator >> (long long &n) {
		char c;
		n = 0;
		while (!isdigit(c = read_ch()) && c != '-');
		long long sgn = 1;
		if (c == '-') {
			n = 0;
			sgn = -1;
		} else {
			n = c - '0';
		}
		while (isdigit(c = read_ch())) {
			n = 10 * n + c - '0';
		}
		n *= sgn;
		return *this;
	}
};
#define cin fin
#define cout fout
ifstream fin("sever.in");
ofstream fout("sever.out");


int tata[200001];
int cul[200001],tol[200001];
struct query
{
    int x,y;
} que[200001];
vector <int> v[200001];
int nivel[200001];
int rasp[200001],cnt[200001];
void Read(int &n,int &m,int &q)
{
    #ifdef HOME
        freopen("test.in","r",stdin);
    #endif // HOME
    int i;
    cin>>n>>m;
    for(i=1; i<=n; i++)
        v[i].clear();
    int x,y;
    for(i=1; i<n; i++)
    {
        cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for(i=1; i<=n; i++)
        cin>>cul[i];
    for(i=1; i<=m; i++)
        cin>>tol[i];
    cin>>q;
    for(i=1; i<=q; i++)
        cin>>que[i].x>>que[i].y;
}
int Plus[200001],Minus[200001],rmq[18][200001],cenete,vec[400001],common_papa[200001],oldCnt[200001];
vector <int> PlusCul[200001],MinusCul[200001];
int bruh[200001],smen[400001];
void dfsPlusMinus(int nod,int papa)
{
    Plus[nod]=++cenete;
    vec[cenete]=nod;
    tata[nod]=papa;
    nivel[nod]=nivel[papa]+1;
    for(auto it:v[nod])
        if(it!=papa)
            dfsPlusMinus(it,nod);
    Minus[nod]=++cenete;
    vec[cenete]=-nod;
}
int lca(int x,int y)
{
    if(nivel[x]>nivel[y])
        swap(x,y);
    int pas=17;
    while(pas!=-1)
    {
        if(nivel[y]-(1<<pas)>=nivel[x])
            y=rmq[pas][y];
        pas--;
    }
    if(x==y)
        return x;
    pas=17;
    while(pas!=-1)
    {
        if(rmq[pas][x]!=rmq[pas][y])
        {
            x=rmq[pas][x];
            y=rmq[pas][y];
        }
        pas--;
    }
    return tata[x];
}
int countCul(int a,int b,int c)
{
    int plu=0,minu=0;
    if(PlusCul[c].size())
        plu=lower_bound(PlusCul[c].begin(),PlusCul[c].end(),b+1)-lower_bound(PlusCul[c].begin(),PlusCul[c].end(),a);
    if(MinusCul[c].size())
        minu=lower_bound(MinusCul[c].begin(),MinusCul[c].end(),b+1)-lower_bound(MinusCul[c].begin(),MinusCul[c].end(),a);
    return plu-minu;
}
vector <int> Sqrt(int n,int m,int q)
{
    int i,j;
    vector <int> ans;
    for(i=1; i<=m; i++)
    {
        rasp[i]=-1;
        cnt[i]=0;
    }
    for(i=1;i<=n;i++)
        nivel[i]=0;
    cenete=0;
    dfsPlusMinus(1,0);
    for(i=1; i<=n; i++)
        rmq[0][i]=tata[i];
    for(j=1; (1<<j)<=n; j++)
        for(i=1; i<=n; i++)
            rmq[j][i]=rmq[j-1][rmq[j-1][i]];
    for(i=1; i<=m; i++)
    {
        PlusCul[i].clear();
        MinusCul[i].clear();//haha minuscul
    }
    for(i=1; i<=n; i++)
    {
        PlusCul[cul[i]].push_back(Plus[i]);
        MinusCul[cul[i]].push_back(Minus[i]);
    }
    for(i=1; i<=m; i++)
    {
        sort(PlusCul[i].begin(),PlusCul[i].end());
        sort(MinusCul[i].begin(),MinusCul[i].end());
    }
    for(i=1; i<=q; i++)
        common_papa[i]=lca(que[i].x,que[i].y);
    int cate=(int)sqrt(q);
    for(i=1; i<=q; i+=cate)
    {
        int j=min(i+cate-1,q);
        for(int k=1; k<=m; k++)
            oldCnt[k]=cnt[k];
        for(int k=1; k<=n; k++)
            bruh[k]=0;
        for(int k=1; k<=2*n; k++)
            smen[k]=0;
        for(int k=i; k<=j; k++)
        {
            int f1=Plus[common_papa[k]],f2=Plus[que[k].x],f3=Plus[que[k].y];
            smen[f1]++;
            smen[f2+1]--;
            bruh[common_papa[k]]++;//se repeta
            smen[f1]++;
            smen[f3+1]--;
        }
        for(int k=1; k<=2*n; k++)
        {
            smen[k]+=smen[k-1];
            if(vec[k]<0)
                cnt[cul[-vec[k]]]-=smen[k];
            else
                cnt[cul[vec[k]]]+=(smen[k]-bruh[vec[k]]);
        }
        vector <int> solv;
        for(int k=1; k<=m; k++)
            if(cnt[k]>=tol[k]+1&&rasp[k]==-1)//hehe
                solv.push_back(k);
        for(int k=i; k<=j; k++)
        {
            int f1=Plus[common_papa[k]],f2=Plus[que[k].x],f3=Plus[que[k].y];
            for(auto it:solv)
            {
                oldCnt[it]+=countCul(f1,f2,it)+countCul(f1,f3,it)-(cul[common_papa[k]]==it);
                if(oldCnt[it]>=tol[it]+1&&rasp[it]==-1)
                    rasp[it]=k;
            }
        }
    }
    for(i=1; i<=m; i++)
        ans.push_back(rasp[i]);
    return ans;
}
int main()
{
    #ifdef HOME
        freopen("test.out","w",stdout);
    #endif // HOME
    int n,m,q;
    Read(n,m,q);
    vector <int> v = Sqrt(n,m,q);

    for(auto it:v)
        cout<<it<<" ";
    cout<<'\n';
    return 0;
}
