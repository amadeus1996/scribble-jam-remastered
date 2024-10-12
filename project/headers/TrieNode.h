#ifndef TRIENODE_H
#define TRIENODE_H

#include <iostream>
#include <unordered_map>


class TrieNode {
    std::unordered_map<char, TrieNode *> children;
    //    std::map<char, TrieNode*> children; # if you want the words in alphabetical order
    bool isWord;
public:
    TrieNode();

    ~TrieNode();

    friend class Trie;
};

#endif //TRIENODE_H
