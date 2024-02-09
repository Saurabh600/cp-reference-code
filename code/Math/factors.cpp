#include <bits/stdc++.h>
using namespace std;

vector<int> factors(int n) {
    if (n < 1) return {};

    vector<int> res;
    for (int f = 1; f * f <= n; f++) {
        if (n % f == 0) {
            if (f * f == n) {
                res.push_back(f);
            } else {
                res.push_back(f);
                res.push_back(n / f);
            }
        }
    }

    return res;
}

int countNumberOfDivisors(int n) {
    map<int, int> mp;
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            n /= i;
            mp[i]++;
        }
    }

    if (n != 1) mp[n]++;
    int res = 1;
    for (auto it : mp) {
        res *= (it.second + 1);
    }

    return res;
}
