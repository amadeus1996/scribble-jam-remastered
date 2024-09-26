#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <algorithm>

class Hint {
    static std::vector<std::string> hints;
public:
    static std::string newHint();

//    friend std::ostream& operator<<(std::ostream&, const Hint&);
};

std::vector<std::string> Hint::hints = {"the", "ar", "we", "ade", "upp", "ach"};

std::string Hint::newHint() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> num(1,Hint::hints.size());
    return hints[static_cast<int>(num(rng))];
}

//std::ostream& operator<<(std::ostream& os, const Hint& obj) {
//    std::cout<<"Letters: "<<obj.letters << "\n";
//    return os;
//}

// -----------------------------------------------------------------------------------

class TrieNode {
    TrieNode* child[26]{};
    bool wordEnd;
public:
    TrieNode();

    ~TrieNode();

    friend class Trie;
};

TrieNode::TrieNode() : wordEnd{false} {}

TrieNode::~TrieNode() {
    for (auto& node : child)
        delete node;
}

// -----------------------------------------------------------------------------------

class Trie {
    TrieNode* root;

    void print(TrieNode*, const std::string&) const;
public:
    Trie();

    ~Trie();

    void printHelper() const;

    void insert(const std::string&);

    [[nodiscard]] bool search(const std::string&) const;
};

Trie::Trie() {
    this->root = new TrieNode();
}

Trie::~Trie() {
    delete root;
}

void Trie::print(TrieNode* node, const std::string& prefix) const {
    if (node->wordEnd) std::cout<<prefix<<"\n";
    for (int i = 0; i < 26; ++i)
        if (node->child[i]) {
            char nextChar = 'a' + i;
            print(node->child[i], prefix + nextChar);
        }
}

void Trie::printHelper() const {
    print(this->root, "");
}

void Trie::insert(const std::string& key) {
    TrieNode* current = root;
    for (const auto& c : key) {
        if (!current->child[c - 'a'])
            current->child[c - 'a'] = new TrieNode();
        current = current->child[c - 'a'];
    }
    current->wordEnd = true;
}

bool Trie::search(const std::string& key) const {
    TrieNode* current = root;
    for (const auto& c : key) {
        if (!current->child[c - 'a'])
            return false;
        current = current->child[c - 'a'];
    }
    return current->wordEnd;
}

// -----------------------------------------------------------------------------------

class Dictionary {
    class Trie trie;
public:
    explicit Dictionary(const std::string&);

    void printWords() const;

    [[nodiscard]] bool searchWord(const std::string&) const;
};

Dictionary::Dictionary(const std::string& file) {
    std::ifstream f (file);
    if (!f) {
        std::cerr<<"Error: invalid file name\n";
        return;
    }
    std::string word;
    while (f >> word) {
        for (int i = 0; i < word.length(); ++i)
            word[i] = tolower(word[i]);
        this->trie.insert(word);
    }
}

void Dictionary::printWords() const {
    trie.printHelper();
}

bool Dictionary::searchWord(const std::string& word) const {
    return trie.search(word);
}

// -----------------------------------------------------------------------------------

class Player {
    std::string name;
    int lives;
    int score;
public:
    Player();

    explicit Player(std::string);

    friend std::ostream& operator<<(std::ostream&, const Player&);

    void guessWord(Dictionary&, std::string&);
};

Player::Player() : name{"noname"}, lives{3}, score{0} {}

Player::Player(std::string name) : name{std::move(name)}, lives{3}, score{0} {}

std::ostream& operator<<(std::ostream& os, const Player& obj) {
    os<<"Name: "<<obj.name<<"\n";
    os<<"Lives: "<<obj.lives<<"\n";
    os<<"Score: "<<obj.score<<"\n";
    return os;
}

void Player::guessWord(Dictionary& dict, std::string& hint) {
    std::cout<<"Hint: "<<hint << "\n";
    std::string guess;
    std::cin>>guess;
    std::transform(guess.begin(), guess.end(), guess.begin(), [](unsigned char c) {return std::tolower(c);});
    if (guess.find(hint) != std::string::npos && dict.searchWord(guess))
        ++score;
    else {
        --lives;
        if (score) --score;
    }
}

int main() {
    Dictionary dict("../../words.txt");
    Player p;
    std::cout<<p;
    for (int i = 0; i < 5; ++i) {
        std::string hint = Hint::newHint();
        p.guessWord(dict, hint);
        std::cout<<p;
    }
    return 0;
}
