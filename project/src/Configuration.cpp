#include "../headers/Configuration.h"
#include <iostream>


Configuration::Configuration() : difficulty{1}, startingLives{3}, maxTimeLimit{15} {}

Configuration::Configuration(const int diff) : difficulty{diff} {
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
