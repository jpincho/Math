#pragma once
#include "vec3.h"

typedef struct
	{
	union
		{
		vec3 vectors[3];
		float raw[3 * 3];
		};
	}mat3;

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
