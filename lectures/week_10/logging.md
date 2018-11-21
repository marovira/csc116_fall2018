# Case Study: A Logging System
So far we have covered quite a substantial range of topics. To summarize, we
have seen:

* classes,
* operators,
* inheritance and polymorphism,
* pointers

What we will do now is to study a case where we can see how all of these
concepts come together to form something useful.

## Logging in C++
It is often times useful when we write code to have a way of producing output in
a specific format. This format can then be used by other programs to easily
pinpoint when an error occurs for example, or as a log of what the program did.
These systems are called Loggers and exist in many C++ applications, from
operating systems, databases, rendering engines, etc. More importantly, this
output is usually needed in several places. As a result, we may need to output
the same thing to multiple locations, from the command line to a specific file.
Our task is to design a very simple logging system that is:

* extensible,
* easy to use,
* globally accessible.

## A First Attempt
We could begin our design by simply using `cout` as follows:

```c++
void printMessage(std::string const& message)
{
    // Format the message here.
    std::cout << message << std::endl;
}
```

While this could work, what if we also wanted to output to a file? Or to a
different stream altogether?
Since we know that function overloading is possible, we can simply do this:

```c++
void printMessage(std::fstream const& stream, std::string const& message)
{
    // Print to a file.
}
```

Fine, but where does the `stream` come from? Who is responsible for not only
*opening* the file for writing, but making sure that the stream does **not** go
out of scope until the program ends? What if we wanted to write to multiple
files?

## The Infamous Singleton
The problem that we are facing here is that we need to maintain several pieces
of data at a global scope. We could simply declare the files individually in a
header file along with the functions to print, but we know from before that
global variables lead to several complications through overshadowing. Moreover
we don't want to have to keep a collection of independent variables. We could
create a class to hold them together along with the functions and keep a global
instance, which again leads to problems of overshadowing. So how can we solve
this?

In C++ there's a very common pattern called the singleton. In essence, the
singleton is a class that by design guarantees the following properties:

1. It is globally accessible (just include the header),
2. There is only **one** instance of the class in the entire program,
3. It **cannot** be accessed except through a specific function.

So it seems that this will solve our problems. Let's see how we can implement
the pattern. In a file called `logger.hpp` we write the following:

```c++
class Logger
{
    Logger();
    ~Logger() = default;

};
```

Notice that since we didn't add an access specifier, then the default is
private, which means that both the constructor and destructor are accessible
only within the class itself. This means that there is no way to do the
following:

```c++
Logger l;       // Error: Logger was declared private.
```

So we're on a good path to ensure that only one instance exists. But what about
copying? We know from the `unique_ptr` that we can delete certain functions. So
let's add that in:

```c++
class Logger
{
    Logger();
    ~Logger() = default;

    Logger(Logger const&) = delete;
    void operator=(Logger const&) = delete;

};
```

By adding these two lines we have now ensured that no copies can be made of the
instance, so we have already fulfilled two of the three requirements of the
singleton. Now we have to deal with the access function:

```c++
class Logger
{
    Logger();
    ~Logger() = default;

    Logger(Logger const&) = delete;
    void operator=(Logger const&) = delete;

public:
    static Logger& getInstance();

};
```

Since we need to give access to the instance, we now make it public. Moreover,
since the function **must** work without an existing instance of the class, it
must be made static. We now fill in the rest of the class:

```c++
class Logger
{
    Logger();
    ~Logger() = default;

    Logger(Logger const&) = delete;
    void operator=(Logger const&) = delete;

public:
    static Logger& getInstance();
    void print(std::string const& message);

private:
    struct LoggerImpl;
    std::unique_ptr<LoggerImpl> mImpl;

};
```

We also use another pattern that we have discussed: PIMPL. Since presumably we
will be modifying this class heavily, we may want to hide the private data
inside the `LoggerImpl` struct, which will reduce compile times. The fact that
the `std::unique_ptr` cannot be copied works in our favour, since we don't want
copies made of the Logger. 

In `logger.cpp` we now add the following definitions:

```c++
struct Logger::LoggerImpl
{
    LoggerImpl() = default;
};

Logger::Logger() :
    mImpl{std::make_unique<LoggerImpl>()}
{  }

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}
```

The definition of the `getInstance` function fills in the remaining requirement
of the singleton. By marking the instance as `static` it makes is so that it's
lifespan is now the entire program. By encapsulating it within the function
itself we ensure that the only way to access it is *through* the function
itself, while returning by reference falls in line with the no copying
requirement.

## Sinks
So far we have most of the general structure of the `Logger` setup. All that is
missing is to provide a way to create multiple outputs. For example, we might
need to output to `cout` as well as a file. All of these operations ultimately
require a single interface: a way to print. Based on this, we simply create a
base interface that everyone must follow and use that.

In `sink.hpp` we add the following:

```c++
class Sink
{
public:
    Sink() = default;
    virtual ~Sink() = default
    
    virtual void print(std::string const& message) = 0;
};

using SinkPtr = std::shared_ptr<Sink>;
```

Since we are going to be operating on the children of the class through
polymorphism, we need to make the destructor virtual. Finally, since the class
does not really need to do much outside of providing an interface, we make it's
only member function pure virtual. The `using` is merely a convenience that will
be useful later.

It is easy to see that if we wanted to add things like the date or the time
before the actual message, it would be very simple to add a single function here
that will do that for us. For the sake of simplicity we will leave it as is.

We now create a new file called `streamsink.hpp` and add the following:

```c++
class StreamSink : public Sink
{
public:
    StreamSink() = default
    ~StreamSink() = default;

    void print(std::string const& message) override
    {
        std::cout << message << std::endl;
    }
};
```

This child will act as our way of printing to `cout`. Once again, we can simply
create new children for files and so forth as required. All that is missing is
to provide a way for the logger to have new sinks added to it, as well as a way
to select the sink we want.

```c++
class Logger
{
    // ...
public:
   void addSink(std::string const& name, SinkPtr const& sink);
   void print(std::string const& stream, std::string const& message);

    // ...
};
```

In order to provide a way of selecting the sink, we assign each one of them a
name that the user can then select for printing. This implies that we will be
using a `std::map` to map the names to the sinks. Our `logger.cpp` now becomes:

```c++
struct Logger::LoggerImpl
{
    LoggerImpl() = default;

    std::map<std::string, SinkPtr> sinks;
};

// ...
void Logger::addSink(std::string const& name, SinkPtr cosnt& sink)
{
    mImpl->sinks.insert({name, sink});
}

void Logger::print(std::string const& stream, std::string const& message)
{
    if (mImpl->sinks.find(stream) != mImpl->sinks.end())
    {
        mImpl->sinks[stream]->print(message);
    }
}
```

These last two functions complete the logger. The first simply inserts the new
sink, while the second does the actual printing. Notice that we check to see if
we have a sink by that name *before* attempting to print. We could add some
error-handling code here if desired.

## Using our Logger
Once that everything is setup, we can now use our Logger:

```c++
#include "logger.hpp"
#include "streamsink.hpp"

void foo()
{
    Logger::getInstance().print("cout", "Foo message");
}

int main()
{
    // Add the sinks here.
    Logger::getInstance().addSink("cout", std::make_shared<StreamSink>());
    Logger::getInstance().print("cout", "Hello World");
}
```
