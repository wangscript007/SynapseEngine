#include <iostream>
#include <fstream>
#include "kEffect.h"
#include <string>



std::string readFile(const char* filePath) {

	printf("Reading file:");
	printf(filePath);
	printf("\n");


	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

kEffect::kEffect(const char* v, const char* f) {

	load(v, f);

}

void kEffect::load(const char* v, const char* f) {


	vID = glCreateShader(GL_VERTEX_SHADER);

	fID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertShaderStr = readFile(v);

	std::string fragShaderStr = readFile(f);
	const char* vertShaderSrc = vertShaderStr.c_str();
	const char* fragShaderSrc = fragShaderStr.c_str();



	GLint result = GL_FALSE;
	int logLength;

	// Compile vertex shader
	std::cout << "Compiling vertex shader." << std::endl;
	glShaderSource(vID, 1, &vertShaderSrc, NULL);
	glCompileShader(vID);

	// Check vertex shader
	GLsizei log_length = 0;
	GLchar message[1024];
	glGetShaderInfoLog(vID, 1024, &log_length, message);

	std::cout << message;


	// Compile fragment shader
	std::cout << "Compiling fragment shader." << std::endl;
	glShaderSource(fID, 1, &fragShaderSrc, NULL);
	glCompileShader(fID);

	log_length = 0;

	glGetShaderInfoLog(fID, 1024, &log_length, message);

	std::cout << message;

	std::cout << "Linking program" << std::endl;
	pID = glCreateProgram();
	glAttachShader(pID, vID);
	glAttachShader(pID, fID);
	glLinkProgram(pID);



	glDeleteShader(vID);
	glDeleteShader(fID);
};

kEffect::kEffect()
{

	

	


};

void kEffect::setMat(const char* name, glm::mat4 mat) {

	GLuint loc = glGetUniformLocation(pID, (GLchar*)name);
	//printf("Loc:%d \n", loc);
	glUniformMatrix4fv(loc, 1, false, glm::value_ptr(mat));

}

void kEffect::setInt(const char* name, int v) {

	GLuint loc = glGetUniformLocation(pID,(GLchar*)name);
	//printf("Loc:%d \n", loc);
	glUniform1i(loc, (GLint)v);
	
}

void kEffect::setFloat(const char* name, float v) {

	GLuint loc = glGetUniformLocation(pID, (GLchar*)name);
	glUniform1f(loc, v);

}

void kEffect::setVec3(const char* name, float v1, float v2, float v3) {

	GLuint loc = glGetUniformLocation(pID, (GLchar*)name);
	glUniform3f(loc, v1,v2,v3);

}

void kEffect::bind() {

	glUseProgram(pID);
	setPars();

};

void kEffect::unbind() {

	glUseProgram(0);

};