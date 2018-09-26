#include <vector>
#include <iostream>
#include <stdexcept>

int maxVal(std::vector<int> const& vec)
{
    if (vec.empty())
    {
        throw std::invalid_argument("Cannot compute maximum of an empty vector!");
    }

    int max{-1000};
    for (auto val : vec)
    {
        if (val > max)
        {
            max = val;
        }
    }

    return max;
}

void foo()
{
    throw std::runtime_error("Error 1");
}

void bar(int a)
{
    try
    {
        foo();
    }
    catch (std::exception const& e)
    {
        std::cout << e.what() << std::endl;
    }

    if (a == 2)
    {
        throw std::runtime_error("Error 2");
    }
}

void baz()
{
    for (int i = 0; i < 8; ++i)
    {
        bar(i);
    }
}

int main()
{
    try 
    {
        baz();
    }
    catch (std::runtime_error const& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
