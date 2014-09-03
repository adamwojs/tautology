#include <iostream>
#include <fstream>
#include <wchar.h>
#include "expression.h"
#include "binarycombination.h"

void is_tautology(Expression expr) {
    bool tautology = true;

    std::map<char, bool>::iterator symbol = expr.symbols.begin();

    // Print varibles names
    for(; symbol != expr.symbols.end(); ++symbol) {
        std::cout << symbol->first << " | ";
    }
    std::cout << std::endl;

    BinaryCombination combination(expr.symbols.size());
    while(!combination.eof()) {
        const std::vector<bool>& c = combination.current();

        symbol = expr.symbols.begin();
        for(int i = 0; symbol != expr.symbols.end(); ++symbol, ++i) {
            // Assign varible
            (*symbol).second = c[i];

            // Print varible value
            std::cout << c[i] << " | ";
        }

        // Calculate expression value for assigned varibles
        bool result = expr.calculate();
        // Print result
        std::cout << result << std::endl;

        tautology &= result;

        combination.next();
    }

    if(tautology) {
        std::cout << "EXPRESSION IS TAUTOLOGY" << std::endl;
    }
    else {
        std::cout << "EXPRESSION IS NOT TAUTOLOGY" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    if(argc > 1) {
        std::fstream f(argv[1]);
        if(!f.is_open()) {
            std::cerr << "Unable to open input file: " << argv[1] << std::endl;
            return -1;
        }

        is_tautology(Expression(f));
    }
    else {
        is_tautology(std::cin);
    }

    return 0;
}
