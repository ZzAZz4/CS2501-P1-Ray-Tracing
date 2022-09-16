#include <light/PointLight.h>


PointLight::PointLight (const Math::vec3& position, const Math::vec3& intensity_value)
    : IncidentLight(intensity_value), position(position) {}


auto PointLight::incidence (const Math::vec3& destination) const -> Incidence {
    const auto vector = this->position - destination;
    const auto distance = Math::length(vector);
    return { vector / (distance * distance), Math::length(vector) };
}
