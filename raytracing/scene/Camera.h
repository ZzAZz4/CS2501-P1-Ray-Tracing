#ifndef UNTITLED26_CAMERA_H
#define UNTITLED26_CAMERA_H

#include <tools/Math.h>

struct Scene;


struct Camera {
    Math::mat4 unit_basis;
    Math::mat4 scale;
    Math::mat4 scaled_basis;
    Math::vec4 position;

    Camera () = default;
    Camera (const Math::vec3& pos_, const Math::vec3& dir_, float v_fov_, float aspect_, float dist_);
    static Camera pointing (const Math::vec3& from, const Math::vec3& to, float v_fov, float aspect, float dist);

    void move_forward (float distance);
    void move_right (float distance);
    void move_up (float distance);
    void rotate_up (float angle);
    void rotate_right (float angle);

    [[nodiscard]] Math::vec3 pixel_color (const Scene& scene, float x, float y, int bounces) const;
};


#endif //UNTITLED26_CAMERA_H
