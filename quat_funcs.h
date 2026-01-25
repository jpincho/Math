#pragma once
#include "types.h"
#include "vec4_funcs.h"
#include <math.h>

inline void math_quat_set_identity ( quat *output )
	{
	output->x = output->y = output->z = 0.0f;
	output->w = 1.0f;
	}

inline float math_quat_length ( const quat input )
	{
	float result = 0;
	for ( unsigned index = 0; index < 4; ++index )
		result += input.raw[index] * input.raw[index];
	return sqrtf ( result );
	}

inline void math_quat_normalize ( quat *output )
	{
	float dot = math_vec4_length_squared ( *output );

	if ( dot <= 0.0f )
		{
		math_quat_set_identity ( output );
		return;
		}

	math_vec4_scale ( output, *output, 1.0f / sqrtf ( dot ) );
	}

inline void math_quat_multiply_by_quat ( quat *output, const quat input1, const quat input2 )
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

	output->x = w1x2 + x1w2 + y1z2 - z1y2;
	output->y = w1y2 - x1z2 + y1w2 + z1x2;
	output->z = w1z2 + x1y2 - y1x2 + z1w2;
	output->w = w1w2 - x1x2 - y1y2 - z1z2;
	}

inline void math_quat_to_mat3 ( mat3 *output, const quat input )
	{
	float xx, yy, zz,
		xy, yz, xz,
		wx, wy, wz, norm, s;

	norm = math_vec4_length ( input );
	s = norm > 0.0f ? 2.0f / norm : 0.0f;

	xx = s * input.x * input.x;
	xy = s * input.x * input.y;
	wx = s * input.w * input.x;
	yy = s * input.y * input.y;
	yz = s * input.y * input.z;
	wy = s * input.w * input.y;
	zz = s * input.z * input.z;
	xz = s * input.x * input.z;
	wz = s * input.w * input.z;

	output->vectors[0].raw[0] = 1.0f - yy - zz;
	output->vectors[1].raw[1] = 1.0f - xx - zz;
	output->vectors[2].raw[2] = 1.0f - xx - yy;

	output->vectors[1].raw[0] = xy + wz;
	output->vectors[2].raw[1] = yz + wx;
	output->vectors[0].raw[2] = xz + wy;

	output->vectors[0].raw[1] = xy - wz;
	output->vectors[1].raw[2] = yz - wx;
	output->vectors[2].raw[0] = xz - wy;
	}

inline void math_mat3_to_quat ( quat *output, const mat3 input )
	{
	float trace, r, rinv;
	trace = input.vectors[0].raw[0] + input.vectors[1].raw[1] + input.vectors[2].raw[2];
	if ( trace >= 0.0f )
		{
		r = sqrtf ( 1.0f + trace );
		rinv = 0.5f / r;

		output->raw[0] = rinv * ( input.vectors[1].raw[2] - input.vectors[2].raw[1] );
		output->raw[1] = rinv * ( input.vectors[2].raw[0] - input.vectors[0].raw[2] );
		output->raw[2] = rinv * ( input.vectors[0].raw[1] - input.vectors[1].raw[0] );
		output->raw[3] = r * 0.5f;
		}
	else if ( input.vectors[0].raw[0] >= input.vectors[1].raw[1] && input.vectors[0].raw[0] >= input.vectors[2].raw[2] )
		{
		r = sqrtf ( 1.0f - input.vectors[1].raw[1] - input.vectors[2].raw[2] + input.vectors[0].raw[0] );
		rinv = 0.5f / r;

		output->raw[0] = r * 0.5f;
		output->raw[1] = rinv * ( input.vectors[0].raw[1] + input.vectors[1].raw[0] );
		output->raw[2] = rinv * ( input.vectors[0].raw[2] + input.vectors[2].raw[0] );
		output->raw[3] = rinv * ( input.vectors[1].raw[2] - input.vectors[2].raw[1] );
		}
	else if ( input.vectors[1].raw[1] >= input.vectors[2].raw[2] )
		{
		r = sqrtf ( 1.0f - input.vectors[0].raw[0] - input.vectors[2].raw[2] + input.vectors[1].raw[1] );
		rinv = 0.5f / r;

		output->raw[0] = rinv * ( input.vectors[0].raw[1] + input.vectors[1].raw[0] );
		output->raw[1] = r * 0.5f;
		output->raw[2] = rinv * ( input.vectors[1].raw[2] + input.vectors[2].raw[1] );
		output->raw[3] = rinv * ( input.vectors[2].raw[0] - input.vectors[0].raw[2] );
		}
	else
		{
		r = sqrtf ( 1.0f - input.vectors[0].raw[0] - input.vectors[1].raw[1] + input.vectors[2].raw[2] );
		rinv = 0.5f / r;

		output->raw[0] = rinv * ( input.vectors[0].raw[2] + input.vectors[2].raw[0] );
		output->raw[1] = rinv * ( input.vectors[1].raw[2] + input.vectors[2].raw[1] );
		output->raw[2] = r * 0.5f;
		output->raw[3] = rinv * ( input.vectors[0].raw[1] - input.vectors[1].raw[0] );
		}
	}

inline void math_quat_to_mat4 ( mat4 *output, const quat input )
	{
	float length = math_quat_length ( input );
	float sign = length > 0.0f ? 2.0f / length : 0.0f;

	float xx = sign * input.x * input.x;
	float xy = sign * input.x * input.y;
	float wx = sign * input.w * input.x;
	float yy = sign * input.y * input.y;
	float yz = sign * input.y * input.z;
	float wy = sign * input.w * input.y;
	float zz = sign * input.z * input.z;
	float xz = sign * input.x * input.z;
	float wz = sign * input.w * input.z;

	output->vectors[0].raw[0] = 1.0f - yy - zz;
	output->vectors[1].raw[1] = 1.0f - xx - zz;
	output->vectors[2].raw[2] = 1.0f - xx - yy;

	output->vectors[0].raw[2] = xz + wy;
	output->vectors[1].raw[0] = xy + wz;
	output->vectors[2].raw[1] = yz + wx;

	output->vectors[0].raw[1] = xy - wz;
	output->vectors[1].raw[2] = yz - wx;
	output->vectors[2].raw[0] = xz - wy;

	output->vectors[3].raw[0] = output->vectors[3].raw[1] = output->vectors[3].raw[2] = output->vectors[3].raw[3] = 0.0f;
	output->vectors[0].raw[3] = output->vectors[1].raw[3] = output->vectors[2].raw[3] = 0.0f;
	}

inline void math_quat_to_mat4_transposed ( mat4 *output, const quat input )
	{
	float length = math_quat_length ( input );
	float sign = length > 0.0f ? 2.0f / length : 0.0f;

	float xx = sign * input.x * input.x;
	float xy = sign * input.x * input.y;
	float wx = sign * input.w * input.x;
	float yy = sign * input.y * input.y;
	float yz = sign * input.y * input.z;
	float wy = sign * input.w * input.y;
	float zz = sign * input.z * input.z;
	float xz = sign * input.x * input.z;
	float wz = sign * input.w * input.z;

	output->vectors[0].raw[0] = 1.0f - yy - zz;
	output->vectors[1].raw[1] = 1.0f - xx - zz;
	output->vectors[2].raw[2] = 1.0f - xx - yy;

	output->vectors[1].raw[0] = xy + wz;
	output->vectors[2].raw[1] = yz + wx;
	output->vectors[0].raw[2] = xz + wy;

	output->vectors[0].raw[1] = xy - wz;
	output->vectors[1].raw[2] = yz - wx;
	output->vectors[2].raw[0] = xz - wy;

	output->vectors[0].raw[3] = 0.0f;
	output->vectors[1].raw[3] = 0.0f;
	output->vectors[2].raw[3] = 0.0f;
	output->vectors[3].raw[0] = 0.0f;
	output->vectors[3].raw[1] = 0.0f;
	output->vectors[3].raw[2] = 0.0f;
	output->vectors[3].raw[3] = 1.0f;
	}

inline void math_mat4_to_quat ( quat *output, const mat4 input )
	{
	float trace, r, rinv;
	trace = input.vectors[0].raw[0] + input.vectors[1].raw[1] + input.vectors[2].raw[2];
	if ( trace >= 0.0f )
		{
		r = sqrtf ( 1.0f + trace );
		rinv = 0.5f / r;

		output->raw[0] = rinv * ( input.vectors[1].raw[2] - input.vectors[2].raw[1] );
		output->raw[1] = rinv * ( input.vectors[2].raw[0] - input.vectors[0].raw[2] );
		output->raw[2] = rinv * ( input.vectors[0].raw[1] - input.vectors[1].raw[0] );
		output->raw[3] = r * 0.5f;
		}
	else if ( input.vectors[0].raw[0] >= input.vectors[1].raw[1] && input.vectors[0].raw[0] >= input.vectors[2].raw[2] )
		{
		r = sqrtf ( 1.0f - input.vectors[1].raw[1] - input.vectors[2].raw[2] + input.vectors[0].raw[0] );
		rinv = 0.5f / r;

		output->raw[0] = r * 0.5f;
		output->raw[1] = rinv * ( input.vectors[0].raw[1] + input.vectors[1].raw[0] );
		output->raw[2] = rinv * ( input.vectors[0].raw[2] + input.vectors[2].raw[0] );
		output->raw[3] = rinv * ( input.vectors[1].raw[2] - input.vectors[2].raw[1] );
		}
	else if ( input.vectors[1].raw[1] >= input.vectors[2].raw[2] )
		{
		r = sqrtf ( 1.0f - input.vectors[0].raw[0] - input.vectors[2].raw[2] + input.vectors[1].raw[1] );
		rinv = 0.5f / r;

		output->raw[0] = rinv * ( input.vectors[0].raw[1] + input.vectors[1].raw[0] );
		output->raw[1] = r * 0.5f;
		output->raw[2] = rinv * ( input.vectors[1].raw[2] + input.vectors[2].raw[1] );
		output->raw[3] = rinv * ( input.vectors[2].raw[0] - input.vectors[0].raw[2] );
		}
	else
		{
		r = sqrtf ( 1.0f - input.vectors[0].raw[0] - input.vectors[1].raw[1] + input.vectors[2].raw[2] );
		rinv = 0.5f / r;

		output->raw[0] = rinv * ( input.vectors[0].raw[2] + input.vectors[2].raw[0] );
		output->raw[1] = rinv * ( input.vectors[1].raw[2] + input.vectors[2].raw[1] );
		output->raw[2] = r * 0.5f;
		output->raw[3] = rinv * ( input.vectors[0].raw[1] - input.vectors[1].raw[0] );
		}
	}

inline void math_quat_from_euler ( quat *output, const vec3 input )
	{
	float xc, yc, zc, xs, ys, zs;

	xs = sinf ( input.raw[0] * 0.5f );
	xc = cosf ( input.raw[0] * 0.5f );
	ys = sinf ( input.raw[1] * 0.5f );
	yc = cosf ( input.raw[1] * 0.5f );
	zs = sinf ( input.raw[2] * 0.5f );
	zc = cosf ( input.raw[2] * 0.5f );

	output->raw[0] = xc * ys * zs + xs * yc * zc;
	output->raw[1] = xc * ys * zc - xs * yc * zs;
	output->raw[2] = xc * yc * zs + xs * ys * zc;
	output->raw[3] = xc * yc * zc - xs * ys * zs;
	}

inline void math_quat_from_axis_angle ( quat *output, const vec3 axis, float angle )
	{
	float half_angle = angle * 0.5f;
	float half_angle_cos = cosf ( half_angle );
	float half_angle_sin = sinf ( half_angle );
	vec3 normalized_axis;
	math_vec3_normalize_to ( &normalized_axis, axis );
	output->raw[0] = half_angle_sin * normalized_axis.raw[0];
	output->raw[1] = half_angle_sin * normalized_axis.raw[1];
	output->raw[2] = half_angle_sin * normalized_axis.raw[2];
	output->raw[3] = half_angle_cos;
	math_quat_normalize ( output );
	}

inline void math_quat_look ( mat4 *output, const vec3 eye_position, const quat orientation )
	{
	math_quat_to_mat4_transposed ( output, orientation );

	vec4 temp_eye;
	math_vec4_from_vec3 ( &temp_eye, eye_position );
	temp_eye.w = 1.0f;
	math_vec4_multiply_by_mat4 ( &temp_eye, *output, temp_eye );
	for ( unsigned index = 0; index < 4; ++index )
		output->vectors[3].raw[index] = -output->vectors[3].raw[index];
	}

inline void math_quat_conjugate ( quat *output, const quat input )
	{
	output->x = -input.x;
	output->y = -input.y;
	output->z = -input.z;
	output->w = input.w;
	}
