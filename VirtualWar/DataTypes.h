#pragma once
#include <glm/glm.hpp>

struct Vect3 {
	float X, Y, Z;

	Vect3(float x, float y, float z) {
		X = x;
		Y = y;
		Z = z;
	}
	Vect3() {
		X = Y = Z = 0;
	}
	Vect3(const Vect3& v) {
		X = v.X;
		Y = v.Y;
		Z = v.Z;
	}
	Vect3(glm::vec3 v) {
		X = v.x;
		Y = v.y;
		Z = v.z;
	}
	glm::vec3 GL() {
		return glm::vec3(X, Y, Z);
	}
};

struct Vect4 {
	float X, Y, Z, W;
	Vect4(float x, float y, float z, float w) {
		X = x;
		Y = y;
		Z = z;
		W = w;
	}
	Vect4() {
		X = Y = Z = W = 0;
	}
	Vect4(const Vect4& v) {
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		W = v.W;
	}

	static Vect4 Zero() {
		return Vect4(0, 0, 0, 0);
	}

	static Vect4 One() {
		return Vect4(1, 1, 1, 1);
	}

	float Length() {

		return (float)sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W));

	}

	float LengthSqaured() {

		return (float)(X * X) + (Y * Y) + (Z * Z) + (W * W);

	}

	void Normalize() {

		float scale = 1.0f / Length();
		X *=scale;
		Y *= scale;
		Z *= scale;
		W *= scale;

	}

	static Vect4 Add(Vect4 a, Vect4 b) {

		return Vect4(a.X + b.X, a.Y + b.Y, a.Z + b.Z, a.W + b.W);

	}

	static Vect4 Subtract(Vect4 a, Vect4 b) {

		return Vect4(a.X - b.X, a.Y - b.Y, a.Z - b.Z, a.W - b.W);

	}

	static Vect4 Multiply(Vect4 a, float scale) {

		return Vect4(a.X * scale, a.Y * scale, a.Z * scale, a.W * scale);

	}

	static Vect4 Multiply(Vect4 a, Vect4 b) {

		return Vect4(a.X * b.X, a.Y * b.Y, a.Z * b.Z, a.W * b.W);

	}

	static Vect4 Divide(Vect4 a, float scale) {

		return Vect4(a.X / scale, a.Y / scale, a.Z / scale, a.W / scale);

	}

	static Vect4 Divide(Vect4 a, Vect4 scale) {

		return Vect4(a.X / scale.X, a.Y / scale.Y, a.Z / scale.Z, a.W / scale.W);

	}

	static Vect4 ComponentMin(Vect4 a, Vect4 b) {

		Vect4 r;
		if (a.X < b.X) {
			r.X = a.X;
		}
		else {
			r.X = b.X;
		}
		if (a.Y < b.Y) {
			r.Y = a.Y;
		}
		else {
			r.Y = b.Y;
		}
		if (a.Z < b.Z) {
			r.Z = a.Z;
		}
		else {
			r.Z = b.Z;
		}
		if (a.W < b.W)
		{
			r.W = a.W;
		}
		else {
			r.W = b.W;
		}
		return r;
	}

	static Vect4 ComponentMax(Vect4 a, Vect4 b) {

		Vect4 r;
		if (a.X < b.X) {
			r.X = b.X;
		}
		else {
			r.X = a.X;
		}
		if (a.Y < b.Y) {
			r.Y = b.Y;
		}
		else {
			r.Y = a.Y;
		}
		if (a.Z < b.Z) {
			r.Z = b.Z;
		}
		else {
			r.Z = a.Z;
		}
		if (a.W < b.W)
		{
			r.W = b.W;
		}
		else {
			r.W = a.W;
		}
		return r;
	}

	static Vect4 MagnitudeMin(Vect4 l, Vect4 r) {

		if (l.LengthSqaured() < r.LengthSqaured())
		{
			return l;
		}
		return r;

	}

	static Vect4 Normalize(Vect4 v) {

		v.Normalize();
		return v;

	}

	static float Dot(Vect4 l, Vect4 r) {

		return (l.X * r.X) + (l.Y * r.Y) + (l.Z * r.Z) + (l.W * r.W);

	}

	static Vect4 Lerp(Vect4 a, Vect4 b, float blend) {

		Vect4 r;
		r.X = (blend * (b.X - a.X)) + a.X;
		r.Y = (blend * (b.Y - a.Y)) + a.Y;
		r.Z = (blend * (b.Z - a.Z)) + a.Z;
		r.W = (blend * (b.W - a.W)) + a.W;
		return r;
	}




	Vect4 operator+(const Vect4& b) {

		Vect4 r;
		r.X = X + b.X;
		r.Y = Y + b.Y;
		r.Z = Z + b.Z;
		r.W = W + b.W;
		return r;
	}

	Vect4 operator-(const Vect4& b) {

		Vect4 r;
		r.X = X - b.X;
		r.Y = Y - b.Y;
		r.Z = Z - b.Z;
		r.W = W - b.W;
		return r;

	}

	Vect4 operator/(const Vect4& b) {
		Vect4 r;
		r.X = X / b.X;
		r.Y = Y / b.Y;
		r.Z = Z / b.Z;
		r.W = W / b.W;
		return r;

	}

	Vect4 operator*(const Vect4& b) {
		Vect4 r;
		r.X = X * b.X;
		r.Y = Y * b.Y;
		r.Z = Z * b.Z;
		r.W = W * b.W;
		return r;

	}

	Vect4 operator*(float s) {
		Vect4 r;
		r.X = X * s;
		r.Y = Y * s;
		r.Z = Z * s;
		r.W = W * s;
		return r;
	}

	Vect4 operator/(float s) {
		Vect4 r;
		r.X = X / s;
		r.Y = Y / s;
		r.Z = Z / s;
		r.W = W / s;
		return r;
	}
 


	static Vect4 UnitX() {
		return Vect4(1, 0, 0, 0);
	}
	static Vect4 UnitY() {
		return Vect4(0, 1, 0, 0);
	}
	static Vect4 UnitZ() {
		return Vect4(0, 0, 1, 0);
	}
	static Vect4 UnitW() {
		return Vect4(0, 0, 0, 1);
	}
};

struct Vertex {

	Vect3 Pos;
	Vect4 Col;
	Vect3 UV;
	Vect3 Norm;
	Vect3 BiNorm;
	Vect3 Tan;

	int BoneIndices[4];
	float Weight;

	Vertex() {

		Pos = Vect3();
		UV = Vect3();
		Col = Vect4();
		Norm = Vect3();
		BiNorm = Vect3();
		Tan = Vect3();

	}
	Vertex(Vect3 p, Vect3 uv, Vect4 col, Vect3 norm, Vect3 biNorm, Vect3 tan) {
		Pos = p;
		UV = uv;
		Col = col;
		Norm = norm;
		BiNorm = biNorm;
		Tan = tan;
	}
	Vertex(glm::vec3 p, glm::vec3 uv, glm::vec3 col, glm::vec3 norm, glm::vec3 bi, glm::vec3 tan) {
		Pos = Vect3(p);
		UV = Vect3(uv);
		Col = Vect4(1,1,1,1);
		Norm = Vect3(norm);
		BiNorm = Vect3(bi);
		Tan = Vect3(tan);

	}

};

struct Tri {

	int V0, V1, V2;

	Tri(int v0, int v1, int v2) {
		V0 = v0;
		V1 = v1;
		V2 = v2;
	}

	Tri() {
		V0 = V1 = V2 = 0;
	}

	Tri(const Tri& t) {
		V0 = t.V0;
		V1 = t.V1;
		V2 = t.V2;
	}

};


