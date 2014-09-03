#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <map>
#include <istream>
#include <vector>
#include "scanner.h"

class Expression
{
public:
    // Symbols table
    std::map<char, bool> symbols;

    Expression(std::istream& input);

    // Return expression value
    bool calculate();

    // Print expression converted to RPN
    void printf_rpn();

protected:
    Scanner scanner;

    // Expression in RPN
    std::vector<int> output;

private:
    // Parse expression
    void parse();

    /**
      * EXPR            -> LOW_EXPR LOW_EXPR_PRIM
      * LOW_EXPR        -> HIGH_EXPR HIGH_EXPR_PRIM
      * LOW_EXPR_PRIM   -> '&' LOW_EXPR LOW_EXPR_PRIM
      *                 -> '|' LOW_EXPR LOW_EXPR_PRIM
      *                 -> Epsilon
      * HIGH_EXPR       -> VALUE HIGH_EXPR_PRIM
      * HIGH_EXPR_PRIM  -> '=>'  HIGH_EXPR HIGH_EXPR_PRIM
      *                 -> '<=>' HIGH_EXPR HIGH_EXPR_PRIM
      *                 -> Epsilon
      */

    // Low Priority Expression
    void parse_low_expr();

    // High Priority Expression: IMP and IFF
    void parse_high_expr();

    // Value
    void parse_value();
};

#endif // EXPRESSION_H
