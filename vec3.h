#pragma once
#include <stdbool.h>
#include <math.h>

typedef struct
	{
	union
		{
		struct
			{
			float x, y, z;
			};
		float raw[3];
		};
	}vec3;

inline void math_vec3_copy ( const vec3 input, vec3 *output )
	{
	for ( unsigned index = 0; index < 3; ++index )
		output->raw[index] = input.raw[index];
	}

inline bool math_vec3_equals ( const vec3 first, const vec3 second )
	{
	for ( unsigned index = 0; index < 3; ++index )
		{
		if ( first.raw[index] != second.raw[index] )
			return false;
		}
	return true;
	}

inline void math_vec3_add ( const vec3 first, const vec3 second, vec3 *output )
	{
	for ( unsigned index = 0; index < 3; ++index )
		{
		output->raw[index]=first.raw[index]+second.raw[index];
		}
	}

inline void math_vec3_subtract ( const vec3 first, const vec3 second, vec3 *output )
	{
	for ( unsigned index = 0; index < 3; ++index )
		{
		output->raw[index] = first.raw[index] - second.raw[index];
		}
	}

inline float math_vec3_length_squared ( const vec3 input )
	{
	float result = 0;
	for ( unsigned index = 0; index < 3; ++index )
		result += input.raw[index] * input.raw[index];
	return result;
	}

inline float math_vec3_length ( const vec3 input )
	{
	return sqrtf ( math_vec3_length_squared ( input ) );
	}

inline void math_vec3_set_to_zero ( vec3 *output )
	{
	for ( unsigned index = 0; index < 3; ++index )
		output->raw[index] = 0.0f;
	}

inline float math_vec3_dot_product ( const vec3 first, const vec3 second )
	{
	float result = 0;
	for ( unsigned index = 0; index < 3; ++index )
		result += first.raw[index] * second.raw[index];
	return result;
	}

inline void math_vec3_cross_product ( const vec3 first, const vec3 second, vec3 *output )
	{
	output->raw[0] = first.raw[1] * second.raw[2] - first.raw[2] * second.raw[1];
	output->raw[1] = first.raw[2] * second.raw[0] - first.raw[0] * second.raw[2];
	output->raw[2] = first.raw[0] * second.raw[1] - first.raw[1] * second.raw[0];
	}

inline void math_vec3_normalize ( vec3 *output )
	{
	float length = math_vec3_length ( *output );
	for ( unsigned index = 0; index < 3; ++index )
		output->raw[index] /= length;
	}
