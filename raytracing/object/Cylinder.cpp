#include <object/Cylinder.h>


Intersection Cylinder::intersection (const Ray& ray, float min_time, float) const {
    const auto ca = this->base - this->top;
    const auto oc = ray.origin - this->top;

    const float ca_dot_ca = Math::dot(ca, ca);
    const float ca_dot_rd = Math::dot(ca, ray.direction);
    const float ca_dot_oc = Math::dot(ca, oc);
    const float a = ca_dot_ca - ca_dot_rd * ca_dot_rd;
    const float b = ca_dot_ca * Math::dot(oc, ray.direction) - ca_dot_oc * ca_dot_rd;
    const float c = ca_dot_ca * Math::dot(oc, oc) - ca_dot_oc * ca_dot_oc - this->radius * this->radius * ca_dot_ca;
    const float h_sq = b * b - a * c;

    if (h_sq < 0.0) {
        return {};
    }
    const auto h = Math::sqrt(h_sq);

    const float t = (-b - h) / a;
    const float y = ca_dot_oc + t * ca_dot_rd;
    if (y > 0.0 && y < ca_dot_ca && t > min_time) {
        return Intersection::normalized(t, (oc + t * ray.direction - ca * y / ca_dot_ca) * Math::sign(radius), this);
    }
    // caps
    const auto t2 = (((y < 0.f) ? 0.f : ca_dot_ca) - ca_dot_oc) / ca_dot_rd;
    if (t2 <= min_time || Math::abs(b + a * t2) >= h) {
        return {};
    }
    return Intersection::normalized(t2, ca * Math::sign(y * radius), this);
}
