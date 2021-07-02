#pragma once
#include "glm/glm.hpp"
#include <vector>
#include <string>
#include "AnimKeys.h"
#include "glm/glm.hpp"
#include "glm/ext/quaternion_common.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/vec3.hpp"
#include "glm/gtx/compatibility.hpp"
#include "glm/gtx/common.hpp"
class AnimationChannel
{
public:
	std::string name;
	std::vector<VecKey> PosKeys;
	std::vector<RotKey> RotKeys;
	std::vector<VecKey> ScaleKeys;
	glm::quat GetRotation(double time) {

		if (RotKeys.size() == 1)
		{
			return RotKeys[0].key;
		}


		int index = -1;

		for (int i = 0; i < RotKeys.size() - 1; i++) {
			if (time < RotKeys[i].time)
			{
				index = i;
				break;
			}
		}

		if (index == -1) {
			index = 0;
		}

		int nextIndex = index + 1;

		float deltaTime = RotKeys[nextIndex].time - RotKeys[index].time;

		float Factor = (time - RotKeys[index].time) / deltaTime;

		glm::quat start = RotKeys[index].key;
		glm::quat end = RotKeys[nextIndex].key;

		return glm::slerp(start, end, Factor);

	}
	glm::vec3 GetPosition(double time)
	{
		if (PosKeys.size() == 1)
		{
			return PosKeys[0].key;
		}

		int index = -1;

		for (int i = 0; i < PosKeys.size()-1; i++) {
			if (time < PosKeys[i].time)
			{
				index = i;
				break;
			}
		}

		if (index == -1) {
			index = 0;
		}

		int nextIndex = index + 1;

		float deltaTime = PosKeys[nextIndex].time - PosKeys[index].time;

		float Factor = (time - PosKeys[index].time) / deltaTime;

		glm::vec3 start = PosKeys[index].key;
		glm::vec3 end = PosKeys[nextIndex].key;

		return glm::lerp(start, end, Factor);


		if (index == -1) {

			int vv = 5;
		}



		

	}



};

