#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

void print(std::vector<int> const& vec)
{
    for (auto word : vec)
    {
        std::cout << word << " ";
    }

    std::cout << std::endl;
}

int main()
{
    std::vector<int> vec{1, 2, 3, 4};

    // Sample usage of iterators.
    {
        auto it = vec.begin();
        it++;
        *it = 3;
        it++;
        it++;
        it--;
        *it = 5;
        
        // What are the values of vec?
        print(vec);
    }

    // Iterator loop.
    {
        for (auto i = vec.begin(); i != vec.end(); ++i)
        {
            std::cout << *i << std::endl;
        }
    }

    // Some examples with STL
    {
        std::sort(vec.begin(), vec.end());
        if (auto result = std::find(vec.begin(), vec.end(), 10); 
                result != vec.end())
        {
            std::cout << "10 is in our vector" << std::endl;
        }
    }

    // Vectors and iterators
    {
        vec.insert(vec.begin(), 0);
        auto it = vec.begin();
        it++;
        it++;
        vec.insert(it, 10);
        print(vec);

        std::vector<int> vec2{8, 9, 10};
        vec.insert(vec.begin(), vec2.begin(), vec2.end());
        print(vec);

        // We have modified the vector, so it is now invalid. Reset it.
        it = vec.begin();
        it++;
        it++;
        vec.insert(it, vec2.begin(), vec2.end());
        print(vec);

        it = vec.begin();
        it++;
        it++;
        vec.erase(vec.begin(), it);
        print(vec);

        vec.erase(vec.begin(), vec.end());
        print(vec);
    }

    return 0;
}
