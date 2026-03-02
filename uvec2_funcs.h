#pragma once
#include "types.h"
#include <stdbool.h>
#include <math.h>

static inline void math_uvec2_set ( uvec2 *output, const unsigned v1, const unsigned v2 )
	{
	output->raw[0] = v1;
	output->raw[1] = v2;
	}

static inline void math_uvec2_copy ( uvec2 *output, const uvec2 input )
	{
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = input.raw[index];
	}

static inline bool math_uvec2_equals ( const uvec2 first, const uvec2 second )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		if ( first.raw[index] != second.raw[index] )
			return false;
		}
	return true;
	}

static inline void math_uvec2_add ( uvec2 *output, const uvec2 first, const uvec2 second )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		output->raw[index] = first.raw[index] + second.raw[index];
		}
	}

static inline void math_uvec2_subtract ( uvec2 *output, const uvec2 first, const uvec2 second )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		output->raw[index] = first.raw[index] - second.raw[index];
		}
	}

static inline void math_uvec2_multiply ( uvec2 *output, const uvec2 first, const uvec2 second )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		output->raw[index] = first.raw[index] * second.raw[index];
		}
	}

static inline void math_uvec2_divide ( uvec2 *output, const uvec2 first, const uvec2 second )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		output->raw[index] = first.raw[index] / second.raw[index];
		}
	}

static inline float math_uvec2_length_squared ( const uvec2 input )
	{
	float result = 0;
	for ( unsigned index = 0; index < 2; ++index )
		result += input.raw[index] * input.raw[index];
	return result;
	}

static inline float math_uvec2_length ( const uvec2 input )
	{
	return sqrtf ( math_uvec2_length_squared ( input ) );
	}

static inline bool math_uvec2_is_zero ( const uvec2 input )
	{
	for ( unsigned index = 0; index < 2; ++index )
		if ( input.raw[index] != 0 )
			return false;
	return true;
	}

static inline void math_uvec2_set_to_zero ( uvec2 *output )
	{
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = 0;
	}

static inline float math_uvec2_dot_product ( const uvec2 first, const uvec2 second )
	{
	float result = 0;
	for ( unsigned index = 0; index < 2; ++index )
		result += first.raw[index] * second.raw[index];
	return result;
	}

static inline void math_uvec2_normalize ( uvec2 *output )
	{
	float length = math_uvec2_length ( *output );
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = ( unsigned ) ( ( float ) output->raw[index] / length );
	}

static inline void math_uvec2_normalize_to ( uvec2 *output, uvec2 input )
	{
	float length = math_uvec2_length ( input );
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = ( unsigned ) ( ( float ) input.raw[index] / length );
	}

static inline void math_uvec2_scale_inplace ( uvec2 *output, const float scale )
	{
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = ( unsigned ) ( ( float ) output->raw[index] * scale );
	}

static inline void math_uvec2_scale ( uvec2 *output, uvec2 input, const float scale )
	{
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = ( unsigned ) ( ( float ) input.raw[index] * scale );
	}
