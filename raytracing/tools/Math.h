#ifndef UNTITLED26_MATH_H
#define UNTITLED26_MATH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <random>
#include <concepts>

namespace Math {
    using namespace glm;

    constexpr auto cross(const Math::vec3& a, const Math::vec3& b) noexcept {
        return Math::vec3{
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        };
    }


    static constexpr auto infinity = std::numeric_limits<float>::infinity();
};

namespace Math {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    template <std::floating_point T>
    auto random(T min, T max, auto generator = gen) noexcept -> T {
        std::uniform_real_distribution<T> dis(min, max);
        return dis(gen);
    }

    template <std::integral T>
    auto random(T min, T max, auto generator = gen) noexcept -> T {
        std::uniform_int_distribution<T> dis(min, max);
        return dis(gen);
    }
}



#endif //UNTITLED26_MATH_H
