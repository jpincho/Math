#pragma once
#include "types.h"
#include <stdbool.h>
#include <math.h>

inline void math_vec2_set ( vec2 *output, const float v1, const float v2 )
    {
    output->raw[0] = v1;
    output->raw[1] = v2;
    }

inline void math_vec2_copy ( vec2 *output, const vec2 input )
    {
    for ( unsigned index = 0; index < 2; ++index )
        output->raw[index] = input.raw[index];
    }

inline bool math_vec2_equals ( const vec2 first, const vec2 second )
    {
    for ( unsigned index = 0; index < 2; ++index )
        {
        if ( first.raw[index] != second.raw[index] )
            return false;
        }
    return true;
    }

inline void math_vec2_add ( vec2 *output, const vec2 first, const vec2 second )
    {
    for ( unsigned index = 0; index < 2; ++index )
        {
        output->raw[index] = first.raw[index] + second.raw[index];
        }
    }

inline void math_vec2_subtract ( vec2 *output, const vec2 first, const vec2 second )
    {
    for ( unsigned index = 0; index < 2; ++index )
        {
        output->raw[index] = first.raw[index] - second.raw[index];
        }
    }

inline void math_vec2_multiply ( vec2 *output, const vec2 first, const vec2 second )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		output->raw[index] = first.raw[index] * second.raw[index];
		}
	}

inline void math_vec2_divide ( vec2 *output, const vec2 first, const vec2 second )
	{
	for ( unsigned index = 0; index < 2; ++index )
		{
		output->raw[index] = first.raw[index] / second.raw[index];
		}
	}

inline float math_vec2_length_squared ( const vec2 input )
    {
    float result = 0;
    for ( unsigned index = 0; index < 2; ++index )
        result += input.raw[index] * input.raw[index];
    return result;
    }

inline float math_vec2_length ( const vec2 input )
    {
    return sqrtf ( math_vec2_length_squared ( input ) );
    }

inline bool math_vec2_is_zero ( const vec2 input )
    {
    for ( unsigned index = 0; index < 2; ++index )
        if ( input.raw[index] != 0.0f )
            return false;
    return true;
    }

inline void math_vec2_set_to_zero ( vec2 *output )
    {
    for ( unsigned index = 0; index < 2; ++index )
        output->raw[index] = 0.0f;
    }

inline float math_vec2_dot_product ( const vec2 first, const vec2 second )
    {
    float result = 0;
    for ( unsigned index = 0; index < 2; ++index )
        result += first.raw[index] * second.raw[index];
    return result;
    }

inline void math_vec2_normalize ( vec2 *output )
    {
    float length = math_vec2_length ( *output );
    for ( unsigned index = 0; index < 2; ++index )
        output->raw[index] = (float) ( (float) output->raw[index] / length );
    }

inline void math_vec2_normalize_to ( vec2 *output, vec2 input )
    {
    float length = math_vec2_length ( input );
    for ( unsigned index = 0; index < 2; ++index )
        output->raw[index] = (float) ( (float) input.raw[index] / length );
    }

inline void math_vec2_scale_inplace ( vec2 *output, const float scale )
	{
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = (float) ( (float) output->raw[index] * scale );
	}

inline void math_vec2_scale ( vec2 *output, vec2 input, const float scale )
	{
	for ( unsigned index = 0; index < 2; ++index )
		output->raw[index] = (float) ( (float) input.raw[index] * scale );
	}
