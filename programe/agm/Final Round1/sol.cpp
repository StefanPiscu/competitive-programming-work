#include <bits/stdc++.h>

using namespace std;

struct Cmp {
    bool operator()(pair<int, int> a, pair<int, int> b) {
        int la = a.second - a.first;
        int lb = b.second - b.first;
        if(la != lb) return la < lb;

        return a.first > b.first;
    }
};


int v[125];
int main() {
    int n, q; cin >> n >> q;
    v[0] = 1; v[n + 1] = 1;

    for(int qr = 0; qr < q; qr++) {
        int t, x; cin >> t >> x;
        if(t == 1) {
            v[x] ^= 1;
        }
        else {
            vector<pair<int, int>> pairs = {};
            pair<int, int> cnt = {-1, -1};
            for(int i = 0; i <= n + 1; i++) {
                if(v[i] == 0) {
                    if(cnt.first == -1) cnt.first = cnt.second = i;
                    else cnt.second = i;
                }
                else {
                    if(cnt.first != -1) pairs.push_back(cnt);
                    cnt.first = cnt.second = -1;
                }
            }

            priority_queue<pair<int, int>, vector<pair<int, int>>, Cmp> pq;
            for(auto e : pairs) pq.push(e);

            int last_taken = -1;
            while(x--) {
                if(pq.size() == 0) { last_taken = -1; break; }

                auto take_from = pq.top(); pq.pop();
                int taken = (take_from.first + take_from.second) / 2;
                if(taken != take_from.first) pq.push({take_from.first, taken - 1});
                if(taken != take_from.second) pq.push({taken + 1, take_from.second});

                last_taken = taken;
            }

            cout << last_taken << endl;
        }

    }
}