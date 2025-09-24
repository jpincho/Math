#pragma once
#include <stdbool.h>
typedef struct
	{
	union
		{
		float x, y, z, w;
		float raw[4];
		};
	}quat;

inline void math_quat_copy ( const quat origin, quat destination )
	{
	destination.x = origin.x;
	destination.y = origin.y;
	destination.z = origin.z;
	destination.w = origin.w;
	}

inline bool math_quat_equals ( const quat first, const quat second )
	{
	return ( ( first.x == second.x ) && ( first.y == second.y ) && ( first.z == second.z ) && ( first.w == second.w ) );
	}

