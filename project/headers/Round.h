#ifndef ROUND_H
#define ROUND_H


#include "Configuration.h"
#include "Dictionary.h"
#include <atomic>
#include <condition_variable>


class Round {
    static int idCounter;
    int id;
    int score;
    int lives;
    std::string date;
    Configuration *config;
    Dictionary *dict;
    // TODO: std::map<char, int> alphabetVisit;
    // TODO: int timePlayed;
    // TODO: float accuracy;

    static void timer(std::atomic<bool> &, std::condition_variable &);

public:
    Round();

    explicit Round(int);

    Round &operator=(const Round &) = default;

    [[nodiscard]] bool hasLives() const;

    void guessWord();

    friend std::ostream &operator<<(std::ostream &, const Round &);

    ~Round();
};


#endif //ROUND_H
