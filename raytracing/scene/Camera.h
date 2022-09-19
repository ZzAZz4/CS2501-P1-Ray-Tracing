#ifndef UNTITLED26_CAMERA_H
#define UNTITLED26_CAMERA_H

#include <tools/Math.h>

struct Scene;


struct Camera {
    Math::mat3x3 basis;
//    Math::vec3 lower_left;
    Math::vec3 position;

    Camera() = default;
    Camera (const Math::vec3& pos_, const Math::vec3& dir_, float v_fov_, float aspect_, float dist_);
    static auto pointing(const Math::vec3& from, const Math::vec3& to, float v_fov, float aspect, float dist) -> Camera;

    void move_forward(float distance) {
        position += distance * -basis[2];
    }
    void move_right(float distance) {
        position += distance * -basis[0];
    }
    void move_up(float distance) {
        position += distance * -basis[1];
    }

    [[nodiscard]] auto pixel_color (const Scene& scene, float x, float y, int bounces, int samples = 1) const -> Math::vec3;
};


#endif //UNTITLED26_CAMERA_H
