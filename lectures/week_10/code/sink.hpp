#pragma once

#include <string>
#include <memory>

class Sink
{
public:
    Sink() = default;
    virtual ~Sink() = default;

    virtual void print(std::string const& message) = 0;
};

using SinkPtr = std::shared_ptr<Sink>;
