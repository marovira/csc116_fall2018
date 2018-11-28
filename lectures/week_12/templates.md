# Introduction to Templates

## A Brief History of Templates
In order to understand templates in a post-C++11 world, we must first understand
how templates came about and why. This will also help solidify our understanding
of other concepts in C++ that we have used in one way or another without really
knowing what was happening underneath.

A common situation that is found in C is the following: consider the following
code:

```c++
int sum(int x, int y)
{
    return x + y;
}
```

Clearly, the code structure would remain *identical* if we wanted to compute the
sum of a float, or a double, or any other fundamental type. However, since C
does not support function overloading, we are faced with a problem. The way this
was solved (and is still very much used today) is to do the following:

```c++
int sumi(int x, int y)
{
    return x + y;
}

float sumf(float x, float y)
{
    return x + y;
}

double sumd(double x, double y)
{
    return x + y;
}
```

The C standard library on the other hand simply implements one version with the
highest precision available and relies on casting (implicit or explicit) to get
the rest. Either way, it is clear that these two solutions have problems. If we
wanted to change the logic of the `sum` function, we would have to make the
exact same change in *all* versions of the function. Using the C approach
involves casting, which may result in precision errors that would otherwise not
happen.

C++ introduced function overloading when it was first created in 1979. While it
does simplify the problem of having to change the name of the function, it
doesn't solve the underlying problem. So what would we want as a solution?

Ideally, what we would want is to somehow *abstract* away the concept of the
type in the function. In essence, we would want to somehow do the following:

```c++
<type> sum(<type> x, <type> y)
{
    return x + y;
}
```

Where the `<type>` tags would be replaced with *any* type that we wanted. The
thing is that C++ is ultimately a *statically typed* language, so *everything*
must have a type. To satisfy this, we could simply replace the tag that we have
written before with an arbitrary type, which we call `T`:

```c++
T sum(T x, T y)
{
    return x + y;
}
```

But this is not the whole story. `T` is a *dependent* type. This means that it
depends on the type that is used when the function is created. In order to
express this, we use the keyword `typename`. This now completes what is now
known as a **template** in C++:

```c++
template <typename T>
T sum(T x, T y)
{
    return x + y;
}
```

It is worth noting that when templates were first introduced in 1990, there were
no other programming languages that could do anything similar. This concept is
called *generic* programming and was pioneered by C++.

> **Note:**
> It is interesting to note that while templates were introduced in 1990, the
> `typename` keyword was not introduced until 1994. Before this, C++ used `class`
> as the type of the template parameter. While nowadays `typename` is very much
> preferred, `class` is still used in order to help with readability.

### Template and Type Deduction
Templates can ultimately be thought of as objects that are instantiated. Every
time we create a template with a different type, a new *copy* of the code is
created. In order to accomplish this, the compiler performs the following steps:

1. Replace every instance of the typename with the specified type.
2. Compile the code according to the normal rules of C++.

Now consider the following invocation of `sum`:

```c++
int s = sum<int>(1, 2);
```

Looking at this line, it is very clear from the type of the arguments that the
template should be instantiated using `int`, which makes the actual
specification of the template argument redundant. In order to avoid this, the
C++98 standard permitted the compiler to perform *type deductions* on templates
based on the context of the code. This enabled programmers to replace the
previous line with:

```c++
int sum = sum(1, 2);    // Type of 1, 2 is int. Compiler deduces T = int
```

The idea of performing type deductions based on context is not new to us. After
all, that is exactly the way that `auto` works. It is important to notice
however, that template deductions *predate* `auto`. In fact, `auto` is just an
*extension* of template type deduction and uses *exactly* the same rules that
templates do. So if we are able to deduce the type that the compiler assigns to
`auto`, we are able to deduce the type that the compiler assigns to a template
and vice-versa. 

> **Note:**
> The fact that the compiler is allowed to perform such deductions is **very**
> important to keep in mind when writing C++ templates. As we will see, the way
> that the compiler deduces types is actually very clever, and unfortunately can
> lead to bugs that may seem hard to debug.

### Compiler Optimizations and Template Metaprogramming
If providing the compiler with the ability to perform type deductions wasn't
enough, the compiler is also allowed (but not required to) perform certain
optimizations to our code. This ability has existed prior to the creation of C++
Consider the following:

```c++
int a = 10, b = 12;
int c = a + b;
```

As written, it is evident that the value of `c` will be 22. Well, it so happens
that this fact is also evident to the compiler. So much so in fact, that the
compiler is allowed (but again, not required to) perform the following
optimization:

```c++
int a = 10, b = 12, c = 22;
```

This, paired with the introduction of the keyword `const` lead to an interesting
realization. If the compiler knows the values of certain constants at
compile-time, then what is stopping it from performing computations for us?
In C++11, the keyword `constexpr` was introduced. The main difference between
`const` and `constexpr` is the following:

* `const` is a constant that is enforced at runtime and **may** be used at
  compile-time.
* `constexpr` is a constant that is enforced at runtime and **is** available at
  compile-time.

The combination of `constexpr` and templates lead the development team of C++ to
the realization that templates *could* be used to compute things! It was later
discovered that this "programming language" is able to compute anything that
other programming languages can. This is known as *template metaprogramming*.

> **Note:**
> The discovery of template metaprogramming was completely by accident. More
> more surprising than this was the fact that it was "Turing complete" (meaning
> that anything that can be computed by a computer can be done with templates).

### The Problem with Templates
So, if the combination of templates and the compiler is so powerful, why isn't
it used more openly in C++? Why isn't everything done with template
metaprogramming?

While it is true that templates are tremendously powerful, they also have some
severe drawbacks:

1. They *cannot* be debugged easily. Since the code is ultimately run by the
   compiler, any attempt to debug would result in debugging the compiler itself,
   which is simply not possible.
2. The error messages that the compiler produces are not easy to understand.
   This is something that is improving (C++17 helped a lot with this), but they
   are still cryptic and take a lot of skill and knowledge to understand.
3. Templated code is notoriously difficult to read. Again, C++17 helped in this
   regard, but it is still difficult to figure out what templated code is
   actually doing.

That being said, if used carefully, templates are a very powerful tool that
solve many problems and allow us to produce code that is *very* clean and
readable. 

## Making a Template
As we have seen, whenever we want to create a template we do the following:

```c++
template <typename/class T>
<return> <function-name>(<parameters>)
{
    // ...
}
```

Any type that should be templated is now replaced with `T`.This can be used
*anywhere* in the function: from the return type to the parameters and to any
types within the function itself. We can also replace certain expressions with
`auto` to aide in readability.

Some tips on writing with templates:

* Always template the type that the function will take. The fact that the type
  itself could be a template is irrelevant and should not be considered unless
  necessary.
* Whenever writing templates, always consider an example type and write the code
  with that in mind. It will make the abstraction step simpler.
* Remember: the compiler will perform checks to ensure that any type that is
  used in the template satisfies the required operations, so there is no need to
  worry about this.

With this in mind, let us write a function that can print any collection:

```c++
template <typename T>
void printCollection(T const& collection)
{
    for (auto elem : collection)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
```

And here's an example use of this function:

```c++
std::vector<int> vec{1, 2, 3};
std::set<float> set{1, 2, 3};
std::string str{"Some random text"};

printCollection(vec);   // T = std::vector<int>
printCollection(set);   // T = std::set<int>
printCollection<std::string>(str);      // T specified in parameter.
```
