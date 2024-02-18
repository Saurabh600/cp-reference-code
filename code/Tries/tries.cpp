#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<Node *> links;
    bool flag;

    Node() {
        links.resize(128);
        flag = false;
    }

    bool containsKey(char ch) {
        return links[ch] != nullptr;
    }
    Node *get(char ch) {
        return links[ch];
    }
    void put(char ch, Node *node) {
        links[ch] = node;
    }
    void setEnd() {
        flag = true;
    }
    bool isEnd() {
        return flag;
    }
};

class Trie {
    Node *root;

    public:
    Trie() {
        root = new Node();
    }

    void insert(string word) {
        auto node = root;

        for (char ch : word) {
            if (!node->containsKey(ch)) {
                node->put(ch, new Node());
            }
            node = (node->get(ch));
        }
        node->setEnd();
    }

    bool search(string word) {
        auto node = root;
        for (char ch : word) {
            if (!node->containsKey(ch)) return false;
            node = node->get(ch);
        }

        return node->isEnd();
    }

    bool startsWith(string prefix) {
        auto node = root;
        for (char ch : prefix) {
            if (!node->containsKey(ch)) return false;
            node = node->get(ch);
        }

        return true;
    }
};
