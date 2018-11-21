# Smart Pointers

## Virtual Destructors
Last time we discussed how child classes could be turned into their parent class
through either a reference or a pointer. We also discussed how a child can
override a function from the parent, along with the other option which involves
overshadowing of functions. With that in mind, let us consider the following
example:

```c++
class Parent
{
public:
    Parent() = default;
    ~Parent() = default;

    virtual void foo()
    {
        std::cout << "Parent foo" << std::endl;
    }
};

class Child : public Parent
{
public:
    Child() = default;
    ~Child() = default;

    void foo() override
    {
        std::cout << "Foo" << std::endl;
    }
};

int main()
{
    using ParentPtr = std::shared_ptr<Parent>;

    ParentPtr p = std::make_shared<Child>();
    p->foo();
    return 0;
}
```

The question is the following: which destructor will get called when `p` gets
destroyed? Will it be the child or the parent?
It so happens that the **parent** destructor gets called in this case, because
the type of `p` is `Parent&`. The fact that a cast was involved is irrelevant,
and so is the fact that the `Child` class provides its own destructor. The
reason is because the child's destructor *overshadows* the parent's destructor!
So how do we get around this? We use what we already know is the fix for
overshadowing regular functions: declare the destructor as virtual.

```c++
class Parent
{
public:
    Parent() = default;
    virtual ~Parent() = default;

    virtual void foo() = 0;
};
```

This fixes the overshadowing problem as the child's destructor now overrides the
parent and the correct destructor will get invoked when we destroy an instance
of a child through it's parent class.

> **Note:**
> The problem of destructor overshadowing only occurs when the parent class
> contains *at least* one virtual member function (either regular virtual or
> pure virtual) and the casting is performed through a pointer. References are
> safe from this problem since the original child has to exist somewhere prior
> to the creation of the reference.

## Pointers in C++
We will now proceed to do a quick refresher of pointers from C. Consider the
following:

```c++
int b{10};
int* c = &b;        // Fine, c now points at b.
*c = 15;            // The value of b is now 15.
```

We will not get into the semantics of what each line does, as this has already
been covered in C and isn't that relevant to C++ (save for knowing how to get
the address of something or how to dereference a pointer). 

In C, when we wanted to create a new pointer (without taking the address of an
existing variable first), we had to do the following:

```c++
int* c = malloc(sizeof(int));
free(c);
```

This involves invoking the mysterious function `malloc` along with it's obscure
parameters and knowing that it somehow returns the pointer to the thing we want.
This seems very clunky and complicated. Moreover, we have the problem that every
time we create something with `malloc` we have to remember to use `free`. In
older C++, we had the following alternative:

```c++
int* c = new int;
delete c;
```

This seems a bit better. We have replaced `malloc` with `new` which makes the
code a bit more readable, and `free` with `delete`. In spite of this, we still
need to remember to delete anything we create. To summarize both, we have the
following:

| Operation | C | C++ (old) |
|-----------|---|-----------|
| Create | `malloc()` | `new` |
| Delete | `free()` | `delete`|
| Automatic delete? | No | No |

In modern C++ we now have two new types which are called *smart pointers*. These
are:

* `std::shared_ptr`: used when the ownership of the resource the pointer points
  at is **shared** amongst many entities.
* `std::unique_ptr`: used when the ownership of the resource the pointer points
  at is the sole responsibility of the owner.

We will discuss later the implications of these, and when to use each type of
pointer. For now, the relevant thing is what they bring to the table:

| Operation | C | C++ (old) | `std::shared_ptr` | `std::unique_ptr` |
|-----------|---|-----------|-------------------|-------------------|
| Create | `malloc()` | `new` | `std::make_shared<>()` | `std::make_unique<>()`|
| Delete | `free()` | `delete`| NA | NA |
| Automatic delete? | No | No | Yes | Yes |

While the initialization of the pointers is now a bit more verbose (though still
readable and explicit), we have gained two very important things:

* Because smart pointers are objects, we don't need to destroy them ourselves.
  It is handled automatically when they go out of scope. 
* They automatically delete their resources.

The last part is very convenient, as it enables C++ to have something akin to
"garbage collection". 

## Shared Pointers
These are by far the most common of the two smart pointers due to their
simplicity of use. A `shared_ptr` is used when the responsibility of maintaining
whatever data is held by the pointer itself is shared amongst various entities.
In this case, entities are either functions or objects. In essence, the idea of
the `shared_ptr` is the following: so long as at least **one** pointer remains
to the created data, the data will remain. This implies that the data will only
be destroyed when all of the pointers pointing to it have been destroyed.

To understand how this works, we need to understand what the `shared_ptr` does
under the hood. Consider the following line of code:

```c++
std::shared_ptr<int> a = std::make_shared<int>(10);
```

When this line of code get's executed, the following steps take place:

* A new block of memory is created to hold the integer and it's value is set to
  10.
* Alongside this block, another block is created that holds a *counter*. This
  counter is then set to 1.

The counter block is the part that we are most interested in. This keeps track
of all the **references** (i.e. all the pointers) that are currently pointing at
the data block. The destructor for the resource (the `int` in this case) will
only get invoked when this counter reaches 0. The counter is modified by the
following rules:

* Whenever a **copy** of the pointer is made, the counter increases by 1.
* Whenever a **copy** of the pointer is destroyed, the counter decreases by 1.

References do not suffer from this and do not result in any modification to the
counter. With this in mind, consider the following code:

```c++
#include <memory>

using IntPtr = std::shared_ptr<int>;

void foo(IntPtr ptr)
{
    (*ptr)++;
}

void bar(IntPtr const& ptr)
{
    std::cout << *ptr << std::endl;
}

int main()
{
   IntPtr p = std::make_shared<int>(10);    // Counter is now 1.
   auto c = p;                              // Copy made. Counter is 2.
   {
       auto d = c;                          // Copy made. Counter is 3. 
   }
                                            // d is destroyed. Counter is 2.
   foo(c);                                  // c is passed by copy. Counter is 3.
                                            // copy destroyed. Counter is 2.

    bar(c);                                 // c is passed by const&. Counter is 2.
    return 0;
    // Destruction occurs in reverse order of creation.
    // Destroy c first. Counter is 1.
    // Destroy p next. Counter is now 0. Data is now cleared.
}
```

Here we have several operations performed on a `shared_ptr` while keeping track
of the counter. Notice how passing the pointer by `const&` does not result in an
increment (or decrement) of the counter, while passing by copy does. Also notice
that once the pointers go out of scope they are destroyed and the counter is
updated.

> **Note:**
> As you may have guessed, copying `shared_ptr` involves the penalty of having
> update the reference counter. While this is irrelevant for this course, it is
> something to keep in mind. In general for time-sensitive applications, we tend
> tend to pass `shared_ptr` by reference unless we require a copy.

## Unique Pointers
While `shared_ptr` implies that everyone how has a copy is the owner,
`unique_ptr` can only be held by **one** entity at any given time (again, entity
is either a function or an object). More importantly: a `unique_ptr` **cannot**
be copied! It can only be *moved*. While we will not discuss move semantics in
great detail, the fact that the `unique_ptr` cannot be copied gives us a chance
to discuss about the `delete` keyword in terms of functions.

Suppose we have the following class declaration:

```c++
class Widget
{
public:
    Widget() = default;         // Accept compiler default constructor.
    Widget(Widget const& w) = delete;
    Widget& operator=(Widget const& w) = delete;

};
```

The meaning of `= delete` next to the copy constructor and copy assignment
operator is to **remove** these functions. This means that the are no longer
usable, and the compiler will throw an error any time that a copy operation is
attempted on the class. This is exactly how `unique_ptr` prevents copies from
taking place. This also has a very interesting consequence: **any** class that
has a `unique_ptr` as a member will have it's copy semantics deleted. This is
caused by virtue of the fact that `unique_ptr` has no way of copying itself. 

This last fact begs a very interesting question: why would we want to use a
`unique_ptr` if it has so many restrictions? The main reason is *intent*. By
using a `unique_ptr` we clearly state that no one else is allowed to take
ownership of the pointer unless we explicitly give it to them. This is actually
very useful for a common programming pattern called PIMPL.

## The PIMPL Pattern
We had previously discussed how `#include` will take the file that we want to
include and paste it's entire contents into our file. Suppose that we have a
single header file that is included by 20 other headers (this is **very**
common). These 20 headers are also included in several other files, essentially
creating a tree hierarchy of inclusion. At the bottom of the hierarchy we have
our `.cpp` files with all the implementation files. Now suppose that we made a
change to the topmost header. When we compile our code, this will result in the
**entire** tree being re-compiled. For simple cases this may be a matter of
seconds, but it can quickly escalate to hours! 

A way around this is the following: suppose that we had a class with private
member data. The class is defined in a header, which itself is included in
several files. Since we are still in development, we are constantly adding and
removing private members (note that this includes bothy data and functions).
Since the private data is only accessible from within the class itself, then it
makes no sense for other files to re-compile for changes that are *internal* to
the class. What we do instead is use the pointer to implementation (PIMPL)
patter to *hide* the private members in the `.cpp` file. This means that any
changes we make will only affect one file as opposed to the other files. The
pattern is done as follows:

```c++
class Widget
{
public:
    Widget();
    // Public data here.

private:
    struct WidgetImpl;      // Forward declaration of the struct that holds our private data.
    std::unique_ptr<WidgetImpl> mImpl;  // Unique pointer to our data.
};
```

This is done inside the header file. The `.cpp` file then has the following:

```c++
struct Widget::WidgetImpl
{
    // Private members go here.
};

Widget::Widget() :
    mImpl(std::make_unique<WidgetImpl>())
{  }
```

Any changes made to the `.cpp` file result in *just* that one file being
re-compiled. The downside of using the `unique_ptr` is that it forces us to
implement copy semantics ourselves, which may be somewhat tedious depending on
the structure of the class. The trade-off is acceptable in general, as
implementing the copy-semantics (while tedious) is better than having to wait
for long compilation times.

> **Note:**
> The deletion of constructors and operators is also used in another pattern
> has already been mentioned before: the singleton pattern. 
