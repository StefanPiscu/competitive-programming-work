#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
		cin.tie(0);
    int t,n,i,j,cntp=0,cnt1=0,cntm=0,cnt0=0,a;
    long long s;
    cin>>t;
    while(t--)
    {
        cin>>n;
        cntp=0,cnt1=0,cntm=0,cnt0=0;
        for(i=1;i<=n;++i)
        {
            cin>>a;
            if(a==0)
                ++cnt0;
            else if(a==1)
                ++cnt1;
            else if(a<0)
                ++cntm;
            else
                ++cntp;
        }
        s=0;
        s+=cnt0*1LL*(cnt1+cntp);
        s+=cnt1*1LL*(cntp);
        s+=cnt1*1LL*(cnt1-1)/2LL;
        s+=cntm*1LL*(cntp+cnt1);
        cout<<s<<'\n';
    }
}
