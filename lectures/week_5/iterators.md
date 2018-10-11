# Iterators
Previously we had discussed the existence of the `iterator` type, and made some
vague references to functions within the vector that had support for these. We
will now take a much closer look at them.

## An Abstraction
Iterators offer an abstraction over the position of an object in a *general*
container. While we have seen them in the context of vectors, iterators allow us
to iterate over *any* data structure that supports them. In general, iterators
offer the following operators:

* `it++`: increment by one.
* `it--`: decrement by one.
* `*it`: access the element at this position.

Notice that shifting an iterator by arbitrary offsets is not included in this
list. The reason for this will become clear when we discuss other containers,
but the summary is as follows: in general, containers are not required to have
their data laid out in a sequential manner. This means that we don't always know
how to shift from one position to another, so we are restricted to always moving
by one each time.

## Using iterators
Now that we know what we can do with iterators, let us take a closer look at how
to use them:

```c++
std::vector<int> vec{1, 2, 3, 5, 6};
auto it = vec.begin();          // it points at the first element of vec.
it++;                           // it now points at the second element.
*it = 3;                        // Modify vec[1] to 3.
it++;
it++;
it--;
*it = 5;

auto it2 = vec.end();           // it2 points after the last element of vec.

// Loop through the vector and print its elements.
for (auto i = vec.begin(); i != vec.end(); ++i)
{
    std::cout << *i << std::endl;
}
```

As we can see here, iterators provide a nice way of moving through a container,
and also offer us a different format for a for-loop. In fact, the range-loop
is designed to do what the iterator for-loop does.

## Iterators in STL
The standard library has an entire section dedicated to functions that operate
on iterators. You can see these under the `<algorithm>` header
[here](https://en.cppreference.com/w/cpp/header/algorithm). What we will mostly
focus on is on the way that certain functions, such as `std::search` work.

```c++
std::vector<int> vec{1, 2, 3, 4};

// Simple example, check if 3 is in the vector.
auto result = std::search(vec.begin(), vec.end(), 3);
if (result != vec.end())
{
    std::cout << "Found the element!" << std::endl;
}
```

Let's take a look at this more closely. `std::search` takes 3 parameters: the
first two constitute the range in which we wish to search, and the final
parameter is the element to search for. In this case, we wish to search through
the entire vector for 3. The function then returns an iterator. Recall when we
wrote a similar find function. We first wrote it with a return type of `bool`,
but then we wanted to also obtain the position of the element (if it exists).
This meant changing the return type to `int` but also adding a bit of a hack: if
the element is not in the vector, return an invalid index (-1). Iterators on the
other hand have a very convenient property: because of the way we loop through
the container, we will always stop when our iterator is `end`. Hence if we
haven't found the element, we can simply return `end`. This nicely solves the
return value that we otherwise had with indices.

## A Nice Optimization (C++17 only)
In the previous example, we declared a variable called `result` whose scope
would be whatever the function we were contained in was. Suppose that I made
continuous queries to `search`. Then what would happen is one of two things:

1. We re-use the same variable (which may not be ideal), or
2. we declare a new variable each time.

What we can do instead is declare the variable such that its scope is the place
where we use it (the `if` statement). With C++17 we can then do the following:

```c++
std::vector<int> vec{1, 2, 3, 4};

for (auto result = std::search(vec.begin(), vec.end()); result != vec.end())
{
    // Do something.
}
```

This syntax allows us to declare `result` inside of the scope of the `if` and
use it inside, ensuring that it doesn't persist beyond the statement itself.
This is by no means something that is required in general code, but it is a nice
shortcut.

## Iterators in vectors
We previously discussed the existence of functions such as `insert` and `erase`.
Now that we have a deeper understanding of iterators, let us look at these
functions once more. 

```c++
std::vector<int> vec{1, 2, 3, 4, 5};
vec.insert(vec.begin(), 0);         // Insert at the beginning.
auto it = vec.begin();

it++;
it++;
vec.insert(it, 10);                 // Insert at random positions.

std::vector<int> vec2{8, 9, 10};
vec.insert(vec.end(), vec2.begin(), vec2.end());    // Insert vec2 at end.

it = vec.begin();
it++;
it++;
vec.insert(it, vec.begin(), vec.end());     // Insert at random positions.

it = vec.begin();
it++;
it++;
vec.erase(it, vec.end());       // Erase from it to end.
vec.erase(vec.begin(), vec.end()); // Erase the whoe thing.
```

It is worth noting that `erase` will always erase *up to* but *not* including
the end of the range. In other words, if we specify a range with two iterators,
`start` and `end`, `erase` will not remove whatever `end` is pointing at. The
reason for this is fairly straight-forward: the implementation of `erase` uses a
for-loop that is very similar to the iterator loop. In particular, it uses the
condition `start != end`, which means whatever `end` is pointing at will remain
untouched.

The last thing to notice in this code is the repetition of the assignment of
`it`. Notice that both `insert` and `erase` modify the contents of the vector.
As a result, the position that `it` is pointing at may very well not exist
anymore, hence why we re-assign it every time. 

> **Caution:**
> Whenever you use iterators to modify a container, **do not** re-use the same
> iterator as the positions may have changed. It is always better to grab a new
> one and start over. This will avoid unforeseen crashes.
