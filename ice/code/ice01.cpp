/**
 * In-class exercise 1: Manwe Sulimo
 * Consider the following syntactically correct C++ code below. For each
 * variable used, your task is to determine the following:
 * * The type of the variable,
 * * the value of the variable.
 */
#include <iostream>
#include <typeinfo>

int main()
{
    auto expr1 = (2.0 * 3) / (1.5f * 2.0) * (1 + (4 / 3) + (6 / 7));
    auto expr2 = (expr1 / 4) * 1.0f;

    auto a{1};
    auto& b{a};
    auto c{b + 1};
    auto const& d{c};

    // Solutions:
    std::cout << "expr1: double     | " << expr1 << "\n";
    std::cout << "expr2: double     | " << expr2 << "\n";
    std::cout << "a    : int        | " << a << "\n";
    std::cout << "b    : int&       | " << b << "\n";
    std::cout << "c    : int        | " << c << "\n";
    std::cout << "d    : int const& | " << d << "\n";
    std::cout << std::endl;

    return 0;
}
