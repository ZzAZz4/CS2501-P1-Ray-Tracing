#ifndef UNTITLED26_FIREFLY_H
#define UNTITLED26_FIREFLY_H

#include <object/Sphere.h>


struct Firefly : public Sphere {
    glm::vec3 initial_position;
    glm::vec3 destination{};
    glm::vec3 velocity{};
    float random_radius;

    constexpr static float max_acceleration{ 0.8f };
    constexpr static float max_speed{ 1.f };

    Firefly (const glm::vec3& position, float radius, const Material& mat, float random_radius);

    void update (float fElapsedTime);

    void steer (float fElapsedTime);
};

#endif //UNTITLED26_FIREFLY_H
