#ifndef UNTITLED26_DIRECTIONAL_LIGHT_H
#define UNTITLED26_DIRECTIONAL_LIGHT_H

#include <light/Light.h>

struct [[maybe_unused]] DirectionalLight : IncidentLight {
    Math::vec3 direction;

    [[maybe_unused]] DirectionalLight (const Math::vec3& direction, const Math::vec3& intensity_value);
    [[nodiscard]] Incidence incidence(const Math::vec3&) const override;
};

#endif //UNTITLED26_DIRECTIONAL_LIGHT_H
