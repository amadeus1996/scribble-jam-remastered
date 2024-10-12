#include "../headers/MyException.h"


const char *MyException::what() const noexcept {
    return "INVALID INPUT\n";
}
