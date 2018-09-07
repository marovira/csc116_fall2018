# Types, Expressions, Type Deduction, and `const`

As C++ is the successor of C, it supports the same types, but it also adds many
more. As a result, we will use the following terminology:

* A *fundamental type* is a type that is supported by default by the compiler
  without the necessity of including any additional headers.
* A *standard-library type* is a type that requires the inclusion of a header
from the standard library and is pre-pended with `std::`.

That said, C++ supports the following fundamental types:

* `char`: character types,
* `int`: integral type,
* `float, double`: floating point types,
* `bool`: boolean type. Values are `true` or `false`.

It also supports the following *modifier* keywords:

* `unsigned`: positive integral type, for example 0, 1, and 999. Can also work
  with character types.
* `long`: extends the size of the type. Works with integral and floating point.
* `short`: reduces the size of the type. Works with integral values.
* `long long`: increases the size even more. Only works with integral types.

## Quick Review: Statements, Expressions, and Type deductions
A *statement* is a line of code that performs some action. You can usually
identify a statement by the `;` at the end, but it can also have `{}` in its
vicinity. An expression is a series of computations.

```c++
int x;                  // Statement
float a, b;             // Compound statement
x = 2;                  // An expression.
a = 2.0f / 5.0f * x;    // Another expression.
if (x == 5)             // A conditional statement.
{
    x = 10;
}
```

Since C++ is a statically typed language, *every* expression results in a type.
```c++
int a = 8;                      // 8 is integral, so type of a is int
float b = 8.0f;                 // 8.0 is a floating type, adding f explicitly marks it as float
int c = (2.0f / 3) * (4 / 6);   // Resulting type of rhs is int with value 0
float d = (3 / 2) * (4 / 5.0f); // Resulting type of rhs is float with value 0.8
```

## Initializing variables, C++ edition.
In C, we would initialize a variable as follows:

```c++
int a = 6;  // Fine, initialize a with 6
int b;      // Declare b
b = 7;      // Fine, b is now 7
```

In C++, we initialize variables using *universal initialization*:
```c++
int a{6};   // Fine, initialize a with 6
int b;      // Declare b 
b = 7;      // Fine, b is now 7
b = {7};    // Fine, but risky, can lead to problems later on
```

The main reason we do this is that it allows the compiler to do type-checking
for us to ensure that nothing unexpected happens. Consider the following
example:

```c++
int a{6};       // Fine, type of 6 is int
float b{5.0f};  // Fine, type of 5.0f is float
int c{6.0};     // Error: type 'double' cannot be narrowed to 'int'
bool d{5};      // Error: constant expression cannot be narrowed to type 'bool'
```

Note that if we had used the `=` initialization, these lines would've compiled
correctly, but the result is implementation defined. 

> **Note:**
> While it is common to initialize fundamental types with `=`, you should
refrain from using it. Not only is it against C++17 standards, but it will also
help you get used to the syntax as we will be heavily using it later on.

## Making things constant with `const`

There are often times when we want to create variables that represent constants.
For example, the acceleration due to gravity, coefficients of friction, etc.
In C, we would have done one of two things:

```c++
int g = 9.8;            // What stops me from changing g?
#define GRAVITY 9.8     // Don't use macros.
```

Option one is flawed since there is nothing stopping us from changing the value
of the variable `g`. On the other hand, option two involves using a macro, which
in turn foregoes type checks by the compiler and are therefore not good
practice. But what if instead we created a variable that the compiler *enforces*
should never be changed?

```c++
int a{6};
a += 1;             // Fine, a is now 7.
int const b{10};
b += a;             // Error: cannot assign to variable 'b' with const-qualified type 'const int'
a = b;              // Fine, a is not const.
b = a;              // Error: cannot assign to variable 'b' with const-qualified type 'const int'
```

`const` is a bit weird in it's syntax, but it has a simple set of rules:

* `const` will qualify anything to the *left* of it.
* Exception: if `const` is the left-most thing, then it qualifies what is to the
  right.

```c++
int const a{10};    // Fine, a is of type 'const int'
const int b{10};    // Fine, b is of type 'const int'
```
The trick with `const` is to read the line from left to right. So `int const a`
is read as: 'a is of type int and is const (or const int)'. Both ways shown
above are common, but we will use the first one, as it avoids some ambiguities
later on. The use of `const` really shines when we use it with functions.

> **Aside 1**
> There's a relative of `const` called `constexpr`. It has some additional
benefits than plain `const`. Read
[here](https://en.cppreference.com/w/cpp/language/constexpr) if you want to know
more. Can you see a use for `constexpr` over `const`?

> **Aside 2**
> There are times when we wish to convert one type into another. For example,
suppose that we wish to convert a parameter that is given to us of type `float`
to `int`. Since we cannot use a simple assignment as universal initialization
forbids it, we need to use an alternative. For this we use `static_cast`. Read
[here](https://en.cppreference.com/w/cpp/language/static_cast) if you want to
know more.

## Input and Output

Last class we mentioned that `std::cout` was the equivalent of C's `printf`.
While it may be true that both print, `std::cout` is more powerful than
`printf`. The main reason for it is that it is *type-safe*. In other words,
whenever you use the `<<` to send to `std::cout` the compiler will check that
the type you are sending supports being sent! This will become important once we
get into the library types. For now, if we want to print we do:

```c++
int a{10}, b{6};
float c{12.0f};

std::cout << "The value of a is " << a << "\n";         // Add a new line but don't print to screen
std::cout << "The value of b is " << b << "\n";
std::cout << "The value of c is " << c << std::endl;    // Now print.
```

Now suppose we wanted to go the other way, and read something from the user.
Consider the following:

```c++
int a{0};

std::cout << "Please enter a value: ";
std::cin >> a;
std::cout << "Entered: " << a << std::endl;
```

Usually, whenever we deal with user input, it is necessary to perform
error-checking. With `cin`, error checking looks like this:

```c++
#include <limits>
#include <iostream>

int main()
{
    int a{0};
    std::cout << "Please enter a value: ";
    std::cin >> a;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input detected." << std::endl;
    }
    else
    {
        std::cout << "Entered " << a << std::endl;
    }

    return 0;
}
```

`cin.fail()` checks the error flag that is set whenever `cin` is unable to
perform the conversion from the input to the required type. If this is the case,
it is set to `true`. Next, we call `cin.clear()`, which clears out the error
flag, allowing us to check for errors next time we need to grab input from the
user. The final line is a bit tricky, so let's go through it one piece at a
time:

* `std::cin.ignore()`: the purpose of this function is to tell `cin` to ignore
  whatever input it was given. If no arguments are passed, then it will ignore a
  *single* character of input.
* `std::numeric_limits<>`: think of it as a way of retrieving certain special
  numerical values.
* `std::streamsize`: this represents the size of the container where input can
  be held.
* `std::numeric_limits<std::streamsize>::max()`: putting it all together, what
  this line says is: get the maximum size that we can hold as input. Sending
  this value to `std::cin.ignore()` tells it to throw the *entire* line of input
  away.
* The final parameter to `std::cin.ignore()` tells it the following: throw out
  the line until one of two things happen: either we reach the number of
  characters specified in the previous argument, *or* we encounter this
  character. 

So all in all, what the line says is this: throw away everything in `std::cin`
until you either reach the maximum size we can hold, or until you see a `\n`.

## Next Time...
We will cover: scope and functions, references, and `auto`.

