#pragma once
#include "types.h"
#include <stdio.h>
#include <stdarg.h>

inline void math_mat3_dump ( const mat3 matrix )
	{
	for ( unsigned index = 0; index < 3 * 3; ++index )
		{
		printf ( "%f ", matrix.raw[index] );
		if ( ( index + 1 ) % 3 == 0 )
			printf ( "\n" );
		}
	}

inline bool math_mat3_equals ( const mat3 first, const mat3 second )
	{
	for ( unsigned index = 0; index < 3 * 3; ++index )
		{
		if ( first.raw[index] != second.raw[index] )
			return false;
		}
	return true;
	}

inline void math_mat3_copy ( mat3 *output, const mat3 input )
	{
	for ( unsigned column = 0; column < 3; ++column )
		{
		math_vec3_copy ( &output->vectors[column], input.vectors[column] );
		}
	}

inline void math_mat3_from_mat4 ( mat3 *output, const mat4 input )
	{
	for ( unsigned row = 0; row < 3; ++row )
		{
		output->vectors[row].raw[0] = input.vectors[row].raw[0];
		output->vectors[row].raw[1] = input.vectors[row].raw[1];
		output->vectors[row].raw[2] = input.vectors[row].raw[2];
		}
	}

inline void math_mat3_invert ( mat3 *output, const mat3 input)
	{
	// copied from cglm
	float a = input.vectors[0].raw[0], b = input.vectors[0].raw[1], c = input.vectors[0].raw[2],
		d = input.vectors[1].raw[0], e = input.vectors[1].raw[1], f = input.vectors[1].raw[2],
		g = input.vectors[2].raw[0], h = input.vectors[2].raw[1], i = input.vectors[2].raw[2],

		c1 = e * i - f * h, c2 = d * i - g * f, c3 = d * h - g * e,
		idt = 1.0f / ( a * c1 - b * c2 + c * c3 ), ndt = -idt;

	output->vectors[0].raw[0] = idt * c1;
	output->vectors[0].raw[1] = ndt * ( b * i - h * c );
	output->vectors[0].raw[2] = idt * ( b * f - e * c );
	output->vectors[1].raw[0] = ndt * c2;
	output->vectors[1].raw[1] = idt * ( a * i - g * c );
	output->vectors[1].raw[2] = ndt * ( a * f - d * c );
	output->vectors[2].raw[0] = idt * c3;
	output->vectors[2].raw[1] = ndt * ( a * h - g * b );
	output->vectors[2].raw[2] = idt * ( a * e - d * b );
	}

inline void math_mat3_transpose ( mat3 *output, const mat3 input )
	{
	for ( unsigned iterator1 = 0; iterator1 < 3; ++iterator1 )
		{
		for ( unsigned iterator2 = 0; iterator2 < 3; ++iterator2 )
			{
			output->vectors[iterator1].raw[iterator2] = input.vectors[iterator2].raw[iterator1];
			}
		}
	}

inline void math_mat3_set_zero ( mat3 *output )
	{
	for ( unsigned index = 0; index < 3 * 3; ++index )
		{
		output->raw[index] = 0.0f;
		}
	}

inline void math_mat3_set_identity_matrix ( mat3 *output )
	{
	output->raw[0] = 1.0f;
	output->raw[1] = 0.0f;
	output->raw[2] = 0.0f;
	output->raw[3] = 0.0f;
	output->raw[4] = 1.0f;
	output->raw[5] = 0.0f;
	output->raw[6] = 0.0f;
	output->raw[7] = 0.0f;
	output->raw[8] = 1.0f;
	}

inline void math_mat3_scale_vec3 ( mat3 *output, const mat3 input, const vec3 scale )
	{
	for ( unsigned row = 0; row < 3; ++row )
		{
		output->vectors[row].raw[0] = input.vectors[row].raw[0] * scale.raw[0];
		output->vectors[row].raw[1] = input.vectors[row].raw[1] * scale.raw[1];
		output->vectors[row].raw[2] = input.vectors[row].raw[2] * scale.raw[2];
		}
	}

inline void math_mat3_scale_scalar ( mat3 *output, const mat3 input, const float scale )
	{
	for ( unsigned row = 0; row < 3; ++row )
		{
		output->vectors[row].raw[0] = input.vectors[row].raw[0] * scale;
		output->vectors[row].raw[1] = input.vectors[row].raw[1] * scale;
		output->vectors[row].raw[2] = input.vectors[row].raw[2] * scale;
		}
	}
