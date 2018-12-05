# Bonus Round
The material covered in these notes is beyond the regular scope of this course
and it is here mostly for general interest. We will be covering two main things:

* A simple example of template metaprogramming and,
* a list of suggested topics to continue studying in C++.

## Template Metaprogramming
As it happens, we have already been using template metaprogramming without even
realizing it. Last time, we discussed a few ideas on how to solve problems using
templates. Turns out that the more advanced solutions actually employed template
metaprogramming. We will now see a more evident example.

When we discussed recursion, we saw how to compute the Fibonacci sequence. What
if we could compute the sequence at compile-time? Let's see how it can be done:

```c++
template <int N>
struct Fibonacci
{
    static constexpr int value{Fibonacci<N - 1>::value + Fibonacci<N - 2>::value};
};

template <>
struct Fibonacci<0>
{
    static constexpr int value{0};
};

template <>
struct Fibonacci<1>
{
    static constexpr int value{1};
};
```

There's a few things happening here, so let's go in order. First, notice that
we're templating the struct by integers. This is perfectly valid, and it simply
means that we can only use integers as the template parameter. In general, you
are allowed to use *any* type at compile-time **provided** that the type has a
way of being initialized at compile-time. In short, we can use values that have
constructors marked as `constexpr`. For more details concerning this, see the
next section.

The inside of the struct is pretty simple. We are declaring a static variable
because we can't operate at compile-time on an instance of the struct. We
declare it `constexpr` so it can be used at compile-time, and we define the
value using the recursive definition of Fibonacci.

The remaining two structs are *overloads* of the template that specialize on two
values: 0 and 1, which constitute the base-cases of recursion. Remember:
templates are recursive by nature as there are no loops in template
metaprogramming. So how do we use this?

```c++
int main()
{
    std::cout << Fibonacci<20>::value << std::endl;
    return 0;
}
```

Here's the interesting part: because of the way we defined the structs, the
compiler **will** compute the 20th Fibonacci number at compile-time. This means
that by the time the program starts running, `Fibonacci<20>::value` is now a
numerical constant!

So why is this helpful? Clearly the computation of the Fibonacci numbers isn't
that big of a deal computationally speaking, so how is this helpful in real
life?

The answer is in what template metaprogramming *does*:

* It generates code (templates generate code regardless) and
* it moves computations from runtime to compile-time.

This means that we can allow certain code generation steps to take place at
compile-time instead of runtime, which could possible increase the performance
of our code and possibly increase code readability. Admittedly these are topics
for a 4th year course, but it still interesting to know that this is possible.

## Additional Topics
This course on its own provided the majority of the foundations for modern C++.
That said, there are several other topics to learn if the goal is to have
fluency in C++. The following list is a partial suggestion of topics to explore.
They are organized roughly in ascending level of difficulty, and they should be
studied in order. Some references are provided.

* General tricks: `explicit` constructors
  ([1](https://en.cppreference.com/w/cpp/language/explicit)),
  ternary/conditional operator
  ([1](https://en.cppreference.com/w/cpp/language/operator_other)),
* Move semantics: rvalue vs lvalue types, universal references, `&&`,
  move-constructors and move-assignment operators
  ([1](https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers),
  [2](https://www.fluentcpp.com/2018/02/06/understanding-lvalues-rvalues-and-their-references/)).
* Compiler type deduction rules ([1](https://www.aristeia.com/TalkNotes/C++TypeDeductionandWhyYouCareCppCon2014.pdf)).
* Variadic templates and perfect-forwarding
  ([1](https://eli.thegreenplace.net/2014/variadic-templates-in-c/)).

Another topic to explore are general programming patterns. Some suggestions
include:

* Singleton pattern,
* PIMPL idiom,
* CRTP (curiously recurring template pattern),
* Factory pattern,
* Generalized functors, etc.

The books in the references page by Scott Meyers and Andrei Alexandrescu are
invaluable assets when learning how to program in C++.
