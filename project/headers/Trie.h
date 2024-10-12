#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include <string>

class Trie {
    TrieNode *root;

    static void printHelper(const TrieNode *, std::string &);

public:
    Trie();

    ~Trie();

    void insert(const std::string &) const;

    [[nodiscard]] bool search(const std::string &) const;

    void print() const;
};


#endif //TRIE_H
