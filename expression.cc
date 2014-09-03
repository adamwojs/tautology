#include <iostream>
#include <stack>
#include "expression.h"

Expression::Expression(std::istream &input):
        scanner(input)
{
    this->parse();
}

bool Expression::calculate() {
    std::stack<bool> result;
    std::vector<int>::const_iterator i;

    for(i = this->output.begin(); i != this->output.end(); ++i) {
        if(*i == 0 || *i == 1) {
            // Literal 0|1
            result.push((bool) *i);
        }
        else if(*i >= 'a' && *i <= 'z') {
            // Varible value
            result.push(this->symbols[(char) *i]);
        }
        else if(*i == Scanner::TOKEN_NOT) {
            bool arg = result.top();
            result.pop();

            // NOT arg
            result.push(!arg);
        }
        else if(*i == Scanner::TOKEN_AND) {
            bool q = result.top();
            result.pop();
            bool p = result.top();
            result.pop();

            //std::cout << "p = " << p << "q = " << q << " \t" << (p && q) << std::endl;

            // p AND q
            result.push(p && q);
        }
        else if(*i == Scanner::TOKEN_OR) {
            bool q = result.top();
            result.pop();
            bool p = result.top();
            result.pop();

            //std::cout << "p = " << p << "q = " << q << " \t" << (p || q) << std::endl;

            // p OR q
            result.push(p || q);
        }
        else if(*i == Scanner::TOKEN_IFF) {
            bool q = result.top();
            result.pop();
            bool p = result.top();
            result.pop();

            //std::cout << "p = " << p << "q = " << q << " \t" << (p == q) << std::endl;

            // p <=> q
            result.push(p == q);
        }
        else if(*i == Scanner::TOKEN_IMP) {
            bool q = result.top();
            result.pop();
            bool p = result.top();
            result.pop();

            //std::cout << "p = " << p << " q = " << q << " " << (p && !q ? false : true) << std::endl;

            // p => q
            result.push(p && !q ? false : true);
        }
    }

    return result.top();
}

void Expression::printf_rpn() {
    std::vector<int>::const_iterator i;
    for(i = this->output.begin(); i != this->output.end(); ++i) {
        if(*i == 0 || *i == 1) {
            std::cout << *i << std::endl;
        }
        else if(*i >= 'a' && *i <= 'z') {
            std::cout << (char) *i << std::endl;
        }
        else if(*i == Scanner::TOKEN_NOT) {
            std::cout << "NOT" << std::endl;
        }
        else if(*i == Scanner::TOKEN_AND) {
            std::cout << "AND" << std::endl;
        }
        else if(*i == Scanner::TOKEN_OR) {
            std::cout << "OR" << std::endl;
        }
        else if(*i == Scanner::TOKEN_IFF) {
            std::cout << "<=>" << std::endl;
        }
        else if(*i == Scanner::TOKEN_IMP) {
            std::cout << "=>" << std::endl;
        }
   }
}

void Expression::parse() {
    this->scanner.next_token();
    // Grammar start symbol
    this->parse_low_expr();
}

void Expression::parse_low_expr() {
    this->parse_high_expr();

    while(true) {
        switch(this->scanner.current()) {
            case Scanner::TOKEN_IMP:
            case Scanner::TOKEN_IFF:
            {            
                int oper = this->scanner.current();

                this->scanner.next_token();
                this->parse_high_expr();

                // Output:
                this->output.push_back(oper);
            } break;

            default: {
                return ; /* Epsilon */
            }
        }
    }
}

void Expression::parse_high_expr() {
    this->parse_value();

    while(true) {
        switch(this->scanner.current()) {
            case Scanner::TOKEN_OR:
            case Scanner::TOKEN_AND:
            {
                int oper = this->scanner.current();

                this->scanner.next_token();
                this->parse_high_expr();

                this->output.push_back(oper);
            } break;

            case Scanner::TOKEN_NOT: {
                this->scanner.next_token();

                this->parse_value();

                // Output:
                this->output.push_back(Scanner::TOKEN_NOT);
            } break;

            default: {
                return ; /* Epsilon */
            }
        }
    }
}

void Expression::parse_value() {
    switch(this->scanner.current()) {
        case '(': {            
            this->scanner.next_token(); // Skip '('
            this->parse_low_expr();
            this->scanner.next_token(); // Skip ')'
        } break;

        case Scanner::TOKEN_VAR: {
            char id = scanner.value()[0];
            if(this->symbols.find(id) == this->symbols.end()) {
                this->symbols[id] = false;
            }

            // Output:
            this->output.push_back(id);

            this->scanner.next_token();
        } break;

        case Scanner::TOKEN_TRUE:
        case Scanner::TOKEN_FALSE:
        {
            // Output:
            this->output.push_back(this->scanner.current());

            this->scanner.next_token();
        } break;
    }
}
