#ifndef UNTITLED26_SCENE_H
#define UNTITLED26_SCENE_H

#include <object/Shape.h>
#include <object/Ray.h>

#include <light/Light.h>
#include <light/AmbientLight.h>
#include <light/DirectionalLight.h>
#include <light/PointLight.h>

#include <vector>
#include <memory>


struct Scene {
    using Objects = std::vector<std::unique_ptr<Shape>>;
    using IncidentLights = std::vector<std::unique_ptr<IncidentLight>>;

    Objects objects;
    IncidentLights incident_lights;
    AmbientLight ambient_light;
    Math::vec3 background_color;

    [[nodiscard]]
    auto compute_direct_illumination (const Math::vec3& P, const Math::vec3& N, const Math::vec3& v, const Material& mat) const -> Math::vec3;

    [[nodiscard]]
    Intersection find_closest_intersection (const Ray& ray, float min_time, float max_time) const;

    [[nodiscard]]
    auto occlusion (const Ray& ray, float min_time, float max_time, const IncidentLight& light) const -> bool;

    template<typename T>
    auto create_object (auto&& ... args);

    template<typename T>
    auto create_light (auto&& ... args);

    [[nodiscard]]
    static auto trace (const Ray& ray, const Scene& scene, float min_time, float max_time, int bounces) -> Math::vec3;
};


template<typename T>
auto Scene::create_object (auto&& ... args) {
    auto ptr = std::make_unique<T>(std::forward<decltype(args)>(args)...);
    T* underlying = ptr.get();
    objects.emplace_back(std::move(ptr));
    return underlying;
}

template<typename T>
auto Scene::create_light (auto&& ... args) {
    auto ptr = std::make_unique<T>(std::forward<decltype(args)>(args)...);
    T* underlying = ptr.get();

    incident_lights.emplace_back(std::move(ptr));
    return underlying;
}

#endif //UNTITLED26_SCENE_H
