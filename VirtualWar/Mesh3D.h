#pragma once
#include "DataTypes.h"
#include <vector>
#include "Material.h"
#include "ActorBone.h"
struct Subset {

	int FaceCount;
	int FaceStart;
	int VertexCount;
	int VertexStart;

};

class Mesh3D
{
public:
	Mesh3D(int vertices, int tris) {

		Vertices.resize(vertices);
		Tris.resize(tris);

	}

	void SetVertex(int id, Vertex v) {

		Vertices[id] = v;

	}

	void SetTri(int id, Tri t) {

		Tris[id] = t;

	}

	Vertex GetVertex(int id) {
		
		return Vertices[id];
	
	}

	Tri GetTri(int id) {
	
		return Tris[id];
	
	}

	int NumVertices() {

		return (int)Vertices.size();


	}

	int NumTris() {

		return (int)Tris.size();
		
	}

	Mesh3D() { Mat = new Material; };

	void CreateVBO();
	void BindVBO();
	void ReleaseVBO();
	void DrawVBO();
	void UpdateVBO();
	void SetMaterial(Material* mat);
	Material* GetMaterial();

	void BindMaterial();
	void ReleaseMaterial();
	void AddSubset(Subset* sub) {
		Sub.push_back(sub);
	}

	void SetVertexData(std::vector<Vertex> verts)
	{
		//for (int i = 0; i < verts.size(); i++) {
		//	Vert/ices.push_back()

		//}
		Vertices = verts;

	}
	void SetTriData(std::vector<Tri> tris) {
		Tris = tris;


	}

	Mesh3D* Clone() {

		Mesh3D* nm = new Mesh3D;
		
		for (int v = 0; v < Vertices.size(); v++) {
			nm->Vertices.push_back(Vertices[v]);
		}
		for (int t = 0; t < Tris.size(); t++) {
			nm->Tris.push_back(Tris[t]);
		}
		nm->SetMaterial(Mat);
		return nm;

		//nm->Vertices;

		
		//nm->Tris = Tris;



	}

	std::vector<Vertex> GetVertexData() {
		return Vertices;
	}

	std::vector<Tri> GetTriData() {
		return Tris;
	}

	void AddVertex(Vertex v)
	{
		Vertices.push_back(v);
	}

	void AddTri(Tri t) {
		Tris.push_back(t);
	}

	void SetData(void* d) {
		data = d;
	}
	void* GetData()
	{
		return data;
	}
	void AddBone(ActorBone* b) {
		bones.push_back(b);
	}
	int BoneCount() {
		return bones.size();
	}
	ActorBone* GetBone(int num) {
		return bones[num];
	}
private:
	std::vector<ActorBone*> bones;
	std::vector<Vertex> Vertices;
	std::vector<Tri> Tris;
	std::vector<Subset*> Sub;
	GLuint VertexArray;
	GLuint VertexBuffer;
	GLuint IndexBuffer;
	Material* Mat;
	void* data;


};

