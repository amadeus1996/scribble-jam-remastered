#include "../headers/Hint.h"
#include <random>


std::vector<std::vector<std::string>> Hint::hints = {{"the", "ar",  "we",  "upp", "ach", "ver", "str", "con", "ous", "al", "own", "ol", "di",  "ie", "gg", "ee"},
{"tio", "oe",  "ner", "oli", "pl",  "eri", "vo",  "ade", "ute", "bl", "nat", "rs", "cte", "cti"},
{"kp",  "rth", "hir"}};

std::string Hint::newHint(const int difficulty) {
    // DIFFICULTY: 0 = EASY, 1 = MEDIUM, 2 = HARD
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> num1(0, difficulty);
    const int randomDifficulty = static_cast<int>(num1(rng));
    std::uniform_int_distribution<std::mt19937::result_type> num2(0, Hint::hints[randomDifficulty].size() - 1);
    const int size = static_cast<int>(num2(rng));
    return hints[randomDifficulty][size];
}
