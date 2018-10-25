# Operators
We have seen how to add functionality to our classes by adding member functions,
and how to add data through member variables. That said, there have been several
instances where we want to do certain things, such as adding a custom object
into a set, and have been unable to do so. In order to solve this problem (and
many others in fact), we are going to use *operator overloading*.

## What are operators?
Consider the following:

```c++
auto b = 1 + 2;
```

Initially, we simply see this as an operation that adds 1 and 2 and assigns the
result to `b`. However, we can change the way we view this by doing the
following:

```c++
auto b = sum(1, 2);
```

Where `sum()` does what you would expect. Notice that these two statements are
equivalent to each other. In fact, all operations in C++ are ultimately calls to
functions that perform the required task. For fundamental types, these functions
do not exist in code (not directly anyway as they are embedded in both the
compiler and the hardware itself) but for any other type, there is a function
somewhere that performs a specific operation. To this end, these functions are
called **operators** and are declared as follows:

```c++
<return-type> operator<operator-type>(<params>);
```

This syntax is identical to when we declare any function. The only new term here
is the addition of the `operator` keyword.

## Types of operators
There's a list that you can see
[here](https://en.cppreference.com/w/cpp/language/expressions). We will be
primarily focusing on arithmetic operators, though these are by no means the
only ones. 

Beyond the types of operators, there are two ways in which we can add an
operator to an object: as a member function, or as a regular function. Let us
look at member functions first.

## Member operators
Consider the following class:

```c++
class Complex
{
public:
    Complex() :
        mReal{0.0f},
        mImaginary{0.0f}
    {  }

    Complex(float r, float i) : 
        mReal{r},
        mImaginary{i}
    {  }

private:
    float mReal, mImaginary;
};
```

We would like to be able to add other numbers to this class. For now, we will
focus on adding real numbers, and later on we can extend this to add complex
number (as the logic is generally the same). To do this, we can declare an
operator as follows:

```c++
class Complex
{
public:
    // ...
    Complex operator+(float rhs)
    {
        Complex c(mReal + rhs, mImaginary);
        return c;
    }

};
```

Let's take a look at what this operator is doing. Generally speaking, we
consider *binary* operators (that is, operators that take two arguments). Since
`+` is clearly binary, then where is the second argument coming from?

If an operator is defined as a member function, then the left-hand side argument
of the operator is the class **itself**. So in this case, we have defined an
operator that can add `float` on the right of the `Complex` class. Accordingly,
since the operator is a member function, it has access to the internals of the
class and everything works as expected. 

Now suppose that we wanted to add a complex number to a complex number. Well, we
can easily do this as follows:

```c++
class Complex
{
public:
    //...
    Complex operator+(Complex const& rhs)
    {
        Complex c(mReal + rhs.mReal, mImaginary + rhs.mImaginary);
        return c;
    }

};
```

Notice that because both the right and left-hand side of the operator have the
same type, then the operation is fully commutative. This leads to the problem of
making the addition by a real number commutative as well.

## Friend functions
Since having an operator declared inside the class itself implies that the type
of the left-hand side is the class, then we need to declare the operator
outside. We could then do the following:

```c++
class Complex
{
    //...
};

Complex operator+(float lhs, Complex const& rhs)
{
    //...
}
```

There is a problem with this code: because the new operator function is outside
of the class, it no longer has access to the private members, which would make
the implementation impossible. Fortunately, C++ provides a way of bypassing the
`private` property by way of a new keyword: `friend`. Let us look at how we
could use it:

```c++
class Complex
{
public:
    //...
    friend Complex operator+(float lhs, Complex const& rhs);

};

Complex operator+(float lhs, Complex const& rhs)
{
    Complex c{rhs.mReal + lhs, rhs.mImaginary};
    return c;
}
```

Notice that compiling this code works without errors. So what is happening then?
The `friend` keyword allows the following: if a **function** is marked as
`friend`, then that function is allowed access to all the private members of the
class (even though the function exists beyond the scope of the class). There are
a few notes to this:

1. The function must be declared **inside** the class.
2. The function signature (including return type and parameters) must be
   **identical**.

Part one makes sense, if we look at it from the permission stand-point. Only an
element *inside* the class is allowed to give permissions about the class
itself. Hence why the declaration of the friend function must be done within the
class (though the actual implementation cannot be done inside, otherwise we
would be trying to implement a member function). The second point revolves
around the true name of a function. A function is ultimately uniquely identified
(at least for now, we will later see how this is not always the case) by its
return type, name, and parameters (all the elements of the function signature).
In order for the compiler to be able to match the functions, the signatures must
match.
