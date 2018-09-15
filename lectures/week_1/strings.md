# Strings
Recall that in C a string was basically an array of characters that had a null
terminator (`\0`) at the end. Being that strings were arrays, they had the same
downfalls that C arrays had. Additionally, C strings are very cumbersome to use
and lead to difficult to understand and error-prone code. Fortunately, as with
vectors, C++ offers a string object. 

## Initializing strings
Strings can be created in a very similar fashion to vectors. Consider the
following code:

```c++
#include <string>

std::string s1{};               // Creates an empty string
std::string s2{"Hello"};        // Creates a string with "Hello";
```

The first form is identical to the declaration of an empty vector, and likewise
creates an empty string. The second form creates a string with specified text. 

## Iterating over a string
Strings, like vectors, offer both iterators and a `at()` function. As such, the
following loops will work on a string:

```c++
std::string str{"Some random text"};
for (std::size_t i = 0; i < str.size(); ++i)
{
    std::cout << str.at(i);
}
std::cout << std::endl;

for (auto it = str.begin(); it != str.end(); ++it)
{
    std::cout << *it;
}
std::cout << std::endl;

for (auto& c : str)
{
    std::cout << c;
}
std::cout << std::endl;
```

## Reading from IO
A string can be read from the user as follows:

```c++
std::string str{};

std::cout << "Please enter a string: ";
std::cin >> str;                    // Read one word of input.

std::getline(std::cin, str);        // Read the entire line of input
```

## String manipulations
C++ strings offer several useful operations that can be performed on them.
Consider the following example:

```c++
std::string str1{"Some random text"};
std::string str2{"Some other random text"};

std::cout << "Size of str1: " << str1.size() << std::endl;  // Prints 16
// Direct comparation of strings is possible
if (str1 == str2)
{
    std::cout << "Strings are equal" << std::endl;
}

auto concat = str1 + str2;      // Concatenate strings with '+'
auto app = "Hello";
app.append(" World");           // We can also append to a string easily.

auto sub = concat.substr(3, 5); // Returns a substring in the range [3, 5]

concat.push_back('!');          // Insert a single character at end
```

We can also manipulate individual characters in a string in a similar way to C
as in the following example:

```c++
#include <cctype>

std::string str{"HeLlO wOrLd"};

for (auto& ch : str)
{
    if (std::islower(ch))               // Check if character is lower case
    {
        ch = std::toupper(ch);          // Convert to upper case
    }
}
std::cout << str << std::endl;

for (auto& ch : str)
{
    if (std::isupper(ch))               // Check if character is upper chase
    {
        ch = std::tolower(ch);          // Convert to lower case
    }
}

std::cout << str << std::endl;
```
