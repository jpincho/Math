#pragma once
#include "types.h"
#include <stdbool.h>
#include <math.h>

static inline void math_ivec4_set ( ivec4 *output, const int v1, const int v2, const int v3, const int v4 )
	{
	output->raw[0] = v1;
	output->raw[1] = v2;
	output->raw[2] = v3;
	output->raw[3] = v4;
	}

static inline void math_ivec4_copy ( ivec4 *output, const ivec4 input )
	{
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = input.raw[index];
	}

static inline bool math_ivec4_equals ( const ivec4 first, const ivec4 second )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		if ( first.raw[index] != second.raw[index] )
			return false;
		}
	return true;
	}

static inline void math_ivec4_add ( ivec4 *output, const ivec4 first, const ivec4 second )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		output->raw[index] = first.raw[index] + second.raw[index];
		}
	}

static inline void math_ivec4_subtract ( ivec4 *output, const ivec4 first, const ivec4 second )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		output->raw[index] = first.raw[index] - second.raw[index];
		}
	}

static inline void math_ivec4_multiply ( ivec4 *output, const ivec4 first, const ivec4 second )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		output->raw[index] = first.raw[index] * second.raw[index];
		}
	}

static inline void math_ivec4_divide ( ivec4 *output, const ivec4 first, const ivec4 second )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		output->raw[index] = first.raw[index] / second.raw[index];
		}
	}

static inline float math_ivec4_length_squared ( const ivec4 input )
	{
	float result = 0;
	for ( unsigned index = 0; index < 4; ++index )
		result += input.raw[index] * input.raw[index];
	return result;
	}

static inline float math_ivec4_length ( const ivec4 input )
	{
	return sqrtf ( math_ivec4_length_squared ( input ) );
	}

static inline bool math_ivec4_is_zero ( const ivec4 input )
	{
	for ( unsigned index = 0; index < 4; ++index )
		if ( input.raw[index] != 0 )
			return false;
	return true;
	}

static inline void math_ivec4_set_to_zero ( ivec4 *output )
	{
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = 0;
	}

static inline float math_ivec4_dot_product ( const ivec4 first, const ivec4 second )
	{
	float result = 0;
	for ( unsigned index = 0; index < 4; ++index )
		result += first.raw[index] * second.raw[index];
	return result;
	}

static inline void math_ivec4_normalize ( ivec4 *output )
	{
	float length = math_ivec4_length ( *output );
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = ( int ) ( ( float ) output->raw[index] / length );
	}

static inline void math_ivec4_normalize_to ( ivec4 *output, ivec4 input )
	{
	float length = math_ivec4_length ( input );
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = ( int ) ( ( float ) input.raw[index] / length );
	}

static inline void math_ivec4_scale_inplace ( ivec4 *output, const float scale )
	{
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = ( int ) ( ( float ) output->raw[index] * scale );
	}

static inline void math_ivec4_scale ( ivec4 *output, ivec4 input, const float scale )
	{
	for ( unsigned index = 0; index < 4; ++index )
		output->raw[index] = ( int ) ( ( float ) input.raw[index] * scale );
	}
