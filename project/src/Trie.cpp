#include "../headers/Trie.h"

Trie::Trie() {
    this->root = new TrieNode();
}

Trie::~Trie() {
    delete root;
}

void Trie::insert(const std::string &word) const {
    TrieNode *aux = root;
    for (const auto &c: word) {
        if (!aux->children.contains(c))
            aux->children[c] = new TrieNode();
        aux = aux->children[c];
    }
    aux->isWord = true;
}

bool Trie::search(const std::string &word) const {
    TrieNode *aux = root;
    for (const auto &c: word) {
        if (!aux->children.contains(c))
            return false;
        aux = aux->children[c];
    }
    return aux->isWord;
}

void Trie::print() const {
    std::string word;
    printHelper(this->root, word);
}

void Trie::printHelper(const TrieNode *node, std::string &currentWord) {
    if (node->isWord) std::cout << currentWord << "\n";
    for (const auto &[fst, snd]: node->children) {
        currentWord.push_back(fst);
        printHelper(snd, currentWord);
        currentWord.pop_back();
    }
}