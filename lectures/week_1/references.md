# Functions, References, and `auto`

## Quick Recap: Functions and scope.
Recall that the *scope* defines the region in which variables 'live'. We can
find the scope of a variable simply by searching for the nearest set of `{}`.
Consider the following example:

```c++
int main()
{
    int a{0}, b{1};     // Scope of a, b is main.
    std::cout << "The value of a is " << a << std::endl;
    std::cout << "The value of b is " << b << std::endl;

    if (a == 0)
    {
        int c{10};      // Scope of c is the if-statement.
        std::cout << "The value of c is " << c << std::endl;
    }

    c = 0;              // Error: use of undeclared identifier 'c'

    {
        int a{10};      // Nested scope. a 'overshadows' main's a. 
        a = 5;          // Which a is changed?
        std::cout << "The vlaue of a is " << a << std::endl;
    }

    // What is the value of a here?
    std::cout << "The vlaue of a is " << a << std::endl;
}
```

A function is a block of code that serves a specific task or purpose and that is
re-usable. It consists of the following parts:

* Return type: can be any type, including `void`,
* function name,
* parameters.

```c++
// void: return type
// printVar: function name
// int v: parameters
void printVar(int v)
{
    // Question: what is the scope of v?
    std::cout << v << std::endl;
}
```

Function parameters can also have default values. This is a convenient way of
setting common values to input parameters and simplifies calling code.

```c++
// Here, jam has a default value of 2, but can be replaced with another number
void pbAndJ(int jam = 2)
{
   // Make sandwich. 
}

int main()
{
    pbAndJ();   // Fine, jam uses default value of 2
    pbAndJ(6);  // Fine, jam has value 6
}
```

## References
Recall that when we pass a variable to a function, we do not modify the value of
said variable. Consider a swap function, whose purpose is to swap the values of
two variables. We can start by doing the following:

```c++
void swap(int a, int b)
{
    int t = a;
    a = b;
    b = t;
}
```

Notice how this function does not change the values of `a` or `b`. In C, we
would have to use pointers to make this work, but that seems too complicated.
Instead, we are going to use *references*. There are two ways of thinking of
references:

* A pointer to a variable whose value can never be `NULL`, and once assigned
  cannot be made to point to anything else, or
* a constant proxy to a variable.

The second option is more general, as it allows us to use references as a way of
changing the name of a variable. Consider the following example:

```c++
int a{10};
int& b {a};     // b is now a reference to a
b += 1;         // What is the value of a?
a += 1;         // What is the value of both a and b?
```

Returning to our swap function, we can re-write this as follows:

```c++
void swap(int& a, int& b)
{
    int t = a;      // Fine, t now has a copy of a
    a = b;          // Replace a with b
    b = t;          // Assign the original value back
}
```

The biggest advantage of references is that they enable us to pass bigger types
without the penalty of copying. But what if we wanted to pass a big thing to a
function but prevent it from being modified? We can pass it by `const&`. Recall
that `const` qualifies what is to the left of it. Consider the following
function:

```c++
void foo(int const& a) // a is a reference to a const int.
{
    int b = a;  // Fine, b is not const.
    a = b;      // error: cannot assign to variable 'a' with const-qualified type 'const int &'
}
```

## `auto`
If the compiler knows what the type of an expression is, can't we use that to
our advantage and set the type of a variable instead of typing it? Yes! Enter
`auto`. Consider the following:

```c++
auto a{5};      // a is of type int
auto b{5.0};    // b is of type double
auto c = a * b; // c is of type double.
```

The way `auto` works is by doing a type deduction, similar to what we were doing
last time. Once the compiler deduces the type, it is set for the duration of the
life-span of the variable. It **cannot** be changed afterwards.

> **Warning:**
> `auto` does not imply that C++ is a dynamically typed language. Once the type
> for `auto` has been determined, it cannot be changed.

> **Warning:**
> Do **not** use `auto a = {9};`. The type that `a` will have is not `int`, it
> is `std::initializer_list` and will give you errors if you attempt to use it
> as an `int`. Only use `auto` like this: `auto a{6}` or `auto a = 6`.

## Vectors
Recall that C had arrays, which had a fixed type and a fixed size. Their
declaration looked like this:

```c++
int myArray[10] = {0};
```

There are, however, quite a few flaws with them:

* No boundary check. If you access an invalid index, program crashes with no
  idea of why.
* Resizing: attempting to resize an array is very difficult.
* Initialization: arrays *require* a size when they are created.
* Parameter passing: passing arrays requires to pass by pointer or by `[]`. We
  also usually need to provide the size of the array.

Fortunately, C++ has an alternative: `std::vector`:

```c++
#include <vector>

int main()
{
    std::vector<int> myVec{1, 2, 3};    // Notice the use of uniform initialization
    int a = myVec.at(0);                // Access an element in an array with at()
    myVec.push_back(10);                // Insert a new element at end
    unsigned int size = myVec.size();   // Easy access to size of vector
}
```

First, notice how we can initialize a vector with values, same as we did with
arrays. The difference here is the type: `std::vector<int>` defines a `vector`
of type `int`. The `<int>` is called the *template parameter* and defines the
type of the container. Accessing an array with `at` ensures that we get boundary
checks, so we never run off the edge of the array! Additionally, we can add a
new element at the end using `push_back`. Finally, we can always query the size
of the array by using `size`.
