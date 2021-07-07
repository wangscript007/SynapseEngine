#include "Mesh3D.h"


void Mesh3D::BindVBO() {

	glBindVertexArray(VertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);

	// COL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*)(3 * 4));

	//UV
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(7 * 4));

	//Norm
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(10 * 4));

	//Binorm
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(13 * 4));

	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(16 * 4));


}

void Mesh3D::ReleaseVBO() {

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	


}

void Mesh3D::DrawVBO() {


	glDrawElements(GL_TRIANGLES, Tris.size() * 3, GL_UNSIGNED_INT, (void*)(0));
	//glDrawElements(GL_TRIANGLES, Tris.size()*3, GL_UNSIGNED_INT, Tris.data());

}

void Mesh3D::CreateVBO() {

	glGenVertexArrays(1, &VertexArray);
	glGenBuffers(1, &VertexBuffer);


	int maxSize = Vertices.size();

	glBindVertexArray(VertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);


	GLsizeiptr size = (GLsizeiptr)Vertices.size() * sizeof(Vertex);

	glBufferData(GL_ARRAY_BUFFER, size, (const void*)Vertices.data(),GL_DYNAMIC_DRAW);


	// Pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);

	// COL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex),(void*)(3 * 4));

	//UV
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(7 * 4));

	//Norm
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(10 * 4));

	//Binorm
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(13 * 4));

	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(16 * 4));


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Tri) * Tris.size(), Tris.data(), GL_STATIC_DRAW);


}

void Mesh3D::UpdateVBO() {

	int maxSize = Vertices.size();

	glBindVertexArray(VertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);


	GLsizeiptr size = (GLsizeiptr)Vertices.size() * sizeof(Vertex);

	glBufferData(GL_ARRAY_BUFFER, size, (const void*)Vertices.data(), GL_DYNAMIC_DRAW);


	// Pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);

	// COL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*)(3 * 4));

	//UV
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(7 * 4));

	//Norm
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(10 * 4));

	//Binorm
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(13 * 4));

	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(16 * 4));


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Tri) * Tris.size(), Tris.data(), GL_STATIC_DRAW);


}

void Mesh3D::SetMaterial(Material* mat) {

	Mat = mat;

}

Material* Mesh3D::GetMaterial() {

	return Mat;

}

void Mesh3D::BindMaterial() {

	Mat->Bind();

}

void Mesh3D::ReleaseMaterial() {

	Mat->Release();

}
