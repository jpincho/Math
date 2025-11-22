#pragma once
typedef struct
	{
	union
		{
		struct
			{
			int x, y;
			};
		int raw[2];
		};
	} ivec2;

typedef struct
	{
	union
		{
		struct
			{
			unsigned x, y;
			};
		unsigned raw[2];
		};
	} uvec2;

typedef struct
	{
	union
		{
		struct
			{
			float x, y;
			};
		float raw[2];
		};
	} vec2;

typedef struct
	{
	union
		{
		struct
			{
			int x, y, z;
			};
		int raw[3];
		};
	} ivec3;

typedef struct
	{
	union
		{
		struct
			{
			unsigned x, y, z;
			};
		unsigned raw[3];
		};
	} uvec3;

typedef struct
	{
	union
		{
		struct
			{
			float x, y, z;
			};
		float raw[3];
		};
	} vec3;

typedef struct
	{
	union
		{
		struct
			{
			int x, y, z, w;
			};
		int raw[4];
		};
	} ivec4;

typedef struct
	{
	union
		{
		struct
			{
			unsigned x, y, z, w;
			};
		unsigned raw[4];
		};
	} uvec4;

typedef struct
	{
	union
		{
		struct
			{
			float x, y, z, w;
			};
		float raw[4];
		};
	} vec4;

typedef vec4 quat;

typedef struct
	{
	union
		{
		vec2 vectors[2];
		float raw[2 * 2];
		};
	} mat2;

typedef struct
	{
	union
		{
		vec3 vectors[3];
		float raw[3 * 3];
		};
	} mat3;

typedef struct
	{
	union
		{
		vec4 vectors[4];
		float raw[4 * 4];
		};
	} mat4;
