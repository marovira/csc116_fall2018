# Exceptions
Suppose that we are tasked with writing a function that finds the maximum
element of a vector. We could write the following function:

```c++
int maxVal(std::vector<int> const& vec)
{
    int max{-1000};     // Initialize to a very small number.
    for (auto num : vec)
    {
        if (num > max)
        {
            max = num;
        }
    }

    return max;
}
```

> **Aside:** The way we initialized our `max` variable is a bit fragile, as it
> assumes that the vector will not contain elements smaller than -1000. Recall
> when we wanted to clear out the contents of `std::cin` after an invalid read.
> We used `std::numeric_limits<std::streamsize>::max()`. With this in mind, we
> could initialize max to be the smallest possible number an integer can hold.
> How would we accomplish this?

Given the current function, we have a bit of a problem: what happens if the
vector is empty? What should the function return when asked to compute the
maximum of an empty vector?

Consider the following example: you are tasked to write a `log` function. What
happens when you are given a negative number?

There are times when we simply cannot return from a function successfully and we
wish to notify the calling function that an error has occurred. What we do in
this case is to throw an exception:

```c++
int maxVal(std::vector<int> const& vec)
{
    if (vec.empty())
    {
        throw std::runtime_error("Cannot get maximum of empty vector!");
    }
    // ...
}
```

The syntax for throwing an exception is as follows: `throw` followed by the type
of exception we wish to throw. In this case, it is of type
`std::runtime_error`. Whenever you throw an exception you *must* provide a
message to it. We will later see how this message can be retrieved.

When an exception gets thrown, the function returns **immediately** to the
calling function. Any and all lines of code that follow from the throw
instruction are ignored. The behaviour from here depends on whether the calling
function wishes to deal with the exception or not. For now, let's assume that
the exceptions are not dealt with. In this case, the exception continues to
propagate upwards until `main` is reached. Assuming that the exception isn't
handled here either, the program then crashes. Consider then the following
example:

```c++
int danger(int a)
{
    if (a == 2)
    {
        throw std::runtime_error("Fatal core breach!");
    }
    return a;
}

int main()
{
    for (int i = 0; i < 5; ++i)
    {
        std::cout << danger(i) << std::endl;
    }

    return 0;
}
```

In this case, `main` will continuously call `danger`, which will return the
provided value until the `if` condition becomes true, in which case the
exception gets thrown. At this point, we exit the function immediately and
return to main. Notice that main does not handle the error (we will see how in a
minute) and so the program crashes.

> **Note:** There are several kinds of exception which you can look at
> [here](https://en.cppreference.com/w/cpp/header/stdexcept). For the most part
> we will be focusing on `runtime_error` and `invalid_argument` but it's a good
> idea to get acquainted with the rest as they do come up occasionally.

## Try/catch blocks
Now let's suppose that we wish to handle the exception. The logic would be the
following: let's try to execute a function that may throw an error. If no error
gets thrown, then all is well. If an error does occur, we catch it and deal with
it. This line of thinking leads naturally to the following code:

```c++
int danger(int a)
{
    if (a == 2)
    {
        throw std::runtime_error("Fatal core breach!");
    }

    return a;
}

int main()
{
    for (int i = 0; i < 5; ++i)
    {
        try
        {
            // Attempt to run the following function. If it throws...
            std::cout << danger(i) << std::endl;
            std::cout << "At i = " << i << std::endl;
        }
        catch (std::exception const& e)
        {
            // Catch the exception and print it's error message.
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}
```

In the above example, at each iteration of the loop we attempt to call the
function `danger`. For the first two iterations, no exception will be thrown, in
which case the loop continues normally. When `i` is 2, the exception get's
thrown and we return to `main`. Here, we now capture the exception in the
`catch` block under the name `e`. The code that is enclosed in the `catch` block
is now executed and the error message is printed by invoking the `what()`
function. 

Notice that in this example, if an exception gets thrown, the second call to
`std::cout` does **not** get invoked, falling instead to the `catch` block.

> **Note:** you will notice that our exception catches `std::exception` instead
> of the original error that we threw. We will cover later on why this is
> possible, but for now you may interpret this as simply saying: "catch any and
> all errors that are generated in the `try` block". Alternatively we could have
> replaced the type of `e` with `std::runtime_error`, in which case we would
> **only** catch errors of this type. If `std::invalid_argument` get's thrown, it
> will be ignored and the program will crash.

## Examples
In all of the examples above, perform a trace and determine what the output of
the programs will be. This will serve as good practice for the midterm.

Consider the following example:

```c++
void foo()
{
    throw std::runtime_error("Error 1");
}

void bar(int a)
{
    try
    {
        foo();
    }
    catch (std::exception const& e)
    {
        std::cout << e.what() << std::endl;
    }

    if (a == 2)
    {
        throw std::invalid_argument("Error 2");
    }
}

void baz()
{
    for (int i = 0; i < 8; ++i)
    {
        bar(i);
    }
}

int main()
{
    try 
    {
        baz();
    }
    catch (std::exception const& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
```

What would be the output of this program?
