#include "../headers/Dictionary.h"
#include "../headers/MyException.h"
#include <fstream>


Dictionary::Dictionary() {
    std::ifstream f("../words.txt");
    std::string word;
    while (f >> word)
        this->words.insert(word);
    f.close();
}

Dictionary::Dictionary(const std::string &file) {
    try {
        std::ifstream f(file);
        if (!f.is_open()) throw ex;
        std::string word;
        while (f >> word)
            this->words.insert(word);
        f.close();
    }
    catch (const std::exception &ex) {
        std::cout << ex.what();
    }
}

void Dictionary::print() const {
    this->words.print();
}

bool Dictionary::searchWord(const std::string &word) {
    if (this->words.search(word) && !this->usedWords.contains(word)) {
        this->usedWords.insert(word);
        return true;
    }
    return false;
}
