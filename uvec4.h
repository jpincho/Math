#pragma once
#include <stdbool.h>
#include <math.h>

typedef struct
	{
	union
		{
		struct
			{
			unsigned x, y, z, w;
			};
		unsigned raw[4];
		};
	}uvec4;

inline void math_uvec4_copy ( const uvec4 input, uvec4 *output )
	{
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = input.raw[index];
	}

inline bool math_uvec4_equals ( const uvec4 first, const uvec4 second )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		if ( first.raw[index] != second.raw[index] )
			return false;
		}
	return true;
	}


inline void math_uvec4_add ( const uvec4 first, const uvec4 second, uvec4 *output )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		output->raw[index] = first.raw[index] + second.raw[index];
		}
	}

inline void math_uvec4_subtract ( const uvec4 first, const uvec4 second, uvec4 *output )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		output->raw[index] = first.raw[index] - second.raw[index];
		}
	}

inline float math_uvec4_length_squared ( const uvec4 input )
	{
	float result = 0;
	for ( unsigned index = 0; index < 4; ++index )
		result += input.raw[index] * input.raw[index];
	return result;
	}

inline float math_uvec4_length ( const uvec4 input )
	{
	return sqrtf ( math_uvec4_length_squared ( input ) );
	}

inline void math_uvec4_set_to_zero ( uvec4 *output )
	{
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = 0;
	}

inline float math_uvec4_dot_product ( const uvec4 first, const uvec4 second )
	{
	float result = 0;
	for ( unsigned index = 0; index < 4; ++index )
		result += first.raw[index] * second.raw[index];
	return result;
	}
