
#include "ExpressionEvaluator.h"

#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main() {
    ExpressionEvaluator calculator;
    int choice = -1;

    do {
        std::cout << "\n====== EXPRESSION EVALUATOR ======\n";
        std::cout << "1. Evaluate Expression\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Enter a number.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        std::cin.ignore(10000, '\n');

        if (choice == 1) {
            std::string expression;

            std::cout << "Enter expression: ";
            std::getline(std::cin, expression);

            try {
                const std::vector<std::string> postfix =
                    calculator.toPostfix(expression);

                std::cout << "Postfix: ";

                for (const std::string& token : postfix) {
                    if (token == "~") {
                        std::cout << "NEG ";
                    } else if (token == "#") {
                        std::cout << "POS ";
                    } else {
                        std::cout << token << ' ';
                    }
                }

                const double result =
                    calculator.evaluatePostfix(postfix);

                std::cout << "\nResult: "
                          << std::setprecision(12)
                          << result << '\n';

            } catch (const std::exception& error) {
                std::cout << "Error: " << error.what() << '\n';
            }
        } else if (choice == 0) {
            std::cout << "Exiting calculator.\n";
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
