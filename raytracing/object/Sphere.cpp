#include <object/Sphere.h>
#include <object/Ray.h>


Intersection Sphere::intersection (const Ray& ray, float min_time, float) const {
    const auto oc = ray.origin - this->position;
    const auto a = Math::dot(ray.direction, ray.direction);
    const auto b_half = Math::dot(oc, ray.direction);
    const auto c = Math::dot(oc, oc) - this->radius * this->radius;

    const auto discriminant = b_half * b_half - a * c;
    if (discriminant < 0.0f) {
        return {};
    }
    const auto disc_root = std::sqrt(discriminant);
    const auto nearest_solution = (-b_half - disc_root) / a;
    if (nearest_solution >= min_time) {
        return {nearest_solution, (ray.at(nearest_solution) - this->position) / radius, this};
    }
    const auto farthest_solution = (-b_half + disc_root) / a;
    return {farthest_solution, (ray.at(farthest_solution) - this->position) / radius, this};
}
