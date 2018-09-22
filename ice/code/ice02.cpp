/**
 * In-class exercise 2: Varda Elentari
 * Write a syntactically correct C++ function mergeWords that given a vector of
 * strings returns a single string consisting of all the values in the vector
 * concatenated (joined) together and converted to lower-case. Your function
 * must use parameters and return types for input and output (not cin our cout).
 */
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

std::string mergeStrings(std::vector<std::string> words)
{
    std::string result{};
    for (auto word : words)
    {
        result += word;
    }

    for (auto& ch : result)
    {
        ch = std::tolower(ch);
    }

    return result;
}

int main()
{
    std::vector<std::string> vec{"Hello", "World", "again!"};
    auto merge = mergeStrings(vec);
    std::cout << merge << std::endl;
    return 0;
}
