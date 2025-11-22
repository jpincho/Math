#pragma once
#include <xmmintrin.h>
#include "mat4.h"

inline void math_mat4_sse2_transpose_to ( mat4 *output, const mat4 input )
	{
	__m128 r0, r1, r2, r3;

	r0 = _mm_load_ps ( input.vectors[0].raw );
	r1 = _mm_load_ps ( input.vectors[1].raw );
	r2 = _mm_load_ps ( input.vectors[2].raw );
	r3 = _mm_load_ps ( input.vectors[3].raw );

	_MM_TRANSPOSE4_PS ( r0, r1, r2, r3 );

	_mm_store_ps ( output->vectors[0].raw, r0 );
	_mm_store_ps ( output->vectors[1].raw, r1 );
	_mm_store_ps ( output->vectors[2].raw, r2 );
	_mm_store_ps ( output->vectors[3].raw, r3 );
	}
