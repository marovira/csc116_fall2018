#include <iostream>
#include <memory>

class Parent
{
public:
    Parent()
    {
        std::cout << "Parent constructor" << std::endl;
    }

    virtual ~Parent() = default;

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
        std::cout << "Foo" << std::endl;
    }

};

int main()
{
    using ParentPtr = std::shared_ptr<Parent>;

    ParentPtr p = std::make_shared<Child>();
    p->foo();

    return 0;
}
