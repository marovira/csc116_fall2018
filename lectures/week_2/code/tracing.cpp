#include <iostream>

int why(int a)
{
    return a * 4;
}

void madness(int& num1, int num2)
{
    auto tmp{num1};
    num1 += num2;
    num2 = why(num1);
    num1 = tmp + num2;
}

int main()
{
    int x{10}, y{16};
    std::cout << "Before madness...\n";
    std::cout << "x = " << x << ", " << "y = " << y << std::endl;
    madness(x, y);
    std::cout << "After madness...\n";
    std::cout << "x = " << x << ", " << "y = " << y << std::endl;

    return 0;
}
