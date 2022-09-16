//
// Created by Esteban on 8/19/2022.
//

#include <scene/Scene.h>


Intersection Scene::find_closest_intersection (const Ray& ray, float min_time, float max_time) const {
    Intersection closest_hit;
    for (const auto& object: this->objects) {
        auto hit = object->intersection(ray, min_time, max_time);
        if (min_time <= hit.time && hit.time < closest_hit.time) {
            closest_hit = hit;
        }
    }
    return closest_hit;
}

auto Scene::occlusion (const Ray& ray, float min_time, float max_time, const IncidentLight& light) const -> bool {
    for (const auto& object: this->objects) {
        if (object->light == &light) {
            continue;
        }
        const auto hit = object->intersection(ray, min_time, max_time);
        if (min_time <= hit.time && hit.time < max_time) {
            return true;
        }
    }
    return false;
}

auto Scene::compute_direct_illumination (const Math::vec3& P, const Math::vec3& N, const Math::vec3& v, const Material& mat) const -> Math::vec3 {
    auto intensity = this->ambient_light.intensity_value;

    for (const auto& light: this->incident_lights) {
        const auto light_ray = light->incidence(P);

        const auto shadow_hit = this->occlusion(Ray{ P, light_ray.vector }, 0.0001f, light_ray.distance, *light);
        if (shadow_hit) {
            continue;
        }

        const auto N_dot_L = Math::dot(N, light_ray.vector);
        if (N_dot_L > 0) {
            intensity += light->intensity_value * mat.diffuse * N_dot_L;
        }
        if (mat.specular_exp <= 0) {
            continue;
        }
        const auto R = 2.f * N * N_dot_L - light_ray.vector;
        const auto R_dot_V = Math::dot(R, v);
        if (R_dot_V > 0) {
            intensity += light->intensity_value * mat.specular * Math::pow(R_dot_V, mat.specular_exp);
        }
    }
    return intensity;
}



