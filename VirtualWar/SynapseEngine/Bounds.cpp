#include "Bounds.h"
bool isIn(Vect3 p,Bounds* b)
{
if (p.X >= b->min.x)
if (p.Y >= b->min.y)
if (p.Z >= b->min.z)
if (p.X <= b->max.x)
if (p.Y <= b->max.y)
if (p.Z <= b->max.z)
return true;
return false;
};