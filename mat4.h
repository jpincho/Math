#pragma once
#include <Platform/Platform.h>
#include "vec4.h"
#include <stdint.h>

typedef struct
	{
	union
		{
		vec4 vectors[4];
		float raw[4 * 4];
		};
	}mat4;

#if defined (PLATFORM_SSE2_AVAILABLE)
#include "mat4_funcs_sse2.h"
#endif

#include "mat4_funcs.h"
