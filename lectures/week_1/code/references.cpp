#include <iostream>

void swap(int& a, int& b)
{
    int t{a};
    a = b;
    b = t;
}

void printVal(int const& a)
{
    std::cout << a << std::endl;
}

int main()
{
    int x{0}, y{1};
    std::cout << "Before swap: x = " << x << ", y = " << y << std::endl;
    swap(x, y);
    std::cout << "After swap: x = " << x << ", y = " << y << std::endl;
    printVal(x);
}
