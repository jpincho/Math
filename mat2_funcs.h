#pragma once
#include "types.h"
#include <stdio.h>
#include <stdarg.h>

inline void math_mat2_dump ( const mat2 matrix )
    {
    for ( unsigned index = 0; index < 2 * 2; ++index )
        {
        printf ( "%f ", matrix.raw[index] );
        if ( ( index + 1 ) % 2 == 0 )
            printf ( "\n" );
        }
    }

inline bool math_mat2_equals ( const mat2 first, const mat2 second )
    {
    for ( unsigned index = 0; index < 2 * 2; ++index )
        {
        if ( first.raw[index] != second.raw[index] )
            return false;
        }
    return true;
    }

inline void math_mat2_copy ( mat2 *output, const mat2 input )
    {
    for ( unsigned column = 0; column < 2; ++column )
        {
        math_vec2_copy ( &output->vectors[column], input.vectors[column] );
        }
    }

inline void math_mat2_transpose_to ( mat2 *output, const mat2 input )
    {
    for ( unsigned iterator1 = 0; iterator1 < 2; ++iterator1 )
        {
        for ( unsigned iterator2 = 0; iterator2 < 2; ++iterator2 )
            {
            output->vectors[iterator1].raw[iterator2] = input.vectors[iterator2].raw[iterator1];
            }
        }
    }

inline void math_mat2_set_zero ( mat2 *output )
    {
    for ( unsigned index = 0; index < 16; ++index )
        {
        output->raw[index] = 0.0f;
        }
    }

inline void math_mat2_set_identity_matrix ( mat2 *output )
    {
    output->raw[0] = 1.0f;
    output->raw[1] = 0.0f;
    output->raw[2] = 0.0f;
    output->raw[3] = 1.0f;
    }
