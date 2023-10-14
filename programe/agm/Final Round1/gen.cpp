// gen.cpp
#include <bits/stdc++.h>

using namespace std;


int main() {
    int _seed; cin >> _seed;
    srand(_seed);

		int n=12, q=10;
		cout<<n<<" "<<q<<endl;

    std::random_device rd;
    std::mt19937 gen(_seed);
    std::uniform_int_distribution<> distrib(1, n);

    for(int i = 0; i < q; i++) {
        int t = distrib(gen);
        t = (t > 0.15 * n ? 2 : 1);
        cout << t << " " << distrib(gen) << endl;
    }
}