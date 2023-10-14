#import<fstream>
std::ifstream f("scmax.in");
std::ofstream g("scmax.out");
int v['썐'],p['썐'],q['썐'],i,j,n,Q,x;
int a(int I,int Z){while(p[Z]!=I)Z--;if(I>1)a(I-1,Z-1);g<<v[Z]<<" ";}
int main(){
f>>n;
for(i=1;i<=n;i++){
f>>v[i];x=v[i];
j=1;
while(x>q[j]&&j<=Q)j++;
q[j]=x;
p[i]=j;
Q=Q>j?Q:j;
}
g<<Q<<"\n";a(Q,n);
}