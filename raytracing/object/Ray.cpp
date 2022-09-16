//
// Created by Esteban on 8/17/2022.
//

#include <object/Ray.h>
#include <scene/Scene.h>
#include <iostream>

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


auto Ray::trace (const Scene& scene, float min_time, float max_time, int bounces) const -> Math::vec3 {
    const Intersection ray_hit = scene.find_closest_intersection(*this, min_time, max_time);

    if (!ray_hit.object || bounces == 0) {
        return scene.background_color;
    }

    const auto& material = ray_hit.object->material;
    const auto& normal = ray_hit.out_normal;

    const auto hit_point = this->at(ray_hit.time);
    const auto direct = scene.compute_direct_illumination(hit_point, normal, -this->direction, material);

    const auto coefficients = fresnel(this->direction, normal, material);

    auto final_color = (1.f - coefficients.kr - coefficients.kt) * material.color * direct;
    if (coefficients.kt > 0) {
        const auto refracted = refraction(this->direction, normal, coefficients.eta);
        const auto refracted_ray = Ray{ hit_point, refracted };
        const auto refracted_color = refracted_ray.trace(scene, 0.01f, max_time, bounces - 1);
        final_color += coefficients.kt * refracted_color;
    }
    if (coefficients.kr > 0) {
        const auto reflected = Math::reflect(this->direction, normal);
        const auto reflected_ray = Ray{ hit_point, reflected };
        const auto reflected_color = reflected_ray.trace(scene, 0.01f, max_time, bounces - 1);
        final_color += coefficients.kr * reflected_color;
    }

    return material.emission + final_color;
}

//
//auto trace_impl (Ray ray, const Scene& scene, float min_time, float max_time, int bounces) -> Math::vec3 {
//    auto acc_result = Math::vec3{ 0.f, 0.f, 0.f };
//    auto acc_multiplier = 1.f;
//
//    for (; ; bounces -= 1) {
//        const auto ray_hit = scene.find_closest_intersection(ray, min_time, max_time);
//        if (!ray_hit.object) {
//            return acc_result + acc_multiplier * scene.background_color;
//        }
//
//        const auto reflectivity = ray_hit.object->material.reflectivity;
//        const auto hit_point = ray.origin + ray.direction * ray_hit.time;
//        const auto normal = ray_hit.object->normal(ray.origin + ray.direction * ray_hit.time);
//        const auto light_intensity = scene.compute_light(hit_point, normal, -ray.direction, ray_hit.object->material);
//        const auto result_color = Math::clamp(ray_hit.object->material.color * light_intensity, 0.f, 1.f);
//        if (bounces == 0 || reflectivity <= 0) {
//            return acc_result + acc_multiplier * result_color;
//        }
//
//        const auto ref_direction = Math::reflect(ray.direction, normal);
//        ray = Ray{ hit_point, ref_direction };
//        acc_result += acc_multiplier * (1.f - reflectivity) * result_color;
//        acc_multiplier *= reflectivity;
//        min_time = 0.0001f;
//    }
//}
//
//auto Ray::trace (const Scene& scene, float min_time, float max_time, int bounces) const -> Math::vec3 {
//    return trace_impl(*this, scene, min_time, max_time, bounces);
//}







