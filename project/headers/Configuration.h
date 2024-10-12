#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <fstream>


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


#endif //CONFIGURATION_H