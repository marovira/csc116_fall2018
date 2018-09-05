# Day One

## Why learn C++?
Before learning a new language, it is often useful to figure out why we are
learning this new language. In order to figure out why we will learn C++, let's
take a look at the language that we have already studied: C. Our first order of
business then, is to figure out what C is used for and where its weaknesses are.

## What is C used for? Why?

* Operating systems (Windows, Linux, OSX, iOS, Android),
* game engines,
* compilers (fun fact: both the C and C++ compilers are written in C/C++),
* real-time/embedded systems (airplane systems, robots, arduino boards,...)
* the list goes on...

The main reason why C is used in all these areas is because it's a low-level
programming language. In other words, we have the following hierarchy: machine
code (binary) -> assembly -> C.

Because C is so low-level, it also gives complete control to the programmer over
everything and is generally a very permissive language. In other words, so long
as the code is legal, one can do just about anything with C. As can be expected,
this does have it's drawbacks:

* Memory management is tedious: the programmer is in charge of *everything*,
  from allocating to freeing any and all memory.
* String manipulation is tedious: dealing with raw character arrays is often
  error-prone and can lead to difficult to read code.
* Generics are impossible to implement: suppose you have a piece of code that
  operates on `float` types. Then you want to change it to `int`. This would
  involve duplicating the code with the *only* change being replacing `float`
  with `int`. Any other data types would require similar treatment.
* Object-oriented programming is very difficult: many programming patterns can
  be expressed better using objects, which C does not natively support.
* Functional programming is not possible: parallelism is *very* tedious and
  error-prone in C, while functional programming makes this transparent.

## Why does C++ exist?
The argument against all of the above points is that there are languages, such
as Python, Java, Lua, Haskell, etc. that support many if not all of these
features and provide solutions to the problems of C. This is true, but *none*
of these languages can match the performance that C can achieve. In fact, this
is the reason why the term *native performance* exists in the first place. This
leaves a gap in terms of programming languages: a language that can be as
low-level as C but have the features that we want. This is the reason why C++
exists today.

## Hello World: C++ edition
The standard C++ hello world example looks like this:

```c++
#include <iostream>

int main()
{
    std::cout << "Hello World" << std::endl;
    return 0;
}
```

And we compile it as follows:

```sh
g++ -std=c++17 -Wall -o hello hello.cpp
```

Here `g++` is the compiler itself. `-std=c++17` sets the language standard that
we will be using. This course will focus primarily on C++17. If you are looking
online for help, you can check for relevant information by ensuring the
following keywords appear:

* Modern C++,
* C++11,
* C++14,
* C++17

At this level, there is little difference between C++11, C++14 and C++17. That
said, we will be covering features that are *exclusively* from C++17. These will
be mentioned when we cover them. To run the above code, simply execute:

```sh
./hello
```

We will now look at the code line by line. In the first line, we include
`<iostream>`. This is the equivalent of C's `<stdio.h>`. The declaration of main
should look familiar, as it is the same for C. The only difference is in how we
print. Without diving into too much detail (we will cover this later),
`std::cout` is our version of `stdout` from C. The `<<` 'pipe' whatever we want
to the 'stream'. Finally, `std::endl` has two functions:

* Insert a `\n` at the end of the line,
* Immediately print everything to standard out.

The `std::` that prepends these is called the *namespace*. For now, you can
think about namespaces as the address where these objects live in. If we want to
use them, we have to specify their 'address' followed by the name of the thing
we want to use.

## Next Time...
We will begin talking about the types that C++ supports, expressions, type
deduction, and more about `std::cout` and `std::cin`.
