#pragma once
#include "Object.h"

class Sphere : public Object
{
public:
	Sphere() = default;

	Sphere(const glm::vec3& center, float radius, std::shared_ptr<Material> material) :
		//<class Object base class constructor passing material>,
		Object(material),
		//<set center>,
		m_center(center),
		//<set radius>{}
		m_radius(radius)
	{}

	bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) override;

private:
	//<vector 3, default to 0> m_center;
	glm::vec3 m_center = glm::vec3(0.0f, 0.0f, 0.0f);
	float m_radius = 0;
};