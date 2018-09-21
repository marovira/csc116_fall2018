#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> split(std::string const& str, char delim = ' ')
{
    // Iterate over each character.
    std::vector<std::string> words{};
    std::string word{};
    bool isSpace{false};
    for (auto ch : str)
    {
        // If the current character is not the delimiter, add it to the string.
        if (ch != delim)
        {
            isSpace = false;
            word.push_back(ch);
        }

        // If it is the delimiter and it's the first time we have seen it, then
        // the word is done. Save it on the vector and clear it for the
        // next time.
        if (ch == delim && !isSpace)
        {
            isSpace = true;
            words.push_back(word);
            word.clear();
        }
        
        // If it is the delimiter and we have seen it before, then we don't
        // care, continue.
        if (ch == delim && isSpace)
        {
            continue;
        }
    }

    // Check the final value of isSpace. If it ended in spaces, then
    // we do nothing. If it didn't, then save the word.
    if (!isSpace)
    {
        words.push_back(word);
    }

    return words;
}

int main()
{
    std::string text{"Some,random,text,with,no,purpose"};
    std::cout << "Started with: " << text << std::endl;
    auto words = split(text, ',');
    std::cout << "After split: \n";
    for (auto& word : words)
    {
        std::cout << word << "\n";
    }

    std::cout << std::endl;

    return 0;
}
