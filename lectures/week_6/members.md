# Member Variables and Member Functions
Last time we gave an overview of the structure of a class and its main
components. We will now go into more detail related to the member variables and
functions from a class.

## Member Functions
Recall that *any* function declared in the scope of the class (be they public or
private) is called a member function. Since they are declared within the class,
they also have access to all other member functions and variables (regardless of
whether they be public or private). Let's see an example of this:

```c++
class Widget
{
public:
    // Constructors go here.

    void performTask()
    {
        mCounter++;     // Fine, access to member variable.
        doOtherTask();  // Fine, access to member function.
    }

private:
    void doOtherTask()
    {
        std::cout << mCounter << std::endl;
    }

    int mCounter;
};
```

In this example, `performTask` is a public function that invokes a private
function and modifies a private member. Since these are regular functions, they
can also take parameters as normal. 

## `const` Functions
Consider the following example:

```c++
class Widget
{
public:
    // Constructors go here.

    void updateWidget(int x, int y)
    {
        mX += x;
        mY += y;
    }

private:
    int mX, mY;
};
```

Now suppose that we have a function whose signature is as follows:

```c++
void run(Widget const& w)
{
    // ...
    w.updateWidget(10, 0);  // Error: 'this' argument to member function 'updateWidget' has type 'const Widget', but function is not marked const
}
```

If we attempt to run this, we would get a compiler error. Why did this happen? 
Well we notice that `w` is passed by `const&` to `run`, which means that we are
not allowed to modify w. Unfortunately, `updateWidget` modifies the internal
member variables, which violates the `const` requirement. In fact, this would be
the case with *any* function that we invoke on `w` regardless of whether they
modify the state or not. So how can we solve this?

It so happens that we can also mark member functions as `const`. What this
implies is that the function is not allowed to make *any* modifications to the
internal data of the class. By marking a member function as `const`, it can now
be invoked on any instance that is marked with the `const` qualifier.

> **Aside:**
> This pattern is actually very common in C++. As a general rule, any function
> that does not modify the state of the class should be marked as `const`. Take
> a look at the declaration of `size()` from the vector class. Notice how it's
> marked `const`? Now look at `push_back()`. Why isn't this one `const`?

## Accessing Data Members
Thus far we have marked all data members as private, which is a general practice
in C++. But it is also possible that we may want to access this data. The
question is how can we do it if it's marked as `private`?

We could just write a function that returns the value of the variable. But what
if we wanted to modify it? What then?

```c++
class Widget
{
public:
    // Constructors go here.

    int getData()
    {
        return mNum;
    }

private:
    int mNum;

};
```

Well, we could return by `int&`. But suppose we wanted this function to be
`const`. Clearly returning by `int&` bypasses the `const` qualifier, so we can't
do this. Instead, we can either return by value or return by `const&`. In fact,
this is the way that the `at()` function from vectors is implemented.

## Default Constructors/Destructors
Recall that the compiler will, in the absence of a user-defined constructor or
destructor, generate a standard constructor or destructor as needed. The
important thing to note here is that this all happens *implicitly*, and it is
sometimes hard to figure out exactly what the compiler is generating in each
instance. On the other hand, writing an empty destructor is tedious and
repetitive. So, is there a way of *explicitly* accepting the compiler-provided
constructor or destructor? Consider the following:

```c++
class Widget
{
public:
    Widget() = default;     // Fine, accept the compiler default constructor.
    ~Widget() = default;    // Fine, accept the compiler default destructor.

};
```

The `default` keyword allows us to explicitly mark constructors and destructors
that are provided by the compiler. 

> **Note:**
> This is mostly a way of saving time. It is true that all compiler provided
> constructors and destructors are *implicitly* marked as default. Without
> diving into the subtleties of this, it simply makes our code easier to read by
> clearly stating our intent.
