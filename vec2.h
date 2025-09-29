#pragma once
#include <stdbool.h>
#include <math.h>

typedef struct
	{
	union
		{
		struct
			{
			float x, y;
			};
		float raw[2];
		};
	}vec2;

inline void math_vec2_copy ( const vec2 input, vec2 *output )
	{
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = input.raw[index];
	}

inline bool math_vec2_equals ( const vec2 first, const vec2 second )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		if ( first.raw[index] != second.raw[index] )
			return false;
		}
	return true;
	}

inline void math_vec2_add ( const vec2 first, const vec2 second, vec2 *output )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		output->raw[index] = first.raw[index] + second.raw[index];
		}
	}

inline void math_vec2_subtract ( const vec2 first, const vec2 second, vec2 *output )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		output->raw[index] = first.raw[index] - second.raw[index];
		}
	}
inline float math_vec2_length_squared ( const vec2 input )
	{
	float result = 0;
	for ( unsigned index = 0; index < 2; ++index )
		result += input.raw[index] * input.raw[index];
	return result;
	}

inline float math_vec2_length ( const vec2 input )
	{
	return sqrtf ( math_vec2_length_squared ( input ) );
	}

inline void math_vec2_set_to_zero ( vec2 *output )
	{
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = 0.0f;
	}

inline float math_vec2_dot_product ( const vec2 first, const vec2 second )
	{
	float result = 0;
	for ( unsigned index = 0; index < 2; ++index )
		result += first.raw[index] * second.raw[index];
	return result;
	}

inline void math_vec2_normalize ( vec2 *output )
	{
	float length = math_vec2_length ( *output );
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] /= length;
	}
