# Associative Containers
We have covered 3 types of containers thus far: vectors, lists, and sets. Of
these, both vectors and lists are *sequential* containers, while sets are
*associative*. Sequential containers store their data in sequence (with the
order provided by insertion), whereas associative containers usually organize
their contents according to some defined rules. We will now introduce the
remaining associative containers from the standard library, and perform the same
analysis we did before.

## Maps
It is sometimes useful to provide a relationship between elements, where one can
be used as the *key* to find the other. This structure is represented by
`std::map` from the standard library. In it, elements are stored as key-value
pairs, and allow for fast searching of elements. With this in mind, we can
expand our table of associative containers to be the following:

| Container | Insert | Search | Duplicates | Order |
|-----------|--------|--------|------------|-------|
| Set | log(n) | log(n) | no | less |
| Map | log(n) | log(n) | no | less |

Let's now take a look at how to use a map:

```c++
#include <map>

std::map<int, std::string> students;
students.insert({1, "Bruce"});
students.insert({2, "Aflred"});
students.insert({3, "Selina"});
```

A map ultimately stores pairs of objects (key-value pairs). As a result,
`insert()` takes as its argument the pair to insert. The full type of this is
`std::pair<Type1, Type2>`. Since this is far too tedious to type manually, we
mostly use uniform initialization and let the compiler worry about the details.

Since maps have keys, we can actually index into the map with the key in a
similar way to vectors:

```c++
auto s = students.at(1);    // Fine, s is now "Bruce"
auto s2 = students[2];      // Fine, s2 is now "Alfred"
```

So far, this seems fairly innocuous. As you might expect, if we try to index
with `at` on a key that doesn't exist, we get an exception. The risk here is
that `[]` does **not** do this at all. Instead, if the index does not exist, it
will **insert** a new element into the map.

```c++
students[4] = "Harleen";         // Insert new pair (4, "Harleen")
```

This means that `[]` cannot be used whenever we pass a map into a function by
`const&` since it modifies the contents of the map. As a general rule, it is
best to avoid using this entirely, as it can lead to unintended consequences.

Like sets, maps also provide a `find`, and we can also loop:

```c++
// We can also use find.
// Recall that find returns an iterator, which is ultimately a pointer. So 
// to access the data we need to use ->
auto search = students.find(2);
std::cout << search->first << " " << seach->second << std::endl;

// These to versions are equivalent to each other.
std::cout << (*search).first << " " << (*search).second << std::endl;

// Loop through a map:
for (auto entry : students)
{
    std::cout << entry.first << " " << entry.second << std::endl;
}

// Using expansion of pairs, we can also do this (C++17 only):
for (auto [key, value] : students)
{
    std::cout << key << " " << value << std::endl;
}

```

## Unordered set
What if we don't care about order and we want faster search times? Then use
`std::unordered_set`. Note that when elements are inserted into this set, they
**cannot** be modified again (by iterators or otherwise).

| Container | Insert | Search | Duplicates | Order |
|-----------|--------|--------|------------|-------|
| Set | log(n) | log(n) | no | less |
| Map | log(n) | log(n) | no | less (key) |
| unordered_set | 1* | 1* | no | NA |

The operations that an `unordered_set` has are identical to those that a set
has. The reason why the times for insert and searching are marked as 1* is
because these are *amortized* times. The other real difference between sets and
unordered sets is the requirement that a type needs to be inserted into one.

Recall that sets require a way to sort the elements. An unordered set on the
other hand requires a hash function for the given object. If you wish to learn
more, take a look at the `std::hash` group located under the `<functional>`
header. Hashes, how they are computed, and their use lie beyond the scope of
this course.

> **Note:**
> We won't get into what this really means. All that is relevant is that the
> times for searching and inserting are pseudo-constant.

> **Aside:**
> Hashes are very interesting functions, but they are also quite complex. If you
> interested in this type of material, you may consider taking CSc 225.

## Unordered map
These are the equivalent of unordered sets for maps. They allow for faster
searching and insertion at the cost of ordering. Like unordered sets, they also
require a hash function for the keys.

| Container | Insert | Search | Duplicates | Order |
|-----------|--------|--------|------------|-------|
| Set | log(n) | log(n) | no | less |
| Map | log(n) | log(n) | no | less (key) |
| unordered_set | 1* | 1* | no | NA |
| unordered_map | 1* | 1* | no | NA |

## Multisets, Multimaps
The last group are the containers that allow duplication of the data they hold.
Beyond this, the properties are the same. The containers in this category are:

* `std::multiset`,
* `std::multimap`,
* `std::unordered_multiset`, and
* `std::unordered_multimap`.

The only point of interest with the multi-family is the usefulness of the
`count()` function present in both maps and sets (and their multi-relatives). In
both cases, the `count()` function returns the number of occurrences of the
given element (in the case of sets) or key (in the case of maps). Now, since
both maps and sets guarantee the uniqueness of their elements/keys, then this
function is superfluous as it can only return 0 or 1. In fact, it's only real
use is as a way of finding elements that does not involve using iterators. We
can re-write the find pattern as follows:

```c++
// Using iterators:
if (auto result = set.find(1); result != set.end())
{
    // Found the element.
}

// Using count:
if (auto ct = set.count(1); ct != 0)
{
    // Now grab the iterator to the element.
    auto result = set.find(1);
}
```

Admittedly this pattern would be more helpful for maps since we can directly
index them using the key, but the overall structure remains the same. 

In the case of the multi-family, the `count()` function becomes more useful.
Since these containers allow for multiple copies of elements/keys to exist, then
`count()` will return the number of times each element/key appears, which gives
us a broader range of values other than just 0 or 1.

With this out of the way, we can now complete the table for associative
containers:

| Container | Insert | Search | Duplicates | Order |
|-----------|--------|--------|------------|-------|
| Set | log(n) | log(n) | no | less |
| Map | log(n) | log(n) | no | less (key) |
| unordered_set | 1* | 1* | no | NA |
| unordered_map | 1* | 1* | no | NA |
| multiset | log(n) | log(n) | yes | less |
| multimap | log(n) | log(n) | yes | less (key) |
| unordered_multiset | 1* | 1* | yes | NA |
| unordered_multimap | 1* | 1* | yes | NA |
