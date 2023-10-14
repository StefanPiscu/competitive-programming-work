#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

#define int long long
int isqrt(int x) {
    int ans = 0;
    for(int step = (1 << 30); step > 0; step /= 2) {
        if((ans + step) * (ans + step) <= x)
            ans += step;
    }
    return ans;
}

int bulanmic = 1000;
int nrcand= 100;
int bulan = 5000000;

struct cand{
  int val;
  int a, b;
  bool operator<(const cand &ot) const{
    return val<ot.val;
  }
};
int a, b, r;

int bulanMicut(int norma, int normb){
  int maxim = (-1LL * 1e9) * 1e9;
  for(int vara = norma - bulanmic; vara <= norma + bulanmic; vara++) {
      if(vara * vara <= r * r) {
          int varb = isqrt(r * r - vara * vara);
          maxim = max(maxim, a * vara + b * varb);
      }
      else break;
  }

  for(int varb = normb - bulanmic; varb <= normb + bulanmic; varb++) {
      if(varb * varb <= r * r) {
          int vara = isqrt(r * r - varb * varb);
          maxim = max(maxim, a * vara + b * varb);
      }
      else break;
  }
  return maxim;
}

void solve() {
    cin >> a >> b >> r;

    a = max(a, -a); b = max(b, -b);
    if(a == 0 && b == 0) {
        cout << 0 << endl;
        return;
    }

    int norma = round((1.0 * a * r) / isqrt(a * a + b * b));
    int normb = round((1.0 * b * r) / isqrt(a * a + b * b));

    int maxim = (-1LL * 1e9) * 1e9;
    vector<cand> cs;

    for(int vara = norma - bulan; vara <= norma + bulan; vara+=bulanmic) {
        if(vara * vara <= r * r) {
            int varb = isqrt(r * r - vara * vara);
            cs.push_back({a * vara + b * varb, vara, varb});
        }
        else break;
    }

    for(int varb = normb - bulan; varb <= normb + bulan; varb+=bulanmic) {
        if(varb * varb <= r * r) {
            int vara = isqrt(r * r - varb * varb);
            cs.push_back({a * vara + b * varb, vara, varb});
        }
        else break;
    }

    sort(cs.begin(), cs.end());
    for(int i=0;i<=min((int) (cs.size()-1), nrcand);++i){
      maxim=max(maxim, bulanMicut(cs[i].a, cs[i].b));
    }
    cout<<maxim<<"\n";

    return;
}

int32_t main() {
    int t; cin >> t;
    bulan/=t;
    while(t--) solve();
}