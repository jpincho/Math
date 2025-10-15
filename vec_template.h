#pragma once
#include "types.h"
#include <stdbool.h>
#include <math.h>

inline void math_TYPENAME_set ( TYPENAME *output, const TYPE v1, const TYPE v2, const TYPE v3, const TYPE v4 )
	{
	output->raw[0] = v1;
	output->raw[1] = v2;
	output->raw[2] = v3;
	output->raw[3] = v4;
	}

inline void math_TYPENAME_copy ( TYPENAME *output, const TYPENAME input )
	{
	for ( unsigned index = 0; index < COMPONENT_COUNT; ++index )
		output->raw[index] = input.raw[index];
	}

inline bool math_TYPENAME_equals ( const TYPENAME first, const TYPENAME second )
	{
	for ( unsigned index = 0; index < COMPONENT_COUNT; ++index )
		{
		if ( first.raw[index] != second.raw[index] )
			return false;
		}
	return true;
	}

inline void math_TYPENAME_add ( TYPENAME *output, const TYPENAME first, const TYPENAME second )
	{
	for ( unsigned index = 0; index < COMPONENT_COUNT; ++index )
		{
		output->raw[index] = first.raw[index] + second.raw[index];
		}
	}

inline void math_TYPENAME_subtract ( TYPENAME *output, const TYPENAME first, const TYPENAME second )
	{
	for ( unsigned index = 0; index < COMPONENT_COUNT; ++index )
		{
		output->raw[index] = first.raw[index] - second.raw[index];
		}
	}

inline float math_TYPENAME_length_squared ( const TYPENAME input )
	{
	float result = 0;
	for ( unsigned index = 0; index < COMPONENT_COUNT; ++index )
		result += input.raw[index] * input.raw[index];
	return result;
	}

inline float math_TYPENAME_length ( const TYPENAME input )
	{
	return sqrtf ( math_TYPENAME_length_squared ( input ) );
	}

inline bool math_TYPENAME_is_zero ( const TYPENAME input )
	{
	for ( unsigned index = 0; index < COMPONENT_COUNT; ++index )
		if ( input.raw[index] != ZERO )
			return false;
	return true;
	}

inline void math_TYPENAME_set_to_zero ( TYPENAME *output )
	{
	for ( unsigned index = 0; index < COMPONENT_COUNT; ++index )
		output->raw[index] = ZERO;
	}

inline float math_TYPENAME_dot_product ( const TYPENAME first, const TYPENAME second )
	{
	float result = 0;
	for ( unsigned index = 0; index < COMPONENT_COUNT; ++index )
		result += first.raw[index] * second.raw[index];
	return result;
	}

inline void math_TYPENAME_cross_product ( TYPENAME *output, const TYPENAME first, const TYPENAME second )
	{
	output->raw[0] = first.raw[1] * second.raw[2] - first.raw[2] * second.raw[1];
	output->raw[1] = first.raw[2] * second.raw[0] - first.raw[0] * second.raw[2];
	output->raw[2] = first.raw[0] * second.raw[1] - first.raw[1] * second.raw[0];
	}

inline void math_TYPENAME_normalize ( TYPENAME *output )
	{
	float length = math_TYPENAME_length ( *output );
	for ( unsigned index = 0; index < COMPONENT_COUNT; ++index )
		output->raw[index] = (TYPE) ( (float) output->raw[index] / length );
	}

inline void math_TYPENAME_normalize_to ( TYPENAME *output, TYPENAME input )
	{
	float length = math_TYPENAME_length ( input );
	for ( unsigned index = 0; index < COMPONENT_COUNT; ++index )
		output->raw[index] = (TYPE) ( (float) input.raw[index] / length );
	}

inline void math_TYPENAME_scale ( TYPENAME *output, const float scale )
	{
	for ( unsigned index = 0; index < COMPONENT_COUNT; ++index )
		output->raw[index] = (TYPE) ( (float) output->raw[index] * scale );
	}

inline void math_TYPENAME_scale_to ( TYPENAME *output, TYPENAME input, const float scale )
	{
	for ( unsigned index = 0; index < COMPONENT_COUNT; ++index )
		output->raw[index] = (TYPE) ( (float) input.raw[index] * scale );
	}
