#pragma once
#include "types.h"
#include <stdbool.h>
#include <math.h>

static inline void math_uvec4_set ( uvec4 *output, const unsigned v1, const unsigned v2, const unsigned v3, const unsigned v4 )
	{
	output->raw[0] = v1;
	output->raw[1] = v2;
	output->raw[2] = v3;
	output->raw[3] = v4;
	}

static inline void math_uvec4_copy ( uvec4 *output, const uvec4 input )
	{
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = input.raw[index];
	}

static inline bool math_uvec4_equals ( const uvec4 first, const uvec4 second )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		if ( first.raw[index] != second.raw[index] )
			return false;
		}
	return true;
	}

static inline void math_uvec4_add ( uvec4 *output, const uvec4 first, const uvec4 second )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		output->raw[index] = first.raw[index] + second.raw[index];
		}
	}

static inline void math_uvec4_subtract ( uvec4 *output, const uvec4 first, const uvec4 second )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		output->raw[index] = first.raw[index] - second.raw[index];
		}
	}

static inline void math_uvec4_multiply ( uvec4 *output, const uvec4 first, const uvec4 second )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		output->raw[index] = first.raw[index] * second.raw[index];
		}
	}

static inline void math_uvec4_divide ( uvec4 *output, const uvec4 first, const uvec4 second )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		output->raw[index] = first.raw[index] / second.raw[index];
		}
	}

static inline float math_uvec4_length_squared ( const uvec4 input )
	{
	float result = 0;
	for ( unsigned index = 0; index < 4; ++index )
		result += input.raw[index] * input.raw[index];
	return result;
	}

static inline float math_uvec4_length ( const uvec4 input )
	{
	return sqrtf ( math_uvec4_length_squared ( input ) );
	}

static inline bool math_uvec4_is_zero ( const uvec4 input )
	{
	for ( unsigned index = 0; index < 4; ++index )
		if ( input.raw[index] != 0 )
			return false;
	return true;
	}

static inline void math_uvec4_set_to_zero ( uvec4 *output )
	{
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = 0;
	}

static inline float math_uvec4_dot_product ( const uvec4 first, const uvec4 second )
	{
	float result = 0;
	for ( unsigned index = 0; index < 4; ++index )
		result += first.raw[index] * second.raw[index];
	return result;
	}

static inline void math_uvec4_normalize ( uvec4 *output )
	{
	float length = math_uvec4_length ( *output );
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = ( unsigned ) ( ( float ) output->raw[index] / length );
	}

static inline void math_uvec4_normalize_to ( uvec4 *output, uvec4 input )
	{
	float length = math_uvec4_length ( input );
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = ( unsigned ) ( ( float ) input.raw[index] / length );
	}

static inline void math_uvec4_scale_inplace ( uvec4 *output, const float scale )
	{
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = ( unsigned ) ( ( float ) output->raw[index] * scale );
	}

static inline void math_uvec4_scale ( uvec4 *output, uvec4 input, const float scale )
	{
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = ( unsigned ) ( ( float ) input.raw[index] * scale );
	}
