#include <bits/stdc++.h>
using namespace std;
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
int main()
{
    #ifdef HOME
        freopen("test.out","w",stdout);
    #endif // HOME
    int n,m,q;
    Read(n,m,q);
    vector <int> v = Brute(n,m,q);

    for(auto it:v)
        cout<<it<<" ";
    cout<<'\n';
    return 0;
}