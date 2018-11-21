#pragma once

#include "sink.hpp"

#include <iostream>

class StreamSink : public Sink
{
public:
    StreamSink() = default;
    ~StreamSink() = default;

    void print(std::string const& message) override
    {
        std::cout << message << std::endl;
    }
};
