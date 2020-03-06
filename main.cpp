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

    Logger log;

    Record record{"TAG", private_class};

    log(LogLevel::DEBUG) << "BOOM" << std::endl;
    log(LogLevel::DEBUG) << record << std::endl;



    return 0;
}
//[ccls 4] [E] initializer list cannot be used on the right hand side of operator '<<'
