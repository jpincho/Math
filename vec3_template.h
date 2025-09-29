#pragma once
#include <stdbool.h>
#include <math.h>

typedef struct
	{
	union
		{
		struct
			{
			TYPE x, y, z;
			};
		TYPE raw[3];
		};
	}TYPENAME;

inline void math_TYPENAME_copy ( const TYPENAME input, TYPENAME *output )
	{
	for ( unsigned index = 0; index < 3; ++index )
		output->raw[index] = input.raw[index];
	}

inline bool math_TYPENAME_equals ( const TYPENAME first, const TYPENAME second )
	{
	for ( unsigned index = 0; index < 3; ++index )
		{
		if ( first.raw[index] != second.raw[index] )
			return false;
		}
	return true;
	}

inline void math_TYPENAME_add ( const TYPENAME first, const TYPENAME second, TYPENAME *output )
	{
	for ( unsigned index = 0; index < 3; ++index )
		{
		output->raw[index]=first.raw[index]+second.raw[index];
		}
	}

inline void math_TYPENAME_subtract ( const TYPENAME first, const TYPENAME second, TYPENAME *output )
	{
	for ( unsigned index = 0; index < 3; ++index )
		{
		output->raw[index] = first.raw[index] - second.raw[index];
		}
	}

inline float math_TYPENAME_length_squared ( const TYPENAME input )
	{
	float result = 0;
	for ( unsigned index = 0; index < 3; ++index )
		result += input.raw[index] * input.raw[index];
	return result;
	}

inline float math_TYPENAME_length ( const TYPENAME input )
	{
	return sqrtf ( math_TYPENAME_length_squared ( input ) );
	}

inline void math_TYPENAME_set_to_zero ( TYPENAME *output )
	{
	for ( unsigned index = 0; index < 3; ++index )
		output->raw[index] = ZERO;
	}

inline float math_TYPENAME_dot_product ( const TYPENAME first, const TYPENAME second )
	{
	float result = 0;
	for ( unsigned index = 0; index < 3; ++index )
		result += first.raw[index] * second.raw[index];
	return result;
	}

inline void math_TYPENAME_cross_product ( const TYPENAME first, const TYPENAME second, TYPENAME *output )
	{
	output->raw[0] = first.raw[1] * second.raw[2] - first.raw[2] * second.raw[1];
	output->raw[1] = first.raw[2] * second.raw[0] - first.raw[0] * second.raw[2];
	output->raw[2] = first.raw[0] * second.raw[1] - first.raw[1] * second.raw[0];
	}

inline void math_TYPENAME_normalize ( TYPENAME *output )
	{
	float length = math_TYPENAME_length ( *output );
	for ( unsigned index = 0; index < 3; ++index )
		output->raw[index] /= length;
	}
