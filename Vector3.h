#pragma once
#include <stdbool.h>

#define DECLARE_VECTOR(TYPE,NAME) \
typedef struct\
	{\
	union\
		{\
		struct\
			{\
			TYPE x, y, z;\
			};\
		TYPE raw[3];\
		};\
	}NAME;\
\
inline void math_##NAME##_copy ( const NAME origin, NAME *destination )\
	{\
	destination->x = origin.x; \
	destination->y = origin.y; \
	destination->z = origin.z; \
	}\
\
inline bool math_##NAME##_equals ( const NAME first, const NAME second )\
	{\
	return ( ( first.x == second.x ) && ( first.y == second.y ) && ( first.z == second.z ) ); \
	}

DECLARE_VECTOR ( int, ivec3 )
DECLARE_VECTOR ( float, vec3 )
DECLARE_VECTOR ( unsigned, uvec3 )

#undef DECLARE_VECTOR

#define MATH_VEC3_ZERO_INIT {0.0f, 0.0f, 0.0f}
#define MATH_VEC3_ZERO ((vec3)MATH_VEC3_ZERO_INIT)
#define MATH_IVEC3_ZERO_INIT {0, 0, 0}
#define MATH_IVEC3_ZERO ((ivec3)MATH_IVEC3_ZERO_INIT)
#define MATH_UVEC3_ZERO_INIT {0u, 0u, 0u}
#define MATH_UVEC3_ZERO ((uvec3)MATH_UVEC3_ZERO_INIT)
