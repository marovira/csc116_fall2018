#include "logger.hpp"

#include <map>

struct Logger::LoggerImpl
{
    LoggerImpl() = default;

    std::map<std::string, SinkPtr> sinks;
};

Logger::Logger() :
    mImpl{std::make_unique<LoggerImpl>()}
{  }

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Logger::print(std::string const& stream, std::string const& message)
{
    // First check if the stream actually exists.
    if (mImpl->sinks.find(stream) != mImpl->sinks.end())
    {
        // The sink exists, so print the message.
        mImpl->sinks[stream]->print(message);
    }
}

void Logger::addSink(std::string const& name, SinkPtr const& sink)
{
    mImpl->sinks.insert({name, sink});
}

