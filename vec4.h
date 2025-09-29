#pragma once
#include <stdbool.h>
#include <math.h>

typedef struct
	{
	union
		{
		struct
			{
			float x, y, z, w;
			};
		float raw[4];
		};
	}vec4;

inline void math_vec4_copy ( const vec4 input, vec4 *output )
	{
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = input.raw[index];
	}

inline bool math_vec4_equals ( const vec4 first, const vec4 second )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		if ( first.raw[index] != second.raw[index] )
			return false;
		}
	return true;
	}


inline void math_vec4_add ( const vec4 first, const vec4 second, vec4 *output )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		output->raw[index] = first.raw[index] + second.raw[index];
		}
	}

inline void math_vec4_subtract ( const vec4 first, const vec4 second, vec4 *output )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		output->raw[index] = first.raw[index] - second.raw[index];
		}
	}

inline float math_vec4_length_squared ( const vec4 input )
	{
	float result = 0;
	for ( unsigned index = 0; index < 4; ++index )
		result += input.raw[index] * input.raw[index];
	return result;
	}

inline float math_vec4_length ( const vec4 input )
	{
	return sqrtf ( math_vec4_length_squared ( input ) );
	}

inline void math_vec4_set_to_zero ( vec4 *output )
	{
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = 0.0f;
	}

inline float math_vec4_dot_product ( const vec4 first, const vec4 second )
	{
	float result = 0;
	for ( unsigned index = 0; index < 4; ++index )
		result += first.raw[index] * second.raw[index];
	return result;
	}

inline void math_vec4_normalize ( vec4 *output )
	{
	float length = math_vec4_length ( *output );
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] /= length;
	}
