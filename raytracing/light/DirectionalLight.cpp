#include <light/DirectionalLight.h>

[[maybe_unused]] DirectionalLight::DirectionalLight (const Math::vec3& direction, const Math::vec3& intensity_value)
    : IncidentLight(intensity_value), direction(Math::normalize(direction)) {}


Incidence DirectionalLight::incidence (const Math::vec3&) const {
    return { this->direction, Math::infinity };
}

