# Problem Solving with Templates
We have now covered everything that we need to know to start using templates in
our code. Let's see how we can use them to solve certain problems or how to
generalize our code to work on arbitrary types.

## Functional
Recall the following two functions that we had defined previously:

```c++
void forEach(std::vector<int> data, std::function<void(int)> f)
{
    for (auto elem : data)
    {
        f(elem);
    }
}

int accumulate(std::vector<int> data, std::function<int(int, int)> f)
{
    int result{};
    for (auto elem : data)
    {
        result = f(result, elem);
    }

    return result;
}
```

As defined, these functions will only work for vectors of integers. Since the
logic is identical in the case of a generic container, we can use templates to
make them generic. Let's begin with `forEach`:

```c++
template <typename T, typename UnaryFunction>
void forEach(T data,  UnaryFunction f)
{
    // ...
}
```

Notice that our template takes *two* parameters instead of one. The reason is
the following: we are templating on the container type. The fact that the
container itself may be templated is irrelevant. The problem here is that we
have no way of fully specifying the signature for `f`, because we don't know the
type that the container holds. In order to solve this, we simply template the
function as well and let the compiler handle the deduction on the actual type of
the function itself.

> **Experiment:**
> Look at the full templated code and try to guess what kind of deductions and
> restrictions the compiler imposes on the type `UnaryFunction`.

Now let's take a look at `accumulate`:

```c++
template <typename T, typename BinaryFunction, typename U>
U accumulate(T data, BinaryFunction f, U initial)
{
    U result{initial};
    for (auto elem : data)
    {
        result = f(result, elem);
    }

    return result;
}
```

The first two template parameters are expected, since they're the same we had on
the `forEach`. The question now is why do we need a third template parameter? 
Simply put, we have a problem on the *return* type of the function. Again,
because the collection itself is templated, then we have no way of accessing the
underlying type. In order to get around this, we simply require another value
which gives us the return type. This is in fact what the C++ standard library
uses.

Now suppose that we didn't want to have to specify an initial value. How would
we get around this?

### Option 1
Inside all of the containers from the standard library there is a type that is
called `type_value`. This is set to be the type that the container is templated
on. So `std::vector<int>` sets `type_value = int`. So what we could do to solve
the problem is do this:

```c++
template <typename T, typename BinaryFunction>
auto accumulate(T data, BinaryFunction f)
{
    typename T::value_type result{};
    for (auto elem : data)
    {
        result = f(result, elem);
    }

    return result;
}
```

We need to specify the `typename` in this case because `T` is a dependent type,
which makes `T::value_type` a dependent type as well. By specifying `auto` as
the return type, we let the compiler figure out the type and all is well.

### Option 2
There are two downsides to the previous option:

* We are using `auto` as the return type with no other hints to the compiler,
  which could be brittle if the function was more complex.
* We require our collections to have `value_type`.

Of particular concern is the second part. What if we have a data structure that
doesn't have that? Could we get around it?

Well, we can observe that by using a ranged-for loop we are requiring that the
container have iterators. Specifically, we require `begin()` and `end()`. So
what if we somehow used these to specify the return type?

```c++
template <typename T, typename BinaryFunction>
auto accumulate(T data, BinaryFunction f) -> typename decltype(*data.begin())
{
    typename decltype(*data.begin()) result{};
    for (auto elem : data)
    {
        result = f(result, elem);
    }

    return result;
}
```

This introduces a new C++ function: `decltype`. What this function does is it
grabs the *type* of an **expression**. So in this case,
`decltype(*data.begin())` is saying: grab the type of `*data.begin()` and use
it. In the context of `->`, it telling the compiler to set the return type of
the function to be the type of `*data.begin()`. Remember that since iterators
are ultimately pointers, we need to dereference them.

This almost works. The problem is that `*begin()` will return a **reference**
not a copy. This means that the return type of accumulate is now a reference to
`result`. This causes a big issue: `result` will be destroyed when the function
exits, and the reference that is returned will be pointing at nothing, which is
invalid. The correct solution is the following:

```c++
template <typename T, typename BinaryFunction>
auto accumulate3(T data, BinaryFunction f) -> typename std::remove_reference<decltype(*data.begin())>::type
{
    typename std::remove_reference<decltype(*data.begin())>::type result{};
    for (auto elem : data)
    {
        result = f(result, elem);
    }

    return result;
}
```

This corroborates what we had said earlier about template syntax: it is very
hard to understand and difficult to debug. What we are saying is the following:
grab the return type of `*data.begin()`, remove the reference, and get the
actual type back. We need to use `typename` because again, this all depends on
`T` which is itself a dependent type. The benefit of doing this is that we have
now gained the ability to pass in *any* data collection that supports iterators.

## Enabling Templates for Specific Types
The last example we will see is how to use templates to make sure that only
types that have specific qualities are used. Consider the following example:

```c++
float abs(float x)
{
    if (x < 0)
    {
        return -x;
    }

    return x;
}
```

We could template this as follows:

```c++
template <typename T>
T abs(T x)
{
    // ...
}
```

It would be reasonable to ensure that only numeric types are used with this
template. This means that we want both integral (`int`) and floating point types
(`float` and `double`). Using templates, we can produce the following solution:

```c++
template <typename T,
         typename std::enable_if<std::is_arithmetic<T>::value>>
T abs(T x)
{
    if (x < 0)
    {
        return -x;
    }
    return x;
}
```

So what is happening here? `std::enable_if` does what you would expect. Given a
condition the template is enabled if the condition is true. Otherwise it gives
an error. The question is this: how does the compiler evaluate expressions? 

Recall that we had discussed `constexpr`. The idea is that somewhere in the
standard library there is a struct containing a `constexpr` variable that is
either true or false. Specifically, this struct is called `is_arithmetic` and is
specialized to be true on the types that we want and false otherwise. So, with
this information, the compiler is able to determine if the template should be
enabled because it has access to the values of the `constexpr` variables at
compile-time.

## Aside: SFINAE
It is interesting to realize that the standard library does not have
specializations of `is_arithmetic` for *every* possible type, since that would
not be reasonable (or even possible). So how does this work then? If an
instantiation is attempted, the compiler will check to see if a specialization
of `is_arithmetic` exists. It will start with the first specialization that was
declared and check to see if it matches. If it doesn't, the compiler throws this
away and proceeds. At the end, it will either have removed all options or it
will have one. If it has an option, the template is well-formed and everything
works, otherwise an error is emitted. The idea that the compiler doesn't stop
trying to make the deduction until it has ran out of options is called
**SFINAE** (substitution failure is not an error). This concept is one of the
corner-stones of template metaprogramming.
