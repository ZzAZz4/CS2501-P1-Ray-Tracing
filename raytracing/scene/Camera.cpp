//
// Created by Esteban on 8/17/2022.
//

#include <scene/Camera.h>
#include <scene/Scene.h>
#include <object/Ray.h>

auto Camera::pixel_color (const Scene& scene, float x, float y, int bounces, int samples [[maybe_unused]]) const -> Math::vec3 {
    const auto viewport_point = this->position + this->basis * Math::vec3(x - 0.5, y - 0.5, -1.0);
    const auto ray = Ray::between(position, viewport_point);
    const auto color = Scene::trace(ray, scene, 1.0f, Math::infinity, bounces);
    const auto gc_color = Math::sqrt(color);
    return Math::clamp(gc_color, 0.f, 1.f);
}

auto calculate_basis (const Math::vec3& dir, const Math::vec3& up, float dist, float v_fov, float ratio) -> Math::mat3x3 {
    const auto k_vec = -Math::normalize(dir);
    const auto i_vec = Math::normalize(Math::cross(up, k_vec));
    const auto j_vec = Math::normalize(Math::cross(k_vec, i_vec));

    const auto height = 2 * dist * Math::tan(v_fov / 2);
    const auto width = height * ratio;

    return { i_vec * width, j_vec * height, k_vec * dist };
}

Camera::Camera (const Math::vec3& pos_, const Math::vec3& dir_, float v_fov_, float aspect_, float dist_)
    : basis(calculate_basis(dir_, Scene::up, dist_, v_fov_, aspect_)),
      position(pos_) {
}

auto Camera::pointing (const Math::vec3& st_, const Math::vec3& ed_, float v_fov_, float aspect_, float dist_) -> Camera {
    return { st_, Math::normalize(ed_ - st_), v_fov_, aspect_, dist_ };
}
