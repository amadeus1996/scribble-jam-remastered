#ifndef GAME_H
#define GAME_H

#include "Dictionary.h"
#include "Round.h"
#include <vector>


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


#endif //GAME_H
