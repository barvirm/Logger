#pragma once
#include <ostream>
#include <sstream>
#include <functional>
#include <iostream>

#include <string_view>
#include <experimental/source_location>

#include "Singleton.h"

#define LOG(level, object) internal::Logger::instance().log(level, __FILE__, __LINE__, __PRETTY_FUNCTION__, object)
#define LOG_REDIRECT(ostream) internal::Logger::instance().redirect(ostream)
#define LOG_STRINGIFY_OBJECT(level, object, stringify_func) internal::Logger::instance().log(level, __FILE__, __LINE__, __PRETTY_FUNCTION__, object, stringify_func)
#define LOG_PERMISSION(level) internal::Logger::instance().set_permission(level)



enum class LogLevel : std::uint8_t { 
    NOTICE = 0,
    DEBUG = 1,
    INFORMATION = 2,
    WARNING = 3,
    ERROR = 4, 
    CRITICAL = 5
};

template<typename T>
class Record {
public:

    Record(const std::string_view &tag, const T &t) : tag(tag), t(t) {}
    friend std::ostream &operator<<(std::ostream &os, const Record &record) {
        os << "{" << record.tag << "} " << record.t;
        return os;
    }
protected:
    const std::string_view tag;
    const T &t; 
};

class Logger { 
public:

    Logger() = default;

    void redirect(std::ostream &os) { 
        stream.rdbuf(os.rdbuf()); 
    }

    std::ostream &operator() (
        const LogLevel &level, 
        const std::experimental::source_location source = std::experimental::source_location::current()
    ) {
        if (permission(level)) return stream;
        stream << "["; log_level(level); stream << "] ";
        stream << source.file_name() << ":" << source.line() << "-" << source.function_name() << ": ";
        return stream;
    }

    void set_permission(const LogLevel &level) { 
        log_permission = static_cast<std::uint8_t>(level); 
    }


protected:
    void log_level(LogLevel level) {
        switch(level) {
            case LogLevel::CRITICAL:    stream << "CRITICAL"; break;
            case LogLevel::ERROR:       stream << "ERROR"; break;
            case LogLevel::WARNING:     stream << "WARNING"; break;
            case LogLevel::NOTICE:      stream << "NOTICE"; break;
            case LogLevel::INFORMATION: stream << "INFORMATION"; break;
            case LogLevel::DEBUG:       stream << "DEBUG"; break;
        }
    }
    
    bool permission(const LogLevel &level) {
        return log_permission > static_cast<std::uint8_t>(level);
    }

    std::ostream stream{std::cout.rdbuf()};
    std::uint8_t log_permission = 0;
};
