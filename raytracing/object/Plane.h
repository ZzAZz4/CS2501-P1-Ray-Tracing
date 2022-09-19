#ifndef UNTITLED26_PLANE_H
#define UNTITLED26_PLANE_H

#include <object/Shape.h>
#include <tools/Math.h>


struct Plane : public Shape {
    Math::vec3 abc_;
    float d;

    Plane (const Math::vec4& coefficients, const Material& material) :
        Shape(material),
        abc_(Math::vec3{Math::normalize(coefficients)}), d(Math::normalize(coefficients).w) {}

    [[nodiscard]] Intersection intersection (const Ray& ray, float min_time, float max_time) const override;
};


#endif //UNTITLED26_PLANE_H
