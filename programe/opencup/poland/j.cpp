#include <bits/stdc++.h>
using namespace std;

int t;

int n, m;
char a[2002][2002];
bool locked[2002][2002];
int last[2002][2002];

void swapline(int x){
  for(int i=1;i<=m;++i){
    if(a[x][i]=='@') a[x][i]='O';
    else if(a[x][i]=='O') a[x][i]='@';
  }
}

void swapcol(int x){
  for(int i=1;i<=n;++i){
    if(a[i][x]=='@') a[i][x]='O';
    else if(a[i][x]=='O') a[i][x]='@';
  }
}
int main(){
  cin>>t;
  while(t--){
    cin>>n>>m;
    memset(locked, 0, sizeof(locked));
    memset(last, 0, sizeof(locked));
    for(int i=0;i<=n;++i) locked[i][0]=1;
    for(int i=0;i<=m;++i) locked[0][i]=1;
    for(int i=1;i<=n;++i){
      for(int j=1;j<=m;++j){
        cin>>a[i][j];
        if(a[i][j]!='#'){
          if(!locked[i-1][j]) last[i][j]=0;
          else if(!locked[i][j-1]) last[i][j]=1;
          else locked[i][j]=1;
        }
        else locked[i][j]=1;
        if(i==1&&j==1) locked[i][j]=0;
      }
    }
    if(locked[n][m]){
      cout<<"NIE\n";
    }
    else{
      cout<<"TAK\n";
      int crx=n, cry=m;
      vector<char> lines(n+1, 'N');
      vector<char> cols(m+1, 'N');
      vector<char> sol;
      vector<bool> visitedline(n+1, 0), visitedcol(m+1, 0);
      while(crx!=1||cry!=1){
        if(last[crx][cry]==0&&crx>1){
          if(a[crx][cry]=='@'){
            if(!visitedline[crx]) lines[crx]='T', swapline(crx);
            else if(!visitedcol[cry]) cols[cry]='T', swapcol(cry);
          }
          visitedline[crx]=1;
          visitedcol[cry]=1;
          crx--;  
          sol.push_back('D');
        }
        else{
          if(a[crx][cry]=='@'){
            if(!visitedline[crx]) lines[crx]='T', swapline(crx);
            else if(!visitedcol[cry]) cols[cry]='T', swapcol(cry);
          }
          visitedline[crx]=1;
          visitedcol[cry]=1;
          cry--;
          sol.push_back('P');
        }
      }
      /*
      for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
          cout<<a[i][j];
        }
        cout<<"\n";
      }
      */
      reverse(sol.begin(), sol.end());
      for(int i=1;i<=n;++i) cout<<lines[i];
      cout<<"\n";
      for(int j=1;j<=m;++j) cout<<cols[j];
      cout<<"\n";
      for(auto it:sol) cout<<it;
      cout<<"\n";
    }
  }
}