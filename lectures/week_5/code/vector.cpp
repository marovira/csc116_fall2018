#include "Timer.hpp"

#include <vector>
#include <iostream>
#include <algorithm>

using atlas::core::Timer;

void fillVectorBack(std::vector<float>& vec, std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i)
    {
        vec.push_back(i);
    }
}

void fillVectorFront(std::vector<float>& vec, std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i)
    {
        vec.insert(vec.begin(), i);
    }
}

bool findVector(std::vector<float> const& vec, float elem)
{
    for (auto val : vec)
    {
        if (val == elem)
        {
            return true;
        }
    }

    return false;
}

bool findVectorSTL(std::vector<float> const& vec, float elem)
{
    return (std::find(vec.begin(), vec.end(), elem) != vec.end());
}

void traverseVector(std::vector<float> const& vec)
{
    for (auto elem : vec)
    {
        elem += 1;
    }
}

int main()
{
    Timer<std::chrono::milliseconds> timer;
    constexpr std::size_t size = 10000000;

    // Test insert at end.
    //{
        //std::vector<float> vec;
        //timer.start();
        //fillVectorBack(vec, size);
        //std::cout << "Elapsed time: " << timer.elapsed().count() << std::endl;
        //timer.reset();
    //}

    // Test insert at front.
    //{
        //std::vector<float> vec;
        //timer.start();
        //fillVectorBack(vec, size);
        //std::cout << "Elapsed time: " << timer.elapsed().count() << std::endl;
        //timer.reset();
    //}

    //// Test search.
    {
        std::vector<float> vec;
        fillVectorBack(vec, size);
        timer.start();
        findVector(vec, static_cast<float>(size - 1));
        std::cout << "Elapsed time: " << timer.elapsed().count() << std::endl;
        timer.reset();
    }

    {
        std::vector<float> vec;
        fillVectorBack(vec, size);
        timer.start();
        findVectorSTL(vec, static_cast<float>(size - 1));
        std::cout << "Elapsed time: " << timer.elapsed().count() << std::endl;
        timer.reset();
    }

    {
        std::vector<float> vec;
        fillVectorBack(vec, size);
        timer.start();
        traverseVector(vec);
        std::cout << "Elapsed time: " << timer.elapsed().count() << std::endl;
        timer.reset();
    }

    return 0;
}
