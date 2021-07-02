#pragma once
#include "glm/glm.hpp"
#include "DataTypes.h"

struct Bounds {

	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 extent;
	Bounds() {
		min = glm::vec3(0, 0, 0);
		max = glm::vec3(0, 0, 0);
		extent = glm::vec3(0, 0, 0);
	}
	Bounds(glm::vec3 m, glm::vec3 mx) {
		min = m;
		max = mx;
		extent = max - min;

	}

};

bool isIn(Vect3 p, Bounds* b);