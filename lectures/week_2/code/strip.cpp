#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string line, char delim = ' ')
{
    std::vector<std::string> words;
    std::string word;
    bool isDelim{false};
    for (auto ch : line)
    {
        if (ch != delim)
        {
            isDelim = false;
            word.push_back(ch);
        }

        if (ch == delim && !isDelim)
        {
            words.push_back(word);
            word.clear();
            isDelim = true;
        }

        if (ch == delim && isDelim)
        {
            continue;
        }
    }

    if (!isDelim)
    {
        words.push_back(word);
    }

    return words;
}

std::string strip(std::string line, char delim = ' ')
{
    std::string result{};
    bool isDelim{false};
    for (auto ch : line)
    {
        if (ch != delim)
        {
            result.push_back(ch);
            isDelim = false;
        }

        if (ch == delim && !isDelim)
        {
            isDelim = true;
            result.push_back(ch);
        }

        if (ch == delim && isDelim)
        {
            continue;
        }
    }

    return result;
}

int main()
{
    std::string text{"Yay    it's     Friday!"};
    auto words = split(strip(text));
    for (auto word : words)
    {
        std::cout << word << std::endl;
    }

    return 0;

}
