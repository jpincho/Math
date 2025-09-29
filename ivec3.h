#pragma once
#include <stdbool.h>
#include <math.h>

typedef struct
	{
	union
		{
		struct
			{
			int x, y, z;
			};
		int raw[3];
		};
	}ivec3;

inline void math_ivec3_copy ( const ivec3 input, ivec3 *output )
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

inline void math_ivec3_add ( const ivec3 first, const ivec3 second, ivec3 *output )
	{
	for ( unsigned index = 0; index < 3; ++index )
		{
		output->raw[index]=first.raw[index]+second.raw[index];
		}
	}

inline void math_ivec3_subtract ( const ivec3 first, const ivec3 second, ivec3 *output )
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

inline void math_ivec3_cross_product ( const ivec3 first, const ivec3 second, ivec3 *output )
	{
	output->raw[0] = first.raw[1] * second.raw[2] - first.raw[2] * second.raw[1];
	output->raw[1] = first.raw[2] * second.raw[0] - first.raw[0] * second.raw[2];
	output->raw[2] = first.raw[0] * second.raw[1] - first.raw[1] * second.raw[0];
	}
