#include <vector>
#include <string>
#include <iostream>
#include <cctype>

void invertCaps(std::vector<std::string>& words)
{
    // Iterate by reference so the changes are reflected in the vector.
    for (auto& word : words)
    {
        for (auto& ch : word)
        {
            // Check if it is uppercase. If it is, then turn to lower. If not
            // then check if it is lowercase and convert to upper. If it is 
            // neither, do nothing.
            if (std::isupper(ch))
            {
                ch = std::tolower(ch);
            }
            else if (std::islower(ch))
            {
                ch = std::toupper(ch);
            }
        }
    }
}

void print(std::vector<std::string> const& vec)
{
    for (auto val : vec)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<std::string> words{"HeLlO", "wOrLd", "AgAiN"};
    print(words);
    invertCaps(words);
    print(words);
    return 0;
}
