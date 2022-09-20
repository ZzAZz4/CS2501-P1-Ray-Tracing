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
    const auto desired_velocity = destination - position;
    const auto distance = Math::length(desired_velocity);

    const auto steering = Math::cap_length(Math::normalize(desired_velocity) * max_speed - velocity, max_acceleration);
    velocity = Math::cap_length(velocity + steering * fElapsedTime, max_speed);
    position += velocity * fElapsedTime;

    if (distance >= random_radius) {
        position = destination;
        velocity = -velocity;
        destination = initial_position + random_in_radius(random_radius);
    }
    else if (distance < max_speed * fElapsedTime) {
        destination = initial_position + random_in_radius(random_radius);
    }

}
