#ifndef UNTITLED26_CYLINDER_H
#define UNTITLED26_CYLINDER_H

#include <object/Shape.h>


struct Cylinder : public Shape {
    Math::vec3 base;
    Math::vec3 top;
    float radius;

    Cylinder(const Math::vec3& base, const Math::vec3& top, const float radius, const Material& material) noexcept
        : Shape{ material }, base(base), top(top), radius(radius) {
    }

    [[nodiscard]] Intersection intersection (const Ray& ray, float min_time, float max_time) const override;
};

#endif //UNTITLED26_CYLINDER_H
