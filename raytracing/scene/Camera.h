#ifndef UNTITLED26_CAMERA_H
#define UNTITLED26_CAMERA_H

#include <tools/Math.h>

struct Scene;


struct Camera {
    Math::mat4 unit_basis;
    Math::mat4 scale;
    Math::mat4 scaled_basis;
    Math::vec4 position;

    Camera() = default;
    Camera (const Math::vec3& pos_, const Math::vec3& dir_, float v_fov_, float aspect_, float dist_);
    static auto pointing(const Math::vec3& from, const Math::vec3& to, float v_fov, float aspect, float dist) -> Camera;

    void move_forward(float distance) { position -= distance * unit_basis[2]; }
    void move_right(float distance) { position -= distance * unit_basis[0]; }
    void move_up(float distance) { position -= distance * Math::vec4(0, -1, 0, 0); }
    void rotate_up(float angle) {
        unit_basis = glm::rotate(glm::mat4(1.f), -angle, glm::vec3(unit_basis[0])) * unit_basis;
        scaled_basis = unit_basis * scale;
    }
    void rotate_right(float angle) {
        unit_basis = glm::rotate(glm::mat4(1.f), -angle, glm::vec3(0, 1, 0)) * unit_basis;
        scaled_basis = unit_basis * scale;
    }


    [[nodiscard]] auto pixel_color (const Scene& scene, float x, float y, int bounces, int samples = 1) const -> Math::vec3;
};


#endif //UNTITLED26_CAMERA_H
