#include "../headers/Round.h"
#include "../headers/Hint.h"


int Round::idCounter = 0;

Round::Round() : score{0}, lives{3} /* TODO: timePlayed{0}, accuracy{1} */ {
    // TODO: alphabetVisit
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

    this->dict = new Dictionary;

    this->config = new Configuration;
}

Round::Round(const int diff) : score{0} /* TODO: timePlayed{0}, accuracy{1} */ {
    // TODO: alphabetVisit
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

    this->dict = new Dictionary;

    this->config = new Configuration(diff);

    this->lives = this->config->startingLives;
}

bool Round::hasLives() const {
    return this->lives > 0;
}

void Round::timer(std::atomic<bool> &timeUp, std::condition_variable &cv) {
    for (int i = 0; i < 100 && !timeUp.load(); ++i)
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    timeUp = true;
    cv.notify_all();
}

void Round::guessWord() {
    // generate a hint (depending on the difficulty)
    // TODO: work on hints for custom difficulty
    const std::string hint = Hint::newHint(this->config->difficulty == 3 ? 2 : this->config->difficulty);
    std::string input;
    int guesses = this->config->numberOfGuesses;

    // print the current hint and stats
    std::cout << "HINT: " << hint << "\n";
    std::cout << this->lives << " LIVES, " << this->score << " SCORE\n";
    std::cout << guesses << " GUESSES\n\n";

    // timer thread: correctly guessing within 5 seconds gives 1 extra score
    std::atomic<bool> timeUp(false);
    std::condition_variable cv;
    std::thread timerObj(&Round::timer, std::ref(timeUp), std::ref(cv));

    while (guesses) {
        std::cin >> input;
        if (input.find(hint) != std::string::npos && this->dict->searchWord(input)) {
            // there are 4 ways to get points/score
            // 1. the guess is correct (+1)
            // 2. the guess is within 5 seconds (+1)
            // 3. it was on the first guess (+1)
            // 4. the guessed word's length is >=8 (long word) (+1)
            // 1 12 13 14 123 124 134 1234

            this->score += 1; // if the guess is correct

            if (!timeUp)
                this->score += 1; // if it's within 5 seconds

            // if it's on the first guess (first try)
            switch (this->config->difficulty) {
                case 0: // EASY DIFFICULTY
                    if (guesses == 5)
                        this->score += 1;
                    break;
                case 1: // MEDIUM DIFFICULTY
                    if (guesses == 3)
                        this->score += 1;
                    break;
                case 2: // HARD DIFFICULTY
                    if (guesses == 2)
                        this->score += 1;
                    break;
                default: // CUSTOM DIFFICULTY
                    if (guesses == this->config->numberOfGuesses)
                        this->score += 1;
                    break;
            }

            if (input.length() >= 8)
                this->score += 1;

            // guess is correct, so end the timer (so it doesn't sleep for 5 seconds)
            timeUp = true;
            break;
        }
        --guesses; // the guess was incorrect
    }

    // if the player ran out of guesses, make sure to end the timer (in case it didn't end)
    // otherwise it may sleep for 5 seconds
    // update the other attributes as well
    if (!guesses) {
        timeUp = true;
        if (this->score)
            this->score -= 1;
        this->lives -= 1;
    }

    // if (timerObj.joinable())
    timerObj.join();
}

std::ostream &operator<<(std::ostream &os, const Round &round) {
    os << *(round.config);
    os << "SCORE: " << round.score << "\n";
    // os << "ACCURACY: " << round.accuracy << "\n";
    // os << "TIME: " << round.timePlayed << "\n";
    os << "DATE: " << round.date << "\n";
    return os;
}

Round::~Round() {
    delete this->dict;
    delete this->config;
}
