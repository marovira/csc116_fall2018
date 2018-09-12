# Vectors

A vector is a much more versatile and powerful tool than the C arrays where. In
terms of functionality, a vector allows us to:

* Declare one without knowing the initial size,
* Resize on command by inserting elements in *any* position,
* Boundary checks,
* Easy way of getting the size,
* Plus many more!

## Creating Vectors
There are several ways in which we can construct a new vector. Consider the
following code:

```c++
std::vector<int> vec1;              // Vector initialized with size 0
std::vector<int> vec2{1, 2, 3};     // Uniform initialization used
std::vector<int> vec3(5);           // Vector initialized with size 5
std::vector<int> vec3(5, 0);        // Vector initialized with size 5 full of 0
```

Let's take a look at line one. `std::vector` is a type, which defines the vector
object. As before `<int>` is the template parameter. In this case, the line says
that `vec1` is a vector of `int`. This line creates an empty vector.
The second form uses uniform initialization to create a vector with some initial
values. In this case, our vector will contain the values we specify (1, 2, 3),
and will have the appropriate size.
The third form creates a vector with a specified size. It is important to note
that the data is not initialized, and should be treated as an uninitialized
variable. Finally, the last form also creates a vector of a specified size, but
initializes all of the elements of the vector with the specified value.

>**Note:**
> While it may appear weird at first to use `vec2{1, 2, 3}` and `vec3(5)`, the
> meaning behind each statement is what sets them apart. The first form
> *initializes* a vector with a *specific* set of values. The second form on the
> other hand merely *constructs* a vector with a specific size.

## Inserting Elements
One of the biggest advantages of a vector is its ability to resize on demand.
Consider the following:

```c++
std::vector<int> vec;
std::cout << "The size is: " << vec.size() << std::endl;
vec.push_back(5);       // Vec contains { 5 }
std::cout << "The size is: " << vec.size() << std::endl;
vec.push_back(6);       // Vec contains { 5, 6 }
std::cout << "The size is: " << vec.size() << std::endl;
```

`vec` is initially declared as an empty vector. The function `push_back` inserts
elements at the end, increasing the size as new elements are pushed. The
`size()` function returns the current size of the vector.

It would seem that if we can insert elements at the end, we should be able to
use something like `push_front` to insert at the front of the vector.
Unfortunately vectors do not have such a function. That said, we can use a more
generic form of `push_back` to insert at arbitrary locations:

```c++
std::vector<int> vec;
vec.push_back(5);
vec.push_back(6);
vec.insert(vec.begin(), 4);     // Inserts 4 at the beginning
vec.insert(vec.begin() + 2, 7); // Inserts at position 2  
```

`insert()` in this form takes two parameters: the position in which we are
inserting, and the element to insert. So what does `vec.begin()` and `vec.end()`
return? These functions return something that is called an iterator. An iterator
is basically a pointer to an element of the vector. The reason why these exist
is because iterators allow us to traverse vectors (and other data structures)
with the same code.

## Iterating over vectors
A first attempt would be to manually index into the vector, similar to how we
iterated over arrays in C. We would then do this:

```c++
// vec same as previous example.
for (std::size_t i = 0; i < vec.size(); ++i)
{
    std::cout << vec.at(i) << std::endl;
}
```

We use `std::size_t` as that is the return type of `size()`, which is
essentially an alias of `unsigned int`. While this works fine, it is also not
generic, as it requires the container to have an `at()` function. Previously we
mentioned that iterators were used by other containers, so let's use them to
iterate over our vector instead:

```c++
// vec is the same as before
for (auto it = vec.begin(); it != vec.end(); ++it)
{
    std::cout << *it << std::endl;
}
```

The type of `it` is deduced as `std::vector<int>::iterator`. Since this is very
tedious to remember and type, we simply use `auto` to let the compiler do the
work for us. The biggest advantage of using iterators is that we *cannot* run
over the edge of the vector. That said, the syntax is very awkward and does
require a dereferencing of the iterator (since it's ultimately a pointer).
Fortunately, C++ does have a better alternative:

```c++
// vec same as before
for (auto& elem : vec)
{
    std::cout << elem << std::endl;
}
```

This is called a `range-loop` or a `for-each` loop. Underneath this pattern uses
the iterators that we have already seen, which means that it still retains the
boundary guarantee of the previous loop. That said, it does have the advantage
of being significantly shorter and easier to write.

> **Note:**
> In this example, we declared elem as `auto&`, effectively making it a
> reference to an element of the vector. We could have also declared it as `auto
> elem`. Given what we know of references, what are the advantages of each? How
> could we modify this such that we have a reference that we cannot modify?

## Other useful things...
We can also concatenate vectors by using an overload of `insert`. The code looks
as follows:

```c++
std::vector<int> vec1{1, 2, 3};
std::vector<int> vec2{4, 5, 6};

vec1.insert(vec1.end(), vec2.begin(), vec2.end());
```

In this case, `insert` takes in where we want to insert, and the range from the
second vector that we wish to insert. Our example simply appends the entire
second vector to `vec1`. Can you modify this code so that only a subset of
`vec2` is inserted into `vec1`?
