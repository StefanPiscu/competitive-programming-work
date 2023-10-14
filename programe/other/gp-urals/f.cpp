#include <bits/stdc++.h>
using namespace std;

int n, m;

vector<vector<pair<int, int>>> costs;
int dp[1502][1502][3];
pair<pair<int, int>, int> from[1502][1502][3];
int used[1502][1502][3];

void recprint(int n, int k, int j) {
    // cerr << "PRT" << n << " " << k << " " << j << " " << used[n][k][j] << endl;
    if(n == 1) {
        cout << costs[1][j].second << " ";
        return;
    }
    recprint(from[n][k][j].first.first, from[n][k][j].first.second, from[n][k][j].second);
    cout << used[n][k][j] << " ";
}

int32_t main(){
    cin>>n>>m;
    for(int i = 0; i < 1502; i++) for(int j = 0; j < 1502; j++) for(int k = 0; k < 3; k++) dp[i][j][k] = 2e9;
    vector<int> a(m+1);
    costs.resize(n+1);
    for(int i=1;i<=m;++i) cin>>a[i];
    for(int i=1;i<=m;++i){
        for(int j=1;j<=n;++j){
            int x;
            cin>>x;
            costs[j].push_back({x, i});
        }
    }
    for(int j=1;j<=n;++j) sort(costs[j].begin(), costs[j].end());
    int BND=min(3, m);
    for(int k=0;k<BND;++k) dp[1][1][k]=costs[1][k].first;
    for(int i=1;i<n;++i){
        for(int j=0;j<BND;++j){
            int crStudent=costs[i][j].second;
            int bnd=min(i, a[crStudent]);
            /*
            for(int k=1;k<=bnd;++k){
                cout<<i<<" "<<costs[i][j].second<<" "<<k<<" "<<dp[i][k][j]<<"\n";
            }
            */
            for(int j2=0;j2<BND;++j2){
                int nxStudent=costs[i+1][j2].second;
                for(int k=1;k<=bnd;++k){
                    if(nxStudent==crStudent){
                        if(k<a[crStudent]) {
                            dp[i+1][k+1][j2]=min(dp[i+1][k+1][j2], dp[i][k][j]+costs[i+1][j2].first);
                            if(dp[i + 1][k + 1][j2] == dp[i][k][j] + costs[i + 1][j2].first) {
                                from[i + 1][k + 1][j2] = {{i, k}, j};
                                used[i + 1][k + 1][j2] = costs[i + 1][j2].second;
                            }
                        }
                    }
                    else {
                        dp[i+1][1][j2]=min(dp[i+1][1][j2], dp[i][k][j]+costs[i+1][j2].first);
                        if(dp[i + 1][1][j2] == dp[i][k][j] + costs[i + 1][j2].first) {
                            from[i + 1][1][j2] = {{i, k}, j};
                            used[i + 1][1][j2] = costs[i + 1][j2].second;
                        }
                    }
                }
            }
        }
    }
    int sol=2e9;
    tuple<int, int, int> bestBoi;
    for(int j=0;j<BND;++j){
        int crStudent=costs[n][j].second;
        int bnd=min(n, a[crStudent]);
        for(int k=1;k<=bnd;++k){
            //cout<<n<<" "<<costs[n][j].second<<" "<<k<<" "<<dp[n][k][j]<<"\n";
            sol=min(sol, dp[n][k][j]);
            if(sol==dp[n][k][j]){
                bestBoi={n, k, j};
            }
        }
    }
    cout<<sol<<"\n";
    recprint(get<0>(bestBoi), get<1>(bestBoi), get<2>(bestBoi));
    return 0;
}