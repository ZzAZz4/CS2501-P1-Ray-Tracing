//
// Created by Esteban on 8/17/2022.
//

#include <scene/Camera.h>
#include <scene/Scene.h>
#include <object/Ray.h>

Math::vec3 Camera::pixel_color (const Scene& scene, float x, float y, int bounces) const {
    const glm::vec3 viewport_point = this->position + this->scaled_basis * Math::vec4(x - 0.5, y - 0.5, -1.0, 1.0);
    const auto ray = Ray::between(this->position, viewport_point);
    const auto ray_color = Scene::trace(ray, scene, 1.0f, Math::infinity, bounces);
    const auto gc_color = Math::sqrt(ray_color);
    auto result_color = Math::clamp(gc_color, 0.f, 1.f);
    return result_color;
}

Math::mat4 calculate_basis (const Math::vec3& pos, const Math::vec3& dir, const Math::vec3& up) {
    return glm::lookAt(pos, dir, up);
}

Math::mat4 calculate_scale (float dist, float v_fov, float ratio) {
    const auto height = 2 * dist * Math::tan(v_fov / 2.f);
    const auto width = height * ratio;
    return Math::scale(Math::mat4(1.f), Math::vec3{ width, height, dist });
}

Camera::Camera (const Math::vec3& pos_, const Math::vec3& dir_, float v_fov_, float aspect_, float dist_)
    : unit_basis(calculate_basis(glm::vec3(0.f), dir_, Math::vec3(0, -1, 0))),
      scale(calculate_scale(dist_, v_fov_, aspect_)),
      scaled_basis(unit_basis * scale),
      position(glm::vec4(pos_, 1)) {
}

Camera Camera::pointing (const Math::vec3& st_, const Math::vec3& ed_, float v_fov_, float aspect_, float dist_) {
    return { st_, Math::normalize(ed_ - st_), v_fov_, aspect_, dist_ };
}

void Camera::move_forward (float distance) {
    const auto forward = Math::cross(Math::vec3(0, 1, 0), Math::vec3(this->unit_basis[0]));
    position -= distance * Math::vec4(forward, 0);
}

void Camera::move_right (float distance) {
    position -= distance * this->unit_basis[0];
}

void Camera::move_up (float distance) {
    position -= distance * Math::vec4(0, -1, 0, 0);
}

void Camera::rotate_up (float angle) {
    unit_basis = glm::rotate(glm::mat4(1.f), -angle, glm::vec3(unit_basis[0])) * unit_basis;
    scaled_basis = unit_basis * scale;
}

void Camera::rotate_right (float angle) {
    unit_basis = glm::rotate(glm::mat4(1.f), -angle, glm::vec3(0, 1, 0)) * unit_basis;
    scaled_basis = unit_basis * scale;
}
