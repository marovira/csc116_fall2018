# Case Study: A Queue
We have seen the history of templates, and we have already seen how to create
templated functions. Since C++ allows us to also template classes, we will now
discuss how to do this with a simple example: a queue.

We will be covering several topics in this discussion. As we go through,
remember that the compiler is allowed to perform type deductions. Try to guess
when the compiler is able to do so, and when it fails. In addition, try to keep
the tips we discussed when writing templates in mind. They will all be used in
one way or another.

## Designing a Queue
A queue (which typically represents a first-in-first-out or FIFO system) is
basically a list of objects that retains the FIFO property. In order to fully
showcase templates, we will not be using any containers from the standard
library. Instead, we will be using the linked list class that we used previously
when we talked about recursion. The list class is declared as follows:

```c++
class List
{
public:
    List() :
        mHead{nullptr}
    {  }

    void push_front(int value)
    {

    }

    int pop_back()
    {

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
        Node(int v) :
            data{v},
            next{nullptr}
        {  }

        Node(int v, NodePtr n) :
            data{v},
            next{n}
        {  }

        int data;
        NodePtr next;
    };

    NodePtr mHead;

};
```

Currently, the definitions for `push_front` and `pop_back` are missing. Also
notice that the list can only hold `int`. We will later see how to change this
using templates. For now, we need to fill in the missing functions.

Adding an element to the front of the list involves the following:

* Create a new node with the provided data,
* Make the next of the new node point at the head of the list,
* Make the head of the list point at the new node.

It is often useful in this situation to draw diagrams to visualize the
operations that need to be performed. With this in mind, we can implement the
function as follows:

```c++
    void push_front(int value)
    {
        auto node = std::make_shared<Node>(value);
        node->next = mHead;
        mHead = node;
    }
```

Notice that this will work even if the list is empty. Now let us look at how to
implement `pop_back`. In order to remove the final node from a list, we would
need to have a pointer to the last element and a pointer to the second to last.
However, instead of having two pointers, we can notice that by having a single
pointer on the second to last element, we can perform the operations correctly.
This implies the following operations:

* Walk the list until the second to last node is reached (assume the list is
  never empty for now).
* Create a new pointer that points at the last element,
* Set the second to last element's next to null,
* return the value of the final node.

In code, this translates to the following:

```c++
    int pop_back()
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
```

Notice that the check at the beginning is for the case when the list has only
one element. Not handling that separately would result in a crash, as this line:
`return back->data` would be trying to access a member of `nullptr` which is
invalid. As a result, we handle the case of size 1 separately. This completes
the list definitions. We are now ready to create the queue itself, which is
simply the following:

```c++
class Queue
{
public:
    Queue()
    {  }

    void push(int value)
    {
        mList.push_front(value);
    }

    int pop()
    {
        return mList.pop_back();
    }

    bool empty() const
    {
        return mList.empty();
    }

private:
    List mList;

};
```

## Generalizing the Queue
As defined, the queue is not very useful, as it can only hold one type. What we
would want, is to be able to hold *any* value. In order to accomplish this, we
use templates. We begin with the list class and then proceed to the queue.

```c++
template <typename T>
class List
{
public:
    List() :
        mHead{nullptr}
    {  }

    void push_front(T value)
    {
        auto node = std::make_shared<Node>(value);
        node->next = mHead;
        mHead = node;
    }

    T pop_back()
    {
        auto it = mHead;
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
        Node(T v) :
            data{v},
            next{nullptr}
        {  }

        Node(T v, NodePtr n) :
            data{v},
            next{n}
        {  }

        T data;
        NodePtr next;
    };

    NodePtr mHead;

};
```

So far so good. We simply replaced every instance of `int` with our new type `T`
and that's it. But what about the `Node`? Well, because we have defined the node
class within the list, then the node has access to the template parameter. 

As a thought experiment, suppose that the node class was defined outside. In
this case, we would have to template the node as well in order for it to be used
inside the list class. We would have to do the following:

```c++
template <typename T>
struct Node;        // Template the forward declaration.

template <typename T>
using NodePtr = std::shared_ptr<Node<T>>;       // Template the alias.

template <typename T>
struct Node
{
    // ...
};
```

Notice that we also have to template the alias. In C++, there are two ways of
defining aliases: `typedef` and `using`. Only `using` can be templated, and
hence is what is used in modern C++.

Finally, we also template the queue class as follows:

```c++
template <typename T>
class Queue
{
public:
    Queue()
    {  }

    void push(T value)
    {
        mList.push_front(value);
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
    List mList;
};
```

As written, the code won't compile. In order to fix it, we must specify the
template parameter on list as follows: `List<T> mList;`. But why? It is clear
from the context that the templates are connected... or is it?

It turns out that the compiler cannot make this deduction, as it is possible
that the template arguments could be different. Hence we *must* specify the
template argument.

## Initializer lists
With the design of our queue done, we would also like to use the same
initialization syntax that we used for vectors. In order to do this, we use
`std::initializer_list`. This type is very similar to a vector, except that:

* It's size is constant. We cannot add or remove elements from it.
* We cannot index into the list, we can only iterate over it using iterators or
  ranged-for loops.
* Their size (and elements) must be specified at compile time.

We can add a constructor to the list as follows:

```c++
    List(std::initializer_list<T> const& list)
    {
        for (auto elem : list)
        {
            push_front(elem);
        }
    }
```

And a similar one to the queue:

```c++
    Queue(std::initializer_list<T> const& list) :
        mList{list}
    {  }
```

## Initializer Lists and the Compiler
It is important to notice that *every* time that we write `{...}` in C++ we are
actually defining an `std::initializer_list`. While this is mostly transparent
to us in practice, it has a very interesting consequence: **any** time that a
class defines a constructor that takes an `std::initializer_list`, **every**
time that we use `{}`, it will be selected *regardless* of the types of the data
that is passed in. Moreover, the compiler can use it to determine the type of a
templated object. 

Consider this:

```c++
std::vector vec{1, 2, 3};   // T = int
```

In this case, the compiler is allowed to deduce that the template parameter of
`vec` is an `int` from the initializer list. This is bad practice in general as
the code becomes difficult to read, but it showcases how far the deductions from
the compiler go.
