#pragma once
#include <glm/glm.hpp>
namespace nc {
    struct ray_t
    {
        ray_t() = default;
        ray_t(const glm::vec3& origin, const glm::vec3& direction) :
            origin(origin),
            direction(glm::normalize(direction))
        {}

        glm::vec3 GetPoint(float distance) const {
            return origin + distance * direction;
        }

        glm::vec3 origin;
        glm::vec3 direction;

    };

    glm::vec3 operator*(float t, const ray_t& ray) {
        return ray.origin + t * ray.direction;
    }
}
