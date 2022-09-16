#ifndef UNTITLED26_DIRECTIONALLIGHT_H
#define UNTITLED26_DIRECTIONALLIGHT_H

#include <light/Light.h>

struct DirectionalLight : IncidentLight {
    Math::vec3 direction;

    DirectionalLight (const Math::vec3& direction, const Math::vec3& intensity_value);
    [[nodiscard]] auto incidence(const Math::vec3&) const -> Incidence override;
};

#endif //UNTITLED26_DIRECTIONALLIGHT_H
