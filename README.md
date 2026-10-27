
# Expression Evaluator & Calculator (C++)

A console-based mathematical expression evaluator built using
custom linked-list stacks in C++17.

## Features

- Evaluate arithmetic expressions
- Support +, -, *, / and %
- Handle parentheses and operator precedence
- Convert infix expressions to postfix notation
- Evaluate postfix expressions using a stack
- Support decimal numbers and unary plus/minus
- Detect invalid expressions and mismatched parentheses
- Handle division and modulo by zero

## Data Structures

The project implements a generic stack using a singly linked list.

- Operator stack: used during infix-to-postfix conversion.
- Value stack: used during postfix evaluation.

## Project Structure

```text
ExpressionEvaluator/
├── include/
│   ├── Stack.h
│   └── ExpressionEvaluator.h
├── src/
│   ├── Stack.cpp
│   ├── ExpressionEvaluator.cpp
│   └── main.cpp
├── README.md
└── .gitignore
```

Note: Stack template implementations are defined in Stack.h.

## Requirements

- GCC/G++ compiler
- C++17 or later
- Visual Studio Code (recommended)

## Compile

Run from the project root:

```cmd
g++ -std=c++17 -Wall -Wextra -Wpedantic -Iinclude src\main.cpp src\ExpressionEvaluator.cpp -o calculator.exe
```

## Run

```cmd
.\calculator.exe
```

## Example Expressions

| Expression | Result |
|---|---:|
| 12 + 3 * 4 | 24 |
| (12 + 3) * 4 | 60 |
| 100 / (5 * 2) | 10 |
| -5 + 2 | -3 |
| 10 % 3 | 1 |
| 3.5 * 2 | 7 |

## Concepts Demonstrated

- Stack and LIFO operations
- Linked lists and pointers
- Infix-to-postfix conversion
- Operator precedence
- Expression parsing
- Exception handling
- C++ templates and classes

## Limitations

- Supports arithmetic operators only.
- Does not support exponentiation or variables.
- Uses double-precision floating-point arithmetic.
- Does not support implicit multiplication such as 2(3).

## Future Improvements

- Add exponentiation
- Support variables and named constants
- Add automated unit tests
- Improve numerical overflow handling

## Author

Dhruva M. K.

GitHub: https://github.com/medhruva033
