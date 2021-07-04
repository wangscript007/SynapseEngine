#pragma once
#include "GameIncludes.h"
//#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>


class kEffect
{
public:

	kEffect();
	kEffect(const char* v, const char* f);
	void load(const char* v, const char* f);
	void bind();
	void unbind();
	virtual void setPars() {};
	void setInt(const char* name, int val);
	void setFloat(const char* name, float val);
	void setVec3(const char* name, float v1, float v2, float v3);
	void setMat(const char* name, glm::mat4 mat);
protected:

	GLuint vID, fID;
	GLuint pID;

};

