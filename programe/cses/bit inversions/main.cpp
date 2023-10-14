#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <fstream>
#include <cstring>
using namespace std;
 
 
#define cin fin
#define cout fout
 
ifstream fin("note2.in");
ofstream fout("note2.out");
 
int w, h, mod;
 
int tran[128][128];
int sol[128][128];
int rev[128];
 
int getTransition(int mask1, int mask2){
  int mask3=mask1&mask2;
  for(int rounds=0;rounds<=(w+1);++rounds){
    for(int i=0;i<w;++i){
      if(!(mask2&(1<<i))) continue;
      if((i>0 && (mask3&(1<<(i-1)))) || (mask3&(1<<(i+1)))) mask3|=1<<i;
    }
  }
  return mask3;
}
 
void mul2(int a[128][128], int b[128][128], int sol[128][128]){
  int sz=(1<<w);
  long long c[128][128];
  bool used[128][128];
  memset(used, 0, sizeof(used));
  memset(c, 0, sizeof(c));
  int bt[128][128];
  for(int i=0;i<sz;++i){
    for(int j=0;j<sz;++j){
      bt[i][j]=b[j][i];
    }
  }
  for(int i=0;i<sz;++i){
    for(int j=0;j<sz;++j){
      if(used[i][j]) continue;
      __builtin_prefetch(a[i]);
      __builtin_prefetch(bt[j]);
      for(int k=0;k<sz;++k){
        c[i][j]+=(1LL*a[i][k]*bt[j][k]);
      }
      c[i][j]%=mod;
      c[rev[i]][rev[j]]=c[i][j];
        used[i][j]=1;
        used[rev[i]][rev[j]]=1;
    }
  }
  for(int i=0;i<sz;++i){
    for(int j=0;j<sz;++j){
      sol[i][j]=c[i][j];
    }
  }
}
 
void mul(int a[128][128], int b[128][128], int sol[128][128]){
  int sz=(1<<w);
  int c[128][128];
  memset(c, 0, sizeof(c));
  int bt[128][128];
  for(int i=0;i<sz;++i){
    for(int j=0;j<sz;++j){
      bt[i][j]=b[j][i];
    }
  }
  for(int i=0;i<sz;++i){
    for(int j=0;j<sz;++j){
      __builtin_prefetch(a[i]);
      __builtin_prefetch(bt[j]);
      for(int k=0;k<sz;++k){
        c[i][j]+=(1LL*a[i][k]*bt[j][k]%mod);
        c[i][j]-=mod*(c[i][j]>=mod);
      }
    }
  }
  for(int i=0;i<sz;++i){
    for(int j=0;j<sz;++j){
      sol[i][j]=c[i][j];
    }
  }
}
 
void binpow(int mat[128][128], int e, int ans[128][128]){
  e--;
  int sol[128][128];
  int sz=1<<w;
  for(int i=0;i<sz;++i){
    for(int j=0;j<sz;++j) sol[i][j]=mat[i][j];
  }
  while(e){
    if(e&1) mul2(mat, sol, sol);
    mul2(mat, mat, mat);
    e>>=1;
  }
  for(int i=0;i<sz;++i){
    for(int j=0;j<sz;++j){
      ans[i][j]=sol[i][j];
    }
  }
}
 
int main(){
  cin>>w>>h>>mod;
  int sz=1<<w;
  for(int mask1=0;mask1<sz;++mask1){
    for(int mask2=0;mask2<sz;++mask2){
      int mask3=getTransition(mask1, mask2);
      tran[mask3][mask1]++;
    }
  }
  for(int mask1=0;mask1<sz;++mask1){
    for(int i=0;i<w;++i){
      if(mask1&(1<<i)) rev[mask1]|=(1<<(w-i-1));
    }
  }
  for(int i=0;i<w;++i){
    if(i+1==w) sol[(1<<w)-1][0]=1;
    else sol[(1<<(i+1))-1][0]=(1<<(w-i-2));
  }
  if(h>1){
    binpow(tran, h-1, tran);
    mul(tran, sol, sol);
  }
  int ans=0;
  for(int i=1;i<sz;++i) ans+=sol[i][0], ans%=mod;
  cout<<ans<<"\n";
  return 0;
}