#pragma once
#include <Platform/Platform.h>
#include "vec4.h"
#if defined (PLATFORM_SSE2_AVAILABLE)
#include <xmmintrin.h>
#endif

typedef struct
	{
	union
		{
		vec4 vectors[4];
		float raw[16];
		};
	}mat4;

inline void math_mat4_copy ( const mat4 input, mat4 *output )
	{
	for ( unsigned column = 0; column < 4; ++column )
		{
		math_vec4_copy ( input.vectors[column], &output->vectors[column] );
		}
	}

inline void math_mat4_transpose_to ( const mat4 input, mat4 *output )
	{
#if defined ( PLATFORM_SSE2_AVAILABLE )
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
#else
	output[0].raw[0] = input.vectors[0].raw[0];
	output[1].raw[0] = input.vectors[0].raw[1];
	output[0].raw[1] = input.vectors[1].raw[0];
	output[1].raw[1] = input.vectors[1].raw[1];
	output[0].raw[2] = input.vectors[2].raw[0];
	output[1].raw[2] = input.vectors[2].raw[1];
	output[0].raw[3] = input.vectors[3].raw[0];
	output[1].raw[3] = input.vectors[3].raw[1];
	output[2].raw[0] = input.vectors[0].raw[2];
	output[3].raw[0] = input.vectors[0].raw[3];
	output[2].raw[1] = input.vectors[1].raw[2];
	output[3].raw[1] = input.vectors[1].raw[3];
	output[2].raw[2] = input.vectors[2].raw[2];
	output[3].raw[2] = input.vectors[2].raw[3];
	output[2].raw[3] = input.vectors[3].raw[2];
	output[3].raw[3] = input.vectors[3].raw[3];
#endif
	}

inline void math_mat4_set_zero ( mat4 *output )
	{
	for ( unsigned index = 0; index < 16; ++index )
		{
		output->raw[index] = 0.0f;
		}
	}

inline void math_mat4_set_identity_matrix ( mat4 *output )
	{
	output->raw[0] = 1.0f;
	output->raw[1] = 0.0f;
	output->raw[2] = 0.0f;
	output->raw[3] = 0.0f;
	output->raw[4] = 0.0f;
	output->raw[5] = 1.0f;
	output->raw[6] = 0.0f;
	output->raw[7] = 0.0f;
	output->raw[8] = 0.0f;
	output->raw[9] = 0.0f;
	output->raw[10] = 1.0f;
	output->raw[11] = 0.0f;
	output->raw[12] = 0.0f;
	output->raw[13] = 0.0f;
	output->raw[14] = 0.0f;
	output->raw[15] = 1.0f;
	}

inline void math_mat4_set_perspective_matrix ( const float vertical_fov, const float ratio, const float near, const float far, mat4 *output )
	{
	float f, fn;

	math_mat4_set_zero ( output );

	f = 1.0f / tanf ( vertical_fov * 0.5f );
	fn = 1.0f / ( near - far );

	output->vectors[0].raw[0] = f / ratio;
	output->vectors[1].raw[1] = f;
	output->vectors[2].raw[2] = ( near + far ) * fn;
	output->vectors[2].raw[3] = -1.0f;
	output->vectors[3].raw[2] = 2.0f * near * far * fn;
	}

inline void math_mat4_set_view_matrix ( const vec3 eye, const vec3 front, const vec3 up, mat4 *output )
	{
	vec3 unit_front;
	math_vec3_subtract ( front, eye, &unit_front );
	math_vec3_normalize ( &unit_front );

	vec3 unit_side;
	math_vec3_cross_product ( unit_front, up, &unit_side );
	math_vec3_normalize ( &unit_side );

	vec3 unit_up;
	math_vec3_cross_product ( unit_front, unit_side, &unit_up );

	output->vectors[0].raw[0] = unit_side.raw[0];
	output->vectors[0].raw[1] = unit_up.raw[0];
	output->vectors[0].raw[2] = -unit_front.raw[0];
	output->vectors[0].raw[3] = 0.0f;
	output->vectors[1].raw[0] = unit_side.raw[1];
	output->vectors[1].raw[1] = unit_up.raw[1];
	output->vectors[1].raw[2] = -unit_front.raw[1];
	output->vectors[1].raw[3] = 0.0f;
	output->vectors[2].raw[0] = unit_side.raw[2];
	output->vectors[2].raw[1] = unit_up.raw[2];
	output->vectors[2].raw[2] = -unit_front.raw[2];
	output->vectors[2].raw[3] = 0.0f;
	output->vectors[3].raw[0] = -math_vec3_dot_product ( unit_side, eye );
	output->vectors[3].raw[1] = -math_vec3_dot_product ( unit_up, eye );
	output->vectors[3].raw[2] = math_vec3_dot_product ( unit_front, eye );
	output->vectors[3].raw[3] = 1.0f;
	}
