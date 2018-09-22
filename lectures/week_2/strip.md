# Stripping Whitespace
Last time we discussed how to create a function that would split a string on an
arbitrary character. Recall that the function split was implemented as follows:

```c++
std::vector<std::string> split(std::string line, char delim = ' ')
{
    std::vector<std::string> words{};
    std::string word{};
    bool isDelim{false};

    for (auto ch : line)
    {
        if (ch != delim)
        {
            isDelim = false;
            word.push_back(ch);
        }

        if (ch == ' ' && !isDelim)
        {
            words.push_back(word);
            word.clear();
            isDelim = true;
        }

        if (ch == ' ' && isSpace)
        {
            continue;
        }
    }

    i f(!isDelim)
    {
        words.push_back(word);
    }

    return words;
}
```

Interestingly, the C++ library is very spartan when it comes to string
manipulations, taking a more C-approach of encouraging programmers to implement
any and all functionality they desire. Languages such as Python allow the
following sequence of operations on a string: first remove any extra white-space
from the string, and then split on a given delimiter. This implies that after
the strip operation is done, there should only be one character of white-space
between words (so if multiple spaces are used, there should only be one left).
Let's see if we can implement a strip function in C++, and then how we can
combine it with `split` so we can emulate the same behaviour.

Once again, we first need to determine what our function signature will be.
Given that the task is to take a string and remove all white-space, we conclude
that our function should look like this:

```c++
std::string strip(std::string text)
```

> **Exercise:** Notice how the parameter is passed by value to the function.
> Would it make sense to pass by reference? What about `const&`?

Let's implement our function now:

```c++
std::string strip(std::string text)
{
    std::string result{};           // Store the final string here.
    for (auto ch : text)
    {
        if (ch != ' ')              // If the character is not a space...
        {
            result.push_back(ch);   // Insert it in our string.
        }

        if (ch == ' ')
        {
            result.push_back(ch);   // Always save the first instance.
        }
    }

    return result;
}
```

We can see how the code is almost identical to the one we used for `split`. In
fact, we can also re-use the flag system to detect when the first space occurs.
Let's add it in:

```c++
std::string strip(std::string text)
{
    std::string result{};
    bool isSpace{false};
    for (auto ch : text)
    {
        if (ch != ' ')
        {
            isSpace = false;            // Not a space.
            result.push_back(ch);
        }

        if (ch == ' ' && !isSpace)
        {
            result.push_back(ch);
            isSpace = true;             // This is our first space.
        }

        if (ch == ' ' && isSpace)       // We have seen a space...
        {
            continue;                   // so ignore the rest.
        }
    }

    return result;
}
```

This completes the function. In the same spirit as before, we can extend this to
arbitrary characters to strip by using default parameters:

```c++
std::string strip(std::string text, char delim = ' ')
{
    // ...
}
```

Now let's see an example of how these functions work together:

```c++
std::string text{"Some    random   text   "};
auto result = strip(text);      // Remove all spaces except for the first
auto words = split(text);       // Split into the words.
// Print them out...
```

Notice that since every parameter is passed by *value*, then we ensure that each
function has no side-effects and the only change the function has is through
it's return value. This is known as a **pure** function, and is a building block
for something we will see later on which is called functional programming. It
turns out that because the functions are pure, we can join everything into a
single line as follows:

```c++
std::string text{"Some    random   text   "};
auto words = split(strip(text));    // First strip white-space, then split.
// Print it out...
```

> **Exercise:** We defined a *pure* function as a function that does not modify
> it's input parameters and it's only side-effect is the return value. Based on
> this, would these functions still be pure if I changed their function
> signatures to take their parameters by `&`? What about `const&`? 
