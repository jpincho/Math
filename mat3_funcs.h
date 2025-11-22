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

inline void math_mat3_transpose_to ( mat3 *output, const mat3 input )
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
