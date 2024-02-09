#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;
const int mod = 1e9 + 7;

ll modmul(ll a, ll b) {
    return ((a % mod) * (b % mod)) % mod;
}

ll modpow(ll a, ll x) {
    ll res = 1;
    a = a % mod;
    while (x > 1) {
        if (x & 1) res = modmul(res, a);
        x >>= 1;
        a = modmul(a, a);
    }

    return res % mod;
}