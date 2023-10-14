#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

ofstream out("correct.out");

bool check(int n, int start) {
    cerr << "Starting with: " << start << endl;
    vector<int> perm;
    for(int i = 1; i <= ((1 << n) << n); i++) {
        perm.push_back(i);
    }
    swap(perm[0], perm[start + 1]);
    sort(perm.begin() + 1, perm.end());

    int counter = 0;
    vector<vector<int>> mat((1 << n) + 1, vector<int>((1 << n) + 1));

    do {
        counter += 1;
        if(counter % (1 << 24) == 0) {
            cerr << "Reached: ";
            for(auto e : perm)
                cerr << e << " ";
            cerr << endl;
        }

        for(int i = 0; i < (1 << n); i++) {
            for(int j = 0; j < (1 << n); j++) {
                mat[i + 1][j + 1] = perm[(j << n) | i];
                mat[i + 1][j + 1] += mat[i + 1][j] + mat[i][j + 1] - mat[i][j];
            }
        }

        unordered_set<int64_t> s;
        for(int i = 0; i + (1 << (n - 1)) <= (1 << n) && s.size() <= 2; i++) {
            for(int j = 0; j + (1 << (n - 1)) <= (1 << n) && s.size() <= 2; j++) {
                int64_t sum = mat[i + (1 << (n - 1))][j + (1 << (n - 1))]
                                - mat[i][j + (1 << (n - 1))]
                                - mat[i + (1 << (n - 1))][j]
                                + mat[i][j];
                // cerr << i << " " << j << " " << sum << endl;

                s.insert(sum);
            }
        }

        if(s.size() == 1) {
            cerr << "Found for " << n << endl;
            for(int i = 0; i < (1 << n); i++) {
                for(int j = 0; j < (1 << n); j++) {
                    cerr << mat[i + 1][j + 1] << " ";
                }
                cerr << endl;
            }

            out << "Found for " << n << endl;
            for(int i = 0; i < (1 << n); i++) {
                for(int j = 0; j < (1 << n); j++) {
                    out << mat[i + 1][j + 1] << " ";
                }
                out << endl;
            }
            out << endl;
            return true;
        }
    } while(next_permutation(perm.begin(), perm.end()));

    cerr << "Not found for " << n << endl;
    return false;
}

int main()
{
    std::thread a01(check, 2,  1);
    std::thread a02(check, 2,  2);
    std::thread a03(check, 2,  3);
    std::thread a04(check, 2,  4);
    std::thread a05(check, 2,  5);
    std::thread a06(check, 2,  6);
    std::thread a07(check, 2,  7);
    std::thread a08(check, 2,  8);
    std::thread a09(check, 2,  9);
    std::thread a10(check, 2, 10);
    std::thread a11(check, 2, 11);
    std::thread a12(check, 2, 12);
    std::thread a13(check, 2, 13);
    std::thread a14(check, 2, 14);
    std::thread a15(check, 2, 15);
    std::thread a16(check, 2, 16);

    a01.join();
    a02.join();
    a03.join();
    a04.join();
    a05.join();
    a06.join();
    a07.join();
    a08.join();
    a09.join();
    a10.join();
    a11.join();
    a12.join();
    a13.join();
    a14.join();
    a15.join();
    a16.join();

    return 0;
}