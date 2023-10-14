#include <bits/stdc++.h>

using namespace std;

#define int long long

int n;


unordered_map<int, vector<pair<int, int>>> hm;

void add(int x, int y, int r) {
    int min_x = max(0LL, x - (int)floor(cbrt(r))), max_x = min(n, x + (int)floor(cbrt(r)));
    for(int cnt_x = min_x; cnt_x <= max_x; cnt_x++) {
        int dx = max(cnt_x - x, x - cnt_x);
        int dy = floor(cbrt(r - dx * dx * dx));

        int min_y = max(0LL, y - dy), max_y = min(n, y + dy);
        
#ifdef LOCAL
        cerr << cnt_x << " " << min_y << " " << max_y << endl;
#endif //LOCAL

        hm[cnt_x].push_back({min_y, max_y});
    }
}

int32_t main() {
    int m;
    cin >> n >> m;

    for(int i = 1; i <= m; i++) {
        int x, y, r; cin >> x >> y >> r;
        add(x, y, r);
    }

    int ans = 0;
    for(auto column : hm) {
        sort(column.second.begin(), column.second.end());

        int last = -100;
        for(auto intervals : column.second) {
            if(intervals.first <= last) intervals.first = last + 1;
            ans += max(0LL, intervals.second - intervals.first + 1);
            last = max(last, intervals.second);
        }
    }

    cout << 1LL * (n + 1) * (n + 1) - ans << endl;
}
