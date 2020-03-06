#include "CustomClass.h"
#include "Logger.h"
#include <fstream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <functional>

std::string glm_to_string(const glm::vec3 &v) {
    return glm::to_string(v);
}

int main() {
    PublicCustomClass public_class;
    PrivateCustomClass private_class;
    glm::vec3 glm_vec{3,1,4};

    // std::ofstream fs("log_test.txt", std::ios_base::out);

    // Logger::redirect(fs);
    // Logger::permission(LogLevel::ERROR);
    
    // C++20
    Logger::log(LogLevel::DEBUG, "BOOM");
    Logger::log(LogLevel::CRITICAL, "BOOM - CRITICAL");
    Logger::log(LogLevel::ERROR, "BOOM - ERROR");
    Logger::log(LogLevel::DEBUG, public_class);
    Logger::log(LogLevel::DEBUG, private_class);
    Logger::log(LogLevel::DEBUG, glm_vec, {glm_to_string});
    Logger::log(LogLevel::DEBUG, glm_vec, {glm::to_string<glm::vec3>});

    // Log(Severity, TAG) << object;
    // Log(Severity) << {TAG, message};
    // Log(Severity) << {TAG, object};
    
    
    // C++ old
    /*
    // LOG_REDIRECT(fs);
    // LOG_PERMISSION(LogLevel::ERROR);
    LOG(LogLevel::DEBUG, "BOOM");
    LOG(LogLevel::CRITICAL, "BOOM - CRITICAL");
    LOG(LogLevel::ERROR, "BOOM - ERROR");
    LOG(LogLevel::DEBUG, public_class);
    LOG(LogLevel::DEBUG, private_class);
    LOG_STRINGIFY_OBJECT(LogLevel::DEBUG, glm_vec, {glm_to_string});
    LOG_STRINGIFY_OBJECT(LogLevel::DEBUG, glm_vec, {glm::to_string<glm::vec3>});
    */
    return 0;
}
