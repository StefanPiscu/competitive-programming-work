#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

const int offset = (1 << 22);
const int64_t INF = (1LL << 61) + 7;

struct node {
    int64_t death_range = 0; /// [1 ... death_range]

    int64_t deterministic_range = 0; /// [death_range + 1 ... deterministic_range]
    int64_t deterministic_value = 0;

    int64_t damage = 0; /// [deterministic_range + 1 ... INF]

#ifdef LOCAL
    void print() {
        cerr << "Node has values: " << endl;
        cerr << "\t" << "Death range: " << death_range << endl;
        cerr << "\t" << "Deterministic range: " << deterministic_range << endl;
        cerr << "\t" << "Deterministic value: " << deterministic_value << endl;
        cerr << "\t" << "Damage: " << damage << endl;
        cerr << endl;
        return;
    }
#endif // LOCAL
};

node aint[2 * offset];

node normalize(node ret) {
    if(ret.death_range > INF) ret.death_range = INF;
    if(ret.deterministic_range > INF) ret.deterministic_range = INF;
    if(ret.deterministic_value > INF) ret.deterministic_value = INF;
    if(ret.damage > INF) ret.damage = INF;

    return ret;
}

node combine(node left, node right) {
    node ret;

    /// Death Range:
    ret.death_range = left.death_range;
    if(left.deterministic_value <= right.death_range) {
        ret.death_range = max(ret.death_range, left.deterministic_range);
        ret.death_range = max(ret.death_range, right.death_range + left.damage);
    }

    /// Deterministic stuff:
    if(ret.death_range > left.deterministic_range) {
        ret.deterministic_range = ret.death_range;
        ret.deterministic_value = 0;
    }
    else {
        ret.deterministic_range = left.deterministic_range;

        if(left.deterministic_value > right.deterministic_range)
            ret.deterministic_value = left.deterministic_value - right.damage;
        else
            ret.deterministic_value = right.deterministic_value;
    }

    if(left.damage + right.deterministic_range >= ret.deterministic_range) {
        ret.deterministic_range = right.deterministic_range + left.damage;
        ret.deterministic_value = right.deterministic_value;
    }


    /// Damage:
    ret.damage = left.damage + right.damage;

    return normalize(ret);
}

void set_node(int pos, char ch, int64_t num) {
    pos += offset;

    if(ch == 'B') { /// Beast
        node tmp;

        tmp.death_range = num;
        tmp.deterministic_range = num;
        tmp.deterministic_value = 0;
        tmp.damage = num;

        aint[pos] = tmp;
    }
    if(ch == 'K') { /// Tavern
        node tmp;

        tmp.death_range = num - 1;
        tmp.deterministic_range = INF;
        tmp.deterministic_value = num;
        tmp.damage = 0;

        aint[pos] = tmp;
    }
    if(ch == 'C') { /// Healing witch
        node tmp;

        tmp.death_range = 0;
        tmp.deterministic_range = num;
        tmp.deterministic_value = num;
        tmp.damage = 0;

        aint[pos] = tmp;
    }

    pos /= 2;

    while(pos >= 1) {
        aint[pos] = combine(aint[2 * pos], aint[2 * pos + 1]);

        pos /= 2;
    }
}

#ifdef LOCAL
node query_rec(int pos, int l, int r, int gl, int gr) {
    if(r < gl || gr < l) return node();
    if(gl <= l && r <= gr) return aint[pos];

    int mid = (l + r) / 2;

    return combine(
                   query_rec(2 * pos, l, mid, gl, gr),
                   query_rec(2 * pos + 1, mid + 1, r, gl, gr)
                   );
}
#endif // LOCAL

void solve() {
    int n, q;
    int64_t h;
    cin >> n >> q >> h;

    for(int i = 1; i <= n; i++) {
        char ch; int64_t num;
        cin >> ch >> num;

        set_node(i, ch, num);
    }
    set_node(n + 1, 'B', INF);

    for(int i = 1; i <= q; i++) {
        char tip; cin >> tip;
        if(tip == 'D') { /// Query
            int index; cin >> index;

            int next_node = index + offset;
            node calculated = node();
			node aux= node();
			while((aux=combine(calculated, aint[next_node])).death_range>=h){
				if(next_node&1){
					calculated=aux;
					next_node+=1;
				}
				else next_node>>=1;
			}
			while(combine(calculated, aint[next_node]).death_range<h){
				if(next_node>=offset) break;
				if((aux=combine(calculated, aint[next_node*2])).death_range>=h){
					calculated=aux;
					next_node=next_node*2+1;
				}
				else{
					next_node=next_node*2;
				}
			}
            if(index > next_node - offset - 1)
                cout << -1 << endl;
            else
                cout << next_node - offset - 1 << endl;

            /*
            while(true) {
                // cerr << current_node << endl;
                if(combine(road, aint[current_node]).death_range < h) {
                    while(current_node % 2 == 0 && combine(road, aint[current_node / 2]).death_range < h) {
                        current_node /= 2;
                    }
                    road = combine(road, aint[current_node]);
                    while(current_node < offset) {
                        current_node *= 2;
                        current_node += 1;
                    }
                    current_node += 1;
                }
                else {
                    break;
                }
            }
			

            // cerr << current_node - offset - 1 << endl;
            // road.print(); cerr << endl;

            if(index > current_node - offset - 1)
                cout << -1 << endl;
            else
                cout << current_node - offset - 1 << endl;
            */
        }
        if(tip == 'Z') { /// Change
            int index; char ch; int64_t num;
            cin >> index >> ch >> num;
            set_node(index, ch, num);
        }
    }
}

int main() {
#ifndef LOCAL
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif // LOCAL

    int t; cin >> t;
    while(t--) solve();
}
