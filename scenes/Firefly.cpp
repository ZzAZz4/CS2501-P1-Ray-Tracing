#include "Firefly.h"

Math::vec3 random_in_radius (float r) {
    return Math::normalize(Math::vec3(rand(), rand(), rand())) * Math::randf(-r, r);
}

Firefly::Firefly (const glm::vec3& position, float radius, const Material& mat, float random_radius)
    : Sphere(position, radius, mat),
      initial_position(position),
      destination(position + random_in_radius(random_radius)),
      random_radius(random_radius) {

}

void Firefly::update (float fElapsedTime) {
    steer(fElapsedTime);
    Sphere::material.emission += Math::vec3(1.f, 1.f, 1.f) * Math::randf(-0.25f, 0.25f);
}

void Firefly::steer (float fElapsedTime) {
    auto desired_velocity = destination - position;
    auto distance = Math::length(desired_velocity);

    auto steering = Math::normalize(desired_velocity) * max_speed - velocity;
    steering = Math::normalize(steering) * Math::min(max_acceleration, Math::length(steering));

    velocity += steering * fElapsedTime;
    velocity = Math::normalize(velocity) * Math::min(max_speed, Math::length(velocity));

    position += velocity * fElapsedTime;

    if (distance < max_speed * fElapsedTime) {
        destination = initial_position + random_in_radius(random_radius);
        if (distance >= random_radius) {
            position = destination;
            velocity = -velocity;
        }
    }
}
