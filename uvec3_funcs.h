#pragma once
#include "types.h"
#include <stdbool.h>
#include <math.h>

inline void math_uvec3_set ( uvec3 *output, const unsigned v1, const unsigned v2, const unsigned v3 )
	{
	output->raw[0] = v1;
	output->raw[1] = v2;
	output->raw[2] = v3;
	}

inline void math_uvec3_copy ( uvec3 *output, const uvec3 input )
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

inline void math_uvec3_add ( uvec3 *output, const uvec3 first, const uvec3 second )
	{
	for ( unsigned index = 0; index < 3; ++index )
		{
		output->raw[index] = first.raw[index] + second.raw[index];
		}
	}

inline void math_uvec3_subtract ( uvec3 *output, const uvec3 first, const uvec3 second )
	{
	for ( unsigned index = 0; index < 3; ++index )
		{
		output->raw[index] = first.raw[index] - second.raw[index];
		}
	}

inline void math_uvec3_multiply ( uvec3 *output, const uvec3 first, const uvec3 second )
	{
	for ( unsigned index = 0; index < 3; ++index )
		{
		output->raw[index] = first.raw[index] * second.raw[index];
		}
	}

inline void math_uvec3_divide ( uvec3 *output, const uvec3 first, const uvec3 second )
	{
	for ( unsigned index = 0; index < 3; ++index )
		{
		output->raw[index] = first.raw[index] / second.raw[index];
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

inline bool math_uvec3_is_zero ( const uvec3 input )
	{
	for ( unsigned index = 0; index < 3; ++index )
		if ( input.raw[index] != 0 )
			return false;
	return true;
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

inline void math_uvec3_cross_product ( uvec3 *output, const uvec3 first, const uvec3 second )
	{
	output->raw[0] = first.raw[1] * second.raw[2] - first.raw[2] * second.raw[1];
	output->raw[1] = first.raw[2] * second.raw[0] - first.raw[0] * second.raw[2];
	output->raw[2] = first.raw[0] * second.raw[1] - first.raw[1] * second.raw[0];
	}

inline void math_uvec3_normalize ( uvec3 *output )
	{
	float length = math_uvec3_length ( *output );
	for ( unsigned index = 0; index < 3; ++index )
		output->raw[index] = (unsigned) ( (float) output->raw[index] / length );
	}

inline void math_uvec3_normalize_to ( uvec3 *output, uvec3 input )
	{
	float length = math_uvec3_length ( input );
	for ( unsigned index = 0; index < 3; ++index )
		output->raw[index] = (unsigned) ( (float) input.raw[index] / length );
	}

inline void math_uvec3_scale_inplace ( uvec3 *output, const float scale )
	{
	for ( unsigned index = 0; index < 3; ++index )
		output->raw[index] = (unsigned) ( (float) output->raw[index] * scale );
	}

inline void math_uvec3_scale ( uvec3 *output, uvec3 input, const float scale )
	{
	for ( unsigned index = 0; index < 3; ++index )
		output->raw[index] = (unsigned) ( (float) input.raw[index] * scale );
	}
