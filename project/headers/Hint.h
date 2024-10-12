#ifndef HINT_H
#define HINT_H

#include <vector>
#include <string>


class Hint {
    static std::vector<std::vector<std::string>> hints;
public:
    static std::string newHint(int);
};

#endif //HINT_H
