#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

int64_t gcd_group(string s, int64_t ez_break) {
    int64_t gcd = stoll(s);
    do {
        gcd = __gcd(gcd, (int64_t)stoll(s));
        if(ez_break > gcd) return gcd;
    }while(next_permutation(s.begin(), s.end()));
    return gcd;
}

int64_t rets[200];
int64_t solve(int dig1, int len1) {
    /* for(int64_t i = 1; i <= 1e8; i++) {
        string smul = to_string(i * n);
        sort(smul.begin(), smul.end());
        if(gcd_group(smul, n) == n)
            return i * n;
    } */

    // for(int dig1 = 0; dig1 <= 9; dig1++)        { for(int len1 = 0; len1 <= 20; len1++) {
        // cerr << "Currently at " << dig1 << " and " << len1 << endl;
    for(int dig2 = dig1 + 1; dig2 <= 9; dig2++) { for(int len2 = 0; len2 <= 20; len2++) {
    for(int dig3 = dig2 + 1; dig3 <= 9; dig3++) { for(int len3 = 0; len3 <= 20; len3++) {
    for(int dig4 = dig3 + 1; dig4 <= 9; dig4++) { for(int len4 = 0; len4 <= 20; len4++) {
        if(len1 + len2 + len3 + len4 == 0 || len1 + len2 + len3 + len4 >= 14) continue;

        string smul = "";
        for(int l = 0; l < len1; l++) smul += (char)(dig1 + '0');
        for(int l = 0; l < len2; l++) smul += (char)(dig2 + '0');
        for(int l = 0; l < len3; l++) smul += (char)(dig3 + '0');
        for(int l = 0; l < len4; l++) smul += (char)(dig4 + '0');

        int64_t gc = gcd_group(smul, 0);

        for(int i = 0; i < smul.size(); i++) {
            if(smul[i] != '0') { swap(smul[i], smul[0]); break; }
        }

        if(gc <= 105 && (rets[gc] == -1 || rets[gc] > stoll(smul))) {
            rets[gc] = stoll(smul);
        }
    }}
    }}
    }}
    // }}
    cerr << "Finished a future" << endl;
    return 0;
}

int main() {
    /*int counter = 0;
    for(int i = 10; i <= 1e3; i++) {
        cout << i << ": " << solve2(i) << endl;
    }*/

    for(int i = 0; i <= 105; i++)
        rets[i] = -1;

    vector<future<int64_t>> futures;
    for(int dig1 = 0; dig1 <= 9; dig1++) {
        for(int len1 = 0; len1 <= 20; len1++) {
            futures.push_back(move(async(std::launch::async, solve, dig1, len1)));
            cerr << "Created future " << dig1 << " and " << len1 << endl;
    }    
    }

    for(auto &f : futures) f.get();

    ofstream out("prec.out");
    out << "vector<int> prec = {";
    for(int i = 0; i <= 105; i++) {
        cerr << i << endl;
        out << rets[i] << ", ";
    }
    out << "};" << endl;

    // cout << "Solved " << counter << endl;
}