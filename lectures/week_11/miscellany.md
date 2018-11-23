# Miscellaneous Topics in Functional Programming

## Specifying the return of a lambda
So far, we have seen that the compiler is allowed to perform the deduction of
the return type of any lambda that we create. While this works fine for most
cases, it presents a problem when we have multiple return statements with
conflicting types (either intentionally or not). Consider the following example:

```c++
auto fn = [](std::vector<std::string> const& vec)
{
    if (vec.empty())
    {
        return "";
    }

    std::string str{};
    for (auto word : vec)
    {
        str += word;
    }

    return str;
};
```

As written, this will result in a compiler error, saying that "return type must
match". But why is this a problem here?
The type of the first return is `const char*`, while the type of the second
return is `std::string`. While it is true that we can convert `const char*` into
a string via one of the constructors of `std::string`, the compiler isn't
capable of making this deduction. In order to solve the problem, we can either:

* Manually ensure that the return type of all return statements within the
  lambda are consistent and return the same type, or
* Manually tell the compiler what the return of the lambda should be.

In general, it may be easier to use the second option, as it allows the compiler
to perform whatever conversions are required. To do this, we do the following:

```c++
auto fn = [](std::vector<std::string> const& vec) -> std::string
{
    if (vec.empty())
    {
        return "";
    }

    std::string str{};
    for (auto word : vec)
    {
        str += word;
    }

    return str;
};
```

The `->` syntax in the case of functions is used to specify the return type of
the function. So what we have done is tell the compiler what the return type of
the lambda will be and the code now compiles correctly.

## Capturing `this`
Suppose that we have the following (contrived) situation:

```c++
class Widget
{
public:
    Widget() :
        mNum{0}
    {  }

    void doSomething()
    {
        // Capture mNum by reference.
        auto fn = [&mNum]()
        {
            mNum++;
        };
        
        // Do something.
    }

private:
    int mNum;
};
```

The lambda `fn` needs access to the member data (private or public) of the
class, so we simply pass it through the closure and use it inside. Unfortunately
this does not compile. 

The reason why this fails is because the member variables are tied to an
*instance* of the class. In other words, they require that somewhere there be a
declaration like `Widget w;` and that `w` be made accessible to the lambda.
Since this clearly is not the case, then we are apparently stuck. However, we do
have a solution. Recall that all classes contain a pointer to the *current*
instance of the class called `this`. If we require access to the member data of
the class (variables, functions, etc.) then we can simply do the following:

```c++
class Widget
{
public:
    Widget() :
        mNum{0}
    {  }

    void doSomething()
    {
        auto fn = [this]()
        {
            mNum++;
        };
        
        // Do something.
    }

private:
    int mNum;
};
```

By capturing `this` in the closure of the lambda we have now brought the
*entire* class scope into the lambda itself by *reference*. Any changes the
lambda performs to the member variables will be reflected outside. Effectively,
this make the lambda a member of the class and can now work like any other
function.

## The Challenge
Suppose that we have a vector of data, and we want to perform certain operations
on the vector. The operations we wish to compute are:

* Compute the average,
* variance,
* standard deviation, and
* min/max.

Now it is true that we could simply implement functions to do these operations
and that's it. In order to make it interesting you are given the following
restrictions:

1. You are not allowed to use loops of any kind. That means: no ranged-for,
   iterator-for, index-for, while, do-while, or `goto`.
2. You are not allowed to create auxiliary functions. All operations must be
   defined within `main`.
3. You are allowed to use any provided functions, but you may not use any
   functional utilities from the standard library.

To aide you in your task, you are given the following set of definitions:

```c++
using UnaryOperator = std::function<float(std::vector<float> const&)>;
using BinaryOperator = std::function<float(float, float)>;
using Compute = std::function<float(std::vector<float> const&>);
```

These create new types for the different kinds of functions that we will be
using throughout this challenge. In addition, you are also given the following
functions:

```c++
void forEach(std::vector<float> const& data, UnaryOperator const& op)
{
    for (auto elem : data)
    {
        op(data);
    }
}
```

`forEach` will iterate over the vector of data and apply the `UnaryOperator`
function to each element. Notice that `UnaryOperator` does *not* return
anything. This means that any results that you want to obtain *must* be captured
through the closure of a lambda.

```c++
float accumulate(std::vector<float> const& data, BinaryOperator const& op)
{
    float result{};
    for (auto elem : data)
    {
        result = op(result, elem);
    }
    return result;
}
```

`accumulate` is used to basically "sum up" the numbers in a vector of data. In
order to do this, it takes a `BinaryOperator` which acts as the summation. The
way this is accomplished is by accumulating the result of adding the first
parameter to the second in the *first* parameter. Ultimately, this is emulating
the following: `result += elem` but in a more general way.

Using these tools together with lambdas, your task is to implement the required
operations. Here are a few hints:

* First, think carefully about what you need the operation to perform.
* When designing lambdas, it is always simpler to start with an empty closure
  and then slowly add things as required.
* Lambdas can have lambdas inside of them.
* Lambdas can capture lambdas in their closure.
* Try to re-use previously defined lambdas.

## Getting Started
To give you a starting hand, we are going to present how to implement the
`average` lambda. We begin as follows:

```c++
auto average = [](std::vector<float> const& data)
{

};
```

Notice that we don't need to capture anything (and if we do we can always add it
later) so the closure is left empty. Now, we need to iterate over the elements
of the vector and add them up. A straight-forward solution would be to use
`accumulate`. We can do the following:

```c++
auto average = [](std::vector<float> const& data)
{
    auto sum = accumulate(data, [](float x, float y) { return x + y; });
    return sum / data.size();
};
```

Since we want to accumulate the sum in `x`, all that we have to do is add `y` to
it. The last line just returns the average as expected.

An alternative formulation would've involved using `forEach`. Notice that the
`UnaryOperator` does not return anything, so we need a way of getting around
this restriction: the closure of the lambda. We do the following:

```c++
auto average = [](std::vector<float> const& data)
{
    float sum{};
    forEach(data, [&sum](float x) { sum += x; });
    return sum / data.size();
};
```

Notice that we *must* capture by reference so that the resulting sum is kept in
`sum`. If we passed by copy, we would not get the right result.

Now it's your turn! Using this example, try to figure out how to build the rest
of the operations. 

## Taking it Further
If you want more of a challenge, there is one more version of this that can be
attempted:

* Implement the same operators using recursion. You are not allowed to use any
  loops, the standard library functional utilities, or the provided functions.
  To make things easier, you are allowed to create your own auxiliary functions.
