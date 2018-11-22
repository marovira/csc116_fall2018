# Lambdas

## Why are lambdas useful?
For the most part, lambdas are used in 2 different circumstances:

* We require a relatively small (or simple) set of lines of code that will be
  re-used within **one** function (be it in main, a class, or regular
  functions). The functionality that we require is so specific that it's
  difficult to generalize and the effort of making the function a member (if we
  are in a class) or adding it to a header (or both) is not worth it. In this
  case, we simply make a lambda and use it like  a regular function but it
  remains in the place that we use it.
* We have a function that needs to use a relatively large number of parameters
  to work. Most of these will either be `const` or are passed by copy. This is
  in addition to the parameters of the actual function itself. This usually
  happens in the same situation as the above case (though not always). We have
  two options:

  * We can create a struct to bundle all the data together and pass the struct
    into the function, or
  * we can write a function signature with *all* the parameters.

  If neither of these is appealing, use a lambda.
* We are dealing with a function that has an argument of `std::function`. Since
  we typically just want to use the function without extra overhead, we use a
  lambda. Moreover, if the function that we want to use has to use additional
  parameters, we **must** use a lambda, as changing the function signature would
  result in a compiler error.

As a general rule, lambdas are either completely necessary (case 3) or just
offer a convenience. That said, the syntax of the lambda is somewhat alien to
everything else in C++. So what would the alternative be?

Well, suppose that we wanted to use `std::for_each` to print all the elements of
a vector (yes, this is incredibly contrived, but it works for illustration
purposes). If we didn't want to use lambdas, we could do this:

```c++
struct Print
{
    void operator()(int n)
    {
        std::cout << n << std::endl;
    }
};

int main()
{
    std::vector<int> vec{1, 2, 3, 4};

    std::for_each(vec.begin(), vec.end(), Print());

    return 0;
}
```

The `Print` object that we created is called a *functor*. Now suppose that we
also wanted to print the line number. Clearly we can't change the function
signature that `std::for_each` expects, but our struct can hold data. So we can
do the following:

```c++
struct Print
{
    Print() :
        lineNum{0}
    {  }

    void operator()(int n)
    {
        std::cout << "Line (" << lineNum << "): " << n << std::endl;
        lineNum++;
    }

    int lineNum;
};

int main()
{
    std::vector<int> vec{1, 2, 3, 4};

    std::for_each(vec.begin(), vec.end(), Print());

    return 0;
}
```

And so on for any additional variable that we wanted the struct to hold. Keep in
mind that if the struct had to modify variables outside of it's scope, they need
to be passed by reference through the constructor. In either case, let us now
see how this code would be written if we used lambdas:

```c++
int main()
{
    std::vector<int> vec{1, 2, 3, 4};

    int lineNum{0};
    std::for_each(vec.begin(), vec.end(), 
            [&lineNum](int n)
            {
                std::cout << "Line (" << lineNum << "): " << n << std::endl;
                lineNum++;
            });

    return 0;
}
```

Notice that we need to capture `lineNum` by reference so that the line count
persists. Clearly the second option is a lot simpler to write and requires less
lines of code while ultimately accomplishing the same thing.

> **Note:**
> Lambdas aren't a fix for everything. There are times when we do need to use
> functors. This is especially important if we have to remember *state* across
> invocations of the function. 

## Introduction to Recursion
A topic that is tied to functional programming is recursion. If you recall, we
discussed how pure programming languages do not have loops of any kind. So the
question is: how do we iterate?

Let us consider the example of adding the elements of a vector. With loops we
would do the following:

```c++
int sum(std::vector<int> const& vec)
{
    int sum{0};
    for (auto num : vec)
    {
        sum += num;
    }

    return sum;
}
```

However, we can express the sum as follows: `sum = vec[last] + (sum of remaining
elements)`. Admittedly this is a very weird way of thinking about this problem,
but let's see how we could implement this:

```c++
int sum(std::vector<int> const& vec)
{
    auto newVec = vec;
    newVec.pop_back();
    return vec.back() + sum(newVec);
}
```

Notice that we have now reduced the code somewhat and the last line calls the
function again. Now we have a problem: how do we know when to stop calling the
function?

```c++
int sum(std::vector<int> const& vec)
{
    if (vec.empty())
    {
        return 0;
    }

    auto newVec = vec;
    newVec.pop_back();
    return vec.back() + sum(newVec);
}
```

This function will return the sum as expected. This type of pattern is known as
**recursion**. Basically a function is *recursive* if it calls itself within its
body. There are two rules of recursion:

* **ALWAYS** make sure that you have a base case. Failure to do so results in
  infinite recursion and your program crashing.
* Each function call *should* reduce the problem until the base case is reached.
  Failure to do so results in infinite recursion.

Recursion gives us a way of expressing certain concepts more easily, as well as
reducing the amount of code (or the complexity of said code) that is required to
achieve the desired result.

## Singly-linked Lists
We will now turn our attention to a data structure where recursion actually
helps to make our code easier: singly-linked lists. Recall that a singly-linked
list is a structure where each node contains a pointer to the next node in the
list, with the final pointer being null. For these examples, we will be using
the declaration of the linked list found in the code folder for this week.
Suppose that we wanted to print the list forward. All that we would simply have
to do is:

```c++
void printForwards(List const& l)
{
    if (l.head == nullptr)
    {
        return;
    }

    auto it = l.head;
    while (it != nullptr)
    {
        std::cout << it->data << std::endl;
        it = it->next;
    }
}
```

The question now is this: how do we print backwards?

It turns out that there is now direct way of doing it using iteration. An option
would be to simply iterate forwards, storing the data of the list into another
data structure (like a vector or a stack) and then read the data stored in the
structure backwards. This seems a bit tedious for something so simple. As it
happens, we can use recursion to make our lives easier:

```c++
void printRecurse(NodePtr const& p)
{
    if (p == nullptr)
    {
        return;
    }

    printRecurse(p->next);
    std::cout << p->data << std::endl;
}

void printBackwards(List const& l)
{
    printRecurse(l.head);
}
```

What we did here is to decouple the recursive function from the actual function
we want to use in code. Basically `printBackwards` is just a convenience wrapper
for `printRecurse` as a way of maintaining the same interface as
`printForwards`. With this out of the way, let us take a look at `printRecurse`.

As per our guidelines, we first specify what the base case of our recursion is.
If we hit a `nullptr`, we know we have reached the end of the list and we return
immediately. Next, we invoke ourselves, basically trying to find the end of the
list. Once we have (the base case we discussed previously), then we know that by
that point we have reached the end, so we can now start printing. A rather nice
side-effect of this function is that we can easily modify it so that it prints
forwards: simply swap the order of the print statement and the call to
`printRecurse`. 
