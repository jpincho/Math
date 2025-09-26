#pragma once
#include "Vector3.h"

typedef vec3 mat3[3];

inline void math_mat3_copy(const mat3 input, mat3 output)
	{
	for (unsigned column = 0; column < 3; ++column)
		{
		math_vec3_copy(input[column], &output[column]);
		}
	}
