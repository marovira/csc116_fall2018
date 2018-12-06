/**
 * In-class exercise 11: Eru Iluvatar
 */

#include <iostream>
#include <memory>

template <typename T>
class List
{
public:
    List() : 
        head{nullptr}
    {  }

    void push_front(T value)
    {
        auto node = std::make_shared<Node>(value);
        node->next = head;
        head = node;
    }

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

    NodePtr head;
};

// Your function here.
template <typename T>
T removeIndex(std::size_t i, List<T>& list)
{
    auto it = list.head;
    std::size_t index{};
    while (it->next != nullptr && index < (i - 1))
    {
        it = it->next;
        index++;
    }

    auto pop = it->next;
    it->next = pop->next;
    return it->data;
}

template <typename T>
void printList(List<T> const& list)
{
    auto it = list.head;
    while (it != nullptr)
    {
        std::cout << it->data << " ";
        it = it->next;
    }
    std::cout << std::endl;
}

int main()
{
    List<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    printList(list);

    auto val = removeIndex(1, list);

    printList(list);

    return 0;
}
