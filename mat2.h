#pragma once
#include "vec2.h"

typedef vec2 mat2[2];

inline void math_mat2_copy(const mat2 input, mat2 output)
	{
	for (unsigned column = 0; column < 2; ++column)
		{
		math_vec2_copy(input[column], &output[column]);
		}
	}
