/**
 * In-class exercise 8: Orome
 * What is the output of the following syntactically correct C++ program?
 */
#include <iostream>
#include <memory>

class Parent
{
public:
    Parent()
    {
        std::cout << "Parent constructor" << std::endl;
    }

    virtual ~Parent()
    {
        std::cout << "Parent destructor" << std::endl;
    }

    virtual void foo()
    {
        std::cout << "Parent foo" << std::endl;
    }
};

class Child : public Parent
{
public:
    Child()
    {
        std::cout << "Child constructor" << std::endl;
    }

    ~Child()
    {
        std::cout << "Child destructor" << std::endl;
    }

    void foo() override
    {
        std::cout << "Child foo" << std::endl;
    }
};

int main()
{
    std::shared_ptr<Parent> p = std::make_shared<Child>();
    p->foo();
    return 0;
}
