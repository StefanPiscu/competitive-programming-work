#import<bits/stdc++.h>
using namespace std;
ofstream w("apm.out");
ifstream r("apm.in");
tuple<int,int,int>e[1<<20],d;
int t[1<<20],m,a,b,c,i,j,x,k;
int f(int x){return t[x]?t[x]=f(t[x]):x;}
main(){r>>m>>m;
while(r>>a>>b>>c)e[++i]={c,a,b};
sort(e,e+m);
auto&[l,p,q]=e[0];
for(;j<m;)tie(c,a,b)=d=e[++j],e[f(b)^(x=f(a))?t[x]=b,p+=c,++q:j]=d;
for(;k<q;)tie(c,a,b)=e[k++],w<<a<<" "<<b<<" ";
}