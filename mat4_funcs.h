#pragma once
#include "types.h"
#include <stdio.h>
#include <stdarg.h>

inline void math_mat4_dump ( const mat4 matrix )
	{
	for ( unsigned index = 0; index < 4 * 4; ++index )
		{
		printf ( "%f ", matrix.raw[index] );
		if ( ( index + 1 ) % 4 == 0 )
			printf ( "\n" );
		}
	}

inline bool math_mat4_equals ( const mat4 first, const mat4 second )
	{
	for ( unsigned index = 0; index < 4 * 4; ++index )
		{
		if ( first.raw[index] != second.raw[index] )
			return false;
		}
	return true;
	}

inline void math_mat4_copy ( mat4 *output, const mat4 input )
	{
	for ( unsigned column = 0; column < 4; ++column )
		{
		math_vec4_copy ( &output->vectors[column], input.vectors[column] );
		}
	}

inline void math_mat4_transpose ( mat4 *output, const mat4 input )
	{
	for ( unsigned iterator1 = 0; iterator1 < 4; ++iterator1 )
		{
		for ( unsigned iterator2 = 0; iterator2 < 4; ++iterator2 )
			{
			output->vectors[iterator1].raw[iterator2] = input.vectors[iterator2].raw[iterator1];
			}
		}
	}

inline void math_mat4_set_zero ( mat4 *output )
	{
	for ( unsigned index = 0; index < 4 * 4; ++index )
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

inline void math_mat4_set_perspective_matrix ( mat4 *output, const float vertical_fov, const float ratio, const float near, const float far )
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

inline void math_mat4_set_view_matrix ( mat4 *output, const vec3 camera_pos, const vec3 front, const vec3 up )
	{
	vec3 unit_front;
	math_vec3_subtract ( &unit_front, front, camera_pos );
	math_vec3_normalize ( &unit_front );

	vec3 unit_side;
	math_vec3_cross_product ( &unit_side, unit_front, up );
	math_vec3_normalize ( &unit_side );

	vec3 unit_up;
	math_vec3_cross_product ( &unit_up, unit_side, unit_front );

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
	output->vectors[3].raw[0] = -math_vec3_dot_product ( unit_side, camera_pos );
	output->vectors[3].raw[1] = -math_vec3_dot_product ( unit_up, camera_pos );
	output->vectors[3].raw[2] = math_vec3_dot_product ( unit_front, camera_pos );
	output->vectors[3].raw[3] = 1.0f;
	}

inline void math_mat4_set_rotation_matrix ( mat4 *output, const float angle, const vec3 axis )
	{
	vec3 normalized_axis, scaled_normalized_1_minus_cos, scaled_normalized_sin;

	float cosine = cosf ( angle );

	math_vec3_normalize_to ( &normalized_axis, axis );
	math_vec3_scale ( &scaled_normalized_1_minus_cos, normalized_axis, 1.0f - cosine );
	math_vec3_scale ( &scaled_normalized_sin, normalized_axis, sinf ( angle ) );

	math_vec3_scale ( (vec3 *) &output->vectors[0], normalized_axis, scaled_normalized_1_minus_cos.raw[0] );
	math_vec3_scale ( (vec3 *) &output->vectors[1], normalized_axis, scaled_normalized_1_minus_cos.raw[1] );
	math_vec3_scale ( (vec3 *) &output->vectors[2], normalized_axis, scaled_normalized_1_minus_cos.raw[2] );

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

inline void math_mat4_set_rotation_matrix_x ( mat4 *output, const float angle )
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

inline void math_mat4_set_rotation_matrix_y ( mat4 *output, const float angle )
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

inline void math_mat4_set_rotation_matrix_z ( mat4 *output, const float angle )
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

inline void math_mat4_set_translation_matrix ( mat4 *output, const vec3 translation )
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

inline void math_mat4_set_scale_matrix ( mat4 *output, const vec3 scale )
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

inline void math_mat4_scale_vec3 ( mat4 *output, const mat4 input, const vec3 scale )
	{
	for ( unsigned row = 0; row < 4; ++row )
		{
		output->vectors[row].raw[0] = input.vectors[row].raw[0] * scale.raw[0];
		output->vectors[row].raw[1] = input.vectors[row].raw[1] * scale.raw[1];
		output->vectors[row].raw[2] = input.vectors[row].raw[2] * scale.raw[2];
		output->vectors[row].raw[3] = input.vectors[row].raw[3];
		}
	}

inline void math_mat4_scale_vec4 ( mat4 *output, const mat4 input, const vec4 scale )
	{
	for ( unsigned row = 0; row < 4; ++row )
		{
		output->vectors[row].raw[0] = input.vectors[row].raw[0] * scale.raw[0];
		output->vectors[row].raw[1] = input.vectors[row].raw[1] * scale.raw[1];
		output->vectors[row].raw[2] = input.vectors[row].raw[2] * scale.raw[2];
		output->vectors[row].raw[3] = input.vectors[row].raw[3] * scale.raw[3];
		}
	}

inline void math_mat4_scale_scalar ( mat4 *output, const mat4 input, const float scale )
	{
	for ( unsigned row = 0; row < 4; ++row )
		{
		output->vectors[row].raw[0] = input.vectors[row].raw[0] * scale;
		output->vectors[row].raw[1] = input.vectors[row].raw[1] * scale;
		output->vectors[row].raw[2] = input.vectors[row].raw[2] * scale;
		output->vectors[row].raw[3] = input.vectors[row].raw[3] * scale;
		}
	}

inline bool math_mat4_inverse ( mat4 *output, const mat4 input )
	{
	// Copied from https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
	/**
	 * References an element of 4x4 matrix.
	 * Calculate the linear storage index of the element and references it.
	 */
#define MAT(m,r,c) (m)[(c)*4+(r)]
	 /**
	  * Swaps the values of two floating point variables.
	  */
#define SWAP_ROWS(a, b) { float *_tmp = a; (a)=(b); (b)=_tmp; }

	const float *m = input.raw;
	float wtmp[4][8];
	float m0, m1, m2, m3, s;
	float *r0, *r1, *r2, *r3;

	r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];

	r0[0] = MAT ( m, 0, 0 ), r0[1] = MAT ( m, 0, 1 ),
		r0[2] = MAT ( m, 0, 2 ), r0[3] = MAT ( m, 0, 3 ),
		r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,

		r1[0] = MAT ( m, 1, 0 ), r1[1] = MAT ( m, 1, 1 ),
		r1[2] = MAT ( m, 1, 2 ), r1[3] = MAT ( m, 1, 3 ),
		r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,

		r2[0] = MAT ( m, 2, 0 ), r2[1] = MAT ( m, 2, 1 ),
		r2[2] = MAT ( m, 2, 2 ), r2[3] = MAT ( m, 2, 3 ),
		r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,

		r3[0] = MAT ( m, 3, 0 ), r3[1] = MAT ( m, 3, 1 ),
		r3[2] = MAT ( m, 3, 2 ), r3[3] = MAT ( m, 3, 3 ),
		r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;

	/* choose pivot - or die */
	if ( fabsf ( r3[0] ) > fabsf ( r2[0] ) ) SWAP_ROWS ( r3, r2 );
	if ( fabsf ( r2[0] ) > fabsf ( r1[0] ) ) SWAP_ROWS ( r2, r1 );
	if ( fabsf ( r1[0] ) > fabsf ( r0[0] ) ) SWAP_ROWS ( r1, r0 );
	if ( 0.0F == r0[0] )
		return false;

	/* eliminate first variable     */
	m1 = r1[0] / r0[0]; m2 = r2[0] / r0[0]; m3 = r3[0] / r0[0];
	s = r0[1]; r1[1] -= m1 * s; r2[1] -= m2 * s; r3[1] -= m3 * s;
	s = r0[2]; r1[2] -= m1 * s; r2[2] -= m2 * s; r3[2] -= m3 * s;
	s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;
	s = r0[4];
	if ( s != 0.0F ) { r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s; }
	s = r0[5];
	if ( s != 0.0F ) { r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s; }
	s = r0[6];
	if ( s != 0.0F ) { r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s; }
	s = r0[7];
	if ( s != 0.0F ) { r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s; }

	/* choose pivot - or die */
	if ( fabsf ( r3[1] ) > fabsf ( r2[1] ) ) SWAP_ROWS ( r3, r2 );
	if ( fabsf ( r2[1] ) > fabsf ( r1[1] ) ) SWAP_ROWS ( r2, r1 );
	if ( 0.0F == r1[1] )
		return false;

	/* eliminate second variable */
	m2 = r2[1] / r1[1]; m3 = r3[1] / r1[1];
	r2[2] -= m2 * r1[2]; r3[2] -= m3 * r1[2];
	r2[3] -= m2 * r1[3]; r3[3] -= m3 * r1[3];
	s = r1[4]; if ( 0.0F != s ) { r2[4] -= m2 * s; r3[4] -= m3 * s; }
	s = r1[5]; if ( 0.0F != s ) { r2[5] -= m2 * s; r3[5] -= m3 * s; }
	s = r1[6]; if ( 0.0F != s ) { r2[6] -= m2 * s; r3[6] -= m3 * s; }
	s = r1[7]; if ( 0.0F != s ) { r2[7] -= m2 * s; r3[7] -= m3 * s; }

	/* choose pivot - or die */
	if ( fabsf ( r3[2] ) > fabsf ( r2[2] ) ) SWAP_ROWS ( r3, r2 );
	if ( 0.0F == r2[2] )
		return false;

	/* eliminate third variable */
	m3 = r3[2] / r2[2];
	r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
		r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
		r3[7] -= m3 * r2[7];

	/* last check */
	if ( 0.0F == r3[3] )
		return false;

	s = 1.0F / r3[3];             /* now back substitute row 3 */
	r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

	m2 = r2[3];                 /* now back substitute row 2 */
	s = 1.0F / r2[2];
	r2[4] = s * ( r2[4] - r3[4] * m2 ), r2[5] = s * ( r2[5] - r3[5] * m2 ),
		r2[6] = s * ( r2[6] - r3[6] * m2 ), r2[7] = s * ( r2[7] - r3[7] * m2 );
	m1 = r1[3];
	r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
		r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
	m0 = r0[3];
	r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
		r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

	m1 = r1[2];                 /* now back substitute row 1 */
	s = 1.0F / r1[1];
	r1[4] = s * ( r1[4] - r2[4] * m1 ), r1[5] = s * ( r1[5] - r2[5] * m1 ),
		r1[6] = s * ( r1[6] - r2[6] * m1 ), r1[7] = s * ( r1[7] - r2[7] * m1 );
	m0 = r0[2];
	r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
		r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

	m0 = r0[1];                 /* now back substitute row 0 */
	s = 1.0F / r0[0];
	r0[4] = s * ( r0[4] - r1[4] * m0 ), r0[5] = s * ( r0[5] - r1[5] * m0 ),
		r0[6] = s * ( r0[6] - r1[6] * m0 ), r0[7] = s * ( r0[7] - r1[7] * m0 );

	float *out = output->raw;
	MAT ( out, 0, 0 ) = r0[4]; MAT ( out, 0, 1 ) = r0[5],
		MAT ( out, 0, 2 ) = r0[6]; MAT ( out, 0, 3 ) = r0[7],
		MAT ( out, 1, 0 ) = r1[4]; MAT ( out, 1, 1 ) = r1[5],
		MAT ( out, 1, 2 ) = r1[6]; MAT ( out, 1, 3 ) = r1[7],
		MAT ( out, 2, 0 ) = r2[4]; MAT ( out, 2, 1 ) = r2[5],
		MAT ( out, 2, 2 ) = r2[6]; MAT ( out, 2, 3 ) = r2[7],
		MAT ( out, 3, 0 ) = r3[4]; MAT ( out, 3, 1 ) = r3[5],
		MAT ( out, 3, 2 ) = r3[6]; MAT ( out, 3, 3 ) = r3[7];

#undef SWAP_ROWS
#undef MAT

	return true;
	}

inline void math_mat4_multiply ( mat4 *output, const mat4 m1, const mat4 m2 )
	{
	float a00 = m1.vectors[0].raw[0], a01 = m1.vectors[0].raw[1], a02 = m1.vectors[0].raw[2], a03 = m1.vectors[0].raw[3],
		a10 = m1.vectors[1].raw[0], a11 = m1.vectors[1].raw[1], a12 = m1.vectors[1].raw[2], a13 = m1.vectors[1].raw[3],
		a20 = m1.vectors[2].raw[0], a21 = m1.vectors[2].raw[1], a22 = m1.vectors[2].raw[2], a23 = m1.vectors[2].raw[3],
		a30 = m1.vectors[3].raw[0], a31 = m1.vectors[3].raw[1], a32 = m1.vectors[3].raw[2], a33 = m1.vectors[3].raw[3],

		b00 = m2.vectors[0].raw[0], b01 = m2.vectors[0].raw[1], b02 = m2.vectors[0].raw[2], b03 = m2.vectors[0].raw[3],
		b10 = m2.vectors[1].raw[0], b11 = m2.vectors[1].raw[1], b12 = m2.vectors[1].raw[2], b13 = m2.vectors[1].raw[3],
		b20 = m2.vectors[2].raw[0], b21 = m2.vectors[2].raw[1], b22 = m2.vectors[2].raw[2], b23 = m2.vectors[2].raw[3],
		b30 = m2.vectors[3].raw[0], b31 = m2.vectors[3].raw[1], b32 = m2.vectors[3].raw[2], b33 = m2.vectors[3].raw[3];

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
