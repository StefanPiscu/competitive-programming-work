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

int bulan = 300000000;

void solve() {
    int a, b, r;
    cin >> a >> b >> r;

    a = max(a, -a); b = max(b, -b);
    if(a == 0 && b == 0) {
        cout << 0 << endl;
        return;
    }

    int norma = round((1.0 * a * r) / isqrt(a * a + b * b));
    int normb = round((1.0 * b * r) / isqrt(a * a + b * b));

    int maxim = (-1LL * 1e9) * 1e9;

    for(int vara = norma - bulan; vara <= norma + bulan; vara++) {
        if(vara * vara <= r * r) {
            int varb = isqrt(r * r - vara * vara);
            maxim = max(maxim, a * vara + b * varb);
        }
    }

    for(int varb = normb - bulan; varb <= normb + bulan; varb++) {
        if(varb * varb <= r * r) {
            int vara = isqrt(r * r - varb * varb);
            maxim = max(maxim, a * vara + b * varb);
        }
    }

    cout << maxim << endl;
    return;
}

int32_t main() {
    int t; cin >> t;
    bulan/=t;
    while(t--) solve();
}