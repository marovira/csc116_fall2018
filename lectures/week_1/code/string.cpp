#include <iostream>
#include <string>
#include <cctype>
#include <limits>

int main()
{
    // Initializing strings
    {
        std::string str1{};                     // Creates an empty string
        std::string str2{"Some random text"};   // Creates a string with text
        std::string str3 = "Some other text";   // Ditto

        // Read a single word from the user. What happens if more than
        // one word is entered?
        std::string str4{};
        std::cout << "Please enter a word: ";
        std::cin >> str4;
        std::cout << "Entered: " << str4 << std::endl;


        // Read the whole line.
        std::string str5{};
        std::cout << "Please enter a line of text: ";
        // This is done due to the consecutive reads of cin and the fact that we
        // are mixing std::cin >> with std::getline.
        std::cin.ignore();
        std::getline(std::cin, str5);
        std::cout << "Entered: " << str5 << std::endl;
    }

    // Iterate through strings. Notice how all of these for-loops are
    // identical to the ones we saw for vectors
    {
        std::string str{"Some very random and absurd text"};

        // Simple for-loop
        for (std::size_t i = 0; i < str.size(); ++i)
        {
            std::cout << str.at(i);             // Same as with vectors
        }
        std::cout << std::endl;

        // Iterator for loop
        for (auto it = str.begin(); it != str.end(); ++it)
        {
            std::cout << *it;                   // Iterators, same as vectors
        }
        std::cout << std::endl;

        // Ranged for loop
        for (auto& ch : str)
        {
            std::cout << ch;
        }
        std::cout << std::endl;
    }

    // String manipulation
    {
        std::string str1{"Hello darkness my old friend "};
        std::string str2{"I've come to talk with you again"};

        // Query the size
        std::cout << "Size of str1 " << str1.size() << std::endl;

        // We can compare strings directly
        if (str1 == str2)
        {
            std::cout << "Lyrics matched!" << std::endl;
        }
        else
        {
            std::cout << "Lyrics didn't match..." << std::endl;
        }

        // What is the type of concat?
        auto concat = str1 + str2;      // Concatenate using '+'.
        std::string concat2{};
        concat2 += str1;                // Or like this
        concat2 += str2;
        std::cout << concat << std::endl;
        std::cout << concat2 << std::endl;

        std::string app{"Hello "};
        app.append("World!");           // We can also append strings.
        std::cout << app << std::endl;
    }

    // Character manipulation
    {
        std::string str{"HeLlO wOrLd"};
        std::cout << str << std::endl;

        for (auto& ch : str)
        {
            // If the character is lower-case
            if (std::islower(ch))
            {
                ch = std::toupper(ch);      // Convert to upper-case
            }
        }
        std::cout << str << std::endl;

        for (auto& ch : str)
        {
            // If the character is upper-case
            if (std::isupper(ch))
            {
                ch = std::tolower(ch);      // Convert to lower-case
            }
        }
        std::cout << str << std::endl;
    }

    return 0;
}
