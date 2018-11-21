# Introduction to Functional Programming in C++

## What is Functional Programming?
Before we answer this question, we need to figure out what kind of language C++
actually is. In order to do this, let us take a look at the structure of C++:

* At the bottom, we have C. Essentially, anything that C can do, C++ can do as
  well. Any C++ compiler can compile C code (but not the other way around).
* C with objects: this is where we started learning C++. Basically it's treating
  the language as if it where C with the addition of a few new classes (vectors,
  maps, etc.)l
* Object-Oriented Programming (OOP): This is where the concepts of inheritance
  and polymorphism fit in.

Note that each new part contains the other, and it is possible to use them
somewhat independently of each other (so we can write pure C, but we can also
bring the standard library and use C with classes for example). Due to this C++
is a multi-modal language. 

That said, C++ also falls under another category of languages: *imperative*.
Other examples of imperative languages include: C, Python, Java, Fortran,
amongst others.
So what exactly is an imperative language? Basically, an imperative language is
a language that expresses it's intent through *commands* or *instructions*.
Consider the following simple code:

```c++
std::vector<int> vec{1, 2, 3, 4, 5};
int sum {0};
for (std::size_t i{0}; i < vec.size(); ++i)
{
    sum += vec.at(i);
}
```

Every line of code is telling us what to do:

* First make a vector of integers,
* then make a variable called `sum` of type `int`,
* next iterate over every index of the vector and,
* add up the value of `sum` to the value of the current index of the vector.

In this context functions are literally just bundles of instructions that we
save for future use. The main issue with imperative programming is that it's
very difficult to read once the code becomes more complex. For example, we could
attempt to read the implementation details for `std::vector` but we would
quickly realize that the code is mostly illegible. In general, most code in C++
that is sufficiently complex will look like this.

The question that we could pose is the following: what if instead of having
instructions be our smallest unit, we used operations (what functions ultimately
represent)? Then the code would be comprised of function calls and operations to
be performed on data. This is the main idea behind *functional* or *declarative*
programming. 

C++ has a layer that can do functional programming, but it is not a full
functional language (for that see Haskell, which is a pure functional language).
As a matter of fact, pure functional languages do not have:

* for-loops (or any iteration for that matter),
* if/else statements (or other branching).

So what does this actually look like? Let us re-write the above code using the
functional library of C++:

```c++
#include <algorithm>

std::vector<int> vec{1, 2, 3, 4, 5};
int sum {0};
std::for_each(vec.begin(), vec.end(), [&sum](int a) { sum += a; });
```

Or even better:

```c++
std::vector<int> vec{1, 2, 3, 4, 5};
auto sum = std::accumulate(vec.begin(), vec.end(), 0);
```

Notice that all 3 versions of the code are **identical** to each other and do
the same thing. They are just expressed differently.

## "Type" of Functions
So if we are going to move from instructions to operations (i.e. functions), we
need to figure out what their type is. After all, C++ is still a statically
typed language, so we need to know which types we're dealing with.
Consider the following C++ functions:

```c++
void foo();
void bar();
void baz();
```

What they all have in common is that they all return `void` and take no
arguments. We can think of functions in a very similar way to variables, where
`int a` declares a variable called `a` of type `int`. In the first line, we
declare a variable (function) called `foo`. But what is its type?

In reality, the types of functions is very complex and difficult to remember.
Fortunately, the standard library provides us with a very convenient wrapper,
which we will use and refer to as the "type" of the function. The type looks
like this:

```c++
#include <functional>

std::function<ret(params)> fn;
```

The template arguments to `std::function` consist of the following two things:

* The return type,
* open  `(`, the parameters to the function (if any), close `)`.

So in the above case, we could say that we declared a variable called `foo` of
type `std::function<void()>`.

## The anatomy of a lambda
We will now introduce the concept of a lambda, which is fundamental in
functional programming (at least as far as C++ is concerned). A *lambda* is
basically a function that we can create on-the-fly. It behaves in the exact same
way as any variable we can declare, and like any function we can invoke. The
syntax for a lambda and its invocation are as follows:

```c++
auto fn = []() { std::cout << "Hello!" << std::endl; };
fn();
```

We always use `auto` for the type of a lambda. Their real type is very difficult
to guess, and although we could still use `std::function<...>`, it is better to
let the compiler do the deductions. 

The next bit is the `[]`. This is called the **closure** of a lambda. Basically
what a closure does is it allows us to bring variables from outside the function
into the scope of the lambda. Consider the following:

```c++
int a{0};
auto add = []() { a++; };
add();
```

This won't compile, because `a` is not declared in the scope of the lambda. Now
it's tempting to think that because the scope of the lambda lives within the
bigger scope of wherever `a` and `add` are declared, then it should have it.
This is **false**. The scope of the lambda is completely independent (and in
fact *separate*) from the scope that is was declared in. So what if we need a
variable inside the lambda? Well we simply add it to the closure as follows:

```c++
int a{0};
auto add = [&a](){ a++; };
```

Closures obey the same rules as parameters for functions so:

* Capturing a variable as `[a]` captures by *value*,
* Capturing a variable as `[&a]` captures by *reference*.

Additionally to these two, we have two special captures:

* `[=]` captures **everything** (within the same scope) that was declared
  *prior* to the declaration of the lambda by value. 
* `[&]` captures **everything** (within the same scope) that was declared
  *prior* to the declaration of the lambda by reference.

The rest of the lambda is identical to a regular function. `()` denotes the
parameters that the lambda takes (if any), and `{};` denotes the body of the
lambda (notice the semicolon at the end).

## Using Lambdas
Based on this, we can write the following simple example with lambdas:

```c++
std::vector<int> vec{1, 2, 3, 4, 5};
std::for_each(vec.begin(), vec.end(), [](int a) { std::cout << a << std::endl; });
```

Notice that this is equivalent to just iterating over the vector and printing
values as with a regular for-loop.
