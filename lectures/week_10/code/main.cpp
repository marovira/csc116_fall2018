#include "logger.hpp"
#include "streamsink.hpp"

void foo()
{
    Logger::getInstance().print("cout", "Foo message");
}

int main()
{
    Logger::getInstance().addSink("cout", std::make_shared<StreamSink>());
    Logger::getInstance().print("cout", "Hello World");
    foo();

    return 0;
}
