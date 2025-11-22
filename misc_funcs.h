#pragma once
#include "constants.h"

inline float math_degrees_to_radians ( const float degrees )
	{
	return degrees * MATH_PI / 180.0f;
	}

inline float math_radians_to_degrees ( const float radians )
	{
	return radians * 180.0f / MATH_PI;
	}
