#pragma once
#include "Vector4.h"

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
#if defined(__wasm__) && defined(__wasm_simd128__)
	glm_mat4_transp_wasm(input, output);
#elif defined(__AVX__)
	glm_mat4_transp_avx(input, output);
#elif defined( __SSE__ ) || defined( __SSE2__ )
	glm_mat4_transp_sse2(input, output);
#elif defined(CGLM_NEON_FP)
	glm_mat4_transp_neon(input, output);
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