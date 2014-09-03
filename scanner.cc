#include "scanner.h"

Scanner::Scanner(std::istream& input):
        input(input)
{
    this->token  = -1;
    this->tvalue = "";
}

int Scanner::next_token(bool preview) {
    std::streampos pos = input.tellg();
    // Current token
    int token = -1;
    // Current token value
    std::string tvalue = "";

    if(!input.eof()) {
        input >> tvalue;

        if(tvalue[0] == '0') {
            token = Scanner::TOKEN_FALSE;
        }
        else if(tvalue[0] == '1') {
            token = Scanner::TOKEN_TRUE;
        }
        else if(tvalue[0] >= 'a' && tvalue[0] <= 'z') {
            token = Scanner::TOKEN_VAR;
        }
        else if(tvalue == "~") {
            token = Scanner::TOKEN_NOT;
        }
        else if(tvalue == "|") {
            token = Scanner::TOKEN_OR;
        }
        else if(tvalue == "&") {
            token = Scanner::TOKEN_AND;
        }
        else if(tvalue == "=>") {
            token = Scanner::TOKEN_IMP;
        }
        else if(tvalue == "<=>") {
            token = Scanner::TOKEN_IFF;
        }
        else {
            token = tvalue[0];
        }
    }

    if(!preview) {
        this->token  = token;
        this->tvalue = tvalue;
    } else {
        input.seekg(pos);
    }

    return token;
}

std::string Scanner::value() const {
    return this->tvalue;
}

int Scanner::current() const {
    return this->token;
}
