#pragma once
#include "vec2.h"

typedef struct
	{
	union
		{
		vec2 vectors[2];
		float raw[2 * 2];
		};
	}mat2;

inline bool math_mat2_equals ( const mat2 first, const mat2 second )
	{
	for ( unsigned index = 0; index < 2 * 2; ++index )
		{
		if ( first.raw[index] != second.raw[index] )
			return false;
		}
	return true;
	}

inline void math_mat2_copy ( mat2 *output, const mat2 input )
	{
	for ( unsigned column = 0; column < 2; ++column )
		{
		math_vec2_copy ( &output->vectors[column], input.vectors[column] );
		}
	}
