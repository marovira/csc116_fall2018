# Tracing and Searching
So far we have been mostly focusing on a theoretical approach to several
concepts of C++. Now that we have a gamut of types and some understanding about
how they work, it is time to see them in action.

## References and scope
We have reviewed the concept of scope and have introduced references, so it is
now time to see how they all fit together. Let's consider the following
simplified example of a scenario that occurs in real-world applications:

```c++
#include <iostream>

int why(int a)
{
    return a * 4;
}

void madness(int& num1, int num2)
{
    auto tmp{num1};
    num1 += num2;
    num2 = why(num1);
    num1 = tmp + num2;
}

int main()
{
    int x{10}, y{16};
    std::cout << "Before madness...\n";
    std::cout << "x = " << x << ", " << "y = " << y << std::endl;
    madness(x, y);
    std::cout << "After madness...\n";
    std::cout << "x = " << x << ", " << "y = " << y << std::endl;

    return 0;
}
```

> **Exercise:** What is the output of this program? What would happen if I were to
> change the signature of `why` to `int why(int const& a)`? Would the output
> change?

## Searching
Let's take a look at some applications of vectors. We begin with a linear
search. The problem is as follows: given a vector of data, find a given element.

```c++
#include <vector>
#include <iostream>

bool exists(std::vector<int> vec, int val)
{
    for (auto elem : vec)
    {
        if (elem == val)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::cout << "Does 3 exist in our vector? ";
    std::cout << exists(vec, 5) << std::endl;
    std::cout << "What about 7? ";
    std::cout << exists(vec, 5) << std::endl;

    return 0;
}
```

> **Exercise:** What happens if I change `std::vector<int> vec` to
> `std::vector<int> const& vec`? What are the advantages/disadvantages of each
> one? 
> In the loop, we use `auto elem : vec`. What happens if I use `auto& elem`? Is
> there any benefit? What about `auto const& elem`?

Now let's try this again, but instead of searching for a specific element, what
if we asked for the number of elements that are less than or equal to a given
number?

```c++
#include <vector>
#include <iostream>

int lessThan(std::vector<int> vec, int val)
{
    int count{0};
    for (auto elem : vec)
    {
        if (elem <= val)
        {
            ++count;
        }
    }

    return count;
}
```

Finally, let's expand this to return all those elements that are less than or
equal to a given number.

```c++
#include <vector>
#include <iostream>

std::vector<int> lessThan(std::vector<int> vec, int val)
{
    std::vector<int> result;
    for (auto elem : vec)
    {
        if (elem <= val)
        {
            result.push_back(elem);            
        }
    }

    return result;
}
```

> **Exercise:** Re-write the above searching functions to operate on strings
> instead of on numbers. Change the `lessThan` function to return all strings
> whose length is less than the given string. What do you observe? Does the code
> change substantially between numbers and strings?

Now, let's say that we want to increment a given vector by a specific amount.
How would we do this?

```c++
#include <vector>
#include <iostream>

void increment(std::vector<int>& vec, int val)
{
    for (auto& elem : vec)
    {
        elem += val;
    }
}
```

> **Exercise:** Re-write the above function using `.at()` and then using
> iterators.
