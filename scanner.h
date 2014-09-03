#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <iostream>

class Scanner
{
public:
    enum Token {
        TOKEN_FALSE = 0,
        TOKEN_TRUE  = 1,
        TOKEN_VAR   = 256,
        TOKEN_NOT,
        TOKEN_OR,
        TOKEN_AND,
        TOKEN_IMP,
        TOKEN_IFF
    };

    Scanner(std::istream& input);

    // Get next token
    int next_token(bool preview = false);

    // Get current token value
    std::string value() const;

    // Get current token
    int current() const;

protected:
    // Input stream
    std::istream& input;

    // Token
    int token;
    // Token value
    std::string tvalue;
};

#endif // SCANNER_H
