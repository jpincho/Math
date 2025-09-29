#pragma once
#include <stdbool.h>
#include <math.h>

typedef struct
	{
	union
		{
		struct
			{
			int x, y;
			};
		int raw[2];
		};
	}ivec2;

inline void math_ivec2_copy ( const ivec2 input, ivec2 *output )
	{
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = input.raw[index];
	}

inline bool math_ivec2_equals ( const ivec2 first, const ivec2 second )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		if ( first.raw[index] != second.raw[index] )
			return false;
		}
	return true;
	}

inline void math_ivec2_add ( const ivec2 first, const ivec2 second, ivec2 *output )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		output->raw[index] = first.raw[index] + second.raw[index];
		}
	}

inline void math_ivec2_subtract ( const ivec2 first, const ivec2 second, ivec2 *output )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		output->raw[index] = first.raw[index] - second.raw[index];
		}
	}
inline float math_ivec2_length_squared ( const ivec2 input )
	{
	float result = 0;
	for ( unsigned index = 0; index < 2; ++index )
		result += input.raw[index] * input.raw[index];
	return result;
	}

inline float math_ivec2_length ( const ivec2 input )
	{
	return sqrtf ( math_ivec2_length_squared ( input ) );
	}

inline void math_ivec2_set_to_zero ( ivec2 *output )
	{
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = 0;
	}

inline float math_ivec2_dot_product ( const ivec2 first, const ivec2 second )
	{
	float result = 0;
	for ( unsigned index = 0; index < 2; ++index )
		result += first.raw[index] * second.raw[index];
	return result;
	}
