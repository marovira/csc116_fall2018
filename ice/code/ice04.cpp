/**
 * In-class exercise 4: Yavanna Kementari
 *
 */
#include <iostream>
#include <set>

bool equal(std::set<int> const& s1, std::set<int> const& s2)
{
     if (s1.size() != s2.size())
     {
         return false;
     }

    for (auto e : s1)
    {
        if (s2.find(e) == s2.end())
        {
            return false;
        }
    }

    return true;
}

// Another possible solution.
bool equal2(std::set<int> const& s1, std::set<int> const& s2)
{
    return (s1 == s2);
}

int main()
{
    std::set<int> s1{1, 2, 3, 4, 5};
    std::set<int> s2{2, 3, 1, 5, 4};

    std::cout << equal(s1, s2) << std::endl;
    return 0;
}
