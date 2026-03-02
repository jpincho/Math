#pragma once
#include "types.h"
#include <stdbool.h>
#include <math.h>

static inline void math_ivec2_set ( ivec2 *output, const int v1, const int v2 )
	{
	output->raw[0] = v1;
	output->raw[1] = v2;
	}

static inline void math_ivec2_copy ( ivec2 *output, const ivec2 input )
	{
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = input.raw[index];
	}

static inline bool math_ivec2_equals ( const ivec2 first, const ivec2 second )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		if ( first.raw[index] != second.raw[index] )
			return false;
		}
	return true;
	}

static inline void math_ivec2_add ( ivec2 *output, const ivec2 first, const ivec2 second )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		output->raw[index] = first.raw[index] + second.raw[index];
		}
	}

static inline void math_ivec2_subtract ( ivec2 *output, const ivec2 first, const ivec2 second )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		output->raw[index] = first.raw[index] - second.raw[index];
		}
	}

static inline void math_ivec2_multiply ( ivec2 *output, const ivec2 first, const ivec2 second )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		output->raw[index] = first.raw[index] * second.raw[index];
		}
	}

static inline void math_ivec2_divide ( ivec2 *output, const ivec2 first, const ivec2 second )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		output->raw[index] = first.raw[index] / second.raw[index];
		}
	}

static inline float math_ivec2_length_squared ( const ivec2 input )
	{
	float result = 0;
	for ( unsigned index = 0; index < 2; ++index )
		result += input.raw[index] * input.raw[index];
	return result;
	}

static inline float math_ivec2_length ( const ivec2 input )
	{
	return sqrtf ( math_ivec2_length_squared ( input ) );
	}

static inline bool math_ivec2_is_zero ( const ivec2 input )
	{
	for ( unsigned index = 0; index < 2; ++index )
		if ( input.raw[index] != 0 )
			return false;
	return true;
	}

static inline void math_ivec2_set_to_zero ( ivec2 *output )
	{
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = 0;
	}

static inline float math_ivec2_dot_product ( const ivec2 first, const ivec2 second )
	{
	float result = 0;
	for ( unsigned index = 0; index < 2; ++index )
		result += first.raw[index] * second.raw[index];
	return result;
	}

static inline void math_ivec2_normalize ( ivec2 *output )
	{
	float length = math_ivec2_length ( *output );
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = ( int ) ( ( float ) output->raw[index] / length );
	}

static inline void math_ivec2_normalize_to ( ivec2 *output, ivec2 input )
	{
	float length = math_ivec2_length ( input );
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = ( int ) ( ( float ) input.raw[index] / length );
	}

static inline void math_ivec2_scale_inplace ( ivec2 *output, const float scale )
	{
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = ( int ) ( ( float ) output->raw[index] * scale );
	}

static inline void math_ivec2_scale ( ivec2 *output, ivec2 input, const float scale )
	{
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = ( int ) ( ( float ) input.raw[index] * scale );
	}
