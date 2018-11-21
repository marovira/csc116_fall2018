#include "pimpl.hpp"

#include <iostream>

struct Widget::WidgetImpl
{
    WidgetImpl() :
        id{"Default"}
    {  }

    std::string id;
};

Widget::Widget() :
    mImpl{std::make_unique<WidgetImpl>()}
{  }

void Widget::setId(std::string const& id)
{
    mImpl->id = id;
}

void Widget::id() const
{
    std::cout << mImpl->id << std::endl;
}


int main()
{
    Widget w;
    w.setId("widget");
    w.id();

    // We can't do copies of Widget until we define the copy semantics
    // ourselves.
    // auto w2 = w;

    return 0;
}
