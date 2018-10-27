/**
 * In-class exercise 6: Mandos
 * What is the output of the syntactically correct C++ program below?
 */
#include <iostream>

class Widget
{
public:
    Widget()
    {
        std::cout << "Make widget" << std::endl;
    }

  ~Widget()
    {
        std::cout << "Clear widget" << std::endl; 
    }
};

class Window 
{
public:
  Window()
    {
        std::cout << "Make window" << std::endl; 
    }

  ~Window()
    {
        std::cout << "Clear window" << std::endl; 
    }

private:
  Widget mWidget;
};

int main() 
{
    std::cout << "Begin" << std::endl;
    Window w;
    std::cout << "End" << std::endl;
    return 0;
}
