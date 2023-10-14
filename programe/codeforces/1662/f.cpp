#include <bits/stdc++.h>
 
using namespace std;
 
const int BULAN = 20;
 
struct AintGraph {
    int offset;
    vector<vector<int>> gzero, gone;
    vector<int> st, st2, actual, dist;
 
    int alocat = 1;
    int nxt() {
        gzero.push_back({});
        gone.push_back({});
 
        int ans = alocat;
        alocat++;
 
        return ans;
    }
 
    void add_edge(int x, int y, int c) {
        // cerr << "edge: " << x << " " << y << " " << c << endl;
 
        if(c == 0) gzero[x].push_back(y);
        if(c == 1) gone[x].push_back(y);
    }
 
    AintGraph(int _n) {
        _n += 7;
        offset = 1;
        while(offset < _n) offset *= 2;
        gzero.resize(offset);
        gone.resize(offset);
 
        st.resize(2 * offset);
        for(auto &e : st) {
            e = nxt();
        }
 
        st2.resize(2 * offset);
        for(auto &e : st2) {
            e = nxt();
        }
 
        actual.resize(2 * offset);
        for(auto &e : actual) {
            e = nxt();
        }
 
        for(int i = 1; i < offset; i++) {
            add_edge(st[i], st[2 * i], 0);
            add_edge(st[i], st[2 * i + 1], 0);
        }
    }
 
    void activate(int node) {
        // cerr << "Activating " << node << endl;
        int pos = offset + node;
 
        while(pos >= 1) {
            int prev = st[pos];
            int cnt = nxt();
 
            add_edge(cnt, prev, 0);
            add_edge(cnt, actual[node], 1);
 
            st[pos] = cnt;
 
            pos /= 2;
        }
 
        pos = offset + node;
        while(pos >= 1) {
            int prev = st2[pos];
            int cnt = nxt();
 
            add_edge(prev, cnt, 0);
            add_edge(actual[node], cnt, 1);
 
            st2[pos] = cnt;
 
            pos /= 2;
        }
    }
 
    void _connect(int node, int l, int r, int gl, int gr, int source) {
        if(gr < l || r < gl) return;
 
        if(gl <= l && r <= gr) {
            add_edge(source, st[node], 0);
            add_edge(st2[node], source, 0);
            return;
        }
 
        int mid = (l + r) / 2;
        _connect(2 * node, l, mid, gl, gr, source);
        _connect(2 * node + 1, mid + 1, r, gl, gr, source);
        return;
    }
 
    void connect(int l, int r, int node) {
        // cerr << "Connecting " << node << " to " << l << " " << r << endl;
        _connect(1, 0, offset - 1, l, r, actual[node]);
    }
 
 
 
    void init(vector<int> p) {
        vector<pair<int, int>> pows;
        for(int i = 0; i < p.size(); i++) {
            pows.push_back({p[i], i});
        }
        sort(pows.begin(), pows.end());
        reverse(pows.begin(), pows.end());
 
        for(int i = 0; i < pows.size(); i++) {
            for(int j = i; j < pows.size() && pows[j].first == pows[i].first; j++) {
                activate(pows[j].second);
            }
            for(int j = i; j < pows.size() && pows[j].first == pows[i].first; j++) {
                int l = max(0, pows[j].second - pows[j].first);
                int r = min(offset - 1, pows[j].second + pows[j].first);
 
                connect(l, r, pows[j].second);
                i = j;
            }
        }
    }
 
    int calcdist(int a, int b) {
        a = actual[a]; b = actual[b];
 
        dist = vector<int>(gone.size(), 1e9);
        dist[a] = 0;
 
        deque<int> q; q.push_back(a);
        while(q.size()) {
            auto cnt = q.front(); q.pop_front();
 
            for(auto vec : gzero[cnt]) {
                if(dist[vec] > dist[cnt]) {
                    dist[vec] = dist[cnt];
                    q.push_front(vec);
                }
            }
 
            for(auto vec : gone[cnt]) {
                if(dist[vec] > dist[cnt] + 1) {
                    dist[vec] = dist[cnt] + 1;
                    q.push_back(vec);
                }
            }
        }
 
        return dist[b];
    }
};
 
void solve() {
    int n, a, b; cin >> n >> a >> b;
    AintGraph ag(n + 7);
 
    vector<int> ps(n);
    for(auto &e : ps) cin >> e;
 
    ag.init(ps);
 
    #ifdef LOCAL
        cerr << "\t\t\t";
    #endif // LOCAL
    cout << ag.calcdist(a - 1, b - 1) << endl;
}
 
int main() {
    int t; cin >> t;
    while(t--) solve();
}