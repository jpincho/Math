#pragma once
#include <stdbool.h>

#define DECLARE_VECTOR(TYPE,NAME) \
typedef struct\
	{\
	union\
		{\
		struct\
			{\
			TYPE x, y, z, w;\
			};\
		TYPE raw[4];\
		};\
	}NAME;\
\
inline void math_##NAME##_copy ( const NAME origin, NAME *destination )\
	{\
	destination->x = origin.x; \
	destination->y = origin.y; \
	destination->z = origin.z; \
	destination->w = origin.w; \
	}\
\
inline bool math_##NAME##_equals ( const NAME first, const NAME second )\
	{\
	return ( ( first.x == second.x ) && ( first.y == second.y ) && ( first.z == second.z ) && ( first.w == second.w ) ); \
	}

DECLARE_VECTOR ( int, ivec4 );
DECLARE_VECTOR ( float, vec4 );
DECLARE_VECTOR ( unsigned, uvec4 );

#undef DECLARE_VECTOR

#define MATH_VEC4_ZERO_INIT {0.0f, 0.0f, 0.0f, 0.0f}
#define MATH_VEC4_ZERO ((vec4)MATH_VEC4_ZERO_INIT)
#define MATH_IVEC4_ZERO_INIT {0, 0, 0, 0}
#define MATH_IVEC4_ZERO ((ivec4)MATH_IVEC4_ZERO_INIT)
#define MATH_UVEC4_ZERO_INIT {0u, 0u, 0u, 0u}
#define MATH_UVEC4_ZERO ((uvec4)MATH_UVEC4_ZERO_INIT)
