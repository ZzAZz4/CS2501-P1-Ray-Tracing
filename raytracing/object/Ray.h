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

    static Ray between (const Math::vec3& a, const Math::vec3& b) {
        return { a, b - a };
    }

    Math::vec3 at (float time) const noexcept {
        return origin + time * direction;
    }
};


#endif //UNTITLED26_RAY_H
