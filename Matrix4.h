#pragma once
#include "Vector4.h"
#if defined (PLATFORM_SSE2_AVAILABLE)
#include <xmmintrin.h>
#endif

typedef vec4 mat4[4];

inline void math_mat4_copy(const mat4 input, mat4 output)
	{
	for (unsigned column = 0; column < 4; ++column)
		{
		math_vec4_copy(input[column], &output[column]);
		}
	}

inline void math_mat4_transpose_to(const mat4 input, mat4 output)
	{
#if defined ( PLATFORM_SSE2_AVAILABLE )
	__m128 r0, r1, r2, r3;

	r0 = _mm_load_ps ( input[0].raw );
	r1 = _mm_load_ps ( input[1].raw );
	r2 = _mm_load_ps ( input[2].raw );
	r3 = _mm_load_ps ( input[3].raw );

	_MM_TRANSPOSE4_PS ( r0, r1, r2, r3 );

	_mm_store_ps ( output[0].raw, r0 );
	_mm_store_ps ( output[1].raw, r1 );
	_mm_store_ps ( output[2].raw, r2 );
	_mm_store_ps ( output[3].raw, r3 );
#else
	output[0].raw[0] = input[0].raw[0]; output[1].raw[0] = input[0].raw[1];
	output[0].raw[1] = input[1].raw[0]; output[1].raw[1] = input[1].raw[1];
	output[0].raw[2] = input[2].raw[0]; output[1].raw[2] = input[2].raw[1];
	output[0].raw[3] = input[3].raw[0]; output[1].raw[3] = input[3].raw[1];
	output[2].raw[0] = input[0].raw[2]; output[3].raw[0] = input[0].raw[3];
	output[2].raw[1] = input[1].raw[2]; output[3].raw[1] = input[1].raw[3];
	output[2].raw[2] = input[2].raw[2]; output[3].raw[2] = input[2].raw[3];
	output[2].raw[3] = input[3].raw[2]; output[3].raw[3] = input[3].raw[3];
#endif
	}
