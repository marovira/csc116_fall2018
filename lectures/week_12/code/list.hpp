#include <memory>
#include <initializer_list>

template <typename T>
class List
{
public:
    List() : 
        mHead{nullptr}
    {  }

    List(std::initializer_list<T> const& list)
    {
        for (auto elem : list)
        {
            push_front(elem);
        }
    }

    void push_front(T value)
    {
        auto node = std::make_shared<Node>(value);
        node->next = mHead;
        mHead = node;
    }

    T pop_back()
    {
        auto it = mHead;
        if (it->next == nullptr)
        {
            mHead = nullptr;
            return it->data;
        }

        while (it->next != nullptr && it->next->next != nullptr)
        {
            it = it->next;
        }
        auto back = it->next;
        it->next = nullptr;
        return back->data;
    }

    bool empty() const
    {
        return mHead == nullptr;
    }

private:
    struct Node;

    using NodePtr = std::shared_ptr<Node>;

    struct Node
    {
        Node(T value) :
            data{value},
            next{nullptr}
        {  }

        T data;
        NodePtr next;
    };

    NodePtr mHead;
};
