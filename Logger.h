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


namespace internal {
    class Logger {
    public:


        template <typename T>
        void log(
            const LogLevel level,
            const std::string_view &filename,
            const int line,
            const std::string_view &function_caller,
            const T &t
        ) {
            if (permission(level)) return;
            stream << "["; log_level(level); stream << "] ";
            stream << filename << ":" << line << "-" << function_caller << ": ";
            stream << t;
            stream << std::endl;
        }

        template <typename T>
        void log(
            const LogLevel level,
            const std::string_view &filename,
            const int line,
            const std::string_view &function_caller,
            const T &t,
            const std::function<std::string(const T &t)> &stringify
        ) {
            if (permission(level)) return;
            stream << "["; log_level(level); stream << "] ";
            stream << filename << ":" << line << "-" << function_caller << ": ";

            stream << stringify(t);
            stream << std::endl;
        }

        void redirect(std::ostream &os) { stream.rdbuf(os.rdbuf()); }
        void set_permission(const LogLevel &level) { log_permission = static_cast<std::uint8_t>(level); }


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

        //Logger(const std::ostream &stream) : stream(stream.rdbuf()) {}
        friend class Singleton<Logger>;
        Logger() {};
    };
}
