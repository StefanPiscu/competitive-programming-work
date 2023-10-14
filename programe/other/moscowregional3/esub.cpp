#include <bits/stdc++.h>

using namespace std;

vector<int64_t> prec = {0,  1, 2, 3, 4, 5, 6, 7, 8, 9, -1, 11, 48, -1, -1, 5055, -1, -1, 288, -1, -1, 7077, 22, -1, 8088, -1, -1, 3699, -1, -1, -1, -1, -1, 33, -1, -1, 48888, -1, -1, -1, -1, -1, -1, -1, 44, 5055555555, -1, -1, -1, -1, -1, -1, -1, -1, 222888888, 55, -1, -1, -1, -1, -1, -1, -1, 111888, -1, -1, 66, -1, -1, -1, -1, -1, 8088888888, -1, -1, -1, -1, 77, -1, -1, -1, 9099999999, -1, -1, -1, -1, -1, -1, 88, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 99, -1, -1, -1, -1, -1, -1};

int64_t rep(int dig, int len) {
    int64_t ans = 0;
    while(len--) {
        ans = ans * 10 + dig;
    }
    return ans;
}

int64_t solve() {
    int64_t n; cin >> n;
    if(n < prec.size()) return prec[n];
    for(int len = 1; len <= 18; len++) {
        for(int dig = 1; dig <= 9; dig++) {
            if(rep(dig, len) % n == 0) {
                if(rep(dig, len) == n) return rep(dig, len);
                else                   return -1;
            }
        }
    }
    return -1;
}

int main()
{
    int t; cin >> t;
    while(t--) cout << solve() << '\n';
    return 0;
}
