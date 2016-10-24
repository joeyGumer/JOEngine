
#ifndef _MATH_H_
#define _MATH_H_

#include "MathGeoLib\Include\MathGeoLib.h"
#include "MathGeoLib\Include\MathBuildConfig.h"

//WARNING : taking this function from glmath because i have to discover how to do a prespective with MathGeoLib
//totally provisional
/*float4x4 perspective(float fovy, float aspect, float n, float f)
{
	float4x4 Perspective;

	float coty = 1.0f / tanf(DegToRad(fovy)/2);

	Perspective.ptr()[0] = coty / aspect;
	Perspective.ptr()[5] = coty;
	Perspective.ptr()[10] = (n + f) / (n - f);
	Perspective.ptr()[11] = -1.0f;
	Perspective.ptr()[14] = 2.0f * n * f / (n - f);
	Perspective.ptr()[15] = 0.0f;

	return Perspective;
}*/



#endif _MATH_H_

