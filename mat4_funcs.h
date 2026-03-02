#pragma once
#include "types.h"
#include "vec4_funcs.h"
#include "vec3_funcs.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>


static inline void math_mat4_dump ( const mat4 matrix )
	{
	for ( unsigned column = 0; column < 4; ++column )
		{
		for ( unsigned row = 0; row < 4; ++row )
			{
			printf ( "%f ", matrix.raw[column][row] );
			}
		printf ( "\n" );
		}
	}

static inline bool math_mat4_equals ( const mat4 first, const mat4 second )
	{
	for ( unsigned index = 0; index < 4 * 4; ++index )
		{
		if ( first.flat_raw[index] != second.flat_raw[index] )
			return false;
		}
	return true;
	}

static inline void math_mat4_copy ( mat4 *output, const mat4 input )
	{
	for ( unsigned column = 0; column < 4; ++column )
		{
		math_vec4_copy ( &output->vectors[column], input.vectors[column] );
		}
	}

static inline void math_mat4_transpose ( mat4 *output, const mat4 input )
	{
	for ( unsigned iterator1 = 0; iterator1 < 4; ++iterator1 )
		{
		for ( unsigned iterator2 = 0; iterator2 < 4; ++iterator2 )
			{
			output->vectors[iterator1].raw[iterator2] = input.vectors[iterator2].raw[iterator1];
			}
		}
	}

static inline void math_mat4_set_zero ( mat4 *output )
	{
	for ( unsigned index = 0; index < 4 * 4; ++index )
		{
		output->flat_raw[index] = 0.0f;
		}
	}

static inline void math_mat4_set_identity_matrix ( mat4 *output )
	{
	output->raw[0][0] = 1.0f;
	output->raw[0][1] = 0.0f;
	output->raw[0][2] = 0.0f;
	output->raw[0][3] = 0.0f;

	output->raw[1][0] = 0.0f;
	output->raw[1][1] = 1.0f;
	output->raw[1][2] = 0.0f;
	output->raw[1][3] = 0.0f;

	output->raw[2][0] = 0.0f;
	output->raw[2][1] = 0.0f;
	output->raw[2][2] = 1.0f;
	output->raw[2][3] = 0.0f;

	output->raw[3][0] = 0.0f;
	output->raw[3][1] = 0.0f;
	output->raw[3][2] = 0.0f;
	output->raw[3][3] = 1.0f;
	}

static inline void math_mat4_set_perspective_matrix ( mat4 *output, const float vertical_fov, const float ratio, const float near, const float far )
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

static inline void math_mat4_set_right_handed_view_matrix ( mat4 *output, const vec3 camera_pos, const vec3 front, const vec3 up )
	{
	vec3 unit_front;
	math_vec3_subtract ( &unit_front, front, camera_pos );
	math_vec3_normalize ( &unit_front );

	vec3 unit_side;
	math_vec3_cross_product_to_output ( &unit_side, unit_front, up );
	math_vec3_normalize ( &unit_side );

	vec3 unit_up;
	math_vec3_cross_product_to_output ( &unit_up, unit_side, unit_front );

	output->vectors[0].raw[0] = unit_side.x;
	output->vectors[1].raw[0] = unit_side.y;
	output->vectors[2].raw[0] = unit_side.z;

	output->vectors[0].raw[1] = unit_up.x;
	output->vectors[1].raw[1] = unit_up.y;
	output->vectors[2].raw[1] = unit_up.z;

	output->vectors[0].raw[2] = -unit_front.x;
	output->vectors[1].raw[2] = -unit_front.y;
	output->vectors[2].raw[2] = -unit_front.z;

	output->vectors[0].raw[3] = 0.0f;
	output->vectors[1].raw[3] = 0.0f;
	output->vectors[2].raw[3] = 0.0f;
	output->vectors[3].raw[0] = -math_vec3_dot_product ( unit_side, camera_pos );
	output->vectors[3].raw[1] = -math_vec3_dot_product ( unit_up, camera_pos );
	output->vectors[3].raw[2] = math_vec3_dot_product ( unit_front, camera_pos );
	output->vectors[3].raw[3] = 1.0f;
	}

static inline void math_mat4_set_view_matrix ( mat4 *output, const vec3 camera_pos, const vec3 front, const vec3 up )
	{
	math_mat4_set_right_handed_view_matrix ( output, camera_pos, front, up );
	}

static inline void math_mat4_set_rotation_matrix ( mat4 *output, const float angle, const vec3 axis )
	{
	vec3 normalized_axis, scaled_normalized_1_minus_cos, scaled_normalized_sin;

	float cosine = cosf ( angle );

	math_vec3_normalize_to ( &normalized_axis, axis );
	math_vec3_scale ( &scaled_normalized_1_minus_cos, normalized_axis, 1.0f - cosine );
	math_vec3_scale ( &scaled_normalized_sin, normalized_axis, sinf ( angle ) );

	math_vec3_scale ( ( vec3 * ) &output->vectors[0], normalized_axis, scaled_normalized_1_minus_cos.raw[0] );
	math_vec3_scale ( ( vec3 * ) &output->vectors[1], normalized_axis, scaled_normalized_1_minus_cos.raw[1] );
	math_vec3_scale ( ( vec3 * ) &output->vectors[2], normalized_axis, scaled_normalized_1_minus_cos.raw[2] );

	output->vectors[0].raw[0] += cosine;
	output->vectors[1].raw[0] -= scaled_normalized_sin.raw[2];
	output->vectors[2].raw[0] += scaled_normalized_sin.raw[1];
	output->vectors[0].raw[1] += scaled_normalized_sin.raw[2];
	output->vectors[1].raw[1] += cosine;
	output->vectors[2].raw[1] -= scaled_normalized_sin.raw[0];
	output->vectors[0].raw[2] -= scaled_normalized_sin.raw[1];
	output->vectors[1].raw[2] += scaled_normalized_sin.raw[0];
	output->vectors[2].raw[2] += cosine;

	output->vectors[0].raw[3] = output->vectors[1].raw[3] = output->vectors[2].raw[3] = output->vectors[3].raw[0] = output->vectors[3].raw[1] = output->vectors[3].raw[2] = 0.0f;
	output->vectors[3].raw[3] = 1.0f;
	}

static inline void math_mat4_set_rotation_matrix_x ( mat4 *output, const float angle )
	{
	float cosine = cosf ( angle );
	float sin = sinf ( angle );

	output->vectors[0].raw[0] = 1.0f;
	output->vectors[0].raw[1] = 0.0f;
	output->vectors[0].raw[2] = 0.0f;
	output->vectors[0].raw[3] = 0.0f;
	output->vectors[1].raw[0] = 0.0f;
	output->vectors[1].raw[1] = cosine;
	output->vectors[1].raw[2] = sin;
	output->vectors[1].raw[3] = 0.0f;
	output->vectors[2].raw[0] = 0.0f;
	output->vectors[2].raw[1] = -sin;
	output->vectors[2].raw[2] = cosine;
	output->vectors[2].raw[3] = 0.0f;
	output->vectors[3].raw[0] = 0.0f;
	output->vectors[3].raw[1] = 0.0f;
	output->vectors[3].raw[2] = 0.0f;
	output->vectors[3].raw[3] = 1.0f;
	}

static inline void math_mat4_set_rotation_matrix_y ( mat4 *output, const float angle )
	{
	float cosine = cosf ( angle );
	float sin = sinf ( angle );

	output->vectors[0].raw[0] = cosine;
	output->vectors[0].raw[1] = 0.0f;
	output->vectors[0].raw[2] = -sin;
	output->vectors[0].raw[3] = 0.0f;
	output->vectors[1].raw[0] = 0.0f;
	output->vectors[1].raw[1] = 1.0f;
	output->vectors[1].raw[2] = 0.0f;
	output->vectors[1].raw[3] = 0.0f;
	output->vectors[2].raw[0] = sin;
	output->vectors[2].raw[1] = 0.0f;
	output->vectors[2].raw[2] = cosine;
	output->vectors[2].raw[3] = 0.0f;
	output->vectors[3].raw[0] = 0.0f;
	output->vectors[3].raw[1] = 0.0f;
	output->vectors[3].raw[2] = 0.0f;
	output->vectors[3].raw[3] = 1.0f;
	}

static inline void math_mat4_set_rotation_matrix_z ( mat4 *output, const float angle )
	{
	float cosine = cosf ( angle );
	float sin = sinf ( angle );

	output->vectors[0].raw[0] = cosine;
	output->vectors[0].raw[1] = sin;
	output->vectors[0].raw[2] = 0.0f;
	output->vectors[0].raw[3] = 0.0f;
	output->vectors[1].raw[0] = -sin;
	output->vectors[1].raw[1] = cosine;
	output->vectors[1].raw[2] = 0.0f;
	output->vectors[1].raw[3] = 0.0f;
	output->vectors[2].raw[0] = 0.0f;
	output->vectors[2].raw[1] = 0.0f;
	output->vectors[2].raw[2] = 1.0f;
	output->vectors[2].raw[3] = 0.0f;
	output->vectors[3].raw[0] = 0.0f;
	output->vectors[3].raw[1] = 0.0f;
	output->vectors[3].raw[2] = 0.0f;
	output->vectors[3].raw[3] = 1.0f;
	}

static inline void math_mat4_set_translation_matrix ( mat4 *output, const vec3 translation )
	{
	output->vectors[0].raw[0] = 1.0f;
	output->vectors[0].raw[1] = 0.0f;
	output->vectors[0].raw[2] = 0.0f;
	output->vectors[0].raw[3] = 0.0f;
	output->vectors[1].raw[0] = 0.0f;
	output->vectors[1].raw[1] = 1.0f;
	output->vectors[1].raw[2] = 0.0f;
	output->vectors[1].raw[3] = 0.0f;
	output->vectors[2].raw[0] = 0.0f;
	output->vectors[2].raw[1] = 0.0f;
	output->vectors[2].raw[2] = 1.0f;
	output->vectors[2].raw[3] = 0.0f;
	output->vectors[3].raw[0] = translation.x;
	output->vectors[3].raw[1] = translation.y;
	output->vectors[3].raw[2] = translation.z;
	output->vectors[3].raw[3] = 1.0f;
	}

static inline void math_mat4_set_scale_matrix ( mat4 *output, const vec3 scale )
	{
	output->vectors[0].raw[0] = scale.x;
	output->vectors[0].raw[1] = 0.0f;
	output->vectors[0].raw[2] = 0.0f;
	output->vectors[0].raw[3] = 0.0f;
	output->vectors[1].raw[0] = 0.0f;
	output->vectors[1].raw[1] = scale.y;
	output->vectors[1].raw[2] = 0.0f;
	output->vectors[1].raw[3] = 0.0f;
	output->vectors[2].raw[0] = 0.0f;
	output->vectors[2].raw[1] = 0.0f;
	output->vectors[2].raw[2] = scale.z;
	output->vectors[2].raw[3] = 0.0f;
	output->vectors[3].raw[0] = 0.0f;
	output->vectors[3].raw[1] = 0.0f;
	output->vectors[3].raw[2] = 0.0f;
	output->vectors[3].raw[3] = 1.0f;
	}

static inline void math_mat4_scale_vec3 ( mat4 *output, const mat4 input, const vec3 scale )
	{
	for ( unsigned row = 0; row < 4; ++row )
		{
		output->vectors[row].raw[0] = input.vectors[row].raw[0] * scale.raw[0];
		output->vectors[row].raw[1] = input.vectors[row].raw[1] * scale.raw[1];
		output->vectors[row].raw[2] = input.vectors[row].raw[2] * scale.raw[2];
		output->vectors[row].raw[3] = input.vectors[row].raw[3];
		}
	}

static inline void math_mat4_scale_vec4 ( mat4 *output, const mat4 input, const vec4 scale )
	{
	for ( unsigned row = 0; row < 4; ++row )
		{
		output->vectors[row].raw[0] = input.vectors[row].raw[0] * scale.raw[0];
		output->vectors[row].raw[1] = input.vectors[row].raw[1] * scale.raw[1];
		output->vectors[row].raw[2] = input.vectors[row].raw[2] * scale.raw[2];
		output->vectors[row].raw[3] = input.vectors[row].raw[3] * scale.raw[3];
		}
	}

static inline void math_mat4_scale_scalar ( mat4 *output, const mat4 input, const float scale )
	{
	for ( unsigned row = 0; row < 4; ++row )
		{
		output->vectors[row].raw[0] = input.vectors[row].raw[0] * scale;
		output->vectors[row].raw[1] = input.vectors[row].raw[1] * scale;
		output->vectors[row].raw[2] = input.vectors[row].raw[2] * scale;
		output->vectors[row].raw[3] = input.vectors[row].raw[3] * scale;
		}
	}

static inline bool math_mat4_inverse ( mat4 *output, const mat4 input )
	{
	float a = input.raw[0][0], b = input.raw[0][1], c = input.raw[0][2], d = input.raw[0][3];
	float e = input.raw[1][0], f = input.raw[1][1], g = input.raw[1][2], h = input.raw[1][3];
	float i = input.raw[2][0], j = input.raw[2][1], k = input.raw[2][2], l = input.raw[2][3];
	float m = input.raw[3][0], n = input.raw[3][1], o = input.raw[3][2], p = input.raw[3][3];
	float c1  = k * p - l * o,  c2  = c * h - d * g,  c3  = i * p - l * m;
	float c4  = a * h - d * e,  c5  = j * p - l * n,  c6  = b * h - d * f;
	float c7  = i * n - j * m,  c8  = a * f - b * e,  c9  = j * o - k * n;
	float c10 = b * g - c * f,  c11 = i * o - k * m,  c12 = a * g - c * e;
	float idt = 1.0f / ( c8 * c1 + c4 * c9 + c10 * c3 + c2 * c7 - c12 * c5 - c6 * c11 ), ndt = -idt;

	output->raw[0][0] = ( f * c1  - g * c5  + h * c9 )  * idt;
	output->raw[0][1] = ( b * c1  - c * c5  + d * c9 )  * ndt;
	output->raw[0][2] = ( n * c2  - o * c6  + p * c10 ) * idt;
	output->raw[0][3] = ( j * c2  - k * c6  + l * c10 ) * ndt;

	output->raw[1][0] = ( e * c1  - g * c3  + h * c11 ) * ndt;
	output->raw[1][1] = ( a * c1  - c * c3  + d * c11 ) * idt;
	output->raw[1][2] = ( m * c2  - o * c4  + p * c12 ) * ndt;
	output->raw[1][3] = ( i * c2  - k * c4  + l * c12 ) * idt;

	output->raw[2][0] = ( e * c5  - f * c3  + h * c7 )  * idt;
	output->raw[2][1] = ( a * c5  - b * c3  + d * c7 )  * ndt;
	output->raw[2][2] = ( m * c6  - n * c4  + p * c8 )  * idt;
	output->raw[2][3] = ( i * c6  - j * c4  + l * c8 )  * ndt;

	output->raw[3][0] = ( e * c9  - f * c11 + g * c7 )  * ndt;
	output->raw[3][1] = ( a * c9  - b * c11 + c * c7 )  * idt;
	output->raw[3][2] = ( m * c10 - n * c12 + o * c8 )  * ndt;
	output->raw[3][3] = ( i * c10 - j * c12 + k * c8 )  * idt;
	return true;
	}

static inline void math_mat4_multiply ( mat4 *output, const mat4 m1, const mat4 m2 )
	{
	float a00 = m1.vectors[0].raw[0], a01 = m1.vectors[0].raw[1], a02 = m1.vectors[0].raw[2], a03 = m1.vectors[0].raw[3];
	float a10 = m1.vectors[1].raw[0], a11 = m1.vectors[1].raw[1], a12 = m1.vectors[1].raw[2], a13 = m1.vectors[1].raw[3];
	float a20 = m1.vectors[2].raw[0], a21 = m1.vectors[2].raw[1], a22 = m1.vectors[2].raw[2], a23 = m1.vectors[2].raw[3];
	float a30 = m1.vectors[3].raw[0], a31 = m1.vectors[3].raw[1], a32 = m1.vectors[3].raw[2], a33 = m1.vectors[3].raw[3];
	float b00 = m2.vectors[0].raw[0], b01 = m2.vectors[0].raw[1], b02 = m2.vectors[0].raw[2], b03 = m2.vectors[0].raw[3];
	float b10 = m2.vectors[1].raw[0], b11 = m2.vectors[1].raw[1], b12 = m2.vectors[1].raw[2], b13 = m2.vectors[1].raw[3];
	float b20 = m2.vectors[2].raw[0], b21 = m2.vectors[2].raw[1], b22 = m2.vectors[2].raw[2], b23 = m2.vectors[2].raw[3];
	float b30 = m2.vectors[3].raw[0], b31 = m2.vectors[3].raw[1], b32 = m2.vectors[3].raw[2], b33 = m2.vectors[3].raw[3];

	output->vectors[0].raw[0] = a00 * b00 + a10 * b01 + a20 * b02 + a30 * b03;
	output->vectors[0].raw[1] = a01 * b00 + a11 * b01 + a21 * b02 + a31 * b03;
	output->vectors[0].raw[2] = a02 * b00 + a12 * b01 + a22 * b02 + a32 * b03;
	output->vectors[0].raw[3] = a03 * b00 + a13 * b01 + a23 * b02 + a33 * b03;
	output->vectors[1].raw[0] = a00 * b10 + a10 * b11 + a20 * b12 + a30 * b13;
	output->vectors[1].raw[1] = a01 * b10 + a11 * b11 + a21 * b12 + a31 * b13;
	output->vectors[1].raw[2] = a02 * b10 + a12 * b11 + a22 * b12 + a32 * b13;
	output->vectors[1].raw[3] = a03 * b10 + a13 * b11 + a23 * b12 + a33 * b13;
	output->vectors[2].raw[0] = a00 * b20 + a10 * b21 + a20 * b22 + a30 * b23;
	output->vectors[2].raw[1] = a01 * b20 + a11 * b21 + a21 * b22 + a31 * b23;
	output->vectors[2].raw[2] = a02 * b20 + a12 * b21 + a22 * b22 + a32 * b23;
	output->vectors[2].raw[3] = a03 * b20 + a13 * b21 + a23 * b22 + a33 * b23;
	output->vectors[3].raw[0] = a00 * b30 + a10 * b31 + a20 * b32 + a30 * b33;
	output->vectors[3].raw[1] = a01 * b30 + a11 * b31 + a21 * b32 + a31 * b33;
	output->vectors[3].raw[2] = a02 * b30 + a12 * b31 + a22 * b32 + a32 * b33;
	output->vectors[3].raw[3] = a03 * b30 + a13 * b31 + a23 * b32 + a33 * b33;
	}
