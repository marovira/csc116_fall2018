#include <iostream>
#include <string>
#include <vector>
#include <set>

template <typename T>
T sum(T x, T y)
{
    return x + y;
}

template <typename T>
void printCollection(T const& collection)
{
    for (auto elem : collection)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> vec{1, 2, 3};
    std::set<float> set{1, 2, 3};
    std::string str{"Some random text"};

    printCollection(vec);   // T = std::vector<int>
    printCollection(set);   // T = std::set<int>
    printCollection<std::string>(str);      // T specified in parameter.
    return 0;
}
