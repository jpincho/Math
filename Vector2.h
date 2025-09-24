#pragma once
#include <stdbool.h>

#define DECLARE_VECTOR(TYPE,TYPENAME) \
typedef struct\
	{\
	union\
		{\
		struct\
			{\
			TYPE x, y; \
			};\
		TYPE raw[2];\
		};\
	}TYPENAME;\
\
inline void math_##TYPENAME##_copy ( const TYPENAME origin, TYPENAME *destination )\
	{\
	destination->x = origin.x; \
	destination->y = origin.y; \
	}\
	\
	inline bool math_##TYPENAME##_equals ( const TYPENAME first, const TYPENAME second )\
	{\
	return ( ( first.x == second.x ) && ( first.y == second.y ) ); \
	}
DECLARE_VECTOR ( int, ivec2 )
DECLARE_VECTOR ( float, vec2 )
DECLARE_VECTOR ( unsigned, uvec2 )

#undef DECLARE_VECTOR

//#define TYPENAME ivec2
//#define TYPE int
//#include "Vector2FunctionTemplates.h"

#define MATH_VEC2_ZERO_INIT {0.0f, 0.0f}
#define MATH_VEC2_ZERO ((vec2)MATH_VEC2_ZERO_INIT)
#define MATH_IVEC2_ZERO_INIT {0, 0}
#define MATH_IVEC2_ZERO ((ivec2)MATH_IVEC2_ZERO_INIT)
#define MATH_UVEC2_ZERO_INIT {0u, 0u}
#define MATH_UVEC2_ZERO ((uvec2)MATH_UVEC2_ZERO_INIT)
