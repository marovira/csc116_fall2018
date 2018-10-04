#include <vector>
#include <iostream>

void fill(std::vector<int>& vec, int a, int b)
{
    for (int i = a; i <= b; ++i)
    {
        vec.push_back(i);
    }
}

void print(std::vector<int> const& vec)
{
    for (auto val : vec)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector<int> vec;
    fill(vec, 0, 10);
    print(vec);
    return 0;
}
