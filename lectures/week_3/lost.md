# Lost and Found: Missing Topics

## Global Variables
A global variable is a variable declared outside of the scope of any function or
control block. Their scope is then the *entire* file and can be accessed by
any function.

```c++
#include <iostream>

int a{10};      // Global variable.

void foo()
{
    std::cout << a << std::endl;
}

int main()
{
    foo();
    return 0;
}
```

> **Note:** The real scope of the global variable is the entire file that we are
> in. Since most of our programs are single-file, then this is equivalent to
> saying that their scope is the entire program. As we move on to more complex
> programs, the scope of a global variable is the file that it is declared in.

> **Warning:**  The use of global variables leads to very hard to find bugs and
> unexpected program behaviour. Use with extreme caution.

## Namespaces and `using`
A common trick that appears often amongst older C++ programmers is the following
line:

```c++
using namespace std;

// ...
```

The purpose of this line is to bring the `std` namespace in (and everything
contained inside of it) to the current file so as to avoid having to
continuously type `std::`. This is usually placed in the global scope. While at
this point it is very hard to see anything wrong with this, there are some
downsides. Namespaces exist with the specific purpose of protecting names from
clashing with each other.

Consider the following example from a programmer who just knows C:

```c++
#include <algorithm>
#include <iostream>

using namespace std;

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp
}

int main()
{
    int a{10}, b{6};
    swap(a, b);         // This should not compile, but it does!
}
```

As written, the call to `swap` should have generated a compiler error, since the
types of `a` and `b` don't match with the function signature. So why does this
compile? The reason is that the `<algorihtm>` header has a `swap` function
defined which takes its parameters by reference. Hence the compiler will use
this version without any indications since we brought the entire `std`
namespace.

Now suppose that we are trying to do some operations with 3D vectors. We could
create a simple struct to hold the three variables. Consider the following:

```c++
#include <vector>
#include <iostream>

using namespace std;

struct vector
{
    float x, y, z;
};


int main()
{
    vector vec;     // What is the type of vec?    
    return 0;
}
```

If we tried to compile this we would get an error message that reads 'reference
to `vector` is ambiguous'. While this example may seem a bit contrived, it is a
sample of things that can (and often do) occur in production level code. Due to
this, it is generally considered a bad programming practice to bring the `std`
namespace (or any namespace really) into the global scope. There are, however,
other alternatives:

```c++
using std::vector;  // Fine, bring only std::vector
using std::string;  // Fine, bring only std::string

vector<int> vec;
string str{};
```

These can be placed in the global scope (though again this is not completely
advisable) but they can also be placed inside of the functions that require
them. This makes sure that the scope is contained to the scope of the function
and prevents name clashing.

> **Advise:** While it may be tempting to continue doing this (especially since
> our programs are very simple), why tempt fate? When problems arise due to
> bringing the `std` namespace, they are usually in large sets of code and they
> get very difficult and time-consuming to debug and fix.

## Function overloading
A common problem in C is having a function with a specific name but wanting
different versions of the same function with different parameters. For example:

```c++
int max(int a, int b)
{
    // ...
}

// What do we do for float, double...?
```

In C++ we can declare the same function multiple times provided the arguments of
the function change. The change can be as simple as just changing the type, to
the number of parameters. This is known as *function overloading* and is a very
common thing in C++.

## Catch-all for Exceptions
When we learned exceptions, we saw that if we wanted to catch *any* exception we
did the following:

```c++
try
{
    // ...
}
catch (std::exception const& e)
{
    // ...
}
```

We also saw that `try` can throw anything, not just exceptions. We can truly
catch anything by doing this:

```c++
try
{
    // ...
}
catch (...)
{
    // ...
}
```

This will let us catch *anything* regardless of whether it is an exception or
not. The downside of this approach is that we can only catch the exceptions, not
refer to them since `...` has no type. Hence if an error message is thrown, we
have no way of retrieving it.

## Uniform Initialization for structs
Similarly to how we can use uniform initialization to set the values in a vector
or the contents of a string, we can do the same thing with structs. Consider the
following struct from the histogram example:

```c++
struct WordData
{
    std::string word{};
    int count{0};
};
```

In the example, we set the data manually as follows:

```c++
WordData data;
data.word = word;
data.count = 1;
```

We could have also used uniform initialization to do the following:

```c++
WordData data{word, 1};
```

This has the same effect as the previous version, but has the benefit of being
much shorter. It is important to notice that the *order* in which the members
are declared in the struct should be the same as the order in which the
parameters are given in the initialization. 
