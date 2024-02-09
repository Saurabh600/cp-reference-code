#include <bits/stdc++.h>
using namespace std;

bool check_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }

    return true;
}

vector<int> Sieve_of_Eratosthenes(int n) {
    vector<int> prime(n + 1, 1);

    prime[0] = prime[1] = 0;
    for (int p = 2; p * p <= n; p++) {
        if (prime[p]) {
            for (int j = p * p; j <= n; j += p) prime[j] = 0;
        }
    }

    return prime;
}