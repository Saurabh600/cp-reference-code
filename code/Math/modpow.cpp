#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;
const int mod = 1e9 + 7;

ll modmul(ll a, ll b) {
    return ((a % mod) * (b % mod)) % mod;
}

ll modpow(ll a, ll x, ll mod) {
    a %= mod;
    ll res = 1;
    while (x > 0) {
        if (x & 1) res = (res * a) % mod;
        x >>= 1;
        a = (a * a) % mod;
    }
    return res;
}
