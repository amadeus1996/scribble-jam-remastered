#include "../headers/Round.h"
#include "../headers/Hint.h"


int Round::idCounter = 0;

Round::Round() : score{0}, lives{3} /* TODO: timer{10}, timePlayed{0}, accuracy{1} */ {
    // for (char i = 'a'; i <= 'z'; ++i)
    //     this->alphabetVisit[i] = false;
    const time_t aux = time(nullptr);
    const std::string currentTime = ctime(&aux);
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

Round::Round(int diff) : config(diff), score{0} /* TODO: timePlayed{0}, accuracy{1} */ {
    this->lives = this->config.startingLives;
    // this->timer = static_cast<float>(this->config.maxTimeLimit);
    // for (char i = 'a'; i <= 'z'; ++i)
        // this->alphabetVisit[i] = false;
    const time_t aux = time(nullptr);
    const std::string currentTime = ctime(&aux);
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
    const std::string hint = Hint::newHint(this->config.difficulty == 3 ? 2 : this->config.difficulty);
    std::cout << "HINT: " << hint << "\n";
    std::cout << this->lives << " LIVES, " << this->score << " SCORE\n\n";
    std::string input;
    std::cin >> input;
    if (dict.searchWord(input) && input.find(hint) != std::string::npos) {
        this->score += 1;
        if (input.length() >= 8) this->score += 1;
        // for (const auto &c: input)
            // if (this->alphabetVisit.find(c) == this->alphabetVisit.end())
                // this->alphabetVisit[c] = true;
    }
    else {
        if (score) this->score -= 1;
        this->lives -= 1;
    }
}

std::ostream &operator<<(std::ostream &os, Round &round) {
    os << round.config;
    os << "SCORE: " << round.score << "\n";
    // os << "ACCURACY: " << round.accuracy << "\n";
    // os << "TIME: " << round.timePlayed << "\n";
    os << "DATE: " << round.date << "\n";
    return os;
}
