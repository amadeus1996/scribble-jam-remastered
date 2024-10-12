#ifndef ROUND_H
#define ROUND_H

#include "Configuration.h"
#include "Dictionary.h"


class Round {
    static int idCounter;
    int id;
    Configuration config;
    int score;
    int lives;
    // TODO: float timer;
    // TODO: std::map<char, int> alphabetVisit;
    // TODO: int timePlayed;
    // TODO: float accuracy;
    std::string date;
public:
    Round();

    explicit Round(int);

    Round &operator=(const Round &) = default;

    [[nodiscard]] bool hasLives() const;

    void guessWord(Dictionary &);

    friend std::ostream &operator<<(std::ostream &, Round &);
};


#endif //ROUND_H
