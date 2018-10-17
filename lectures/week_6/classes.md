# Introduction to Classes
So far we have used structures like vectors and lists, which ultimately are
collections of data and functions. We have already seen how we can bundle data
together using structs, but we would also like to be able to bundle
functionality along with the data. 

The idea for this is the following: while we could do every operation in a
problem ourselves, eventually the sheer number of operations that we would have
to perform at that level of control would be immense (think of the way C works).
What we would want, then, is to delegate related tasks to specific blocks in
such a way that we do not need to concern ourselves with *how* (the
implementation) things work, but *what* they do. This is the mindset behind
**object-oriented** programming: separate related tasks and data into
**objects** which can then be used without concern for their implementation
details.

With this in mind, let us take a look at how we can create our own objects in
C++:

```c++
class Widget
{
public:
    Widget()
    {  }

    ~Widget()
    {  }

    void foo()
    {
        std::cout << "Hello World" << std::endl;
    }

private:
    int mNum;
};
```

Let's ignore the contents of `Widget` for a bit, and let us look at the overall
structure. Notice how the declaration of `Widget` looks almost identical to the
one we used for structs. In fact, as far as C++ is concerned, structs and
classes are the same thing (save for a minor difference which we will look at
later on). With this out of the way, let us look at each line and figure out
what they are doing.

## `public` vs `private`
After the declaration of `class Widget` we have a new keyword: `public` and it's
relative `private`. In order to understand what these mean, we first need to
define what the scope of the class is. Anything that is declared within the
curly braces that follow `class Widget` lives in the class-scope. Anything
marked under the `private` tag can only be accessed by functions that live
within the class-scope. Anything declared under the `public` tag can be accessed
outside of the class-scope. We will look at some examples of this later, but for
now just remember the following:

* `public`: anyone outside the class can access.
* `private`: only things declared in the class-scope can access.

## Member Functions and Variables
Next, we look at the 3 functions declared: `Widget()`, `~Widget()`, and `foo()`.
These are all called member functions, though the first two have very specific
names. Any member function that carries the name of the class and does not have
a ~ in front is called a **constructor**. Functions that have the name of the
class and a ~ in front are called **destructors**. As the name implies,
*constructors* construct objects while *destructors* destroy them. 

The final thing is the data of the `Widget` class itself, here declared to be an
integer called `mNum`. This is called a member variable (or member data).

> **Note:**
> While it may be common for other programming languages (such as Java) to call
> member functions *methods*, that is not the case in C++. Since C++ is
> ultimately built on C, we call them *functions*, not methods.

> **Convention:**
> In C++ it is fairly common to prepend any member variable with either `m` or
> `m_`. This allows us to easily distinguish between regular variables and
> member variables. For this course, I will be using `m` over `m_` but this is a
> personal preference.

## Making an object
We have now seen all of the terms that we need to understand how classes are
formed. Now let's see how to use them and what these terms mean in practice.
Consider the following declaration of `Widget`:

```c++
class Widget
{
public:
    Widget()
    {  }

    ~Widget()
    {  }

    void printGreeting()
    {
        std::cout << "Hello world!" << std::endl;
    }

private:
    int mNum;
};
```

We can make a new instance of a `Widget` and use it's functions as follows:

```c++
Widget w;
w.printGreeting();
```

As we can see here, the syntax is now identical to the ones we use when
declaring a vector or when we made structs. Let us now take a look at the
implications of `public` and `private`.

## `public` and `private`
Suppose that we changed `printGreeting` to the following:

```c++
class Widget
{
public:
    // ...

    void printGreeting()
    {
        // Fine, printGreeting is part of Widget, so we have access to 
        // mNum.
        mNum += 5; 
        std::cout << "Hello world! " << mNum << std::endl;
    }

    // ...

};
```

Since `printGreeting` is declared within the class-scope of `Widget`, we have
access to any member variable (and indeed any member function) that the class
has. Now let's see what happens in main:

```c++
int main()
{
    Widget w;
    w.printGreeting();  // Fine, function declared as public so we can use it.
    w.mNum = 5;         // Error: 'mNum' is a private member of 'Widget'
    return 0;
}
```

As we can see here, we are allowed to invoke `printGreeting` because it was
declared under the `public` tag. Since `mNum` is declared under `private`, we
are not allowed to access it in main because we are outside of the class-scope.

## Constructing and Destroying an Object
Let's now take a look at how constructors and destructors work. First, let us
add something to them so we can see when they are invoked:

```c++
class Widget
{
public:
    Widget()
    {
        std::cout << "In constructor" << std::endl;
    }

    ~Widget()
    {
        std::cout << "In destructor" << std::endl;
    }
    
    // ...

};
```

Let's now use the following main:

```c++
int main()
{
    Widget w;

    return 0;
}
```

Running this code, we can see that the output of the program is:

```
In constructor
In destructor
```

Let's see if we can explain this behaviour. First, we notice that the
constructor gets invoked. This happens on the line `Widget w;`. In fact, this
line is *implicitly* calling the constructor for the `Widget` class, since it's
we are creating a new instance. 

To understand when the destructor gets called, let us see first what the *scope*
of `w` is. Notice how `w` lives inside of main, hence when we return from it,
the variable ceases to exist. As a result, the destructor will get invoked when
a variable is destroyed, which happens when it goes out of scope. Let us look at
another example:

```c++
int main()
{
    {
        Widget w;
        w.printGreeting();
    }

    return 0;
}
```

In this example, the construct is still invoked when we create `w` and is
invoked when `w` goes out of scope, which occurs at the closing brace.

## Initializing Member Variables
Thus far, the member variable `mNum` has been left in an uninitialized. When we
used structs, we provided default values for the member variables. Since we now
have constructors, we will see a more flexible way of initializing them:

```c++
class Widget
{
public:
    Widget() :
        mNum{0}     // Fine, mNum is now 0.
    { 
        // By this point, mNum is already initialized to 0.
        // This is equivalent to:
        mNum = 0;
    }

    // ...

};
```

By initializing variables in this fashion, we guarantee that by the time the
first line of the constructor executes (if any), the variables are already
initialized to their respective values. Since constructors are typical
functions, we can also pass parameters to them:

```c++
class Widget
{
public:
    Widget(int num) :
        mNum{num}       // Fine, mNum is now equal to num.
    {

    }

    // ...

};
```

## The Compiler and the Most Vexing Parse
Creating a single constructor that takes a parameter has an interesting
consequence. Recall that before, we could create a `Widget` as follows:

```c++
Widget w;
```

With our new setup, we cannot do this. Any attempt results in this:

```c++
Widget w;   // Error: no matching constructor for initialization of 'Widget'
```

So what happened? Notice that since we did not declare a constructor that takes
no parameters (an empty constructor), we cannot create `w` in this fashion. This
begs an interesting question: if classes and structs are the same, then why were
we allowed to create a struct in this fashion if we didn't define *any*
constructors?

The answer to this is the source of great pleasure and headaches for C++
developers. The compiler actually does quite a bit of work behind the scenes,
and among this is the creation of default constructors for any struct and
classes that **do not** define one themselves. When we created a struct before,
the compiler automatically generated a constructor (and destructor) for them. In
this case however, because we have elected to define our own constructor (one
that takes a parameter), the compiler will **not** create an empty constructor
for us. This explains why the new setup prevents the creation of a `Widget` with
no parameters.

Suppose that we solve this by adding an empty constructor:

```c++
class Widget
{
public:
    Widget() : 
        mNum{0}
    {  }

    Widget(int num) :
        mNum{num}
    {  }

    // ...

};
```

A common problem in C++ is to do the following:

```c++
int main()
{
    Widget w();
    w.printGreeting(); // error: request for member 'printGreeting' in 'w', which is of non-class type 'Widget()'

    return 0;
}
```

This error may come as a surprise, since most would expect `Widget w();` to
create a new widget instance. Unfortunately, this line gets parsed as: "declare
a function named `w` that takes no arguments and returns a `Widget`". This is
known as the **Most Vexing Parse** or MVP for short. This is a side-effect of
the way the compiler parses lines and has its root in C declarations. We can
solve this in one of two ways:

```c++
Widget w;       // Fine, create a Widget. Empty constructor used.
Widget w{};     // Fine, create a Widget. Emtpy constructor used.
```

> **Warning:**
> The most vexing parse is something that comes up fairly often in C++
> programming, and can lead to a great deal of frustration. The easy solution
> (and in fact one of the arguments for) is to use uniform initialization. There
> is an argument against this, but that lies beyond the scope of this course.
