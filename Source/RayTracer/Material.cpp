#include "Material.h"
#include "Random.h"

bool Lambertian::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& color, ray_t& scattered) const
{
    //glm::vec3 target = <raycast hit point + raycast hit normal + random in unit sphere>
	glm::vec3 target = (raycastHit.point + raycastHit.normal + randomInUnitSphere());
    //glm::vec3 direction = <create a direction from raycast hit point to the target and normalize it>;
    glm::vec3 direction = normalize(ray.direction + target);

    //scattered = <set scattered ray with raycast hit point as the origin and the new direction>;
    scattered = ray_t(raycastHit.point, direction);
    //color = <set color to material albedo>;
    color = m_albedo;

    return true;
}

bool Metal::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered) const
{
	//glm::vec3 reflected = <get reflected ray from normalized ray direction and raycast hit normal>;
	glm::vec3 reflected = (normalize(ray.direction), raycastHit.normal);

	// set scattered ray from reflected ray + random point in sphere (fuzz = 0 no randomness, fuzz = 1 random reflected)
	// a mirror has a fuzz value of 0 and a diffused metal surface a higher value
	//scattered = ray_t{ <raycast hit point>, <reflected + random unit sphere * fuzz> };
	scattered = ray_t{ raycastHit.point, reflected + randomInUnitSphere() * m_fuzz};
	color = m_albedo;
	// make sure that reflected ray is going away from surface normal (dot product > 0, angle between vectors < 90 degrees)
	return glm::dot(scattered.direction, raycastHit.normal) > 0;
}
