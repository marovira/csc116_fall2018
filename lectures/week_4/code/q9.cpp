#include <vector>
#include <string>
#include <iostream>

bool find(std::vector<std::string> const& words, std::string const& word)
{
    for (auto w : words)
    {
        if (w == word)
        {
            return true;
        }
    }

    return false;
}

std::vector<std::string> repeats(std::vector<std::string>const& words)
{
    std::vector<std::string> result;
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
                // First check if we have seen this word before.
                if (!find(result, words.at(i)))
                {
                    result.push_back(words.at(i));
                }
            }
        }
    }

    return result;
}

void print(std::vector<std::string> const& vec)
{
    if (vec.empty())
    {
        std::cout << "No elements in vector" << std::endl;
        return;
    }

    for (auto val : vec)
    {
        std::cout << val << " ";
    }

    std::cout << std::endl;
}

int main()
{
    std::vector<std::string> text1{"Some", "random", "text", "again"};
    std::vector<std::string> text2{"some", "random", "some", "text"};
    auto rep1 = repeats(text1);
    auto rep2 = repeats(text2);

    print(rep1);
    print(rep2);

    return 0;
}
