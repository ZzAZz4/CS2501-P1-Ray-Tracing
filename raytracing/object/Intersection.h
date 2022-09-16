#ifndef UNTITLED26_INTERSECTION_H
#define UNTITLED26_INTERSECTION_H

#include <object/Ray.h>

struct Intersection {
    Math::vec3 out_normal;
    const Shape* object;
    float time;

    Intersection () noexcept
        : out_normal(), time(Math::infinity), object(nullptr) {
    }

    Intersection (float time, const Math::vec3& normal, const Shape* shape) noexcept
        : out_normal(Math::normalize(normal)), time(time), object(shape) {
    }

    bool operator < (const Intersection& other) const noexcept {
        return time < other.time;
    }
};

#endif //UNTITLED26_INTERSECTION_H
