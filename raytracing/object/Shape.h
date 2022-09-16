//
// Created by Esteban on 8/17/2022.
//

#ifndef UNTITLED26_SHAPE_H
#define UNTITLED26_SHAPE_H

#include <tools/Math.h>
#include <object/Intersection.h>
#include <object/Material.h>

struct Ray;
struct Light;

struct Shape {
    Material material;
    const Light* light;

    constexpr explicit Shape(const Material& material_) : material(material_), light(nullptr) {}
    constexpr Shape(const Material& material_, const Light* light) : material(material_), light(light) {}
    virtual ~Shape() = default;

    [[nodiscard]] virtual Intersection intersection (const Ray& ray, float min_time, float max_time) const = 0;
//    [[nodiscard]] virtual auto normal (const Math::vec3& point) const -> Math::vec3 = 0;
};

#endif //UNTITLED26_SHAPE_H
