#import<bits/stdc++.h>
std::ifstream r("apm.in");std::ofstream w("apm.out");
int m,k=-1,i,j,z,t[1<<20],x;
struct s{int x,y,z;}d,e[1<<20];
int f(int x){return t[x]?t[x]=f(t[x]):x;}
main(){r>>m>>m;
for(;r>>e[i].x>>e[i].y>>e[i].z;i++);
std::sort(e,e+m,[](s a,s b){return a.z<b.z;});
for(;j<m;)d=e[j],e[f(d.y)^(x=f(d.x))?t[x]=d.y,e[-1].x+=d.z,e[-1].y++:j++]=d;
for(;k<m;k++)w<<e[k].x<<" "<<e[k].y<<" ";
}