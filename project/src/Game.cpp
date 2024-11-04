#include "../headers/Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>


Game *Game::instance = nullptr;

Game::~Game() {
    for (const auto &round: this->roundsPlayed)
        delete round;
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

    return input;
}

void Game::playRound() {
    system("CLS");
    if (this->roundsPlayed.empty()) {
        std::cout << "BEFORE PLAYING: WORDS THAT HAVE LESS THAN 3 LETTERS WILL NOT BE TAKEN INTO CONSIDERATION. "
                "THE GAME IS NOT CASE-SENSITIVE. PRESS ANY KEY TO PROCEED\n\n";
        waitForInput();
    }

    const int input = enterDifficulty();
    if (!input) {
        system("CLS");
        return;
    }

    auto *round = new Round(input - 1);

    std::string difficulty;
    if (input == 1)
        difficulty = "EASY";
    else if (input == 2)
        difficulty = "MEDIUM";
    else if (input == 3)
        difficulty = "HARD";
    else if (input == 4) {
        difficulty = "CUSTOM";
        std::cout << "\n";
    }

    for (int i = 0; i < 3; ++i) {
        std::cout << difficulty << " DIFFICULTY PICKED\n";
        std::cout << "GAME STARTING IN " << 3 - i << "...\n\n";
        Sleep(1000);
    }

    while (round->hasLives()) {
        system("CLS");
        round->guessWord();
    }
    this->roundsPlayed.push_back(round);

    system("CLS");
    std::cout << "YOU LOST!\n\n";
    std::cout << *round << "\n";
    std::cout << "PRESS ANY KEY TO CONTINUE\n";
    waitForInput();
}

void Game::printRounds() const {
    system("CLS");
    for (const auto &round: this->roundsPlayed)
        std::cout << *round << "\n";

    std::cout << "PRESS ANY KEY TO CONTINUE\n";
    waitForInput();
}

void Game::run() {
    system("CLS");
    bool ok = true;

    while (ok) {
        printMenu();
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
