#include "../headers/TrieNode.h"
#include <iostream>

TrieNode::TrieNode() : isWord{false} {}

TrieNode::~TrieNode() {
    for (auto &child: children)
        delete child.second;
}