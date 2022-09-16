//
// Created by Esteban on 8/17/2022.
//

#ifndef UNTITLED26_RAY_H
#define UNTITLED26_RAY_H

#include <tools/Math.h>

struct Scene;
struct Shape;

struct RayHit {
    const Shape* object;
    float time;
};

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

    [[nodiscard]]
    auto trace (const Scene& scene, float min_time, float max_time, int bounces) const -> Math::vec3;
};


#endif //UNTITLED26_RAY_H
