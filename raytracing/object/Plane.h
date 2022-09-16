//
// Created by Esteban on 8/25/2022.
//

#ifndef UNTITLED26_PLANE_H
#define UNTITLED26_PLANE_H

#include <object/Shape.h>
#include <tools/Math.h>


struct Plane : public Shape {
    Math::vec3 abc_;
    float d;

    constexpr Plane (const Math::vec4& coefficients, const Material& material) :
        Shape(material),
        abc_(Math::vec3{ coefficients}), d(coefficients.w) {}

    [[nodiscard]] Intersection intersection (const Ray& ray, float min_time, float max_time) const override;
//    [[nodiscard]] auto normal (const Math::vec3& point) const -> Math::vec3 override;
};


#endif //UNTITLED26_PLANE_H
