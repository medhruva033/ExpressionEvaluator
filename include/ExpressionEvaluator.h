
#pragma once

#include <string>
#include <vector>

class ExpressionEvaluator {
public:
    std::vector<std::string> toPostfix(
        const std::string& expression) const;

    double evaluatePostfix(
        const std::vector<std::string>& postfix) const;

    double evaluate(const std::string& expression) const;

private:
    bool isOperator(char ch) const;
    int precedence(char op) const;
    bool isRightAssociative(char op) const;
};
