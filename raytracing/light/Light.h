//
// Created by Esteban on 8/19/2022.
//

#ifndef UNTITLED26_LIGHT_H
#define UNTITLED26_LIGHT_H

#include <light/Incidence.h>

struct Shape;

struct Light {
    Math::vec3 intensity_value;
    Light() = default;
    Light(const Math::vec3& intensity_value) : intensity_value(intensity_value) {}
};

struct IncidentLight : public Light {
    IncidentLight(const Math::vec3& intensity_value) : Light(intensity_value) {}
    virtual ~IncidentLight () = default;

    [[nodiscard]] virtual auto incidence(const Math::vec3& destination) const -> Incidence = 0;
};



#endif //UNTITLED26_LIGHT_H
