#include <iostream>

class Widget
{
public:

    // Define the empty constructor.
    Widget() :
        mNum{0}
    {
        std::cout << "In empty constructor" << std::endl;
    }

    // Now define a constructor with arguments.
    Widget(int num) :
        mNum{num}
    {
        std::cout << "In argument constructor" << std::endl;
    }

    ~Widget()
    {
        std::cout << "In destructor" << std::endl;
    }

    void printGreeting()
    {
        // Fine, we have access to mNum because we are in the class.
        mNum += 5;
        std::cout << "Hello World! " << mNum << std::endl;
    }

private:
    int mNum;
};

int main()
{
    Widget w;           // Fine, create a widget with empty constructor.
    w.printGreeting();  // Fine, printGreeting is public.
    // w.mNum;          // error: 'mNum' is a private member of 'Widget'.

    {
        // Widget w2();     // Most vexing parse.
        Widget w2{};
        w2.printGreeting();
    }

    {
        Widget w3(10);      // Fine, mNum is now 10.
        w3.printGreeting();
    }

    return 0;
}
