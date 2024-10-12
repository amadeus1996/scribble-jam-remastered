#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Trie.h"
#include <unordered_set>


class Dictionary {
    Trie words;
    std::unordered_set<std::string> usedWords;
public:
    Dictionary();

    explicit Dictionary(const std::string &);

    void print() const;

    [[nodiscard]] bool searchWord(const std::string &);
};


#endif //DICTIONARY_H
