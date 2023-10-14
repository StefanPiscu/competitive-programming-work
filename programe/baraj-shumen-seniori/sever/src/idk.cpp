#include <bits/stdc++.h>
#include <chrono>
#include <thread>
using namespace std;


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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
vector <pair<int,int>> getTree(int n)
{
    int lenLant=rng()%(n-1)+1;
    vector<pair<int, int>> edges;
    for(int i=1; i<lenLant; ++i)
        edges.push_back({i, i+1});
    for(int i=lenLant+1; i<=n; ++i)
        edges.push_back({rng()%(i-1)+1, i});
    vector<int> eye(n+1);
    for(int i=1; i<=n; ++i)
        eye[i]=i;
    random_shuffle(eye.begin()+1, eye.end());
    vector<pair<int, int>> edges2;
    for(auto it:edges)
    {
        int a=eye[it.first], b=eye[it.second];
        if(a>b)
            swap(a, b);
        edges2.push_back({a, b});
    }
    return edges2;
}
void genTest()
{
    freopen("test.in","w",stdout);
    int n=rng()%50+1,m=rng()%50+1,i;
    cout<<n<<" "<<m<<'\n';///nr. de noduri si nr. de culori
    vector<pair<int,int>> edges=getTree(n);
    for(auto it:edges)
        cout<<it.first<<" "<<it.second<<'\n';
    for(i=1; i<=n; i++) ///culorile
        cout<<rng()%m+1<<" ";
    cout<<'\n';
    for(i=1; i<=m; i++) ///tolerantele
        cout<<rng()%10+1<<" ";
    cout<<'\n';
    int q=rng()%20+1;
    cout<<q<<'\n';///nr. de query-uri
    for(i=1; i<=q; i++)
        cout<<rng()%n+1<<" "<<rng()%n+1<<'\n';
    fclose(stdout);
}
void Read(int &n,int &m,int &q)
{
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
void dfs(int nod,int papa)
{
    nivel[nod]=nivel[papa]+1;
    tata[nod]=papa;
    for(auto it:v[nod])
        if(it!=papa)
            dfs(it,nod);
}
vector <int> Brute(int n,int m,int q)
{
    int i;
    vector <int> ans;
    for(i=1; i<=n; i++)
        nivel[i]=0;
    for(i=1; i<=m; i++)
    {
        rasp[i]=-1;
        cnt[i]=0;
    }
    dfs(1,0);
    for(i=1; i<=q; i++)
    {
        int x=que[i].x,y=que[i].y;
        if(nivel[x]>nivel[y])
            swap(x,y);
        while(nivel[y]>nivel[x])
        {
            cnt[cul[y]]++;
            if(cnt[cul[y]]==tol[cul[y]]+1)
                rasp[cul[y]]=i;
            y=tata[y];
        }
        while(x!=y)
        {
            cnt[cul[y]]++;
            if(cnt[cul[y]]==tol[cul[y]]+1)
                rasp[cul[y]]=i;
            cnt[cul[x]]++;
            if(cnt[cul[x]]==tol[cul[x]]+1)
                rasp[cul[x]]=i;
            y=tata[y];
            x=tata[x];
        }
        cnt[cul[x]]++;
        if(cnt[cul[x]]==tol[cul[x]]+1)
            rasp[cul[x]]=i;
    }
    for(i=1; i<=m; i++)
        ans.push_back(rasp[i]);
    return ans;
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
vector<int> Idk(int n,int m,int q)
{
    int i,j;
    vector <int> ans;
    for(i=1; i<=m; i++)
    {
        rasp[i]=-1;
        cnt[i]=0;
    }
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
		for(int k=1; k<=q; k++)
		{
				int f1=Plus[common_papa[k]],f2=Plus[que[k].x],f3=Plus[que[k].y];
				for(int it=1;it<=m;++it)
				{
						oldCnt[it]+=countCul(f1,f2,it)+countCul(f1,f3,it)-(cul[common_papa[k]]==it);
						if(oldCnt[it]>=tol[it]+1&&rasp[it]==-1)
								rasp[it]=k;
				}
		}
    for(i=1; i<=m; i++)
        ans.push_back(rasp[i]);
    return ans;
}
int main()
{
    //genTest();
    int n,m,q;
    Read(n,m,q);
    //vector <int> v1 = Brute(n,m,q);
    vector <int> v2 = Idk(n,m,q);
    //cout<<"Brute:\n";
    //for(auto it:v1)
    //    cout<<it<<" ";
    //cout<<'\n';
    //cout<<"Sqrt:\n";
    for(auto it:v2)
        cout<<it<<" ";

    cout<<'\n';
		/*
    int ok=1;
    for(int i=0; i<(int)v1.size(); i++)
        ok&=(v1[i]==v2[i]);
    assert(ok==1);
		*/
    return 0;
}