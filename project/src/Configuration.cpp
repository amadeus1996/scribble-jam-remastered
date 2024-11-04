#include "../headers/Configuration.h"
#include <iostream>


Configuration::Configuration() : difficulty{1}, startingLives{3}, numberOfGuesses{3} {
}

Configuration::Configuration(const int diff) : difficulty{diff} {
    switch (this->difficulty) {
        case 0: // EASY DIFFICULTY
            this->startingLives = 5;
            this->numberOfGuesses = 5;
            break;
        case 1: // MEDIUM DIFFICULTY
            this->startingLives = 3;
            this->numberOfGuesses = 3;
            break;
        case 2: // HARD DIFFICULTY
            this->startingLives = 2;
            this->numberOfGuesses = 2;
            break;
        default: // CUSTOM DIFFICULTY
            std::cout << "STARTING LIVES: ";
            std::cin >> this->startingLives;
            std::cout << "NUMBER OF GUESSES: ";
            std::cin >> this->numberOfGuesses;
            break;
    }
}

std::ostream &operator<<(std::ostream &os, const Configuration &config) {
    os << "DIFFICULTY: ";
    switch (config.difficulty) {
        case 0:
            std::cout << "EASY (5 LIVES, 5 GUESSES)\n";
            break;
        case 1:
            std::cout << "MEDIUM (3 LIVES, 3 GUESSES)\n";
            break;
        case 2:
            std::cout << "HARD (2 LIVES, 2 GUESSES)\n";
            break;
        default:
            std::cout << "CUSTOM (" << config.startingLives << " LIVES, " << config.numberOfGuesses << " GUESSES)\n";
            break;
    }
    return os;
}
