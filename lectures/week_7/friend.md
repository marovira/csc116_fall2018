# The `friend` Keyword
Recall that last time we discussed a way of declaring an operator whose
left-hand side was not the class by adding it as a friend to the class. We had
the following example:

```c++
class Complex
{
public:
    // ...
    friend Complex operator+(Complex const& rhs);

private:
    // ...
};

Complex operator+(Complex const& rhs)
{
    // ...
}
```

This enabled the `operator+` function to access the private members of the class
even though it is declared outside. As it happens, the `friend` keyword works
with more than just operators. We can also declare regular functions as well as
classes as `friend`. 

Consider the following example:

```c++
class Complex
{
public:
    // ...
    friend float length(Complex const& c);  // Fine, length is now friend.
};

float length(Complex const& c)
{
    // ...
}
```

In this instance, the `length` function is **not** a member function, but it is
still allowed to access the private members of the class since it was declared
`friend`. We can also declare classes as follows:

```c++
class Widget
{
public:
    // ...
    friend class Window;
};

class Window
{
    // ...
    void addWidget(Widget const& w)
    {
        // We now have access to w's private data here.
    }
};
```

By declaring the `Window` class as a friend, we have given access to **all**
instances of the `Window` class access to the private data of any `Widget`.

## Summary ##
 We have seen several things for classes: public/private, static, friend, etc.
 When and how these keywords are used is entirely dependent on the design and
 what we are trying to accomplish. That being said, here is a **very** general
 rule of thumb for the use cases (these are mostly for illustration, and based
 on cases I have seen through my travels in C++):
 
* `friend` tends to be used more for operators than anything else. There are
  cases where they are used for functions, but they tend to be very specific
  use cases. Classes is something that is very rare.
* `static` is used for one of the following:
  * Helper functions (like your assignment),
  * Functions that either create a new instance of a class on *very* specific
    and sometimes convoluted circumstances, or by populating an instance.
  * The static singleton pattern (see
    [here](https://sourcemaking.com/design_patterns/singleton)).
* `public`/`private`: these are the bread and butter of classes. Determining
  what should be public or private is very dependent on what we want to
  accomplish and whether things should be visible to others. Take a look at some
  of the classes in the [Atlas framework](https://github.com/marovira/atlas) and
  try to see if you can determine why things are public or private.

## Miscellaneous Topics

### Declaration vs Implementation of Classes.
In general, we seldom declare and implement a class in the same place (as we
have been doing thus far). As with your assignment, classes are generally
declared in a header file, while the implementation details are placed in a
separate file. For our `Complex` class, we could have done the following:

* In `Complex.hpp`:

```c++
// Add any necessary headers here.

class Complex
{
public:
    Complex();
    Complex(float r, float i);

    Complex operator+(Complex const& rhs);
    Complex operator+(float r);

    // ...
private:
    float mReal, mImaginary;
};
```

* In `Complex.cpp`

```c++
#include "Complex.hpp"      // Include header.

Complex::Complex() :        // Define default constructor.
    mReal{0.0f},
    mImaginary{0.0f}
{  }

Complex::Complex(float r, float i) :    // Define other constructor.
    mReal{r},
    mImaginary{i}
{  }

Complex Complex::operator+(Complex const& rhs) // Define operator+
{
    // ...
}

// ....
```

Notice that we append every function signature with `Complex::`. This is to make
sure that when we compile our code, the compiler knows that the functions that
we are implementing in our `cpp` file correspond with the ones that we declared
in the header. This is a **very** common way of organizing our code. We will
later see that there are times when we need to implement everything in the
header itself, but generally this is the way code tends to be implemented.

### The `inline` Keyword
To understand `inline` we first need to understand what `#include` does. Every
time that we write `#include` in our code, what the compiler ultimately does is
to take the contents of the file we are including and pasting them to our file.
Now suppose that we define a function in a header. What happens when we include
that header in 3 different files? 

In this case, we end up with 3 copies of the same function, and compilation
fails. To avoid this, we declare the function in the header `inline`. This tells
the compiler that there is only one instance of the function (even if it is
repeated by other files including it) and everything works correctly. 

> **Note:**
> There is another meaning for `inline`, which involves an optimization that can
> (but not always) be done by the compiler. If you wish to know more, see
> [here](https://en.cppreference.com/w/cpp/language/inline)
