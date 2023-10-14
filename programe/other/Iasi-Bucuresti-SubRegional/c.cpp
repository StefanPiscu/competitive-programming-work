#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e4 + 7;
int n;

struct pers {
    vector<int> love;
    vector<int> hate;

    int sat = 0, sum = 0;
} people[NMAX];

struct condmap {
    map<string, int> mapper;
    int get(string s) {
        if(mapper.find(s) == mapper.end()) {
            int x = mapper.size() + 1;
            mapper[s] = x;
        }

        return mapper[s];
    }
} cm;

struct nesat {
    bitset<NMAX> notsat;
    int sz = 0;

    void add(int x) { sz += (notsat[x] == false); notsat[x] = true; }
    void rem(int x) { sz -= (notsat[x] == true); notsat[x] = false; }
    bool is(int x) { return notsat[x]; }

    int size() { return sz; }

    int getrand() {
        int ind = notsat._Find_next(rand() % n);
        if(ind == notsat.size()) ind = notsat._Find_next(0);

        return ind;
    }

    int reconsider(int x) {
        if(people[x].sat * 3 <= people[x].sum) add(x);
        else rem(x);
    }
} ns;

vector<int> inf_hates[NMAX];
vector<int> inf_loves[NMAX];
int chosen[255];

int main() {
    srand(388535);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        int k; cin >> k;
        for(int j = 0; j < k; j++) {
            string rd; cin >> rd;

            if(rd[0] == '+') people[i].love.push_back(cm.get(rd.substr(1, rd.size() - 1)));
            if(rd[0] == '-') people[i].hate.push_back(cm.get(rd.substr(1, rd.size() - 1)));

            if(rd[0] == '+') inf_loves[cm.get(rd.substr(1, rd.size() - 1))].push_back(i);
            if(rd[0] == '-') inf_hates[cm.get(rd.substr(1, rd.size() - 1))].push_back(i);
        }

        people[i].sat = people[i].hate.size();
        people[i].sum = k;

        ns.reconsider(i);
    }

    // cerr << "Mapped: " << endl;
    // for(auto pr : cm.mapper) cerr << pr.first << " " << pr.second << endl;

    while(ns.size() > 0) {
        int ind = ns.getrand();

        // cerr << "Fixing " << ind << endl;

        vector<int> perm(people[ind].sum);
        iota(perm.begin(), perm.end(), 0);
        random_shuffle(perm.begin(), perm.end());

        for(int id = 0; id < perm.size(); id++) {
            int i = perm[id];

            bool loves = (i < people[ind].love.size());
            int ingredient = (loves ? people[ind].love[i] : people[ind].hate[i - people[ind].love.size()]);

            if(loves == chosen[ingredient]) continue;

            // cerr << loves << " " << ingredient << endl;

            if(loves) { // Adaug ingredient
                chosen[ingredient] = 1;
                for(auto e : inf_loves[ingredient]) {
                    people[e].sat += 1;
                    ns.reconsider(e);
                }
                for(auto e : inf_hates[ingredient]) {
                    people[e].sat -= 1;
                    ns.reconsider(e);
                }
            }
            else { // Scot ingredient
                chosen[ingredient] = 0;
                for(auto e : inf_hates[ingredient]) {
                    people[e].sat += 1;
                    ns.reconsider(e);
                }
                for(auto e : inf_loves[ingredient]) {
                    people[e].sat -= 1;
                    ns.reconsider(e);
                }
            }

            break;
        }
    }

    // assert(ns.size() == 0);
    for(auto &pr : cm.mapper) {
        if(chosen[pr.second]) cout << pr.first << "\n";
    }
}