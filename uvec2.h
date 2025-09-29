#pragma once
#include <stdbool.h>
#include <math.h>

typedef struct
	{
	union
		{
		struct
			{
			unsigned x, y;
			};
		unsigned raw[2];
		};
	}uvec2;

inline void math_uvec2_copy ( const uvec2 input, uvec2 *output )
	{
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = input.raw[index];
	}

inline bool math_uvec2_equals ( const uvec2 first, const uvec2 second )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		if ( first.raw[index] != second.raw[index] )
			return false;
		}
	return true;
	}

inline void math_uvec2_add ( const uvec2 first, const uvec2 second, uvec2 *output )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		output->raw[index] = first.raw[index] + second.raw[index];
		}
	}

inline void math_uvec2_subtract ( const uvec2 first, const uvec2 second, uvec2 *output )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		output->raw[index] = first.raw[index] - second.raw[index];
		}
	}
inline float math_uvec2_length_squared ( const uvec2 input )
	{
	float result = 0;
	for ( unsigned index = 0; index < 2; ++index )
		result += input.raw[index] * input.raw[index];
	return result;
	}

inline float math_uvec2_length ( const uvec2 input )
	{
	return sqrtf ( math_uvec2_length_squared ( input ) );
	}

inline void math_uvec2_set_to_zero ( uvec2 *output )
	{
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = 0;
	}

inline float math_uvec2_dot_product ( const uvec2 first, const uvec2 second )
	{
	float result = 0;
	for ( unsigned index = 0; index < 2; ++index )
		result += first.raw[index] * second.raw[index];
	return result;
	}
