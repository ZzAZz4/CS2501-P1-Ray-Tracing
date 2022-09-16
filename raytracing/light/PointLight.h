//
// Created by Esteban on 9/13/2022.
//

#ifndef UNTITLED26_POINTLIGHT_H
#define UNTITLED26_POINTLIGHT_H

#include <light/Light.h>

struct PointLight : IncidentLight {
    Math::vec3 position;

    PointLight (const Math::vec3& position, const Math::vec3& intensity_value);
    [[nodiscard]] auto incidence(const Math::vec3& destination) const -> Incidence override;
};

#endif //UNTITLED26_POINTLIGHT_H
