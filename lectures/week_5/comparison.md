# Comparison and Uses of Lists and Sets
Let's recall the properties of the containers that we have seen so far:

| Operation | Vector | List | Set |
|-----------|--------|------|-----|
| insert back | 1 | 1 | NA |
| insert front | n | 1 | NA |
| insert | n | n | log(n) | 
| access | 1 | n | NA |
| search | n | n | log(n) |
| order | user | user | internal (<) |
| layout | sequential | sequential | associative |
| duplicates | yes | yes | no |

As a general rule of thumb, we typically will use vectors for most things, as
lists real advantage is if we are constantly inserting at the front (and even
then we can come up with ways to use a vector over a list). Finally, if we
require constant searching into a container, we prefer sets.

> **Note:**
> In the code directory for this week there are code samples that test the time
> it takes to perform each operation on the different data structures. Take a
> look and see how they perform in you machine. Can you explain the timing
> differences?

## Sets

Due to the nature of sets, they do not allow duplicates, which means we can use
it to prune duplicates from a vector. This can be accomplished as follows:

```c++
std::vector<int> vec{1, 1, 2, 2, 3, 3, 5, 5, 7, 7, 4, 4};
std::set<int> set;

for (auto elem : vec)
{
    set.insert(elem);
}

vec.clear();
for (auto elem : set)
{
    vec.push_back(elem);
}
```

Notice that the final ordering of the vector *will not* be the one we started
with, since elements are ordered in the set. A more compact way of doing this is
as follows:

```c++
std::vector<int> vec{1, 1, 2, 2, 3, 3, 5, 5, 7, 7, 4, 4};

// Sets have a constructor that can take a range of values in the form of
// iterators, so we can use this instead.
std::set<int> set(vec.begin(), vec.end());

// vec.assign() works by setting the values of the vector from the provided
// iterators. Note that this clears out any previous values in the vector and
// replaces them, unlike insert() which just adds elements.
vec.assign(set.begin(), set.end());
```
