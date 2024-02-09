#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<Node *> links;
    bool flag;

    Node() {
        links.resize(26);
        flag = false;
    }

    bool containsKey(char ch) {
        return links[ch - 'a'] != nullptr;
    }
    Node *get(char ch) {
        return links[ch - 'a'];
    }
    void put(char ch, Node *node) {
        links[ch - 'a'] = node;
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

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
