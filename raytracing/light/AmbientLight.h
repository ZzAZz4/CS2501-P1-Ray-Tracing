//
// Created by Esteban on 9/13/2022.
//

#ifndef UNTITLED26_AMBIENTLIGHT_H
#define UNTITLED26_AMBIENTLIGHT_H

#include <light/Light.h>

struct AmbientLight : public Light {
    AmbientLight() = default;
    explicit AmbientLight(const Math::vec3& intensity_value) : Light(intensity_value) {}
};

#endif //UNTITLED26_AMBIENTLIGHT_H
