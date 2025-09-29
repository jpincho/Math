#pragma once
#include <stdbool.h>
#include <math.h>

typedef struct
	{
	union
		{
		struct
			{
			unsigned x, y, z;
			};
		unsigned raw[3];
		};
	}uvec3;

inline void math_uvec3_copy ( const uvec3 input, uvec3 *output )
	{
	for ( unsigned index = 0; index < 3; ++index )
		output->raw[index] = input.raw[index];
	}

inline bool math_uvec3_equals ( const uvec3 first, const uvec3 second )
	{
	for ( unsigned index = 0; index < 3; ++index )
		{
		if ( first.raw[index] != second.raw[index] )
			return false;
		}
	return true;
	}

inline void math_uvec3_add ( const uvec3 first, const uvec3 second, uvec3 *output )
	{
	for ( unsigned index = 0; index < 3; ++index )
		{
		output->raw[index]=first.raw[index]+second.raw[index];
		}
	}

inline void math_uvec3_subtract ( const uvec3 first, const uvec3 second, uvec3 *output )
	{
	for ( unsigned index = 0; index < 3; ++index )
		{
		output->raw[index] = first.raw[index] - second.raw[index];
		}
	}

inline float math_uvec3_length_squared ( const uvec3 input )
	{
	float result = 0;
	for ( unsigned index = 0; index < 3; ++index )
		result += input.raw[index] * input.raw[index];
	return result;
	}

inline float math_uvec3_length ( const uvec3 input )
	{
	return sqrtf ( math_uvec3_length_squared ( input ) );
	}

inline void math_uvec3_set_to_zero ( uvec3 *output )
	{
	for ( unsigned index = 0; index < 3; ++index )
		output->raw[index] = 0;
	}

inline float math_uvec3_dot_product ( const uvec3 first, const uvec3 second )
	{
	float result = 0;
	for ( unsigned index = 0; index < 3; ++index )
		result += first.raw[index] * second.raw[index];
	return result;
	}

inline void math_uvec3_cross_product ( const uvec3 first, const uvec3 second, uvec3 *output )
	{
	output->raw[0] = first.raw[1] * second.raw[2] - first.raw[2] * second.raw[1];
	output->raw[1] = first.raw[2] * second.raw[0] - first.raw[0] * second.raw[2];
	output->raw[2] = first.raw[0] * second.raw[1] - first.raw[1] * second.raw[0];
	}
