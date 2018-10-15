#include "Timer.hpp"

#include <list>
#include <iostream>
#include <algorithm>

using atlas::core::Timer;

void fillListBack(std::list<float>& list, std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i)
    {
        list.push_back(i);
    }
}

void fillListFront(std::list<float>& list, std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i)
    {
        list.push_front(i);
    }
}

bool findList(std::list<float> const& list, float elem)
{
    for (auto val : list)
    {
        if (val == elem)
        {
            return true;
        }
    }

    return false;
}

bool findListSTL(std::list<float> const& list, float elem)
{
    return (std::find(list.begin(), list.end(), elem) != list.end());
}

void traverseList(std::list<float> const& list)
{
    for (auto elem : list)
    {
        elem += 1;
    }
}

int main()
{
    Timer<std::chrono::milliseconds> timer;
    constexpr std::size_t size = 10000000;

    // Test insert at end.
    {
        std::list<float> list;
        timer.start();
        fillListBack(list, size);
        std::cout << "Elapsed time: " << timer.elapsed().count() << std::endl;
        timer.reset();
    }

    // Test insert at front.
    {
        std::list<float> list;
        timer.start();
        fillListBack(list, size);
        std::cout << "Elapsed time: " << timer.elapsed().count() << std::endl;
        timer.reset();
    }

    // Test search.
    //{
        //std::list<float> list;
        //fillListBack(list, size);
        //timer.start();
        //findList(list, static_cast<float>(size - 1));
        //std::cout << "Elapsed time: " << timer.elapsed().count() << std::endl;
        //timer.reset();
    //}

    //{
        //std::list<float> list;
        //fillListBack(list, size);
        //timer.start();
        //findListSTL(list, static_cast<float>(size - 1));
        //std::cout << "Elapsed time: " << timer.elapsed().count() << std::endl;
        //timer.reset();
    //}

    //{
        //std::list<float> list;
        //fillListBack(list, size);
        //timer.start();
        //traverseList(list);
        //std::cout << "Elapsed time: " << timer.elapsed().count() << std::endl;
        //timer.reset();
    //}

    return 0;
}
