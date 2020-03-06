#pragma once

#include <glm/glm.hpp>
#include <ostream>

class PublicCustomClass {
public:
    glm::vec3 test{1,2,3};
};

// Can access only public members
std::ostream &operator<<(std::ostream &os, const PublicCustomClass& cc)
{
    os << "PublicCustomClass = {" << cc.test.x << " " << cc.test.y << " " << cc.test.z << "}";
    return os;
}




class PrivateCustomClass {
    // as a friend can access private members
    friend std::ostream &operator<<(std::ostream &os, const PrivateCustomClass &cc) {
        os << "PrivateCustomClass = {";
        os << cc.test.x << " ";
        os << cc.test.y << " ";
        os << cc.test.z << " ";
        os << cc.test.w << "}";
        return os;
    };
private:
    glm::vec4 test{4,5,6,7};
};

