/**
 * In-class exercise 3: Ulmo
 * Provide the output for the syntactically correct C++ program below.
 */
#include <iostream>

void madness(int& a, int& b) 
{
    if (b > 10)
    {
        auto a{b + 6};
        b = a;
    }
    std::cout << a << " " << b << std::endl;
}

void into(int x, int& y) 
{
    x += 10;
    y = x;
    std::cout << x << " " << y << std::endl;
    madness(x, y);
    ++x;
}

int descend(int& a, int b) 
{
    into(a, b);
    std::cout << a << " " << b << std::endl;
    return b;
}

int main() 
{
    int x{11}, y{137}, z{401};
    x = descend(y, z);

    std::cout << x << std::endl;
    std::cout << y << " " << z << std::endl;

    return 0;
}
