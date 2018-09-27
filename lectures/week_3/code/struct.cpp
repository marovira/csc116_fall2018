#include <vector>
#include <string>
#include <iostream>
#include <fstream>

struct WordData
{
    std::string word{};
    int occurrences{0};
};

int find(std::vector<WordData> const& vec, std::string const& word)
{
    int idx = 0;
    for (auto elem : vec)
    {
        if (elem.word == word)
        {
            return idx;
        }
        ++idx;
    }

    return -1;
}

std::vector<std::string> split(std::string const& line, char delim = ' ')
{
    // Iterate over each character.
    std::vector<std::string> words{};
    std::string word{};
    bool isSpace{false};
    for (auto ch : line)
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

void printStats(std::vector<WordData> const& data)
{
    for (auto entry : data)
    {
        std::cout << entry.word << " : " << entry.occurrences << std::endl;
    }
}

int main()
{
    std::string filename{"text.txt"};
    std::ifstream file;
    file.open(filename);
    std::vector<WordData> stats;

    if (file.is_open())
    {
        std::string line{};
        while (std::getline(file, line))
        {
            // Split the line first.
            auto words = split(line);

            for (auto word : words)
            {
                auto idx = find(stats, word);
                if (idx != -1)
                {
                    stats.at(idx).occurrences++;
                    continue;
                }

                WordData data;
                data.word = word;
                data.occurrences = 1;
                stats.push_back(data);
            }
        }

        printStats(stats);
        file.close();
    }

    return 0;
}
