#include <iostream>
#include <vector>
#include <algorithm>

struct Print
{
    Print() :
        lineNum{0}
    {  }

    void operator()(int n)
    {
        std::cout << "Line (" << lineNum << "): " << n << std::endl;
        lineNum++;
    }

    int lineNum;
};

int main()
{
    std::vector<int> vec{1, 2, 3, 4};

    // Using a functor.
    std::for_each(vec.begin(), vec.end(), Print());

    // Now using lambdas.
    {
        int lineNum{0};
        std::for_each(vec.begin(), vec.end(), 
                [&lineNum](int n)
                {
                    std::cout << "Line (" << lineNum << "): " << n << std::endl;
                    lineNum++;
                });
    }

    return 0;
}
