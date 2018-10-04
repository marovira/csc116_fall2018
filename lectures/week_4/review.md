# Review

Below you will find the solutions to the problems we have covered in class along
with a partial explanation.

## Question 2
Given a vector of strings with mixed capitalization, modify this vector such
that all the strings have their capitalization inverted. So if a character is
lowercase, it should be converted to uppercase and vice-versa.

```c++
void invertCaps(std::vector<std::string>& words)
{
    // Iterate by reference so the changes are reflected in the vector.
    for (auto& word : words)
    {
        for (auto& ch : word)
        {
            // Check if it is uppercase. If it is, then turn to lower. If not
            // then check if it is lowercase and convert to upper. If it is 
            // neither, do nothing.
            if (std::isupper(ch))
            {
                ch = std::tolower(ch);
            }
            else if (std::islower(ch))
            {
                ch = std::toupper(ch);
            }
        }
    }
}
```

## Question 5
Given a string and a range of indices, return the portion of the string that
exists between these indices. For example, given the string "hello" and indices
0, 2, the function would return "hel".

```c++
// There are two possible variants of this: we can either use substr or we can
// the function ourselves. Here are both versions.
std::string substring1(std::string const& str, int start, int end)
{
    return str.substr(start, end);
}

std::string substring2(std::string const& str, int start, int end)
{
    std::string sub{};
    for (int i = start; i <= end; ++i)
    {
        sub.push_back(str.at(i));        
    }
    return sub;
}
```

## Question 6
Design a program that prints out the current time as entered by the user. First
design a struct that will hold hours, minutes, and whether it is am or pm. Parse
the input from the user, which you may assume will be in 24-hour format (so 1pm
is 13:00) and print out the final time.

> **Note:** See `q6.cpp` in the `code` folder for the full solution.

## Question 7
Given a vector of integers and two values a and b, fill this vector with values
in the range [a, b].

> **Note:** This question was poorly worded, and this was the original intent.

```c++
void fill(std::vector<int>& vec, int a, int b)
{
    for (int i = a; i <= b; ++i)
    {
        vec.push_back(i);
    }
}
```

## Question 8
Given a vector of strings, write a function that checks if any string appears
more than once.

```c++
bool repeats(std::vector<std::string> const& words)
{
    for (std::size_t i{0}; i < words.size(); ++i)
    {
        for (std::size_t k{0}; k < words.size(); ++k)
        {
            if (i == k)
            {
                continue;
            }

            if (words.at(i) == words.at(k))
            {
                return true;
            }
        }
    }

    return false;
}
```

## Question 9
Extend the above program to do the following: given a vector of strings, return
a new vector that contains any string that appears more than once. The new
vector must contain only one occurrence of each word.

```c++
bool find(std::vector<std::string> const& words, std::string const& word)
{
    for (auto w : word)
    {
        if (w == words)
        {
            return true;
        }
    }

    return false;
}

std::vector<std::string> repeats(std::vector<std::string>const& words)
{
    std::vector<std::string> result;
    for (std::size_t i{0}; i < words.size(); ++i)
    {
        for (std::size_t k{0}; k < words.size(); ++k)
        {
            if (i == k)
            {
                continue;
            }

            if (words.at(i) == words.at(k))
            {
                // First check if we have seen this word before.
                if (!find(result, words.at(i)))
                {
                    result.push_back(words.at(i));
                }
            }
        }
    }

    return result;
}
```
