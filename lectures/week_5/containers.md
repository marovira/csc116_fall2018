# Containers
Up to this point we have focused on vectors as the only containers for storing
data without really concerning ourselves with the potential drawbacks of using a
vector. We are now ready to begin that discussion and see what other options are
offered by the standard library.

## Vectors
A vector is ultimately a *sequential* container, where all the data is
guaranteed to be *contiguous*. Without getting into the details of how and why,
what this implies is the following:

* Elements in the vector retain the order in which they are inserted, and
* vectors guarantee that the data is stored next to each other, without any gaps
  between elements.

The second point has a very interesting consequence: it makes it very easy to
insert elements at the end, since all that we have to do is create a new block
for the new element, but it makes it slow to insert at the beginning. Let us
understand why this is.

Consider the following vector:

```c++
std::vector<int> list{1, 2, 3, 4, 5, 6};
```

Suppose that we wanted to insert 0 at the beginning. In order to accomplish
this, we would have to shift over the *entire* contents of the vector in order
to make space. In this case, it would take `n` operations to insert at the
beginning of the vector.

Now suppose that we wanted to search for something in our vector. Similarly, in
the worst case we would end up searching through every element of the vector, so
it would take `n` operations to complete.

> **Note:**
> This discussion (and the ones that follow) is a very informal treatise of
> runtime complexity. If you are interested in these topics and want to know
> more, CSc 225 deals with analysis of algorithms, which introduces a far more
> in-depth analysis of runtime.

On the other hand, vectors allow us instant access to random elements (via their
index) have very fast insertions at the end. To summarize, we have the following
analysis of the vector:

| Operation | Runtime |
| ----------|---------|
| insert back  | 1 |
| insert front | n |
| access | 1 |
| search | n |
| order  | user-provided |
| layout | sequential |
| duplicates | yes |

In this case, we denote constant time as 1.

Seeing these results begs the following questions:

* What if we want to constantly insert at the beginning?
* What if we wish to constantly search?

Fortunately, the standard library has several containers which can help with
these tasks. As we will see, typically favouring a particular operation means
sacrificing something.

## Lists
The standard library offers an implementation of a linked-list called `list`.
The syntax for creating one is as follows:

```c++
#include <list>

std::list<int> list{1, 2, 3};   // List now holds 1, 2, 3.
```

Unlike vectors, lists do not store their data in a sequential fashion, but they
do retain the order that you provide. The fact that their data is no longer
sequential has some consequences:

1. Iterators no longer have the ability to shift by arbitrary indices. That's
   why this option is not included in the standard operator set for iterators.
2. Insertions at the beginning and end are as fast as inserting at the end.
3. Elements cannot be accessed by index. If you need the ith element, you must
   loop through to find it.

Searching remains the same as vectors, since lists are ultimately sequential
containers. In summary, we have the following:

| Operation | Runtime |
| ----------|---------|
| insert back  | 1 |
| insert front | 1 |
| access | n |
| search | n |
| order  | user-provided |
| layout | sequential |
| duplicates | yes | 

## Sets
The final container that we will cover at this time is a `set`. Unlike lists and
vectors, sets are *not* sequential containers, but associative. This means that
data is stored using an internal structure (in this case a binary tree) and
ordered in such a way that the smallest element appears first and the largest
appears last. The advantage of this layout is that it allows us very fast
searching (at least compared to a vector or a list), but it comes at the cost of
almost every other operation. A set can be created as follows:

```c++
#include <set>

std::set<int> set{2, 4, 3};     // Set now holds 2, 4, 3 (not in this order).
```

The fact that sets are associative containers as opposed to sequential has the
following consequences:

1. The order of the data is not preserved. Data is ordered from smallest to
   biggest.
2. There can be no duplicates in the set.
3. Searching is fast.

We can summarize this as follows:

| Operation | Runtime |
| ----------|---------|
| insert | log(n) |
| search | log(n) |
| order  | less than |
| layout | associative |
| duplicates | no | 

## Choosing a container
The take-away of this is that we should choose the container that best fits the
type of usage. As a general rule of thumb, we can conclude the following:

* If we want random access to elements, and will only be inserting at the end,
  use a vector.
* If we want to insert at the beginning and at the end, but we *don't* care
  about runtime, use a vector. Otherwise use a list.
* If we are going to be searching constantly, use a set.

## Using lists and sets
Now that we have discussed these structures, let's take a look at how to use
them:

```c++
std::list<int> list{1, 2, 3};
list.push_front(0);                 // Insert at the beginning.
list.push_back(4);                  // Insert at the end.

std::list<int> list2{5, 6, 7};
list.insert(list.end(), list2.begin(), list2.end());    // Same as vectors.

for (auto elem : list)
{
    std::cout << elem << std::endl;
}

list.erase(list.begin(), list.end());               // Same as vectors.
```

Notice that for the most part lists function in the same way as vectors, save
for the lack of random access. Also notice that, unlike vectors, lists provide a
`push_front` function for insertions at the beginning. That said, `insert` will
work in the same way as vectors do.

```c++
std::set<int> set{1, 2, 3, 4};
set.insert(5);          // Insert a new element.

for (auto elem : set)
{
    std::cout << elem << std::endl;
}

if (auto result = set.find(3); result != set.end())
{
    std::cout << "Found element" << std::endl;
}
```

There are a few things to note here: first, sets do not have a `push_front` or
`push_back` since these operations make no sense in the context of trees.
Second, sets offer a `find` function, which we can use instead of `std::find`
(as it will be faster anyway). The syntax for it remains the same though.
