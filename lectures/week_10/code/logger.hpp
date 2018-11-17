#pragma once

#include "sink.hpp"

#include <memory>

class Logger
{
    // Hide the constructor for the class so no one but us can create it.
    Logger();
    ~Logger() = default;

    // We don't want any copy semantics.
    Logger(Logger const&) = delete;
    void operator=(Logger const&) = delete;

public:
    static Logger& getInstance();

    void print(std::string const& stream, std::string const& message);
    void addSink(std::string const& name, SinkPtr const& sink);

private:
    struct LoggerImpl;
    std::unique_ptr<LoggerImpl> mImpl;
};
