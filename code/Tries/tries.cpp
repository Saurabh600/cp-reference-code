#include <bits/stdc++.h>
using namespace std;

class Trie {
    struct Node {
        unordered_map<char, Node*> mp;
        bool isEnd = false;
    };
    Node* root;

    public:
    Trie() {
        this->root = new Node();
    }

    void insert(string word) {
        auto node = root;
        for (char ch : word) {
            if (!node->mp.count(ch)) node->mp[ch] = new Node();
            node = node->mp[ch];
        }
        node->isEnd = true;
    }

    bool search(string word) {
        auto node = root;
        for (char ch : word) {
            if (!node->mp.count(ch)) return false;
            node = node->mp[ch];
        }

        return node->isEnd;
    }

    bool startsWith(string prefix) {
        auto node = root;
        for (char ch : prefix) {
            if (!node->mp.count(ch)) return false;
            node = node->mp[ch];
        }

        return true;
    }
};
