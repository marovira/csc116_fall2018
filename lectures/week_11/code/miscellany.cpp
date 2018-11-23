#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>

class Widget
{
public:
    Widget() :
        mNum{0}
    {  }

    void doSomething()
    {
        // Capture 'this' to have access to the members.
        auto fn = [this]()
        {
            mNum++;
        };
        fn();
    }

private:
    int mNum;
};

int main()
{
    // Specifying the return of a lambda.
    {
        std::vector<std::string> vec{"h", "e", "l", "l", "o"};
        auto fn = [](std::vector<std::string> const& vec) -> std::string
        {
            if (vec.empty())
            {
                return "";
            }

            std::string str{};
            for (auto word : vec)
            {
                str += word;
            }

            return str;
        };

        auto result = fn(vec);
        std::cout << result << std::endl;
    }

    // Capturing this
    {
        Widget w;
        w.doSomething();
    }

    return 0;
}
