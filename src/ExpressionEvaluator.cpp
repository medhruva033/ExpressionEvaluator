
#include "ExpressionEvaluator.h"
#include "Stack.h"

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <vector>

bool ExpressionEvaluator::isOperator(char ch) const {
    return ch == '+' || ch == '-' || ch == '*' ||
           ch == '/' || ch == '%';
}

int ExpressionEvaluator::precedence(char op) const {
    if (op == '~' || op == '#') return 3; // Unary minus/plus
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

bool ExpressionEvaluator::isRightAssociative(char op) const {
    return op == '~' || op == '#';
}

std::vector<std::string> ExpressionEvaluator::toPostfix(
    const std::string& expression) const {

    if (expression.empty()) {
        throw std::invalid_argument("Expression cannot be empty.");
    }

    std::vector<std::string> output;
    Stack<char> operators;

    bool expectOperand = true;
    int parentheses = 0;
    std::size_t i = 0;

    while (i < expression.size()) {
        const unsigned char ch =
            static_cast<unsigned char>(expression[i]);

        if (std::isspace(ch)) {
            ++i;
            continue;
        }

        // Parse integer and decimal numbers.
        if (std::isdigit(ch) || expression[i] == '.') {
            if (!expectOperand) {
                throw std::invalid_argument(
                    "Missing operator between operands.");
            }

            const char* start = expression.c_str() + i;
            char* end = nullptr;
            std::strtod(start, &end);

            if (end == start) {
                throw std::invalid_argument("Invalid number.");
            }

            std::string number(
                start,
                static_cast<std::size_t>(end - start));

            output.push_back(number);
            i += number.size();
            expectOperand = false;
            continue;
        }

        const char op = expression[i];

        if (op == '(') {
            if (!expectOperand) {
                throw std::invalid_argument(
                    "Missing operator before '('.");
            }

            operators.push(op);
            ++parentheses;
            ++i;
            expectOperand = true;
            continue;
        }

        if (op == ')') {
            if (expectOperand || parentheses == 0) {
                throw std::invalid_argument(
                    "Invalid or unmatched parentheses.");
            }

            while (!operators.isEmpty() &&
                   operators.peek() != '(') {
                output.push_back(
                    std::string(1, operators.pop()));
            }

            if (operators.isEmpty()) {
                throw std::invalid_argument(
                    "Mismatched closing parenthesis.");
            }

            operators.pop(); // Remove '('
            --parentheses;
            ++i;
            expectOperand = false;
            continue;
        }

        if (isOperator(op)) {
            char currentOp = op;

            // Detect unary plus/minus, such as -5 or 2 * -3.
            if (expectOperand) {
                if (op == '-') {
                    currentOp = '~';
                } else if (op == '+') {
                    currentOp = '#';
                } else {
                    throw std::invalid_argument(
                        "Operator is missing a left operand.");
                }

                // Unary operators are right-associative.
                // Push directly; do not pop pending binary operators.
                operators.push(currentOp);
                ++i;
                continue;
            }

            // Handle binary operators using precedence.
            while (!operators.isEmpty() &&
                   operators.peek() != '(' &&
                   (precedence(operators.peek()) >
                        precedence(currentOp) ||
                    (precedence(operators.peek()) ==
                         precedence(currentOp) &&
                     !isRightAssociative(currentOp)))) {

                output.push_back(
                    std::string(1, operators.pop()));
            }

            operators.push(currentOp);
            ++i;
            expectOperand = true;
            continue;
        }

        throw std::invalid_argument(
            "Invalid character in expression.");
    }

    if (expectOperand) {
        throw std::invalid_argument(
            "Expression ends with an operator or is incomplete.");
    }

    if (parentheses != 0) {
        throw std::invalid_argument("Mismatched parentheses.");
    }

    while (!operators.isEmpty()) {
        const char op = operators.pop();

        if (op == '(') {
            throw std::invalid_argument("Mismatched parentheses.");
        }

        output.push_back(std::string(1, op));
    }

    return output;
}

double ExpressionEvaluator::evaluatePostfix(
    const std::vector<std::string>& postfix) const {

    Stack<double> values;

    for (const std::string& token : postfix) {
        // Unary minus and unary plus.
        if (token.size() == 1 &&
            (token[0] == '~' || token[0] == '#')) {

            if (values.isEmpty()) {
                throw std::invalid_argument(
                    "Invalid unary expression.");
            }

            double value = values.pop();

            if (token[0] == '~') {
                value = -value;
            }

            values.push(value);
            continue;
        }

        // Binary operators.
        if (token.size() == 1 && isOperator(token[0])) {
            if (values.size() < 2) {
                throw std::invalid_argument(
                    "Invalid expression: missing operand.");
            }

            const double right = values.pop();
            const double left = values.pop();
            double result = 0.0;

            switch (token[0]) {
                case '+':
                    result = left + right;
                    break;

                case '-':
                    result = left - right;
                    break;

                case '*':
                    result = left * right;
                    break;

                case '/':
                    if (right == 0.0) {
                        throw std::domain_error(
                            "Division by zero.");
                    }
                    result = left / right;
                    break;

                case '%':
                    if (right == 0.0) {
                        throw std::domain_error(
                            "Modulo by zero.");
                    }
                    result = std::fmod(left, right);
                    break;
            }

            if (!std::isfinite(result)) {
                throw std::overflow_error(
                    "Result is outside the supported range.");
            }

            values.push(result);
            continue;
        }

        // Parse a numeric token.
        char* end = nullptr;
        const double value = std::strtod(token.c_str(), &end);

        if (end == token.c_str() ||
            *end != '\0' ||
            !std::isfinite(value)) {
            throw std::invalid_argument("Invalid numeric token.");
        }

        values.push(value);
    }

    if (values.size() != 1) {
        throw std::invalid_argument("Invalid expression.");
    }

    return values.pop();
}

double ExpressionEvaluator::evaluate(
    const std::string& expression) const {

    const std::vector<std::string> postfix =
        toPostfix(expression);

    return evaluatePostfix(postfix);
}
