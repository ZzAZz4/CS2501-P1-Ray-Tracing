#ifndef UNTITLED26_RAY_H
#define UNTITLED26_RAY_H

#include <tools/Math.h>

struct Scene;
struct Shape;


struct Ray {
    Math::vec3 origin;
    Math::vec3 direction;


    Ray (const Math::vec3& origin, const Math::vec3& direction) noexcept
        : origin(origin), direction(Math::normalize(direction)) {
    }

    static auto between (const Math::vec3& a, const Math::vec3& b) -> Ray {
        return { a, b - a };
    }

    auto at (float time) const noexcept -> Math::vec3 {
        return origin + time * direction;
    }
};


#endif //UNTITLED26_RAY_H
