#include <vector>
#include <string>
#include <iostream>

bool repeats(std::vector<std::string> const& words)
{
    for (std::size_t i{0}; i < words.size(); ++i)
    {
        for (std::size_t k{0}; k < words.size(); ++k)
        {
            if (i == k)
            {
                continue;
            }

            if (words.at(i) == words.at(k))
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    std::vector<std::string> text1{"Some", "random", "text", "again"};
    std::vector<std::string> text2{"some", "random", "some", "text"};
    std::cout << repeats(text1) << std::endl;
    std::cout << repeats(text2) << std::endl;

    return 0;
}
