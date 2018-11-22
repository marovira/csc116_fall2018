#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

struct Node
{
    Node(int d) :
        data{d}
    {  }

    std::shared_ptr<Node> next;
    int data;
};

using NodePtr = std::shared_ptr<Node>;

struct List
{
    NodePtr head;

    void insert(int a)
    {
        auto newNode = std::make_shared<Node>(a);

        if (head == nullptr)
        {
            head = newNode;
            return;
        }

        newNode->next = head;
        head = newNode;
    }
};

void printForwards(List const& l)
{
    if (l.head == nullptr)
    {
        return;
    }

    auto it = l.head;
    while (it != nullptr)
    {
        std::cout << it->data << std::endl;
        it = it->next;
    }
}

void printRecurse(NodePtr const& p)
{
    if (p == nullptr)
    {
        return;
    }

    printRecurse(p->next);
    std::cout << p->data << std::endl;
}

void printBackwards(List const& l)
{
    printRecurse(l.head);
}

int main()
{
    List l;
    l.insert(4);
    l.insert(3);
    l.insert(2);
    l.insert(1);
    printForwards(l);
    std::cout << std::endl;
    printBackwards(l);

    return 0;
}
