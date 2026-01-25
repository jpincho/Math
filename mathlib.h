#pragma once
#include "ivec2_funcs.h"
#include "uvec2_funcs.h"
#include "vec2_funcs.h"

#include "ivec3_funcs.h"
#include "uvec3_funcs.h"
#include "vec3_funcs.h"

#include "ivec4_funcs.h"
#include "uvec4_funcs.h"
#include "vec4_funcs.h"

#include "quat_funcs.h"

#include "mat2_funcs.h"
#include "mat3_funcs.h"
#include "mat4_funcs.h"

#include "constants.h"

inline vec3 math_multiply_vec3_by_vec3 ( const vec3 first, const vec3 second )
	{
	vec3 output;
	for ( unsigned index = 0; index < 3; ++index )
		{
		output.raw[index] = first.raw[index] * second.raw[index];
		}
	return output;
	}

inline vec3 math_multiply_vec3_by_scalar ( const vec3 vector, const float scalar )
	{
	vec3 output;
	for ( unsigned index = 0; index < 3; ++index )
		{
		output.raw[index] = vector.raw[index] * scalar;
		}
	return output;
	}

inline vec3 math_add_vec3_to_vec3 ( const vec3 first, const vec3 second )
	{
	vec3 output;
	for ( unsigned index = 0; index < 3; ++index )
		{
		output.raw[index] = first.raw[index] + second.raw[index];
		}
	return output;
	}

// Basically, rotate a vector by a quaternion
inline vec3 math_multiply_vec3_by_quat ( const vec3 vector_input, const quat quat_input )
	{
	// According to https://blog.molecular-matters.com/2013/05/24/a-faster-quaternion-vector-multiplication/
	// t = 2 * cross ( q.xyz, v )
	// v' = v + q.w * t + cross(q.xyz, t)

	vec3 quat_xyz = { quat_input.x, quat_input.y, quat_input.z };
	vec3 temp_vec3 = math_vec3_cross_product ( quat_xyz, vector_input );
	temp_vec3 = math_multiply_vec3_by_scalar ( temp_vec3, 2.0f );

	vec3 output = math_add_vec3_to_vec3 ( math_add_vec3_to_vec3 ( vector_input, math_multiply_vec3_by_scalar ( temp_vec3, quat_input.w ) ), math_vec3_cross_product ( quat_xyz, temp_vec3 ) );
	return output;
	}

inline quat math_multiply_quat_by_quat ( const quat input1, const quat input2 )
	{
	const float x1x2 = input1.x * input2.x;
	const float x1y2 = input1.x * input2.y;
	const float x1z2 = input1.x * input2.z;
	const float x1w2 = input1.x * input2.w;

	const float y1x2 = input1.y * input2.x;
	const float y1y2 = input1.y * input2.y;
	const float y1z2 = input1.y * input2.z;
	const float y1w2 = input1.y * input2.w;

	const float z1x2 = input1.z * input2.x;
	const float z1y2 = input1.z * input2.y;
	const float z1z2 = input1.z * input2.z;
	const float z1w2 = input1.z * input2.w;

	const float w1x2 = input1.w * input2.x;
	const float w1y2 = input1.w * input2.y;
	const float w1z2 = input1.w * input2.z;
	const float w1w2 = input1.w * input2.w;

	quat output;
	output.x = w1x2 + x1w2 + y1z2 - z1y2;
	output.y = w1y2 - x1z2 + y1w2 + z1x2;
	output.z = w1z2 + x1y2 - y1x2 + z1w2;
	output.w = w1w2 - x1x2 - y1y2 - z1z2;
	return output;
	}
