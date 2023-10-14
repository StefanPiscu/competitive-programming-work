//#define _GLIBCXX_DEBUG
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

#define int long long

ifstream in("input.txt");
ofstream out("out.txt");

struct level_struct {
    int l;
    vector<int> steps_used;
};

int dist(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int eval(vector<pair<int, int>> a) {
    int sum = 0;
    for(int i = 1; i < a.size(); i++) {
        sum += dist(a[i - 1], a[i]);
    }
    return sum;
}

void add_best(vector<pair<int, int>>& taken_monsters, vector<pair<int, int>>& monsters) {
    int best_diff = 1e9, best_i = -1;
    for(int i = 0; i < monsters.size(); i++) {
        int min_diff = 1e9;
        for(int j = 0; j + 1 < taken_monsters.size(); j++){
            int diff = dist(taken_monsters[j], monsters[i]) + dist(taken_monsters[j + 1], monsters[i]) - dist(taken_monsters[j], taken_monsters[j + 1]);
            min_diff = min(min_diff, diff);
        }
        if(min_diff < best_diff) {
            best_diff = min_diff;
            best_i = i;
        }
    }

    pair<int, int> chosen = monsters[best_i];
    vector<pair<int, int>> newmon;
    for(int i = 0; i < best_i; i++) {
        newmon.push_back(monsters[i]);
    }
    for(int i = best_i + 1; i < monsters.size(); i++) {
        newmon.push_back(monsters[i]);
    }
    monsters = newmon;

    best_diff = 1e9; int best_j = -1;
    for(int j = 0; j + 1 < taken_monsters.size(); j++) {
        int diff = dist(taken_monsters[j], chosen) + dist(taken_monsters[j + 1], chosen) - dist(taken_monsters[j], taken_monsters[j + 1]);
        if(diff < best_diff) {
            best_diff = diff;
            best_j = j;
        }
    }

    // taken_monsters.insert(taken_monsters.begin() + best_j + 1, chosen);

    vector<pair<int, int>> new_taken;
    for(int i = 0; i <= best_j; i++) {
        new_taken.push_back(taken_monsters[i]);
    }
    new_taken.push_back(chosen);
    for(int i = best_j + 1; i < taken_monsters.size(); i++) {
        new_taken.push_back(taken_monsters[i]);
    }
    taken_monsters = new_taken;
}

/*pair<int, int> cntpos;
bool cmp(pair<int, int> a, pair<int, int> b) {
    return dist(a, cntpos) > dist(b, cntpos);
}*/

bool bruv(char ch) {
    if(ch == 'I' || ch == 'O') return 1;
    return 0;
}

string steps(int s, pair<int, int> a, pair<int, int> b, vector<pair<int, int>> avoid) {
    vector<vector<int>>  mat(s, vector<int>(s, 1LL << 30));
    vector<vector<int>>  invdir(s, vector<int>(s, -1));
    vector<vector<char>> dirs(s, vector<char>(s, ' '));
    for(auto e : avoid) mat[e.first][e.second] = -1;
    mat[a.first][a.second] = 0;

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    char c[] = {'U', 'R', 'D', 'L'};

    queue<pair<int, int>> q;
    q.push(a);

    while(!q.empty()) {
        auto cnt = q.front(); q.pop();
        int x = cnt.first, y = cnt.second;
        // cerr << "EEE" << x << " " << y << endl;

        for(int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if(0 <= nx && nx < s && 0 <= ny && ny < s) {
                if(mat[nx][ny] == -1) continue;
                if(mat[nx][ny] > mat[x][y] + 1) {
                    mat[nx][ny] = mat[x][y] + 1;
                    dirs[nx][ny] = c[dir];
                    invdir[nx][ny] = (dir + 2) % 4;
                    q.push({nx, ny});
                }
            }
        }
    }

    int x = b.first;
    int y = b.second;

    string ret = "";
    while(x != a.first || y != a.second) {
        ret += dirs[x][y];
        int dir = invdir[x][y];
        x += dx[dir]; y += dy[dir];
    }

    reverse(ret.begin(), ret.end());
    return ret;
}

int minlee = 1e9;

void solve(int casenum) {
    out << "Case #" << casenum << ": ";

    int n, L, P; in >> n >> L >> P;
    P -= 1;

    vector<vector<vector<char>>> matbkp;

    vector<level_struct> levels;
    for(int lv = 0; lv < n; lv++) {
        in >> lv;
        int s, l; in >> s >> l;
        cerr << "Level " << lv << " has size " << s << endl;

        level_struct level;
        level.steps_used.resize(4 * (s + 2) * (s + 2), -(1LL << 30));
        level.l = l;

        vector<vector<char>> mat(s, vector<char>(s));
        for(auto &r : mat) for(auto &c : r) in >> c;

        if(mat[0][0] == 'M' && bruv(mat[0][1]) && bruv(mat[1][0])) mat[0][0] = '*';
        if(mat[0][s - 1] == 'M' && bruv(mat[0][s - 2]) && bruv(mat[1][s - 1])) mat[0][s - 1] = '*';
        if(mat[s - 1][0] == 'M' && bruv(mat[s - 2][0]) && bruv(mat[s - 1][1])) mat[s - 1][0] = '*';
        if(mat[s - 1][s - 1] == 'M' && bruv(mat[s - 2][s - 1]) && bruv(mat[s - 1][s - 2])) mat[s - 1][s - 1] = '*';

        matbkp.push_back(mat);

        /*for(int i = 0; i < s; i++) {
            for(int j = 0; j < s; j++) {
                cerr << mat[i][j] << " ";
            }
            cerr << endl;
        }
        cerr << endl;*/

        vector<pair<int, int>> monsters;

        int in_x, in_y;
        int out_x, out_y;

        for(int i = 0; i < s; i++) {
            for(int j = 0; j < s; j++) {
                if(mat[i][j] == 'I') in_x = i, in_y = j;
                if(mat[i][j] == 'O') out_x = i, out_y = j;
                if(mat[i][j] == 'M') monsters.push_back({i, j});
            }
        }

        int cnt_x = in_x, cnt_y = in_y;
        int cnt_steps = 0, taken = 0;

        level.steps_used[dist({in_x, in_y}, {out_x, out_y})] = 0;

        vector<pair<int, int>> taken_monsters;
        taken_monsters.push_back({in_x, in_y});
        taken_monsters.push_back({out_x, out_y});

        // levels.step_used[eval(taken_monsters)] = taken_monsters.size() - 2;

        while(monsters.size() > 0) {
            /*cntpos = {cnt_x, cnt_y};
            sort(monsters.begin(), monsters.end(), cmp);

            cnt_steps += dist(monsters[monsters.size() - 1], cntpos);
            taken += 1;

            // cerr << cnt_steps << " " << dist({out_x, out_y}, monsters[monsters.size() - 1]) << " " << taken << endl;

            level.steps_used[cnt_steps + dist({out_x, out_y}, monsters[monsters.size() - 1])] = taken;

            cnt_x = monsters[monsters.size() - 1].first;
            cnt_y = monsters[monsters.size() - 1].second;

            monsters.pop_back();*/

            level.steps_used[eval(taken_monsters)] = taken_monsters.size() - 2;
            add_best(taken_monsters, monsters);
            level.steps_used[eval(taken_monsters)] = taken_monsters.size() - 2;
        }

        for(int i = 1; i < level.steps_used.size(); i++) {
            level.steps_used[i] = std::max(level.steps_used[i], level.steps_used[i - 1]);
            // cerr << level.steps_used[i] << " ";
        } // cerr << endl;

        levels.push_back(level);

        cerr << "Built level " << lv << endl;
    }

    int cntl = 0;
    for(int i = 0; i < n; i++){
        cntl += levels[i].steps_used[0] * levels[i].l;
    }

    vector<int> idx(n, 0);

    while(cntl < L) {
        vector<pair<double, int>> g;
        for(int i = 0; i < n; i++) {
            int idy = idx[i];
            while(idy < levels[i].steps_used.size() && levels[i].steps_used[idy] == levels[i].steps_used[idx[i]]) idy++;

            if(idy < levels[i].steps_used.size())
                g.push_back({(1.* levels[i].l) / (idy - idx[i]), i});
        }

        sort(g.begin(), g.end());
        reverse(g.begin(), g.end());

        int i = g[0].second;
        int idy = idx[i];
        while(levels[i].steps_used[idy] == levels[i].steps_used[idx[i]]) idy++, P--;
        cntl -= levels[i].steps_used[idx[i]] * levels[i].l;
        cntl += levels[i].steps_used[idy] * levels[i].l
        idx[i] = idy;
    }

    string ret = "";
    for(int lv = 0; lv < n; lv++) {
        int taken = levels[lv].steps_used[idx[lv]];

        cerr << "Rebuilding level " << lv << endl;

        int s = matbkp[lv].size();
        vector<vector<char>> mat = matbkp[lv];
        // for(auto &r : mat) for(auto &c : r) in >> c;

        vector<pair<int, int>> monsters;

        int in_x, in_y;
        int out_x, out_y;

        for(int i = 0; i < s; i++) {
            for(int j = 0; j < s; j++) {
                if(mat[i][j] == 'I') in_x = i, in_y = j;
                if(mat[i][j] == 'O') out_x = i, out_y = j;
                if(mat[i][j] == 'M') monsters.push_back({i, j});
            }
        }

        cerr << "There are " << monsters.size() << " monsters, of which " << taken << " are taken " << endl;

        int cnt_x = in_x, cnt_y = in_y;
        int cnt_steps = 0;

        vector<pair<int, int>> taken_monsters;
        taken_monsters.push_back({in_x, in_y});
        taken_monsters.push_back({out_x, out_y});

        while(taken) {
            // cerr << "T:" << taken << endl;

            /* cntpos = {cnt_x, cnt_y};
            sort(monsters.begin(), monsters.end(), cmp);

            // cerr << "M:" << monsters.size() << endl;

            ret += steps(s, cntpos, monsters[monsters.size() - 1], {{in_x, in_y}, {out_x, out_y}});

            cnt_x = monsters[monsters.size() - 1].first;
            cnt_y = monsters[monsters.size() - 1].second;

            monsters.pop_back();
            taken -= 1; */

            // cerr << "T:" << taken << endl;
            // cerr << "M:" << monsters.size() << endl;

            add_best(taken_monsters, monsters);
            taken -= 1;
        }

        // for(auto e : taken_monsters)
        //     cerr << e.first << " " << e.second << endl;

        // cerr << taken_monsters.size() << endl;
        for(int i = 1; i < taken_monsters.size(); i++) {
            // cerr << i << endl;
            if(i != taken_monsters.size() - 1) {
                ret += steps(s, taken_monsters[i - 1], taken_monsters[i], {{in_x, in_y}, {out_x, out_y}});
            }
            else {
                ret += steps(s, taken_monsters[i - 1], taken_monsters[i], {{in_x, in_y}});
            }
        }
    }

    cerr << "Have a lee-way of " << P << " steps!" << endl;
    cerr << "Finished with power" << cntl << endl;

    minlee = min(minlee, P);

    out << ret << endl;
}

int32_t main() {
    int t; in >> t;
    for(int i = 1; i <= t; i++)
        solve(i);

    cerr << "Minlee" << minlee << endl;
}
