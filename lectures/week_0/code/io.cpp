// Simple example on how to read input from the user. This program will 
// continuously read an integer value from the user until '0' is entered.
#include <iostream>
#include <limits>

int main()
{
    // Initialize our holding variable.
    int in{0};

    while (true)
    {
        std::cout << "Please enter a number: ";
        std::cin >> in;

        // Check to see if there were any errors.
        if (std::cin.fail())
        {
            // First, clear out the IO error flag.
            std::cin.clear();

            // Now tell cin to ignore everything left in the line.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                    '\n');
            std::cout << "Invalid input detected. Please enter an integer.";
            std::cout << std::endl;
            continue;
        }

        if (in == 0)
        {
            std::cout << "Exiting..." << std::endl;
            break;
        }

        std::cout << "Entered " << in << std::endl;
    }

    return 0;
}
