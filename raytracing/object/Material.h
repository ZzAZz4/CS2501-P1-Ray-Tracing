#ifndef UNTITLED26_MATERIAL_H
#define UNTITLED26_MATERIAL_H

#include <tools/Math.h>

struct Material {
    Math::vec3 color{ 0, 0, 0 };
    Math::vec3 diffuse{ 1 };
    Math::vec3 specular{ 0 };
    Math::vec3 emission{ 0 };
    float specular_exp{ 0 };
    float reflection{ 0 };
    float index_of_refraction{ 0 };
    float transmittance{ 1 };
};

#endif //UNTITLED26_MATERIAL_H
