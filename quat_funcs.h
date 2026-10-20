#pragma once
#include "types.h"
#include "vec4_funcs.h"
#include <math.h>

static inline void math_quat_set_identity ( quat *output )
	{
	output->x = output->y = output->z = 0.0f;
	output->w = 1.0f;
	}

static inline bool math_quat_equals ( const quat first, const quat second )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		if ( first.raw[index] != second.raw[index] )
			return false;
		}
	return true;
	}

static inline void math_quat_copy ( quat *output, const quat input )
	{
	for ( unsigned index = 0; index < 4; ++index )
		{
		output->raw[index] = input.raw[index];
		}
	}

static inline float math_quat_length ( const quat input )
	{
	float result = 0;
	for ( unsigned index = 0; index < 4; ++index )
		result += input.raw[index] * input.raw[index];
	return sqrtf ( result );
	}

static inline void math_quat_normalize ( quat *output )
	{
	float dot = math_vec4_length_squared ( *output );

	if ( dot <= 0.0f )
		{
		math_quat_set_identity ( output );
		return;
		}

	math_vec4_scale ( output, *output, 1.0f / sqrtf ( dot ) );
	}

static inline void math_quat_multiply_by_quat ( quat *output, const quat input1, const quat input2 )
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

static inline void math_quat_to_mat3 ( mat3 *output, const quat input )
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

static inline void math_mat3_to_quat ( quat *output, const mat3 input )
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

static inline void math_quat_to_mat4 ( mat4 *output, const quat input )
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

	output->vectors[3].raw[0] = output->vectors[3].raw[1] = output->vectors[3].raw[2] = 0.0f;
	output->vectors[0].raw[3] = output->vectors[1].raw[3] = output->vectors[2].raw[3] = 0.0f;
	output->vectors[3].raw[3] = 1.0f;
	}

static inline void math_quat_to_mat4_transposed ( mat4 *output, const quat input )
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

static inline void math_mat4_to_quat ( quat *output, const mat4 input )
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

static inline void math_quat_from_euler ( quat *output, const vec3 input )
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

static inline void math_quat_from_axis_angle ( quat *output, const vec3 axis, float angle )
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

static inline void math_quat_look ( mat4 *output, const vec3 eye_position, const quat orientation )
	{
	math_quat_to_mat4_transposed ( output, orientation );

	vec4 temp_eye;
	math_vec4_from_vec3 ( &temp_eye, eye_position );
	temp_eye.w = 1.0f;
	math_vec4_multiply_by_mat4 ( &temp_eye, *output, temp_eye );
	for ( unsigned index = 0; index < 4; ++index )
		output->vectors[3].raw[index] = -output->vectors[3].raw[index];
	}

static inline void math_quat_conjugate ( quat *output, const quat input )
	{
	output->x = -input.x;
	output->y = -input.y;
	output->z = -input.z;
	output->w = input.w;
	}

static inline void math_quat_slerp ( quat *output, const quat initial, const quat final, const float factor )
	{
	quat normalized_from = initial;
	quat normalized_to = final;
	math_quat_normalize ( &normalized_from );
	math_quat_normalize ( &normalized_to );

	float dot = ( normalized_from.x * normalized_to.x ) +
	            ( normalized_from.y * normalized_to.y ) +
	            ( normalized_from.z * normalized_to.z ) +
	            ( normalized_from.w * normalized_to.w );
	if ( dot < 0.0f )
		{
		math_vec4_scale ( &normalized_to, normalized_to, -1.0f );
		dot = -dot;
		}
	dot = fminf ( dot, 1.0f );

	// check if the two quaternions are nearly identical. If so, interpolate linearly, instead of spherically
	if ( dot > 0.9995f )
		{
		output->x = normalized_from.x + ( ( normalized_to.x - normalized_from.x ) * factor );
		output->y = normalized_from.y + ( ( normalized_to.y - normalized_from.y ) * factor );
		output->z = normalized_from.z + ( ( normalized_to.z - normalized_from.z ) * factor );
		output->w = normalized_from.w + ( ( normalized_to.w - normalized_from.w ) * factor );
		math_quat_normalize ( output );
		}

	const float theta = acosf ( dot );
	const float sin_theta = sinf ( theta );
	const float from_weight = sinf ( ( 1.0f - factor ) * theta ) / sin_theta;
	const float to_weight = sinf ( factor * theta ) / sin_theta;
	output->x = ( normalized_from.x * from_weight ) + ( normalized_to.x * to_weight );
	output->y = ( normalized_from.y * from_weight ) + ( normalized_to.y * to_weight );
	output->z = ( normalized_from.z * from_weight ) + ( normalized_to.z * to_weight );
	output->w = ( normalized_from.w * from_weight ) + ( normalized_to.w * to_weight );
	math_quat_normalize ( output );
	}