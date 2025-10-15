#pragma once
#include "types.h"

inline float math_quat_length ( const quat input )
	{
	float result = 0;
	for ( unsigned index = 0; index < 4; ++index )
		result += input.raw[index] * input.raw[index];
	return sqrtf ( result );
	}

inline void math_quat_to_mat3 ( mat3 *output, const quat input )
	{
	float w, x, y, z,
		xx, yy, zz,
		xy, yz, xz,
		wx, wy, wz, norm, s;

	norm = math_vec4_length ( input );
	s = norm > 0.0f ? 2.0f / norm : 0.0f;

	x = input.raw[0];
	y = input.raw[1];
	z = input.raw[2];
	w = input.raw[3];

	xx = s * x * x;   xy = s * x * y;   wx = s * w * x;
	yy = s * y * y;   yz = s * y * z;   wy = s * w * y;
	zz = s * z * z;   xz = s * x * z;   wz = s * w * z;

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
	float w, x, y, z,
		xx, yy, zz,
		xy, yz, xz,
		wx, wy, wz, norm, s;

	norm = math_quat_length ( input );
	s = norm > 0.0f ? 2.0f / norm : 0.0f;

	x = input.raw[0];
	y = input.raw[1];
	z = input.raw[2];
	w = input.raw[3];

	xx = s * x * x;   xy = s * x * y;   wx = s * w * x;
	yy = s * y * y;   yz = s * y * z;   wy = s * w * y;
	zz = s * z * z;   xz = s * x * z;   wz = s * w * z;

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

	xs = sinf ( input.raw[0] * 0.5f ); xc = cosf ( input.raw[0] * 0.5f );
	ys = sinf ( input.raw[1] * 0.5f ); yc = cosf ( input.raw[1] * 0.5f );
	zs = sinf ( input.raw[2] * 0.5f ); zc = cosf ( input.raw[2] * 0.5f );

	output->raw[0] = xc * ys * zs + xs * yc * zc;
	output->raw[1] = xc * ys * zc - xs * yc * zs;
	output->raw[2] = xc * yc * zs + xs * ys * zc;
	output->raw[3] = xc * yc * zc - xs * ys * zs;
	}
