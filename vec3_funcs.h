#pragma once
#include "types.h"
#include <stdbool.h>
#include <math.h>

inline void math_vec3_set ( vec3 *output, const float v1, const float v2, const float v3 )
    {
    output->raw[0] = v1;
    output->raw[1] = v2;
    output->raw[2] = v3;
    }

inline void math_vec3_copy ( vec3 *output, const vec3 input )
    {
    for ( unsigned index = 0; index < 3; ++index )
        output->raw[index] = input.raw[index];
    }

inline bool math_vec3_equals ( const vec3 first, const vec3 second )
    {
    for ( unsigned index = 0; index < 3; ++index )
        {
        if ( first.raw[index] != second.raw[index] )
            return false;
        }
    return true;
    }

inline void math_vec3_add ( vec3 *output, const vec3 first, const vec3 second )
    {
    for ( unsigned index = 0; index < 3; ++index )
        {
        output->raw[index] = first.raw[index] + second.raw[index];
        }
    }

inline void math_vec3_subtract ( vec3 *output, const vec3 first, const vec3 second )
    {
    for ( unsigned index = 0; index < 3; ++index )
        {
        output->raw[index] = first.raw[index] - second.raw[index];
        }
    }

inline float math_vec3_length_squared ( const vec3 input )
    {
    float result = 0;
    for ( unsigned index = 0; index < 3; ++index )
        result += input.raw[index] * input.raw[index];
    return result;
    }

inline float math_vec3_length ( const vec3 input )
    {
    return sqrtf ( math_vec3_length_squared ( input ) );
    }

inline bool math_vec3_is_zero ( const vec3 input )
    {
    for ( unsigned index = 0; index < 3; ++index )
        if ( input.raw[index] != 0.0f )
            return false;
    return true;
    }

inline void math_vec3_set_to_zero ( vec3 *output )
    {
    for ( unsigned index = 0; index < 3; ++index )
        output->raw[index] = 0.0f;
    }

inline float math_vec3_dot_product ( const vec3 first, const vec3 second )
    {
    float result = 0;
    for ( unsigned index = 0; index < 3; ++index )
        result += first.raw[index] * second.raw[index];
    return result;
    }

inline void math_vec3_cross_product ( vec3 *output, const vec3 first, const vec3 second )
    {
    output->raw[0] = first.raw[1] * second.raw[2] - first.raw[2] * second.raw[1];
    output->raw[1] = first.raw[2] * second.raw[0] - first.raw[0] * second.raw[2];
    output->raw[2] = first.raw[0] * second.raw[1] - first.raw[1] * second.raw[0];
    }

inline void math_vec3_normalize ( vec3 *output )
    {
    float length = math_vec3_length ( *output );
    for ( unsigned index = 0; index < 3; ++index )
        output->raw[index] = (float) ( (float) output->raw[index] / length );
    }

inline void math_vec3_normalize_to ( vec3 *output, vec3 input )
    {
    float length = math_vec3_length ( input );
    for ( unsigned index = 0; index < 3; ++index )
        output->raw[index] = (float) ( (float) input.raw[index] / length );
    }

inline void math_vec3_scale ( vec3 *output, const float scale )
    {
    for ( unsigned index = 0; index < 3; ++index )
        output->raw[index] = (float) ( (float) output->raw[index] * scale );
    }

inline void math_vec3_scale_to ( vec3 *output, vec3 input, const float scale )
    {
    for ( unsigned index = 0; index < 3; ++index )
        output->raw[index] = (float) ( (float) input.raw[index] * scale );
    }
