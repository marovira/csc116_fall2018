# Copy Semantics
So far, we have seen two types of constructors:

* Empty (default) constructors, and
* Parametrized constructors.

While these two have covered several use-cases so far, let us consider what
happens when we want to perform the following two operations:

```c++
Widget w;
Widget w2{w};       // Create a new Widget that is a copy of w.
auto w3 = w;        // Assign one widget to another by copy.
```

These two are examples of copy semantics, which we will now discuss. We begin
with the simplest form: copy constructors.

## Copy Constructors
Similarly to default and parametrized constructors, a copy-constructor performs
a *copy* of the given instance of the class. As a result, the constructor has
the following signature:

```c++
class Widget
{
public:
    Widget() = default;     // Default constructor.
    Widget(Widget const& w) // Copy-constructor.
    {

    }
};
```

The copy construct has the same process as the regular constructors, the only
difference being that **all** member variables get initialized to the same
values as the provided instance.

> **Note:**
> There is an idea in C++ called the "Rule of Zero". This rule states that
> unless our class requires special semantics, we should always accept the
> default constructor that the compiler provides. This is true for copy
> semantics and it's relative move semantics (which we will see briefly later
> on).

Before we
dive into copying, we first need to examine a special pointer that exists within
all classes: `this`.

## `this` Pointer
**Every** class has within it, a pointer to the **current** instance of the
class, called `this`. The use of this pointer falls under two categories:

* A way to disambiguate variable/function names, or
* A way to refer to the current instance.

The first use case is fairly trivial, and basically involves doing the
following:

```c++
class Widget
{
public:
    // Constructors here ...
    void process(int data)
    {
        this->data = data;  // Variable names are the same, use this
        this->push_back(data);      // Refferring to our push_back.
    }

    void push_back(int t)
    {
        
    }

private:
    int data;
};
```

While this is fairly common, it does lead to code that is somewhat clunky. A
better solution is to use a naming convention for variables, which completely
bypasses the need for this pattern. That said, there are times (rare) where this
is necessary.

The second use case crops up in operators and other functions that need to
return the **current** instance of the class. Consider the following operator:

```c++
class Complex
{
public:
    // Constructors here...
    Complex& operator+=(float rhs)
    {
        mReal += rhs;
        return *this;       // Return a reference to ourselves.
    }

    // ...
};
```

Operators that have an `=` in them (`+=`, `-=`, `*=`, etc.) all return a
reference to the current instance. The reason for this is fairly
straight-forward. When we do the following:

```c++
Complex c{1.0f, 2.0f};
c += 5.0f;
```

What we are expecting happens is that the *current* instance of the Complex
class gets incremented by 5. On the other hand, if we do this:

```c++
auto d = c + 5.0f;
```

We expect a *new* instance to be created with the result. This is the reason why
we return a reference to the current class via `*this`.

> **Aside:**
> Admittedly this is not the only reason why we do this. There is also an
> optimization involved that reduces the number of copies created. While this is
> a reasonable argument, the analysis is outside of the scope of this course.

In fact, a very common programming pattern is to implement the following two
operators in sequence:

```c++
class Complex
{
public:
    // Constructors here...

    Complex& operator+=(float rhs)
    {
        mReal += rhs;
        return *this;
    }

    Complex operator+(float rhs)
    {
        Complex result{this};
        result += rhs;
        return result;
    }
};
```

By implementing `+=`, we have now reduced the `+` operator into a trivial
function. This same strategy can be used in the comparison operators:

```c++
class Complex
{
public:
    // Constructors here...

    bool operator==(Complex const& rhs)
    {
        return (mReal == rhs.mReal) && (mImaginary == rhs.mImaginary);
    }

    bool operator!=(Complex const& rhs)
    {
        return !(*this == rhs);
    }
};
```

Again we have now reduced the `!=` operator to a single line.

Now that we have the knowledge of `this`, we can now look at the copy-assignment
operator. The syntax is the following:

```c++
class Complex
{
public: 
    // Constructors here...
    Complex& operator=(Complex const& rhs)
    {
        mReal = rhs.mReal;
        mImaginary = rhs.mImaginary;
        return *this;
    }

};
```

As we can see here, the copy-assignment operator does what it says: creates a
copy of the provided instance and returns a reference to ourselves. For the most
part, copy assignment operators should not be implemented **unless** we have
very good reasons to do so (by the Rule of Zero). Regardless, it is still
important that to know that they exist and what they look like.

An interesting experiment to try involves implementing a simple class with all
the constructors we have seen so far **plus** the assignment operator. Each
function should have a call to `std::cout` in it. Can you predict the number of
lines of output in a simple program? Can you see how the copy constructor can
get invoked constantly?

> **Aside:**
> The main motivation for always using `const&` is to avoid having to invoke the
> copy constructors constantly when we pass values around. As applications grow,
> the time we spend copying things grows as well, so it is important to reduce
> copies as much as possible.

> **Extra (1):**
> In the `code/` directory there is a full implementation of the Complex class
> described here. Try adding the following line: `auto d = a + 5.0f;` at any
> point after the declaration of `a`. Notice how neither the copy constructor or
> the copy-assignment operator gets called. If this intrigues you, take a look
> at the definition of *rvalue* and start looking into *move* semantics. We will
> briefly look at these later on once we talk about smart pointers.
