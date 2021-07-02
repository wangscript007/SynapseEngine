#pragma once
#include "VirtualWarApp.h"
#include "DataTypes.h"
class MeshLines
{
public:

	MeshLines()
	{
		Lines.resize(0);
		Indices.resize(0);
		Col = Vect3(1, 1, 1);

	}

	void SetCol(Vect3 c) {

		Col = c;
	}

	Vect3 GetCol() {
		return Col;

	}

	void AddLine(float x1, float y1, float z1, float x2, float y2, float z2)
	{

		Lines.push_back(x1);
		Lines.push_back(y1);
		Lines.push_back(z1);
		Lines.push_back(x2);
		Lines.push_back(y2);
		Lines.push_back(z2);
		Indices.push_back(ln);
		Indices.push_back(ln + 1);
		ln += 2;


	}

	void DrawVBO() {


		glLineWidth(1.4f);
		//glDrawElements(GL_LINES,ln, GL_UNSIGNED_INT, Indices.data());
		glDrawElements(GL_LINES, ln, GL_UNSIGNED_INT, (void*)(0));

	}

	void BindVBO() {

		glBindVertexArray(VertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);


		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, (GLsizei)4 * 3, 0);


	}

	void ReleaseVBO() {

		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	void CreateVBO() {

		glGenVertexArrays(1, &VertexArray);
		glGenBuffers(1, &VertexBuffer);
		glGenBuffers(1, &IndexBuffer);


		glBindVertexArray(VertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

		int size = Lines.size() * 4;


		glBufferData(GL_ARRAY_BUFFER, size, (const void*)Lines.data(), GL_STATIC_DRAW);


		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false,(GLsizei)4*3, 0);

		glDisableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,(GLsizeiptr)ln * 4, (const void*)Indices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	}


private:
	GLuint VertexArray;
	GLuint VertexBuffer;
	GLuint IndexBuffer;
	std::vector<float> Lines;
	std::vector<unsigned int> Indices;
	int ln = 0;
	Vect3 Col;

};

