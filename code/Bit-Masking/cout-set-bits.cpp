#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;

ll largestPow2(ll n) {
    ll x = 0;
    while ((1LL << x) <= n) x++;
    return x - 1;
}

ll coutSetBits(ll n) {
    ll res = 0, x = 0;
    while (n > 1) {
        x = largestPow2(n);
        n &= (~(1LL << x));
        res += (1LL << (x - 1)) * x;
        res += n + 1;
    }
    res += n;
    return res;
}

ll countSetBitsRecursively(ll n) {
    if (n < 2) return n;

    ll x = largestPow2(n);

    ll bits_till_2x = x * (1LL << (x - 1));  // (2^x)/2 * x == (2^(x-1))*x
    ll bits_from_2x = n - (1LL << x) + 1;    // n - (2^x) + 1 i.e last bit
    ll rest = n & (~(1LL << x));  // from 2^x to n without last set bit
    return bits_till_2x + bits_from_2x + countSetBitsRecursively(rest);
}
