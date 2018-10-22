#include <map>
#include <iostream>
#include <string>

int main()
{
    std::map<int, std::string> students;
    students.insert({1, "Bruce Wayne"});
    students.insert({2, "Alfred Pennyworth"});
    students.insert({3, "Selina Kyle"});
    
    // Indexing by key works.
    auto name = students.at(1);

    // Beware of []!
    students[4] = "Harleen Quinzel";

    // Find works as usual.
    if (auto result = students.find(4); result != students.end())
    {
        std::cout << "Found Harley Quinn!" << std::endl;
        std::cout << result->first << " " << result->second << std::endl;
        // or equivalently:
        std::cout << (*result).first << " " << (*result).second << std::endl;
    }

    // We can iterate
    for (auto& entry : students)
    {
        std::cout << entry.first << " " << entry.second << std::endl;
    }

    // Or for a fancier version (C++17 only):
    for (auto& [key, value] : students)
    {
        std::cout << key << " " << value << std::endl;
    }

    return 0;
}
