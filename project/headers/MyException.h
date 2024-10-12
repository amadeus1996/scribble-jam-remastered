#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <exception>


inline class MyException final : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override;
} ex;


#endif //MYEXCEPTION_H
