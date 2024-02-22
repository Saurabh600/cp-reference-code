#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;

const int N = 1e6 + 7;
const ll MOD = 1e9 + 7;

vector<ll> fact, inv_fact;

ll modmul(ll a, ll b) {
    return ((a % MOD) * (b % MOD)) % MOD;
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

void build_factorial(ll n) {
    fact.resize(n);
    fact[0] = 1;
    for (ll i = 1; i < n; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
}

void build_inverse_factorial(ll n) {
    inv_fact.resize(n);
    inv_fact[0] = 1;
    for (ll i = 1; i < n; i++) {
        inv_fact[i] = modpow(fact[i], MOD - 2, MOD);
    }
}

ll ncr(ll a, ll b) {
    if (b > a) return 0;
    return modmul(modmul(fact[a], inv_fact[b]), inv_fact[a - b]);
}

int main() {
    build_factorial(N);
    build_factorial(N);
    cout << ncr(25, 10) << "\n";
    return 0;
}
