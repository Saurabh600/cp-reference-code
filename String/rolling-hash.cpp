#include <bits/stdc++.h>
using namespace std;

long long power(long long x, long long y, long long p) {
    long long result = 1;
    for (; y; y >>= 1, x = x * x % p) {
        if (y & 1) {
            result = result * x % p;
        }
    }
    return result;
}

long long inverse(long long x, long long p) {
    return power(x, p - 2, p);
}

class Hash {
    private:
    int length;
    const int mod1 = 1e9 + 7, mod2 = 1e9 + 9;
    const int p1 = 31, p2 = 37;
    vector<int> hash1, hash2;
    pair<int, int> hash_pair;

    public:
    inline static vector<int> inv_pow1, inv_pow2;
    inline static int inv_size = 1;

    Hash() {
    }

    Hash(const string& s) {
        length = s.size();
        hash1.resize(length);
        hash2.resize(length);

        int h1 = 0, h2 = 0;
        long long p_pow1 = 1, p_pow2 = 1;
        for (int i = 0; i < length; i++) {
            h1 = (h1 + (s[i] - 'a' + 1) * p_pow1) % mod1;
            h2 = (h2 + (s[i] - 'a' + 1) * p_pow2) % mod2;
            p_pow1 = (p_pow1 * p1) % mod1;
            p_pow2 = (p_pow2 * p2) % mod2;
            hash1[i] = h1;
            hash2[i] = h2;
        }
        hash_pair = make_pair(h1, h2);

        if (inv_size < length) {
            for (; inv_size < length; inv_size <<= 1)
                ;

            inv_pow1.resize(inv_size, -1);
            inv_pow2.resize(inv_size, -1);

            inv_pow1[inv_size - 1] =
                inverse(power(p1, inv_size - 1, mod1), mod1);
            inv_pow2[inv_size - 1] =
                inverse(power(p2, inv_size - 1, mod2), mod2);

            for (int i = inv_size - 2; i >= 0 && inv_pow1[i] == -1; i--) {
                inv_pow1[i] = (1LL * inv_pow1[i + 1] * p1) % mod1;
                inv_pow2[i] = (1LL * inv_pow2[i + 1] * p2) % mod2;
            }
        }
    }

    int size() {
        return length;
    }

    pair<int, int> prefix(const int index) {
        return {hash1[index], hash2[index]};
    }

    pair<int, int> substr(const int l, const int r) {
        if (l == 0) {
            return {hash1[r], hash2[r]};
        }
        int temp1 = hash1[r] - hash1[l - 1];
        int temp2 = hash2[r] - hash2[l - 1];
        temp1 += (temp1 < 0 ? mod1 : 0);
        temp2 += (temp2 < 0 ? mod2 : 0);
        temp1 = (temp1 * 1LL * inv_pow1[l]) % mod1;
        temp2 = (temp2 * 1LL * inv_pow2[l]) % mod2;
        return {temp1, temp2};
    }

    bool operator==(const Hash& other) {
        return (hash_pair == other.hash_pair);
    }
};

int main() {
    string my_str = "geeksforgeeks";
    const int n = my_str.length();
    auto hash = Hash(my_str);
    auto hash_pair = hash.substr(0, n - 1);
    cout << "Hashes of the string " << my_str << " are:\n";
    cout << hash_pair.first << ' ' << hash_pair.second << '\n';
    return 0;
}
