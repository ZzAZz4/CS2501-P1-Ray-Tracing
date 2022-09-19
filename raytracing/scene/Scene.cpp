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


struct Coefficients {
    float kr, kt, eta;
};

Math::vec3 refraction (const Math::vec3& I, const Math::vec3& N, float eta) {
    const auto cos_theta = Math::abs(Math::clamp(Math::dot(I, N), -1.f, 1.f));
    const auto k = 1.f - eta * eta * (1.f - cos_theta * cos_theta);
    return k < 0.f ? Math::vec3(0.f) : eta * I + (eta * cos_theta - sqrtf(k)) * N;
}

float schlick (float ior, float cos_theta) {
    const auto r0_sqrt = (1.f - ior) / (1.f + ior);
    const auto r0 = r0_sqrt * r0_sqrt;
    const auto r_theta = r0 + (1.f - r0) * std::pow(1.f - cos_theta, 5.f);
    return r_theta;
}

Coefficients fresnel (Math::vec3 I, Math::vec3 N, const Material& material) {
    if (material.index_of_refraction == 0.f) {
        return { material.reflection, 0.f, 1.f };
    }
    const auto cos_theta = Math::clamp(Math::dot(I, N), -1.f, 1.f);
    const auto eta = cos_theta > 0 ? material.index_of_refraction : 1.f / material.index_of_refraction;
    const auto has_total_internal_reflection = eta * Math::sqrt(1 - cos_theta * cos_theta) >= 1.f;
    if (has_total_internal_reflection) {
        return { material.transmittance, 0.f, 1.f };
    }
    const auto reflection_probability = schlick(material.index_of_refraction, Math::abs(cos_theta));
    return { material.transmittance * reflection_probability,
             material.transmittance * (1.0f - reflection_probability),
             eta };
}


auto Scene::trace (const Ray& ray, const Scene& scene, float min_time, float max_time, int bounces) -> Math::vec3 {
    const Intersection ray_hit = scene.find_closest_intersection(ray, min_time, max_time);

    if (!ray_hit.object || bounces == 0) {
        return scene.background_color;
    }

    const auto& material = ray_hit.object->material;
    const auto& normal = ray_hit.out_normal;

    const auto hit_point = ray.at(ray_hit.time);
    const auto direct = scene.compute_direct_illumination(hit_point, normal, -ray.direction, material);

    const auto coefficients = fresnel(ray.direction, normal, material);

    auto final_color = (1.f - coefficients.kr - coefficients.kt) * material.color * direct;
    if (coefficients.kt > 0) {
        const auto refracted = refraction(ray.direction, normal, coefficients.eta);
        const auto refracted_ray = Ray{ hit_point, refracted };
        const auto refracted_color = Scene::trace(refracted_ray, scene, 0.01f, max_time, bounces - 1);
        final_color += coefficients.kt * refracted_color;
    }
    if (coefficients.kr > 0) {
        const auto reflected = Math::reflect(ray.direction, normal);
        const auto reflected_ray = Ray{ hit_point, reflected };
        const auto reflected_color = Scene::trace(reflected_ray, scene, 0.01f, max_time, bounces - 1);
        final_color += coefficients.kr * reflected_color;
    }

    return material.emission + final_color;
}




