# Splitting a String
Let's take a look at a more complex example that involves using strings and
vectors concurrently. Consider the following problem: given a string, split it
into words.

Our first task is to determine whether we wish for this to be a function or not.
For the sake of both testing and re-usability we will make this a function. From
the problem description we can then surmise that the input will be a string, and
the output must be a group of strings representing each word. Given how the only
container we currently know of that can hold multiple elements is a vector, we
will choose that. Our function signature is then:

```c++
std::vector<std::string> split(std::string line);
```

> **Exercise:** Notice how the parameter is passed by value to the function.
> Would it make sense to pass it by reference? What about a constant reference?

We are now ready to begin implementing our function. As a first attempt, we can
simply separate the line based on spaces, as that is the determining factor of
when a word is over. Our first attempt then looks like this:

```c++
std::vector<std::string> split(std::string line)
{
    std::vector<std::string> words{};   // We will store our words here.
    std::string word{};                 // Store the current word here.
    for (auto ch : line)
    {
        if (ch != ' ')                  // If the character is a space then...
        {
            word.push_back(ch);         // Use push_back to insert a char.
        }

        if (ch == ' ')
        {
            words.push_back(word);
        }
    }

    return words;
}
```

As stated, the function will not work correctly. In fact, what it will do is to
strip the spaces from the line and return a vector with the words all mashed
together. Let's see if we can fix this:

```c++
std::vector<std::string> split(std::string line)
{
    std::vector<std::string> words{};
    std::string word{};

    for (auto ch : line)
    {
        if (ch != ' ')
        {
            word.push_back(ch);
        }

        if (ch == ' ')
        {
            words.push_back(word);
            word.clear();               // Clear out the word for next time.
        }
    }

    return words;
}
```

Now the function works correctly. However, if we test this we will notice that
the final word is being ignored. We can easily fix this as follows:

```c++
std::vector<std::string> split(std::string line)
{
    std::vector<std::string> words{};
    std::string word{};

    for (auto ch : line)
    {
        if (ch != ' ')
        {
            word.push_back(ch);
        }

        if (ch == ' ')
        {
            words.push_back(word);
            word.clear();
        }
    }

    words.push_back(word);              // Insert the final word.

    return words;
}
```

And now our output is complete. As stated though, the function is very brittle
in the presence of multiple spaces between words (as well as trailing spaces).
We can solve this as follows:

```c++
std::vector<std::string> split(std::string line)
{
    std::vector<std::string> words{};
    std::string word{};
    bool isSpace{false};                // Set a flag for the first space.

    for (auto ch : line)
    {
        if (ch != ' ')
        {
            isSpace = false;            // Not a space, so false.
            word.push_back(ch);
        }

        if (ch == ' ' && !isSpace)
        {
            words.push_back(word);
            word.clear();
            isSpace = true;             // First space detected.
        }

        if (ch == ' ' && isSpace)
        {
            continue;                   // Extra spacing, so ignore it.
        }
    }

    if (!isSpace)                       // Only insert the word if there is one.
    {
        words.push_back(word);
    }

    return words;
}
```

This completes the function, which can now perform a split with arbitrary
numbers of spaces between words. We can also extend this to allow for any
delimiter while still preserving the default value as a space with the following
change to the function signature:

```c++
std::vector<std::string> split(std::string line, char delim = ' ')
```
