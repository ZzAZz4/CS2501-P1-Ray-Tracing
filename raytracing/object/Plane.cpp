//
// Created by Esteban on 8/25/2022.
//

#include <object/Plane.h>
#include <object/Ray.h>


Intersection Plane::intersection (const Ray& ray, float, float) const {
    const float denominator = Math::dot(this->abc_, ray.direction);
    if (denominator == 0.f) {
        return {};
    }
    const auto time = -(Math::dot(abc_, ray.origin) + d) / denominator;
    return { time, this->abc_, this };
}

