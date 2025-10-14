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

inline void math_vec4_set ( vec4 *output, const float v1, const float v2, const float v3, const float v4 )
	{
	output->raw[0] = v1;
	output->raw[1] = v2;
	output->raw[2] = v3;
	output->raw[3] = v4;
	}

inline void math_vec4_copy ( vec4 *output, const vec4 input )
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

inline void math_vec4_add ( vec4 *output, const vec4 first, const vec4 second )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		output->raw[index] = first.raw[index] + second.raw[index];
		}
	}

inline void math_vec4_subtract ( vec4 *output, const vec4 first, const vec4 second )
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
		output->raw[index] = (float) ( (float) output->raw[index] / length );
	}

inline void math_vec4_normalize_to ( vec4 *output, vec4 input )
	{
	float length = math_vec4_length ( input );
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = (float) ( (float) input.raw[index] / length );
	}

inline void math_vec4_scale ( vec4 *output, const float scale )
	{
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = (float) ( (float) output->raw[index] * scale );
	}

inline void math_vec4_scale_to ( vec4 *output, vec4 input, const float scale )
	{
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = (float) ( (float) input.raw[index] * scale );
	}
