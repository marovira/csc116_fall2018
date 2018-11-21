#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>

int main()
{
    // Let's add a vector (imperative mode)
    {
        std::vector<int> vec{1, 2, 3, 4, 5};
        int sum{0};
        for (std::size_t i{0}; i < vec.size(); ++i)
        {
            sum += vec.at(i);
        }
        std::cout << "Sum is: " << sum << std::endl;
    }

    // Add a vector (functional)
    {
        std::vector<int> vec{1, 2, 3, 4, 5};
        int sum{0};
        std::for_each(vec.begin(), vec.end(), [&sum](int a) { sum += a; });
        std::cout << "Sum is: " << sum << std::endl;
    }

    // Add a vector (functional v2)
    {
        std::vector<int> vec{1, 2, 3, 4, 5};
        auto sum = std::accumulate(vec.begin(), vec.end(), 0);
        std::cout << "Sum is: " << sum << std::endl;
    }

    return 0;
}
