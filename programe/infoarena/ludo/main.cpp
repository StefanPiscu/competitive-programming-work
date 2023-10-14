#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;
int v[30005],f[1000005],n,q,x,s,d,cnt,sol[200005];
struct query
{
    int st, dr, ind;
};
query qu[200005];
bool cmp(query a, query b)
{
    if(a.st/x!=b.st/x)
        return a.st<b.st;
    return a.dr<b.dr;
}
int main()
{
    cin>>n;
    x=(int)sqrt(n);
    for(int i=0;i<n;i++)
        cin>>v[i];
    cin>>q;
    for(int i=0;i<q;i++)
    {
        cin>>qu[i].st>>qu[i].dr;
        qu[i].ind=i;
        qu[i].st--;
        qu[i].dr--;
    }
    sort(qu,qu+q,cmp);
    s=qu[0].st;
    d=qu[0].st;
    f[v[s]]++;
    cnt++;
    for(int i=0;i<q;i++)
    {
        if(s<qu[i].st)
        {
            for(int j=s;j<qu[i].st;j++)
            {
                f[v[j]]--;
                if(f[v[j]]==0)
                    cnt--;
            }
        }
        if(s>qu[i].st)
        {
            for(int j=s-1;j>=qu[i].st;j--)
            {
                if(f[v[j]]==0)
                    cnt++;
                f[v[j]]++;
            }
        }
        if(d>qu[i].dr)
        {
            for(int j=d;j>qu[i].dr;j--)
            {
                f[v[j]]--;
                if(f[v[j]]==0)
                    cnt--;
            }
        }
        if(d<qu[i].dr)
        {
            for(int j=d+1;j<=qu[i].dr;j++)
            {
                f[v[j]]++;
                if(f[v[j]]==1)
                    cnt++;
            }
        }
        s=qu[i].st;
        d=qu[i].dr;
        sol[qu[i].ind]=cnt;
    }
    for(int i=0;i<q;i++)
        cout<<sol[i]<<'\n';
    return 0;
}
