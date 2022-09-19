#ifndef UNTITLED26_MATH_H
#define UNTITLED26_MATH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Math {
    using namespace glm;
    static constexpr auto infinity = std::numeric_limits<float>::infinity();

    static float randf(float min, float max) {
        return min + (max - min) * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }

    static int randi(int min, int max) {
        return min + rand() % (max - min);
    }

};

#include <iostream>
std::ostream& operator << (std::ostream& os, const glm::vec3& v);
std::ostream& operator << (std::ostream& os, const glm::vec4& v);
std::ostream& operator << (std::ostream& os, const glm::mat3x3& m);
std::ostream& operator << (std::ostream& os, const glm::mat4x4& m);

#endif //UNTITLED26_MATH_H
