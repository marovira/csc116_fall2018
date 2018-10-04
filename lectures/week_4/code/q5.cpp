#include <string>
#include <iostream>

// There are two possible variants of this: we can either use substr or we can
// the function ourselves. Here are both versions.
std::string substring1(std::string const& str, int start, int end)
{
    return str.substr(start, end);
}

std::string substring2(std::string const& str, int start, int end)
{
    std::string sub{};
    for (int i = start; i <= end; ++i)
    {
        sub.push_back(str.at(i));        
    }

    return sub;
}

int main()
{
    std::string text{"Supercalifragilisticexpialidocious"};
    std::cout << text << std::endl;
    auto sub1 = substring1(text, 1, 10);
    std::cout << sub1 << std::endl;
    auto sub2 = substring2(text, 1, 10);
    std::cout << sub2 << std::endl;

    return 0;
}
