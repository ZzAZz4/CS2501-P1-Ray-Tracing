#include <tools/Math.h>


std::ostream& operator << (std::ostream& os, const Math::vec3& v) {
    os << '[' << v.x << ' ' << v.y << ' ' << v.z << ']';
    return os;
}

std::ostream& operator << (std::ostream& os, const Math::vec4& v) {
    os << '[' << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w << ']';
    return os;
}

std::ostream& operator << (std::ostream& os, const Math::mat3x3& m) {
    os << '[' << m[0] << ' ' << m[1] << ' ' << m[2] << ']';
    return os;
}

std::ostream& operator << (std::ostream& os, const Math::mat4x4& m) {
    os << '[' << m[0] << ' ' << m[1] << ' ' << m[2] << ' ' << m[3] << ']';
    return os;
}