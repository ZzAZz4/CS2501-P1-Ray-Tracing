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
    Math::vec3 direct_color (const Math::vec3& P, const Math::vec3& N, const Math::vec3& v, const Material& m) const;

    [[nodiscard]]
    Intersection find_closest_intersection (const Ray& ray, float min_time, float max_time) const;

    [[nodiscard]]
    bool occlusion (const Ray& ray, float min_time, float max_time, const IncidentLight& light) const;

    template<typename T>
    T* create_object (auto&& ... args);

    template<typename T>
    T* create_light (auto&& ... args);

    [[nodiscard]]
    static Math::vec3 trace (const Ray& ray, const Scene& scene, float min_time, float max_time, int bounces);
};


template<typename T>
T* Scene::create_object (auto&& ... args) {
    auto ptr = std::make_unique<T>(std::forward<decltype(args)>(args)...);
    T* underlying = ptr.get();
    objects.emplace_back(std::move(ptr));
    return underlying;
}

template<typename T>
T* Scene::create_light (auto&& ... args) {
    auto ptr = std::make_unique<T>(std::forward<decltype(args)>(args)...);
    T* underlying = ptr.get();

    incident_lights.emplace_back(std::move(ptr));
    return underlying;
}

#endif //UNTITLED26_SCENE_H
