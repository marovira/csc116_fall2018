#include <iostream>
#include <vector>
#include <string>

bool findElement(std::vector<int> const& vec, int elem)
{
    for (auto num : vec)
    {
        if (num == elem)
        {
            return true;
        }
    }

    return false;
}

int countLessThan(std::vector<int> const& vec, int elem)
{
    int count{0};
    for (auto num : vec)
    {
        if (num < elem)
        {
            ++count;
        }
    }

    return count;
}

std::vector<int> findLessThan(std::vector<int> const& vec, int elem)
{
    std::vector<int> result;
    for (auto num : vec)
    {
        if (num < elem)
        {
            result.push_back(num);
        }
    }

    return result;
}

int main()
{
    std::vector<int> values{0, 1, 2, 3, 4,5, 6, 7, 8, 9};

    std::cout << "Is 6 in our vector? ";
    std::cout << findElement(values, 6) << std::endl;
    std::cout << "Is 10 in our vector? ";
    std::cout << findElement(values, 10) << std::endl;

    std::cout << "The number of elements less than 7 is: ";
    std::cout << countLessThan(values, 7) << std::endl;

    std::cout << "The numbers that are less than 7 are: ";
    auto result = findLessThan(values, 7);
    for (auto num : result)
    {
        std::cout << num << " ";
    }

    std::cout << std::endl;

    return 0;
}
