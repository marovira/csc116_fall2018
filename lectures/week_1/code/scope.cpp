#include <iostream>

int main()
{
    int a{0}, b{1};     // Scope of a, b is main.
    std::cout << "The value of a is " << a << std::endl;
    std::cout << "The value of b is " << b << std::endl;

    if (a == 0)
    {
        int c{10};      // Scope of c is the if-statement.
        std::cout << "The value of c is " << c << std::endl;
    }

    //c = 0;              // error: use of undeclared identifier 'c'

    {
        int a{10};      // Nested scope. a 'overshadows' main's a. 
        a = 5;          // Which a is changed?
        std::cout << "The value of a is " << a << std::endl;
    }

    // What is the value of a here?
    std::cout << "The vlaue of a is " << a << std::endl;
}
