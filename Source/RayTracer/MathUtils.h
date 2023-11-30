#pragma once
#include "glm/glm.hpp"

namespace nc
{
	template <typename T>
	inline T lerp(const T& a, const T& b, float t)
	{
		return (a * (1.0f - t)) + (t * b);
	}

	inline glm::vec3 cross(const glm::vec3& v1, const glm::vec3& v2)
	{
		//< https://nic-gamedev.blogspot.com/2011/11/using-vector-mathematics-cross-products.html Links to an external site. ?

		return glm::vec3(

			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x

		);
	}
}