#pragma once
#include "types.h"
#include <stdbool.h>
#include <math.h>

inline void math_ivec3_set ( ivec3 *output, const int v1, const int v2, const int v3 )
	{
	output->raw[0] = v1;
	output->raw[1] = v2;
	output->raw[2] = v3;
	}

inline void math_ivec3_copy ( ivec3 *output, const ivec3 input )
	{
	for ( unsigned index = 0; index < 3; ++index )
		output->raw[index] = input.raw[index];
	}

inline bool math_ivec3_equals ( const ivec3 first, const ivec3 second )
	{
	for ( unsigned index = 0; index < 3; ++index )
		{
		if ( first.raw[index] != second.raw[index] )
			return false;
		}
	return true;
	}

inline void math_ivec3_add ( ivec3 *output, const ivec3 first, const ivec3 second )
	{
	for ( unsigned index = 0; index < 3; ++index )
		{
		output->raw[index] = first.raw[index] + second.raw[index];
		}
	}

inline void math_ivec3_subtract ( ivec3 *output, const ivec3 first, const ivec3 second )
	{
	for ( unsigned index = 0; index < 3; ++index )
		{
		output->raw[index] = first.raw[index] - second.raw[index];
		}
	}

inline float math_ivec3_length_squared ( const ivec3 input )
	{
	float result = 0;
	for ( unsigned index = 0; index < 3; ++index )
		result += input.raw[index] * input.raw[index];
	return result;
	}

inline float math_ivec3_length ( const ivec3 input )
	{
	return sqrtf ( math_ivec3_length_squared ( input ) );
	}

inline bool math_ivec3_is_zero ( const ivec3 input )
	{
	for ( unsigned index = 0; index < 3; ++index )
		if ( input.raw[index] != 0 )
			return false;
	return true;
	}

inline void math_ivec3_set_to_zero ( ivec3 *output )
	{
	for ( unsigned index = 0; index < 3; ++index )
		output->raw[index] = 0;
	}

inline float math_ivec3_dot_product ( const ivec3 first, const ivec3 second )
	{
	float result = 0;
	for ( unsigned index = 0; index < 3; ++index )
		result += first.raw[index] * second.raw[index];
	return result;
	}

inline void math_ivec3_cross_product ( ivec3 *output, const ivec3 first, const ivec3 second )
	{
	output->raw[0] = first.raw[1] * second.raw[2] - first.raw[2] * second.raw[1];
	output->raw[1] = first.raw[2] * second.raw[0] - first.raw[0] * second.raw[2];
	output->raw[2] = first.raw[0] * second.raw[1] - first.raw[1] * second.raw[0];
	}

inline void math_ivec3_normalize ( ivec3 *output )
	{
	float length = math_ivec3_length ( *output );
	for ( unsigned index = 0; index < 3; ++index )
		output->raw[index] = (int) ( (float) output->raw[index] / length );
	}

inline void math_ivec3_normalize_to ( ivec3 *output, ivec3 input )
	{
	float length = math_ivec3_length ( input );
	for ( unsigned index = 0; index < 3; ++index )
		output->raw[index] = (int) ( (float) input.raw[index] / length );
	}

inline void math_ivec3_scale ( ivec3 *output, const float scale )
	{
	for ( unsigned index = 0; index < 3; ++index )
		output->raw[index] = (int) ( (float) output->raw[index] * scale );
	}

inline void math_ivec3_scale_to ( ivec3 *output, ivec3 input, const float scale )
	{
	for ( unsigned index = 0; index < 3; ++index )
		output->raw[index] = (int) ( (float) input.raw[index] * scale );
	}
