#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <ctime>
#include <conio.h>
#include <synchapi.h>

class MyException : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override;
} ex;

const char *MyException::what() const noexcept {
    return "INVALID INPUT\n";
}

// -----------------------------------------------------------------------------------

class TrieNode {
    std::unordered_map<char, TrieNode *> children;
//    std::map<char, TrieNode*> children; # if you want the words in alphabetical order
    bool isWord;

    TrieNode();

    ~TrieNode();

    friend class Trie;
};

TrieNode::TrieNode() : isWord{false} {}

TrieNode::~TrieNode() {
    for (auto &child: children)
        delete child.second;
}

// -----------------------------------------------------------------------------------

class Trie {
    TrieNode *root;

    void printHelper(TrieNode *, std::string &) const;

public:
    Trie();

    ~Trie();

    void insert(const std::string &);

    [[nodiscard]] bool search(const std::string &) const;

    void print() const;
};

Trie::Trie() {
    this->root = new TrieNode();
}

Trie::~Trie() {
    delete root;
}

void Trie::insert(const std::string &word) {
    TrieNode *aux = root;
    for (const auto &c: word) {
        if (aux->children.find(c) == aux->children.end())
            aux->children[c] = new TrieNode();
        aux = aux->children[c];
    }
    aux->isWord = true;
}

bool Trie::search(const std::string &word) const {
    TrieNode *aux = root;
    for (const auto &c: word) {
        if (aux->children.find(c) == aux->children.end())
            return false;
        aux = aux->children[c];
    }
    return aux->isWord;
}

void Trie::print() const {
    std::string word;
    printHelper(this->root, word);
}

void Trie::printHelper(TrieNode *node, std::string &currentWord) const {
    if (node->isWord) std::cout << currentWord << "\n";
    for (const auto &child: node->children) {
        currentWord.push_back(child.first);
        printHelper(child.second, currentWord);
        currentWord.pop_back();
    }
}

// -----------------------------------------------------------------------------------

class Hint {
    static std::vector<std::vector<std::string>> hints;
public:
    static std::string newHint(int);
};

std::vector<std::vector<std::string>> Hint::hints = {{"the", "ar",  "we",  "upp", "ach", "ver", "str", "con", "ous", "al", "own", "ol", "di",  "ie", "gg", "ee"},
                                                     {"tio", "oe",  "ner", "oli", "pl",  "eri", "vo",  "ade", "ute", "bl", "nat", "rs", "cte", "cti"},
                                                     {"kp",  "rth", "hir"}};

std::string Hint::newHint(int difficulty) {
    // DIFFICULTY: 0 = EASY, 1 = MEDIUM, 2 = HARD
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> num1(0, difficulty);
    int randomDifficulty = static_cast<int>(num1(rng));
    std::uniform_int_distribution<std::mt19937::result_type> num2(0, Hint::hints[randomDifficulty].size() - 1);
    int size = static_cast<int>(num2(rng));
    return hints[randomDifficulty][size];
}

// -----------------------------------------------------------------------------------

class Dictionary {
    Trie words;
    std::unordered_set<std::string> usedWords;
public:
    Dictionary();

    explicit Dictionary(const std::string &);

    void print() const;

    [[nodiscard]] bool searchWord(const std::string &);
};

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
    if (this->words.search(word) && this->usedWords.find(word) == this->usedWords.end()) {
        this->usedWords.insert(word);
        return true;
    }
    return false;
}

// -----------------------------------------------------------------------------------

class Configuration {
    int difficulty;
    int startingLives;
    int maxTimeLimit;

    friend class Round;

public:
    Configuration();

    explicit Configuration(int);

    Configuration &operator=(const Configuration &) = default;

    friend std::ostream &operator<<(std::ostream &, Configuration &);
};

Configuration::Configuration() : difficulty{1}, startingLives{3}, maxTimeLimit{15} {}

Configuration::Configuration(int diff) : difficulty{diff} {
    switch (this->difficulty) {
        case 0:
            this->startingLives = 5;
            this->maxTimeLimit = 15;
            break;
        case 1:
            this->startingLives = 3;
            this->maxTimeLimit = 10;
            break;
        case 2:
            this->startingLives = 2;
            this->maxTimeLimit = 8;
            break;
        default:
            std::cout << "STARTING LIVES: ";
            std::cin >> this->startingLives;
            std::cout << "TIME LIMIT: ";
            std::cin >> this->maxTimeLimit;
            break;
    }
}

std::ostream &operator<<(std::ostream &os, Configuration &config) {
    os << "DIFFICULTY: ";
    switch (config.difficulty) {
        case 0:
            std::cout << "EASY (5 LIVES, 15 SECONDS)\n";
            break;
        case 1:
            std::cout << "MEDIUM (3 LIVES, 10 SECONDS)\n";
            break;
        case 2:
            std::cout << "HARD (2 LIVES, RANDOM 2-8 SECONDS)\n";
            break;
        default:
            std::cout << "CUSTOM (" << config.startingLives << " LIVES, " << config.maxTimeLimit << " SECONDS)\n";
            break;
    }
    return os;
}

// -----------------------------------------------------------------------------------

class Round {
    static int idCounter;
    int id;
    Configuration config;
    int score;
    int lives;
    float timer;
    std::map<char, int> alphabetVisit;
    int timePlayed;
    float accuracy;
    std::string date;
public:
    Round();

    explicit Round(int);

    Round &operator=(const Round &) = default;

    [[nodiscard]] bool hasLives() const;

    void guessWord(Dictionary &);

    friend std::ostream &operator<<(std::ostream &, Round &);
};

int Round::idCounter = 0;

Round::Round() : score{0}, lives{3}, timer{10}, timePlayed{0}, accuracy{1} {
    for (char i = 'a'; i <= 'z'; ++i)
        this->alphabetVisit[i] = false;
    time_t aux = time(nullptr);
    std::string currentTime = ctime(&aux);
    this->date += currentTime.substr(4, 3);
    this->date += ' ';
    int i;
    (currentTime[9] == ' ') ? i = 1 : i = 0;
    this->date += currentTime.substr(8, 2 - i);
    this->date += ' ';
    this->date += currentTime.substr(20 - i, 4);
    this->date += ", ";
    this->date += currentTime.substr(11 - i, 8);
    this->id = ++idCounter;
}

Round::Round(int diff) : config(diff), score{0}, timePlayed{0}, accuracy{1} {
    this->lives = this->config.startingLives;
    this->timer = static_cast<float>(this->config.maxTimeLimit);
    for (char i = 'a'; i <= 'z'; ++i)
        this->alphabetVisit[i] = false;
    time_t aux = time(nullptr);
    std::string currentTime = ctime(&aux);
    this->date += currentTime.substr(4, 3);
    this->date += ' ';
    int i;
    (currentTime[9] == ' ') ? i = 1 : i = 0;
    this->date += currentTime.substr(8, 2 - i);
    this->date += ' ';
    this->date += currentTime.substr(20 - i, 4);
    this->date += ", ";
    this->date += currentTime.substr(11 - i, 8);
    this->id = ++idCounter;
}

bool Round::hasLives() const {
    return this->lives > 0;
}

void Round::guessWord(Dictionary &dict) {
    std::string hint = Hint::newHint(this->config.difficulty == 3 ? 2 : this->config.difficulty);
    std::cout << "HINT: " << hint << "\n";
    std::cout << this->lives << " LIVES, " << this->score << " SCORE\n\n";
    std::string input;
    std::cin >> input;
    // # while (timer) { ... }
    if (dict.searchWord(input) && input.find(hint) != std::string::npos) {
        this->score += 1;
        if (input.length() >= 8) this->score += 1;
//         # if timer >= 1/2 * maxtimeLimit ...
        for (const auto &c: input)
            if (this->alphabetVisit.find(c) == this->alphabetVisit.end())
                this->alphabetVisit[c] = true;
    } else {
        if (score) this->score -= 1;
        this->lives -= 1;
    }
}

std::ostream &operator<<(std::ostream &os, Round &round) {
    os << round.config;
    os << "SCORE: " << round.score << "\n";
    os << "ACCURACY: " << round.accuracy << "\n";
    os << "TIME: " << round.timePlayed << "\n";
    os << "DATE: " << round.date << "\n";
    return os;
}

// -----------------------------------------------------------------------------------

class Game {
    static Game *instance;
    Dictionary *dict;
    std::vector<Round *> roundsPlayed;

    Game();

    ~Game();

public:
    Game(const Game &) = delete;

    Game operator=(const Game &) = delete;

    static Game &getInstance();

    static void destroyInstance();

    static void waitForInput();

    static void printMenu();

    static int enterDifficulty();

    void playRound();

    void printRounds() const;

    void run();
};

Game *Game::instance = nullptr;

Game::Game() {
    this->dict = new Dictionary;
}

Game::~Game() {
    for (auto &round: roundsPlayed)
        delete round;
    delete dict;
}

Game &Game::getInstance() {
    if (!instance) instance = new Game();
    return *instance;
}

void Game::destroyInstance() {
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

void Game::waitForInput() {
    while (true)
        if (_kbhit()) {
            _getch();
            system("CLS");
            break;
        }
}

void Game::printMenu() {
    std::cout << "1. PLAY A MATCH\n";
    std::cout << "2. VIEW PAST GAMES\n";
    std::cout << "3. EXIT\n\n";
}

int Game::enterDifficulty() {
    std::cout << "PICK A DIFFICULTY:\n";
    std::cout << "1. EASY\n";
    std::cout << "2. MEDIUM\n";
    std::cout << "3. HARD\n";
    std::cout << "4. CUSTOM\n";
    std::cout << "ENTER OTHER TO GO BACK\n\n";

    int input;
    std::cin >> input;
    if (input < 1 || input > 4) return 0;

    std::string difficulty;
    if (input == 1) difficulty = "EASY";
    else if (input == 4) difficulty = "CUSTOM";
    else difficulty = input == 2 ? "MEDIUM" : "HARD";
    if (input != 4)
        for (int i = 0; i < 3; ++i) {
            std::cout << difficulty << " DIFFICULTY PICKED\n";
            std::cout << "GAME STARTING IN " << 3 - i << "...\n\n";
            Sleep(1000);
        }
    return input;
}

void Game::playRound() {
    system("CLS");
    if (this->roundsPlayed.empty()) {
        std::cout << "BEFORE PLAYING: WORDS THAT HAVE LESS THAN 3 LETTERS WILL NOT BE TAKEN INTO CONSIDERATION. "
                     "THE GAME IS NOT CASE-SENSITIVE. PRESS ANY KEY TO PROCEED\n\n";
        Game::waitForInput();
    }

    int input = Game::enterDifficulty();
    if (!input) {
        system("CLS");
        return;
    }

    auto *round = new Round(input - 1);
    while (round->hasLives()) {
        system("CLS");
        round->guessWord(*dict);
    }
    this->roundsPlayed.push_back(round);

    system("CLS");
    std::cout << "YOU LOST!\n\n";
    std::cout << *round << "\n";
    std::cout << "PRESS ANY KEY TO CONTINUE\n";
    Game::waitForInput();
}

void Game::printRounds() const {
    system("CLS");
    for (const auto &round: this->roundsPlayed)
        std::cout << *round << "\n";

    std::cout << "PRESS ANY KEY TO CONTINUE\n";
    Game::waitForInput();
}

void Game::run() {
    system("CLS");
    bool ok = true;

    while (ok) {
        Game::printMenu();
        int input;
        std::cin >> input;

        switch (input) {
            case 1:
                playRound();
                break;
            case 2:
                printRounds();
                break;
            default:
                ok = false;
                break;
        }
    }
}

int main() {
    auto &game = Game::getInstance();
    game.run();
    Game::destroyInstance();
    return 0;
}
