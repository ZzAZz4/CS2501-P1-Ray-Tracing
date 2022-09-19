#include <object/Cylinder.h>


Intersection Cylinder::intersection (const Ray& ray, float min_time, float) const {
    Math::vec3 ro = ray.origin;
    Math::vec3 rd = ray.direction;
    Math::vec3 ca = this->base - this->top;
    Math::vec3 oc = ro - this->top;

    float caca = Math::dot(ca, ca);
    float card = Math::dot(ca, rd);
    float caoc = Math::dot(ca, oc);
    float a = caca - card * card;
    float b = caca * Math::dot(oc, rd) - caoc * card;
    float c = caca * Math::dot(oc, oc) - caoc * caoc - this->radius * this->radius * caca;
    float h = b * b - a * c;

    if (h < 0.0) {
        return {};
    }
    h = Math::sqrt(h);

    float t = (-b - h) / a;

    float y = caoc + t * card;
    if (y > 0.0 && y < caca && t > min_time) {
        return Intersection::normalized(t, (oc + t*rd - ca * y / caca) * Math::sign(radius), this);
    }
    // caps
    t = (((y < 0.f) ? 0.f : caca) - caoc) / card;
    if (t <= min_time || Math::abs(b + a * t) >= h) {
        return {};
    }
    return Intersection::normalized(t, ca * Math::sign(y * radius), this);
}
