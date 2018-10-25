/**
 * In-class exercise 5: Aule
 * On the back of the page write a syntactically correct C++ class Widget such
 * that the code shown below compiles and the provided output is produced.
 */
#include <iostream>

class Widget
{
public:
    Widget(int x) :
        mX{x}
    {  }

    void process(int coeff)
    {
        std::cout << "Process: " << mX * coeff << std::endl;
    }

private:
    int mX;
};

int main()
{
    Widget w1{10}, w2{10}, w3{100};
    w1.process(116);
    w2.process(5);
    w3.process(5);
    return 0;
}
