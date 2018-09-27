# Structs
In C, `struct` was basically used as a container for data that had to be
packaged together, either for the sake of convenience and maintainability, or
for other reasons. In C++, `struct` is significantly more powerful and can do
more things. As we will see, strings, vectors, and structs all belong to the
same family tree.

To declare a new struct, we do the following:

```c++
struct Example
{
    // Data goes here.
    int a;
    bool b;
};
```

Once we have a struct declared, we can use it as follows:

```c++
Example ex;         // Create a new struct. Type of ex is Example.
```

It is easy to see how the syntax for creating a new variable of type struct is
very similar to creating a string or vector. The difference is that, as defined,
the members of the struct will be initialized to undefined values, in the same
way C created uninitialized variables. Comparing back to vectors and strings,
when we create a new vector it is already initialized to size 0, while a string
is created as empty.

> **Aside:**
> The idea that things are fully initialized when created is called RAII
> (Resource Allocation Is Initialization) and is a very common practice in C++.
> You may read more about RAII
> [here](https://en.cppreference.com/w/cpp/language/raii).

Since vectors and strings can do this automatically, it would be desirable for
our structs to be able to do the same. We can accomplish this as follows:

```c++
struct Example
{
    int a{};        // Fine, a is initialized with default value 0
    bool b{false};  // Fine, b is initialized with default value false
};
```

Now when we create a struct as before, the data inside is already initialized
and we can proceed as we would normally. To access the data inside the struct
we do the following:

```c++
Example x;
x.a = 5;        // Fine, member 'a' is now 5
x.b = true;     // Fine, member 'b' is now true
```

## Word Histogram
Let us explore an example to see how structs could be useful. Suppose that given
a text file, we wish to determine the number of unique words in the file, and
for each unique word we want to know how many times it appears in the text.
We begin by reading from the file line by line:

```c++
int main()
{
    std::string filename{"text.txt"};
    std::ifstream file;
    file.open(filename);

    if (file.is_open())
    {
        std::string line{};
        while (std::getline(file, line))
        {
            // Do something here.
        }

        file.close();
    }

    return 0;
}
```

Given the line of text, we can use the split function that we wrote
earlier to retrieve the words per line.

```c++
while (std::getline(file, line))
{
    auto words = split(line);
}
```

Now that we have the words it is a matter of only storing the unique words.
For that we use a vector that will hold them, but we need a way of
determining whether a word has been seen before or not. To accomplish this,
we create a function that looks like this:

```c++
bool find(std::vector<string> const& words, std::string const& word)
{
    for (auto w : words)
    {
        if (w == word)
        {
            return true;
        }
    }

    return false;
}
```

The sole purpose of this function is to determine whether a given word
exists in the provided vector or not. We can now integrate this into our
program as follows:

```c++
int main()
{
    // ...
    std::vector<std::string> uniques;

    if (file.is_open())
    {
        std::string line{};
        while (std::getline(file, line))
        {
            auto words = split(line);
            for (auto word : words)
            {
                if (!find(uniques, word))
                {
                    uniques.push_back(word);
                }
            }
        }
        // ...
    }
}
```

We now have the list of unique words in the file. All that remains is to
determine how many times each word appears in the text. To do this, we have
a few options:

1. We could create a new vector of integers to hold the count for each word.
   Every time a word is encountered the vector would be updated. The
   downside of this is that we would need to maintain two vectors.
2. We could package both vectors into a *single* vector that holds both the
   unique words and the counts for each. To accomplish this we would need a
   way of bundling them together.

We proceed with the second option. In order to bundle the data together we use a
struct. We declare one as follows:

```c++
struct WordData
{
    std::string word{};
    int count{0};
};
```

We now replace the `uniques` vector with a vector of `WordData`:

```c++
std::vector<WordData> stats;
```

We are now left with a couple of problems to solve. First, the `find`
function we wrote earlier needs to be updated to reflect the new type of the
vector. Second, we need a way of updating the counts. As written, the
function only tells us whether a word exists in the list. What we would want
to know is the *location* of the word in the vector (if it is there). We
proceed as follows:

```c++
int find(std::vector<WordData> const& words, std::string const& word)
{
    // We use this to keep track of the index we're at.
    int idx{0};
    for (auto w : words)
    {
        if (w.word == word)
        {
            // Found the word, so return its index.
            return idx;
        }
        ++idx;
    }

    // Couldn't find it, so return an invalid index.
    return -1;
}
```

The logic behind the function is the following: we try to find the location
in the vector where the provided word is located. If we find it, return the
index. The issue begins when the word is not in the vector. Since we cannot
return any value that is non-zero due to the fact that the calling code would
have no way of knowing whether the index is valid or not, we return a
specific value that cannot be an index: in this case -1. Finally, our main
function is completed as follows:

```c++
while (std::getline(file, line))
{
    auto words = split(line);

    for (auto word : words)
    {
        auto idx = find(stats, word);
        if (idx != -1)
        {
            stats.at(idx).count++;
            continue;
        }

        WordData data;
        data.word = word;
        data.count = 1;
        stats.push_back(data);
    }
    // ...
}
```

This completes the program.
