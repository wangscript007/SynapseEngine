#include <math.h>
#include "TMaths.h"

float TMaths::PI = 3.14159265f;

float TMaths::GetPI() {
	return PI;
}

float TMaths::DegToRad(float v) {

	return v * (PI / 180.0f);

}

float TMaths::RadToDeg(float v) {

	return v * (180.0f / PI);

}

float TMaths::Rnd(float l, float h) {


	return 0;
	//return l + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (h - l)));

}

int TMaths::Rnd(int min, int max) {
	
	int range = max - min + 1;
	
	return 0;
	//return rand() % range + min;

}

float TMaths::Min(float v1, float v2) {
	if (v1 < v2) return v1;
	return v2;
}

float TMaths::Max(float v1, float v2) {
	if (v1 > v2) return v1;
	return v2;

}

inline float Det(float a, float b, float c, float d)
{
	return a * d - b * c;
}

bool TMaths::LineTriIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float lx, float ly, float lx1, float ly1, float& hx, float& hy,float  &td)
{

	float hx1 = 0;
	float hy1 = 0;
	float hx2 = 0;
	float hy2 = 0;
	float hx3 = 0;
	float hy3 = 0;
	bool hit = false;

	float cd = 100000;
	float cx = 0;
	float cy = 0;


	if (LineIntersect(x1, y1, x2, y2, lx, ly, lx1, ly1, hx1, hy1))
	{
		hit = true;
	}
	
	if (LineIntersect(x2, y2, x3, y3, lx, ly, lx1, ly1, hx2, hy2)) {
		hit = true;
	}

	if (LineIntersect(x3, y3, x1, y1, lx, ly, lx1, ly1, hx3, hy3)) {
		hit = true;
	}

	if (hx1 != 0) {

		float dis = Dist2D(hx1, hy1, lx, ly);
		cd = dis;
		cx = hx1;
		cy = hy1;

	}

	if (hx2 != 0) {

		float dis = Dist2D(hx2, hy2, lx, ly);
		if (dis < cd)
		{
			cd = dis;
			cx = hx2;
			cy = hy2;
		}

	}

	if (hx3 != 0) {

		float dis = Dist2D(hx3, hy3, lx, ly);
		if (dis < cd) {
			cd = dis;
			cx = hx3;
			cy = hy3;
		}

	}

	if (cx != 0) {
		hx = cx;
		hy = hy;
		td = cd;
		return true;
	}
	else {

		return false;
	}


}

float TMaths::Dist2D(float x1, float y1, float x2, float y2) {

	float xd = x2 - x1;
	float yd = y2 - y1;
	return sqrt(xd * xd + yd * yd);

}

bool TMaths::LineIntersect(float x1, float y1, float x2, float y2,float x3,float y3,float x4,float y4,float& hx, float& hy) {

	float detL1 = Det(x1, y1, x2, y2);
	float detL2 = Det(x3, y3, x4, y4);

	float x1mx2 = x1 - x2;
	float x3mx4 = x3 - x4;
	float y1my2 = y1 - y2;
	float y3my4 = y3 - y4;

	float xnom = Det(detL1, x1mx2, detL2, x3mx4);
	float ynom = Det(detL1, y1my2, detL2, y3my4);
	float denom = Det(x1mx2, y1my2, x3mx4, y3my4);
	if (denom == 0.0)//Lines don't seem to cross
	{
		hx = NAN;
		hy = NAN;
		return false;
	}

	hx = xnom / denom;
	hy = ynom / denom;
	if (!isfinite(hx) || !isfinite(hy)) //Probably a numerical issue
		return false;

	return true; //All OK

}