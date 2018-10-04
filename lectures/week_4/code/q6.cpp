#include <iostream>
#include <string>

// We want a struct that holds three things: hours, minutes, and am/pm. The
// first two can be easily held by ints. The last part we can handle with either
// a bool or a string. Here we use a bool.
struct Time
{
    int hours{0};
    int minutes{0};
    bool isAm;
};

int main()
{
    std::cout << "Please enter a time in 24-hour format: ";
    std::string input{};
    std::cin >> input;

    // Now let's split the string into two portions based on ':'.
    std::string hrs, mins;
    // We use this to keep track of when we have seen the colon.
    bool seenColon{false};
    for (auto ch : input)
    {
        if (ch != ':' && !seenColon)
        {
            hrs.push_back(ch);
        }

        if (ch == ':')
        {
            seenColon = true;
        }

        if (ch != ':' && seenColon)
        {
            mins.push_back(ch);
        }
    }

    // We now have the hours and minutes split. So let's convert them into
    // integers.
    auto h = std::stoi(hrs);
    auto m = std::stoi(mins);
    Time t{h, m, false};

    // Finally, we need to convert the 24-hour format to 12-hours.
    if (h < 12)
    {
        t.isAm = true;
    }
    else
    {
        t.hours -= 12;
    }

    // Now print it.
    std::cout << "It is: " << t.hours << ":" << t.minutes;
    if (t.isAm)
    {
        std::cout << " am" << std::endl;;
    }
    else
    {
        std::cout << " pm" << std::endl;
    }

    return 0;
}
