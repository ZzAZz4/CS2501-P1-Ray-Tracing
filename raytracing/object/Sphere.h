//
// Created by Esteban on 8/17/2022.
//

#ifndef UNTITLED26_SPHERE_H
#define UNTITLED26_SPHERE_H

#include <object/Shape.h>


struct Sphere : Shape {
    Math::vec3 position;
    float radius;

    constexpr Sphere (const Math::vec3& position_, float radius_, Material material_)
        : Shape(material_), position(position_), radius(radius_) {}

    [[nodiscard]] Intersection intersection (const Ray& ray, float min_time, float max_time) const override;
//    [[nodiscard]] auto normal (const Math::vec3& point) const -> Math::vec3 override;
};


#endif //UNTITLED26_SPHERE_H
