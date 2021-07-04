#pragma once

class TMaths
{
public:

	static float GetPI();
	static float DegToRad(float v);
	static float RadToDeg(float v);
	static float Rnd(float min, float max);
	static int Rnd(int min, int max);
	static float Min(float v1, float v2);
	static float Max(float v1, float v2);

	static bool LineIntersect(float x1, float y1, float x2, float y2, float x3,float y3,float x4,float y4, float& hx, float& hy);
	static bool LineTriIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float lx, float ly, float lx1, float ly1, float& hx, float& hy,float &td);
	static float Dist2D(float x1, float y1, float x2, float y2);

private:

	static float PI;

};


