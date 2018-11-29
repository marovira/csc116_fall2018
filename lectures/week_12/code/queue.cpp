#include "list.hpp"
#include <iostream>

template <typename T>
class Queue
{
public:
    Queue()
    {  }

    Queue(std::initializer_list<T> const& list) :
        mList{list}
    {  }

    void push(T val)
    {
        mList.push_front(val);
    }

    T pop()
    {
        return mList.pop_back();
    }

    bool empty() const
    {
        return mList.empty();
    }

private:
    List<T> mList;
};

int main()
{
    Queue<int> q{1, 10, 100, 1000};

    while (!q.empty())
    {
        auto val = q.pop();
        std::cout << val << std::endl;
    }
    return 0;
}
